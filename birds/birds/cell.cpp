#include "cell.h"

#include "duck.h"
#include "nightingale.h"

void cell::add(bird *Bird)
{
	m_birdInCell.push_back(Bird);
}

void cell::remove(const bird *Bird)
{
	int size = m_birdInCell.size();

	for (int i = 0; i < size; ++i)
	{
		if (*Bird == *m_birdInCell[i])
		{
			m_birdInCell.erase(m_birdInCell.begin() + i);
			return;
		}
	}
}

int cell::size()
{
	return m_birdInCell.size();
}

bird* cell::operator[](const unsigned int& index)
{
	int size = m_birdInCell.size();

	return index > size ? nullptr : m_birdInCell[index];
}

std::ostream& operator<<(std::ostream& out, const cell& Cell)
{
	int size = Cell.m_birdInCell.size();

	for (int i = 0; i < size; ++i)
	{
		out << *Cell.m_birdInCell[i] << '\n';
	}

	return out;
}

std::istream& operator>>(std::istream& is, cell& Cell)
{
	std::string identifier;
	std::string sleep;
	std::string sing;

	bird* tmp = nullptr;

	while (!is.eof())
	{
		is >> identifier >> sleep >> sing;

		if (sing == "quack!quack!")
		{
			tmp = new duck(identifier, sleep == "sleep");
		}

		if (sing == "phew!phew!")
		{
			tmp = new nightingale(identifier, sleep == "sleep");
		}

		if (tmp)
		{
			Cell.add(tmp);
		}
	}

	return is;
}
