#include "api_auth.h"

using namespace api;

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
	LOG_DEBUG << "register";
	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(k200OK);
	callback(resp);
}
// Add definition of your processing function here
