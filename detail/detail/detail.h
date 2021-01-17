#pragma once

// ������
class detail
{
public:
	// ������������
	detail();
	detail(const long long& stockNumber,
		const char* name,
		const long long& value,
		const char* measure);
	detail(const detail& e);

	// ����������
	virtual ~detail() = 0;

	// ����� �����
	char* Name();

	// ����� ���������
	long long Value();

protected:
	// �������������� �������
	long long stockNumber;
	// ��������
	char* name;
	// �������� 
	long long value;
	// ������� ���������
	char* measure;
};

