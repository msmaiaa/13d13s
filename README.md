# 13d13s - 13 days 13 servers
### Compiled:
- [X] kotlin - javalin (never used the lang before)
- [ ] clojure - ring (never used the lang before)
- [ ] c++ - drogon (have previous experience, never used the lib)
- [ ] haskell - yesod	(never used the lang before)
- [ ] elixir - phoenix (have previous experience but i suck)
- [ ] f# - dotnet (never used the lang before)
- [ ] ocaml - mirage (never used the lang before, but i have familiarity with the synthax)
- [ ] rust - poem (have previous experience)
- [ ] go - echo? (have previous experience)

### Interpreted:
- [ ] php - laravel (wrote hello world years ago)
- [ ] python - fastapi (have previous experience, never used the lib)
- [ ] nodejs - fastify (have previous experience, never used the lib)
- [ ] lua - lapis (have previous experience, never used the lib)

-----
#### The server must:
- Have the following routes  
	- /api/auth/register -> {username: string, password: string} -> 200 (409 if err)
	- /api/auth/login -> {username: string, password: string} -> { token: "string" } 200 (401 if err)
	- /api/protected -> Authorization header -> authorized ? {message: "you're in"} : {message: "you're in! just kidding, fuck you!"}
- Have cors enabled (all origins)
- Persist user data (using an orm if possible)
- Use environment variables for secrets
- httpit benchmark results (running release builds if compiled)
- Setup instructions and final considerations on readme

#### I cant:
- Use youtube (only documentation/articles allowed)
- Ask someone for help
