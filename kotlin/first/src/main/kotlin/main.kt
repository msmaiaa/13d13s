import io.javalin.Javalin

fun main() {
    val app = Javalin.create().start(1337)
    app.get("/") { ctx -> ctx.result("ola mundo") }
}