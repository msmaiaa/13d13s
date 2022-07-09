#pragma once

#include <drogon/HttpController.h>
#include "utils.h"

using namespace jwt_utils;
namespace api
{
	class _protected : public drogon::HttpController<_protected>
	{
	public:
		METHOD_LIST_BEGIN
		METHOD_ADD(_protected::protected_route, "/", Get);
		METHOD_LIST_END
		void protected_route(const HttpRequestPtr &req,
												 std::function<void(const HttpResponsePtr &)> &&callback);
	};
}
