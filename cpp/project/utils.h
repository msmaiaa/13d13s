#ifndef UTILS_H
#define UTILS_H

#include "plugins/JWTplugin.h"
#include <drogon/drogon.h>

#define JWT_SECRET "2123456789123456"
using namespace drogon;

namespace jwt_utils
{
	inline std::string jwt_encode(const std::string &username)
	{
		auto *jwtPointer = drogon::app().getPlugin<JWT>();
		auto jwtClass = jwtPointer->init(JWT_SECRET);
		std::map<std::string, std::string> payload;
		payload["username"] = username;
		return jwtClass.encode(payload);
	}

	inline jwt::jwt_object jwt_decode(const std::string &token)
	{
		auto *jwtPointer = drogon::app().getPlugin<JWT>();
		auto jwtClass = jwtPointer->init(JWT_SECRET);
		return jwtClass.decode(token);
	}
}
#endif