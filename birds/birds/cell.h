#pragma once

#include <vector>

#include "bird.h"

// клетка с птицами
class cell
{
public:
	void add(bird *Bird);
	void remove(const bird *Bird);

	int size();

	bird* operator[](const unsigned int& index);
private:
	std::vector<bird *> m_birdInCell;

	friend std::ostream& operator<<(std::ostream& out, const cell& Cell);
	friend std::istream& operator>>(std::istream& is, cell& Cell);
};

