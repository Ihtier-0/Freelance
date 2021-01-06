#include "part.h"

#include <string>

std::ostream& operator<<(std::ostream& out, const partType& type)
{
	switch (type)
	{
	case partType::body:
	{
		out << "������";
		break;
	}
	case partType::bracket:
	{
		out << "���������";
		break;
	}
	case partType::cuff:
	{
		out << "�������";
		break;
	}
	case partType::flange:
	{
		out << "������";
		break;
	}
	case partType::nut:
	{
		out << "�����";
		break;
	}
	case partType::panel:
	{
		out << "������";
		break;
	}
	case partType::screw:
	{
		out << "����";
		break;
	}
	case partType::sleeve:
	{
		out << "������";
		break;
	}
	case partType::stock:
	{
		out << "����";
		break;
	}
	case partType::unknown:
	{
		out << "����������";
		break;
	}
	}

    return out;
}

std::istream& operator>>(std::istream& is, partType& type)
{
	std::string tmp;

	is >> tmp;

	if (tmp == "������")
	{
		type = partType::body;
	}
	else if (tmp == "���������")
	{
		type = partType::bracket;
	}
	else if (tmp == "�������")
	{
		type = partType::cuff;
	}
	else if (tmp == "������")
	{
		type = partType::flange;
	}
	else if (tmp == "�����")
	{
		type = partType::nut;
	}
	else if (tmp == "������")
	{
		type = partType::panel;
	}
	else if (tmp == "����")
	{
		type = partType::screw;
	}
	else if (tmp == "������")
	{
		type = partType::sleeve;
	}
	else if (tmp == "����")
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
