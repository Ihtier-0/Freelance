#pragma once

#include "part.h"

#include <vector>

// база данных деталей
class partsDatabase
{
public:
	unsigned int size();
	unsigned int countParts(const part& type);
	void addPart(const part& type);
	void removePart(const part& type);
private:
	std::vector<part> m_table;

	friend std::istream& operator>>(std::istream& is, partsDatabase &db);
};

