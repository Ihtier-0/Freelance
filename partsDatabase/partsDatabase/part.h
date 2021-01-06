#pragma once

#include <iostream>

enum class partType
{
	body,   // корпус
	bracket,// кронштейн
	cuff,   // манжета
	flange, // фланец
	nut,    // гайка
	panel,  // панель
	screw,  // винт
	sleeve, // втулка
	stock,  // шток
	unknown // неизвестно
};

std::ostream& operator<<(std::ostream& out, const partType& type);
std::istream& operator>>(std::istream& is, partType& type);

// деталь
class part
{
public:
	part();
	partType get_type() const;
protected:
	partType m_type;

	friend std::ostream& operator<<(std::ostream& out, const part& Part);
};

