import com.fasterxml.jackson.annotation.JsonProperty
import com.fasterxml.jackson.core.JacksonException
import io.javalin.Javalin
import User
import io.github.cdimascio.dotenv.dotenv
import org.ktorm.database.Database
import org.ktorm.dsl.from
import org.ktorm.dsl.insert
import org.ktorm.dsl.select
import org.postgresql.util.PSQLException

class RegisterPayload(
    val username: String,
    val password: String
)

class LoginPayload(
    val username: String,
    val password: String)

fun main() {
    val app = Javalin.create().start(1337);
    val dotenv = dotenv();
    val database = Database.connect(dotenv["DATABASE_URL"], user = dotenv["DATABASE_USER"], password = dotenv["DATABASE_PASSWORD"]);

    app.post("/api/auth/register") { ctx ->
        run {
            val payload = ctx.bodyValidator<RegisterPayload>().get();

            try {
                database.insert(User) {
                    set(it.username, payload.username)
                    set(it.password, payload.password)
                }
                ctx.status(201)
            } catch(e: PSQLException) {
                ctx.status(400).result("User already exists")
            }
        }
    }
    app.post("/api/auth/login", { ctx ->
        ctx.result("/api/auth/login").status(200)
    })
    app.get("/api/protected", { ctx ->
        ctx.result("protected").status(201)
    })
}