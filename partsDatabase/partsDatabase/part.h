#pragma once

#include <iostream>

enum class partType
{
	body,   // ������
	bracket,// ���������
	cuff,   // �������
	flange, // ������
	nut,    // �����
	panel,  // ������
	screw,  // ����
	sleeve, // ������
	stock,  // ����
	unknown // ����������
};

std::ostream& operator<<(std::ostream& out, const partType& type);
std::istream& operator>>(std::istream& is, partType& type);

// ������
class part
{
public:
	part();
	partType get_type() const;
protected:
	partType m_type;

	friend std::ostream& operator<<(std::ostream& out, const part& Part);
};

