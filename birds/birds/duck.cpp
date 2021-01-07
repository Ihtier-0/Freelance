#include "duck.h"

duck::duck(const std::string& identifier, const bool& sleep) : bird(identifier, sleep) {}

std::string duck::sing() const
{
	return "quack!quack!";
}
