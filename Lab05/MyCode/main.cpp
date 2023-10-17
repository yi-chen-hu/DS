#include <iostream>
#include <fstream>
#include "Integer.h"

using namespace std;


void readFile(const char* fileName);


int main()
{
	readFile("input3.txt");
	return 0;
}

void readFile(const char* fileName) {
	ifstream inputFile(fileName);


	char line[3];
	inputFile.getline(line, sizeof(line), '\n');
	int lines = atoi(line);

	for (size_t i = 0; i < lines; i++)
	{
		char str[50];
		string a_str, b_str;
		static int j = 0;
		while (j == i)
		{
			inputFile.getline(str, sizeof(str));
			j++;
		}
		char sign, oper;
		int flag;
		if (str[0] == '-')
		{
			sign = '-';
			flag = 1;
		}
		else
		{
			sign = ' ';
			flag = 0;
		}

		int k = 0;
		while (str[k] != '\0')
		{
			if ((str[k] == '+' || str[k] == '-') && k != 0)
			{
				oper = str[k];
				if (flag == 1)
				{
					for (int i = 1; i < k; i++)
					{
						a_str += str[i];
					}
				}
				else
				{
					for (int i = 0; i < k; i++)
					{
						a_str += str[i];
					}
				}
				int i = k + 1;
				while (str[i] != '\0')
				{
					b_str += str[i];
					i++;
				}
				break;
			}
			k++;
		}
		if (b_str[b_str.length() - 1] == ' ')
			b_str = b_str.substr(0, b_str.length() - 1);

		Integer a(sign, a_str), b(' ', b_str), answer;
		int m = max(a.getSize(), b.getSize());

		a.setSize(m);
		b.setSize(m);
		if (oper == '+')
			answer = a + b;
		else
			answer = a - b;
		cout << i + 1 << endl;
		cout << "num1: " << a << endl;
		cout << "num2: " << b  << endl;
		cout << "result: " << answer << endl;

	}
	inputFile.close();
}