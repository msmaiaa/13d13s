#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api
{
	class _protected : public drogon::HttpController<_protected>
	{
	public:
		METHOD_LIST_BEGIN
		METHOD_ADD(_protected::route, "/", Get);
		METHOD_LIST_END
		void route(const HttpRequestPtr &req,
							 std::function<void(const HttpResponsePtr &)> &&callback);
	};
}
