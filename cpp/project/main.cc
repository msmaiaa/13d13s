#include <drogon/drogon.h>

int main()
{
	// Set HTTP listener address and port
	drogon::app().addListener("0.0.0.0", 1337);
	// Load config file
	// drogon::app().loadConfigFile("../config.json");
	// Run HTTP framework,the method will block in the internal event loop
	drogon::app().createDbClient("postgresql", "127.0.0.1", 5434, "cool_database", "postgres", "postgres");
	drogon::app()
			.run();
	return 0;
}
