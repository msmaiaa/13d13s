#include "api_protected.h"

using namespace api;

void _protected::protected_route(const HttpRequestPtr &req,
																 std::function<void(const HttpResponsePtr &)> &&callback)
{
	auto header = req->getHeader("Authorization");
	if (header.empty())
	{
		auto resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k401Unauthorized);
		callback(resp);
	}
	auto token = header.substr(7);

	Json::Value response_body;
	try
	{
		auto decoded = jwt_utils::jwt_decode(token);
		auto has_username = decoded.payload().has_claim("username");
		response_body["message"] = "You're in!";
		auto resp = HttpResponse::newHttpJsonResponse(response_body);
		resp->setStatusCode(k200OK);
		callback(resp);
	}
	catch (const std::exception &e)
	{
		response_body["message"] = "You're in! Just kidding, fuck you!";
		auto resp = HttpResponse::newHttpJsonResponse(response_body);
		resp->setStatusCode(k401Unauthorized);
		callback(resp);
	}
}