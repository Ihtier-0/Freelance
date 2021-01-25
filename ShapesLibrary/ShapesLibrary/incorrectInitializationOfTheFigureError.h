#pragma once

#include <string>
#include <exception>

class incorrectInitializationOfTheFigureError : public std::exception
{
private:
	std::string m_error;
public:
	incorrectInitializationOfTheFigureError(const std::string& a_error) : m_error(a_error) {}
	const char* what() const noexcept { return m_error.c_str(); }
};
