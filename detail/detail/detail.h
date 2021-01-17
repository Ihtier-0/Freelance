#pragma once

// деталь
class detail
{
public:
	// конструкторы
	detail();
	detail(const long long& stockNumber,
		const char* name,
		const long long& value,
		const char* measure);
	detail(const detail& e);

	// деструктор
	virtual ~detail() = 0;

	// гетер имени
	char* Name();

	// гетер знаечения
	long long Value();

protected:
	// номенклатурным номером
	long long stockNumber;
	// название
	char* name;
	// значение 
	long long value;
	// единица измерения
	char* measure;
};

