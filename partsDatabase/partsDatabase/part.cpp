#include "part.h"

#include <string>

std::ostream& operator<<(std::ostream& out, const partType& type)
{
	switch (type)
	{
	case partType::body:
	{
		out << "корпус";
		break;
	}
	case partType::bracket:
	{
		out << "кронштейн";
		break;
	}
	case partType::cuff:
	{
		out << "манжета";
		break;
	}
	case partType::flange:
	{
		out << "фланец";
		break;
	}
	case partType::nut:
	{
		out << "гайка";
		break;
	}
	case partType::panel:
	{
		out << "панель";
		break;
	}
	case partType::screw:
	{
		out << "винт";
		break;
	}
	case partType::sleeve:
	{
		out << "втулка";
		break;
	}
	case partType::stock:
	{
		out << "шток";
		break;
	}
	case partType::unknown:
	{
		out << "неизвестно";
		break;
	}
	}

    return out;
}

std::istream& operator>>(std::istream& is, partType& type)
{
	std::string tmp;

	is >> tmp;

	if (tmp == "корпус")
	{
		type = partType::body;
	}
	else if (tmp == "кронштейн")
	{
		type = partType::bracket;
	}
	else if (tmp == "манжета")
	{
		type = partType::cuff;
	}
	else if (tmp == "фланец")
	{
		type = partType::flange;
	}
	else if (tmp == "гайка")
	{
		type = partType::nut;
	}
	else if (tmp == "панель")
	{
		type = partType::panel;
	}
	else if (tmp == "винт")
	{
		type = partType::screw;
	}
	else if (tmp == "втулка")
	{
		type = partType::sleeve;
	}
	else if (tmp == "шток")
	{
		type = partType::stock;
	}
	else
	{
		type = partType::unknown;
	}

	return is;
}

std::ostream& operator<<(std::ostream& out, const part& Part)
{
	out << Part.m_type;
	return out;
}

part::part()
{
	this->m_type = partType::unknown;
}

partType part::get_type() const
{
	return m_type;
}
