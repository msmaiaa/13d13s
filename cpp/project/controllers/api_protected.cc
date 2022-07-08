#include "api_protected.h"

using namespace api;

void _protected::route(const HttpRequestPtr &req,
											 std::function<void(const HttpResponsePtr &)> &&callback)
{
	Json::Value response;
	response["message"] = "you're in!";
	auto resp = HttpResponse::newHttpJsonResponse(response);
	callback(resp);
}