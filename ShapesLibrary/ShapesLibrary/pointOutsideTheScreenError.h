#pragma once

#include <string>
#include <exception>

class pointOutsideTheScreenError : public std::exception
{
private:
	std::string m_error;
public:
	pointOutsideTheScreenError(const std::string& a_error) : m_error(a_error) {}
	const char* what() const noexcept { return m_error.c_str(); }
};
