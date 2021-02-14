#pragma once

#include <vector>
#include <ostream>

template<class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T>& v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i)
	{
		out << v[i] << ' ';
	}

	return out;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i)
	{
		out << v[i] << '\n';
	}

	return out;
}