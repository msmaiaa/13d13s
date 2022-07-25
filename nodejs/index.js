const express = require('express');
const app = express();
const jwt = require("jsonwebtoken")
const dotenv = require("dotenv")
const knex = require("knex")
const bcrypt = require("bcrypt")

const JWT_SECRET = 'ijoi3j5ioej9fj3902902j9dfkls,aok094'
const UNAUTHORIZED_JSON = { message: "you're in! just kidding, fuck you"};

const protectedMiddleware = (req, res, next) => {
	let rawToken = req.headers["authorization"];
	if(!rawToken) return res.status(401).json(UNAUTHORIZED_JSON)
	let token = rawToken.split("Bearer ")[1]
	jwt.verify(token, JWT_SECRET, (err, decoded) => {
		if(err) return res.status(401).json(UNAUTHORIZED_JSON)
	}) 
	next();
}

app.use(express.json())

app.post("/api/auth/register", async (req, res) => {
	if(!req.body || !req.body.username || !req.body.password) return res.status(400).json({ message: "username and password required" })
	try {
		let user = await global.pg("users").where("username", req.body.username).first()
		if(user) return res.status(400).json({ message: "username already exists" })
		let hashed_password = hash(req.body.password)
		await global.pg("users").insert({ username: req.body.username, password: hashed_password })
		return res.status(200).json({ message: "ok"});
	} catch(e) {
		return res.status(500).json({ message: "error registering user" })
	}
})

const hash = (string) => {
	let salt = bcrypt.genSaltSync(10);
	return bcrypt.hashSync(string, salt)
}

const sign_token = (data) => {
	return jwt.sign(data, JWT_SECRET)
}

app.post("/api/auth/login", async (req, res) => {
	if(!req.body || !req.body.username || !req.body.password) return res.status(400).json({ message: "username and password required" })
	const { username, password } = req.body;
	const found_user = await global.pg("users").where({ username }).first();
	let is_valid = bcrypt.compareSync(password, found_user.password);
	if(!found_user || !is_valid) return res.status(401).json({ message: "??" })
	let token = sign_token(found_user.id);
	return res.status(200).json({
		token
	});
})

app.get("/api/protected", protectedMiddleware, (req,res) => {
	return res.status(200).json({
		message: "you're in"
	});
})

app.listen(1337, () => {
	dotenv.config();
	const pg = knex({
		client: 'pg',
		connection: process.env.DATABASE_URL,
		searchPath: ['knex', 'public'],
	});
	global.pg = pg;
	
	console.log("server listening at http://localhost:1337");
})