#pragma once

#include <string>

class stackException
{
public:
	stackException(std::string error)
		: m_error(error) {}

	inline const char* what() const noexcept { return m_error.c_str(); }
private:
	std::string m_error;
};