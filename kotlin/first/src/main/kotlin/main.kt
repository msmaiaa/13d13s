import io.github.cdimascio.dotenv.dotenv
import io.javalin.Javalin
import org.jose4j.jwa.AlgorithmConstraints
import org.jose4j.jwa.AlgorithmConstraints.ConstraintType
import org.jose4j.jwe.ContentEncryptionAlgorithmIdentifiers
import org.jose4j.jwe.JsonWebEncryption
import org.jose4j.jwe.KeyManagementAlgorithmIdentifiers
import org.jose4j.keys.AesKey
import org.jose4j.lang.ByteUtil
import org.jose4j.lang.JoseException
import org.ktorm.database.Database
import org.ktorm.dsl.*
import org.postgresql.util.PSQLException
import java.security.Key


class RegisterPayload(
    val username: String,
    val password: String
)

class LoginPayload(
    val username: String,
    val password: String
)

class LoginResponse(
    val username: String,
    val token: String
)

class UserData(val username: String, val password: String, val id: Int) {}
class ProtectedResponse(val message: String) {}

fun encodeJwt(payload: String, secret: String): String {
    val key: Key = AesKey(ByteUtil.concat(secret.toByteArray()))
    val jwe = JsonWebEncryption()
    jwe.payload = payload;
    jwe.algorithmHeaderValue = KeyManagementAlgorithmIdentifiers.A128KW
    jwe.encryptionMethodHeaderParameter = ContentEncryptionAlgorithmIdentifiers.AES_128_CBC_HMAC_SHA_256
    jwe.key = key
    return jwe.compactSerialization
}

fun decodeJWT(jwt: String, secret: String): String? {

    val jwe = JsonWebEncryption()
    jwe.setAlgorithmConstraints(
        AlgorithmConstraints(
            ConstraintType.PERMIT,
            KeyManagementAlgorithmIdentifiers.A128KW
        )
    )
    jwe.setContentEncryptionAlgorithmConstraints(
        AlgorithmConstraints(
            ConstraintType.PERMIT,
            ContentEncryptionAlgorithmIdentifiers.AES_128_CBC_HMAC_SHA_256
        )
    )
    jwe.setKey(AesKey(ByteUtil.concat(secret.toByteArray())))
    jwe.setCompactSerialization(jwt)
    return jwe.getPayload()
}

fun main() {
    val app = Javalin.create().start(1337);
    val dotenv = dotenv();
    val database = Database.connect(
        dotenv["DATABASE_URL"],
        user = dotenv["DATABASE_USER"],
        password = dotenv["DATABASE_PASSWORD"]
    );

    app.post("/api/auth/register") { ctx ->
        run {
            val payload = ctx.bodyValidator<RegisterPayload>().get();
            try {
                database.insert(User) {
                    set(it.username, payload.username)
                    set(it.password, payload.password)
                }
                ctx.status(201)
            } catch (e: PSQLException) {
                ctx.status(400).result("User already exists")
            }
        }
    }
    app.post("/api/auth/login", { ctx ->
        run {
            val payload = ctx.bodyValidator<LoginPayload>().get();
            val users = database
                .from(User)
                .select()
                .where { (User.username eq payload.username) and (User.password eq payload.password) }
                .map { row ->
                    row[User.id]?.let {
                        UserData(
                            username = row[User.username].toString(),
                            password = row[User.password].toString(),
                            id = it.toInt()
                        )
                    }
                };
            if (users.isEmpty()) {
                ctx.status(403);
            } else {
                val jwt = encodeJwt(users[0]!!.username, dotenv["JWT_SECRET"])
                ctx.json(LoginResponse(users[0]!!.username, jwt)).status(200)
            }
        }
    })
    app.get("/api/protected", { ctx ->
        run {
            if (ctx.header("Authorization") != null) {
                try {
                    val decoded = decodeJWT(ctx.header("Authorization")!!.replace("Bearer ", ""), dotenv["JWT_SECRET"]);

                    ctx.status(200).json(ProtectedResponse("hello, " + decoded.toString()))
                } catch (e: JoseException) {
                    ctx.status(401).json(ProtectedResponse("you're in! Just kidding, fuck you"))
                }
            } else {
                ctx.status(401).json(ProtectedResponse("you're in! Just kidding, fuck you"))
            }
        }
    })
}