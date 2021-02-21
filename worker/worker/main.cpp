#include <string>
#include <iostream>
#include <Windows.h>

class worker
{
public:
	worker(const std::string &a_surname, 
		const unsigned int &a_experience,
		const double &a_hourly_wages,
		const unsigned int &a_number_of_hours_worked)
		: m_surname(a_surname),
		m_experience(a_experience),
		m_hourly_wages(a_hourly_wages),
		m_number_of_hours_worked(a_number_of_hours_worked) {}

	worker()
		: m_surname(),
		m_experience(0),
		m_hourly_wages(0),
		m_number_of_hours_worked(0) {}

	std::string surname()
	{
		return m_surname;
	}

	void setSurname(const std::string& a_surname)
	{
		m_surname = a_surname;
	}

	unsigned int experience()
	{
		return m_experience;
	}

	void setExperience(const unsigned int& a_experience)
	{
		m_experience = a_experience;
	}

	double hourly_wages()
	{
		return m_hourly_wages;
	}

	void setHourly_wages(const double& a_hourly_wages)
	{
		m_hourly_wages = a_hourly_wages;
	}

	unsigned int number_of_hours_worked()
	{
		return m_number_of_hours_worked;
	}

	void setHourly_wages(const unsigned int& a_number_of_hours_worked)
	{
		m_number_of_hours_worked = a_number_of_hours_worked;
	}

	// �� �� ������������ ����� 
	double wagesForHoursWorked()
	{
		return m_hourly_wages * m_number_of_hours_worked;
	}

	// ������
	double prize()
	{
		double wages = wagesForHoursWorked();

		if (m_experience <= 1)
		{
			wages *= 0;
		}
		else if (m_experience <= 3)
		{
			wages *= 0.05;
		}
		else if (m_experience <= 5)
		{
			wages *= 0.08;
		}
		else if (m_experience > 5)
		{
			wages *= 0.15;
		}
		else
		{
			wages *= 0;
		}

		return wages;
	}

	void inputFromKeyboard()
	{
		std::cout << "������� �������: ";
		std::cin >> m_surname;

		std::cout << "������� ����: ";
		std::cin >> m_experience;

		std::cout << "������� ������� ���������� �����: ";
		std::cin >> m_hourly_wages;

		std::cout << "������� ���������� ������������ �����: ";
		std::cin >> m_number_of_hours_worked;
	}

	void printOnScreen()
	{
		std::cout << "�������: " << m_surname << '\n';
		std::cout << "����: " << m_experience << '\n';
		std::cout << "������� ���������� �����: " << m_hourly_wages << '\n';
		std::cout << "���������� ������������ �����: " << m_number_of_hours_worked << '\n';
	}

private:
	std::string m_surname; // �������
	unsigned int m_experience; // ����
	double m_hourly_wages; // ������� ���������� �����
	unsigned int m_number_of_hours_worked; // ���������� ������������ �����

	friend std::istream& operator>>(std::istream& is, worker& w)
	{
		is >> w.m_surname >> w.m_experience >> w.m_hourly_wages >> w.m_number_of_hours_worked;

		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, const worker& w)
	{
		os << w.m_surname << ' ' << w.m_experience << ' ' << w.m_hourly_wages << ' ' << w.m_number_of_hours_worked;

		return os;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	worker w;

	w.inputFromKeyboard();
	std::cout << '\n';
	w.printOnScreen();
	std::cout << "\n���������� ����� �� �� �����: " << w.wagesForHoursWorked() << "\n������: " << w.prize();
}