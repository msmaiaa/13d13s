#include "api_auth.h"
#include "plugins/JWTplugin.h"

using namespace api;
struct RegisterOrLoginPayload
{
	std::string username;
	std::string password;
};

Json::Value create_response_json(const std::string &message)
{
	Json::Value response;
	response["message"] = message;
	return response;
}

std::string jwt_encode(const std::string &username)
{
	auto *jwtPointer = drogon::app().getPlugin<JWT>();
	auto jwtClass = jwtPointer->init("1234567891234567");
	std::map<std::string, std::string> payload;
	payload["username"] = username;
	return jwtClass.encode(payload);
}

bool is_valid_payload(const RegisterOrLoginPayload &payload)
{
	return !payload.username.empty() && !payload.password.empty();
}

void auth::login(const HttpRequestPtr &req,
								 std::function<void(const HttpResponsePtr &)> &&callback)
{
	auto body = req->getJsonObject();
	if (!body)
	{
		auto resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k400BadRequest);
		callback(resp);
	}

	RegisterOrLoginPayload payload;
	payload.username = (*body)["username"].asString();
	payload.password = (*body)["password"].asString();

	if (!is_valid_payload(payload))
	{
		auto resp = HttpResponse::newHttpJsonResponse(create_response_json("Invalid body"));
		resp->setStatusCode(k400BadRequest);
		callback(resp);
	}

	auto client = drogon::app().getDbClient();
	auto f = client->execSqlAsyncFuture("SELECT * FROM users WHERE username=$1 AND password=$2", payload.username, payload.password);
	try
	{
		auto result = f.get();
		if (result.empty())
		{
			auto resp = HttpResponse::newHttpJsonResponse(create_response_json("Invalid username or password"));
			resp->setStatusCode(k400BadRequest);
			callback(resp);
		}
		auto jwt = jwt_encode(payload.username);
		Json::Value response_body;
		response_body["token"] = jwt;
		auto resp = HttpResponse::newHttpJsonResponse(response_body);
		resp->setStatusCode(k200OK);
		callback(resp);
	}
	catch (const drogon::orm::DrogonDbException &e)
	{
		auto resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k500InternalServerError);
		callback(resp);
	}
}

void auth::_register(const HttpRequestPtr &req,
										 std::function<void(const HttpResponsePtr &)> &&callback)
{
	auto body = req->getJsonObject();
	if (!body)
	{
		auto resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k400BadRequest);
		callback(resp);
	}

	RegisterOrLoginPayload payload;
	payload.username = (*body)["username"].asString();
	payload.password = (*body)["password"].asString();

	if (!is_valid_payload(payload))
	{
		auto resp = HttpResponse::newHttpJsonResponse(create_response_json("Invalid body"));
		resp->setStatusCode(k400BadRequest);
		callback(resp);
	}

	auto client = drogon::app().getDbClient();
	auto f = client->execSqlAsyncFuture("INSERT INTO users (username, password) VALUES ($1, $2)", payload.username, payload.password);
	try
	{
		f.get();
		auto resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k201Created);
		callback(resp);
	}
	catch (const drogon::orm::DrogonDbException &e)
	{
		// if (e.base().what() == "duplicate key value violates unique constraint \"users_username_key\"")
		// {
		// 	error handling for duplicate username
		// }
		auto resp = HttpResponse::newHttpJsonResponse(create_response_json("User already exists"));
		resp->setStatusCode(k400BadRequest);
		callback(resp);
	}
}
