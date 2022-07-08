#include "api_auth.h"

using namespace api;
struct RegisterPayload
{
	std::string username;
	std::string password;
};

Json::Value response_message(const std::string &message)
{
	Json::Value response;
	response["message"] = message;
	return response;
}

void auth::login(const HttpRequestPtr &req,
								 std::function<void(const HttpResponsePtr &)> &&callback)
{
	Json::Value response;
	response["username"] = "username";
	response["token"] = "token";
	auto resp = HttpResponse::newHttpJsonResponse(response);
	callback(resp);
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

	RegisterPayload payload;
	payload.username = (*body)["username"].asString();
	payload.password = (*body)["password"].asString();

	if (!payload.username.size() || !payload.password.size())
	{
		auto resp = HttpResponse::newHttpJsonResponse(response_message("Invalid body"));
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
		auto resp = HttpResponse::newHttpJsonResponse(response_message("User already exists"));
		resp->setStatusCode(k400BadRequest);
		callback(resp);
	}
}
