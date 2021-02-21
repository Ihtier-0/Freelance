#include <iostream>
#include <string.h> 
#include <windows.h>

using namespace std;


char* encrypt(char* str,
	unsigned int* rowRule,
	const unsigned int& rowSize,
	unsigned int* colRule,
	const unsigned int& colSize,
	const char& fillChar = '?');
char* decipher(char* str,
	unsigned int* rowRule,
	const unsigned int& rowSize,
	unsigned int* colRule,
	const unsigned int& colSize,
	const char& fillChar = '?');

void rangeError(int& value, const int& leftBorder, const int& rightBorder);


void inputArray(unsigned int* Array, const unsigned int& length, const unsigned int& maxNumber);


void menu()
{
	cout << "1) ����������� ���������;" << endl
		<< "2) ������������ ���������;" << endl
		<< "3) �����." << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	int command = 0;

	do
	{
		menu();

		cout << "> ";
		cin >> command;

		rangeError(command, 1, 3);

		switch (command)
		{
		case 1: // 1) ����������� ���������;
		{
			cout << "������� ��������, ������� ����� �����������: ";
			char* str = new char[256];
			cin.get();

			cin.getline(str, 256);

			unsigned int strLen = strlen(str);
			double sqrtStrLen = sqrt(strLen);

			unsigned int row = (int)sqrtStrLen, col = (int)sqrtStrLen;

			while (row * col < strLen)
			{
				++row;
			}

			unsigned int* rowRule = new unsigned int[row],
				* colRule = new unsigned int[col];

			cout << "������� ������� ��� ����� (" << row << " ������������� ����(�)\n"
				<< "�� ������� " << row << ", ���������� ���������� � 0):\n";
			inputArray(rowRule, row, row);

			cout << "������� ������� ��� �������� (" << col << " ������������� ����(�)\n"
				<< "�� ������� " << col << ", ���������� ���������� � 0):\n";
			inputArray(colRule, col, col);

			cout << "������������� ��������:\n"
				<< encrypt(str, rowRule, row, colRule, col)
				<< '\n';

			break;
		}
		case 2:
		{
			cout << "������� ������������� ��������: ";
			char* str = new char[256];
			cin.get();

			cin.getline(str, 256);

			unsigned int row, col;

			cout << "������� ���������� ����� � �������� ������� ����������: ";
			cin >> row >> col;

			unsigned int strSize = strlen(str);

			while (row * col != strSize)
			{
				cout << "���������� ��������� � ������� � ����� �������� �� ���������" << endl
					<< "���������� ��� ���!" << endl;

				cout << "������� ���������� ����� � �������� ������� ����������: ";
				cin >> row >> col;
			}

			unsigned int* rowRule = new unsigned int[row],
				* colRule = new unsigned int[col];

			cout << "������� ������� ��� ����� (" << row << " ������������� ����(�)\n"
				<< "�� ������� " << row << ", ���������� ���������� � 0):\n";
			inputArray(rowRule, row, row);

			cout << "������� ������� ��� �������� (" << col << " ������������� ����(�)\n"
				<< "�� ������� " << col << ", ���������� ���������� � 0):\n";
			inputArray(colRule, col, col);

			cout << "�������������� ��������:\n"
				<< decipher(str, rowRule, row, colRule, col)
				<< '\n';

			break;
		}
		}

	} while (command != 3);
}

void inputArray(unsigned int* Array, const unsigned int& length, const unsigned int& maxNumber)
{
	for (int i = 0; i < length; ++i)
	{
		cin >> Array[i];

		if (Array[i] >= maxNumber)
		{
			cout << "������� ������� ��������. ���������� ��� ���!\n";
			--i;
		}


		for (unsigned int j = 0; j < i; ++j)
		{
			if (Array[i] == Array[j])
			{
				cout << "����������� ������. ������� ���� � ������!\n";
				i = -1;
				break;
			}
		}
	}
}

void rangeError(int& value, const int& leftBorder, const int& rightBorder)
{
	while (value < leftBorder || rightBorder < value)
	{
		cout << "���������� ��� ���: ";
		cin >> value;
	}
}

char* encrypt(char* str, unsigned int* rowRule, const unsigned int& rowSize,
	unsigned int* colRule, const unsigned int& colSize, const char& fillChar)
{
	char** encryptionMatrix = new char* [rowSize];

	for (unsigned int i = 0; i < rowSize; ++i)
	{
		encryptionMatrix[i] = new char[colSize];
	}

	unsigned int strSize = strlen(str);

	unsigned int strIndex = 0;

	for (unsigned int i = 0; i < rowSize; ++i)
	{
		for (unsigned int j = 0; j < colSize; ++j)
		{
			if (strIndex < strSize)
			{
				encryptionMatrix[rowRule[i]][j] = str[strIndex];
			}
			else
			{
				encryptionMatrix[rowRule[i]][j] = fillChar;
			}
			++strIndex;
		}
	}

	unsigned int encryptStrSize = rowSize * colSize;
	char* encryptStr = new char[encryptStrSize + 1];
	unsigned int encryptStrIndex = 0;


	for (unsigned int i = 0; i < colSize; ++i)
	{
		for (unsigned int j = 0; j < rowSize; ++j)
		{
			encryptStr[encryptStrIndex] = encryptionMatrix[j][colRule[i]];
			++encryptStrIndex;
		}
	}


	encryptStr[encryptStrSize] = '\0';


	for (unsigned int i = 0; i < rowSize; ++i)
	{
		delete[] encryptionMatrix[i];
	}

	delete[] encryptionMatrix;


	return encryptStr;
}

char* decipher(char* str, unsigned int* rowRule, const unsigned int& rowSize,
	unsigned int* colRule, const unsigned int& colSize, const char& fillChar)
{

	char** encryptionMatrix = new char* [rowSize];

	for (unsigned int i = 0; i < rowSize; ++i)
	{
		encryptionMatrix[i] = new char[colSize];
	}

	unsigned int strSize = strlen(str);

	unsigned int strIndex = 0;

	for (unsigned int i = 0; i < colSize; ++i)
	{
		for (unsigned int j = 0; j < rowSize; ++j)
		{
			encryptionMatrix[j][colRule[i]] = str[strIndex];
			++strIndex;
		}
	}

	unsigned int decipherStrSize = rowSize * colSize;
	char* decipherStr = new char[decipherStrSize + 1];
	unsigned int decipherStrIndex = 0;

	for (unsigned int i = 0; i < rowSize; ++i)
	{
		for (unsigned int j = 0; j < colSize; ++j)
		{
			decipherStr[decipherStrIndex] = encryptionMatrix[rowRule[i]][j];
			++decipherStrIndex;
		}
	}

	decipherStr[decipherStrSize] = '\0';

	decipherStrIndex = decipherStrSize - 1;


	while (decipherStr[decipherStrIndex] == fillChar)
	{
		decipherStr[decipherStrIndex] = '\0';
		--decipherStrIndex;
	}


	for (unsigned int i = 0; i < rowSize; ++i)
	{
		delete[] encryptionMatrix[i];
	}

	delete[] encryptionMatrix;


	return decipherStr;
}
