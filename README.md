This is a challenge where i create the same api with different languages, so i can rank them (subjectively) in terms of difficulty, usefulness and fun factor. I will try to finish in one sitting as fast as possible. If the language is too exotic i won't time it.  

- :red_circle: - No previous experience
- :white_circle: - Some previous experience, not related to web server/api stuff
- :large_blue_circle: - Have previous experience directly related to web server/api stuff

| Language | Framework | Experience | Time to beat(h:m) | Done |
| -------- | ------- | ----- | ----------- | -- |
| kotlin  | javalin | :red_circle: | ~5:00 | ✔️ |
| clojure  | ring | :red_circle: | | :x: | 
| haskell  | yesod |	:red_circle: | | :x: |
| f#  |  dotnet |:red_circle: | | :x: |
| ocaml  | mirage | :red_circle: | | :x: |
| zig  | zhp | :red_circle: | | :x: |
| vlang  | vweb | :red_circle: | | :x: |
| c#  | dotnet? | :red_circle: | | :x: |
| swift | Swifter | :red_circle: | | :x: |
| scala | akka-http | :red_circle: | | :x: |
| perl | Perldancer | :red_circle: | | :x: |
| java  | Spring | :red_circle: | | :x: |
| crystal  | router.cr | :red_circle: | | :x: |
| odin  | odinhttp | :red_circle: | | :x: |
| racket  | (builtin) | :red_circle: | | :x: |
| dart  | aqueduct | :red_circle: | | :x: |
| julia  | HTTP.jl | :red_circle: | | :x: |
| jolie  | (builtin) | :red_circle: | | :x: |
| imba  | express (js interop) | :red_circle: | | :x: |
| jython  | ? | :red_circle: | | :x: |
| vale  | ? | :red_circle: | | :x: |
| nim  | whip? | :red_circle: | | :x: |
| php  | laravel | :red_circle: | | :x: |
| ruby  | on rails |:red_circle: | | :x: |
| c++ | drogon | :white_circle: | ~7:00 | ✔️ | 
| elixir  | phoenix | :white_circle: | | :x: |
| python  | fastapi |:white_circle: | | :x: |
| lua  | lapis |:white_circle: | | :x: |
| rust  | poem | :large_blue_circle: | | :x: |
| go  | echo |:large_blue_circle: | | :x: |
| nodejs  | express |:large_blue_circle: | | :x: |

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
