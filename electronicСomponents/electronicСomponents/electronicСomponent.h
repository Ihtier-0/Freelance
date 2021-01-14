#pragma once

#include <string>

class electronic�omponent
{
public:
	electronic�omponent();
	electronic�omponent(const long long& a_stockNumber,
		const std::string& name,
		const long long& value,
		const std::string& unit);
	electronic�omponent(const electronic�omponent& e);
	virtual ~electronic�omponent() = 0;

	std::string get_name();

	long long get_value();

protected:
	// �������������� �������
	long long stockNumber;
	// ��������
	std::string name;
	// �������� 
	long long value;
	// ������� ���������
	std::string unit;
};

