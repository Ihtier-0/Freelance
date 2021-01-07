#pragma once

#include <iostream>
#include <string>

// ������� ����� �����
class bird
{
public:
	// ����������� ������� ��������� ������������� � ��������� ���� ����� ��� ���
	bird(const std::string& identifier,
		const bool& sleep);
	// ����������� �����������
	bird(const bird& Bird);
	// �������� ������������
	bird& operator=(const bird& Bird);
	// "�����", ����� ���� ���-�� �������� � ����������� ������
	virtual std::string sing() const = 0;
protected:
	// ������������� (� ���� ������������ ������ ��������)
	std::string m_identifier;
	// ���� ��� ��������� ����� ��� �������� ��������� (�������� ��������) �������
	bool m_sleep;
	// ������� �����:
	// �������� ������ 
	friend std::ostream& operator<<(std::ostream& out, const bird& Bird);
	// �������� �����
	friend std::istream& operator>>(std::istream& is, bird& Bird);
	// �������� ���������
	friend bool operator==(const bird& bird1, const bird& bird2);
};

