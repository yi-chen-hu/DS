#include "DateCalculator.h"

using namespace std;

DateCalculator::DateCalculator():year(2000),month(1),day(1), changeDays(0){}


void DateCalculator::readFile(const char *fileName) {
	ifstream file(fileName);
	char oper;
	char year_str[5];
	char month_str[3];
	char day_str[3];
	char changeDays_str[5];
	while (!file.eof())
	{
		file.get(oper);
		file.get();		//�l���ťզr��
		file.getline(year_str, 5, '/');
		file.getline(month_str, 3, '/');
		file.getline(day_str, 3, ' ');		//��ťզr������
		file.getline(changeDays_str, 5, '\n');
		year = atoi(year_str);
		month = atoi(month_str);
		day = atoi(day_str);
		changeDays = atoi(changeDays_str);
		switch (oper)
		{
		case '+':
			add();
			break;
		case '-':
			minus();
			break;
		default:;
		}
		showDay();
	}
}

void DateCalculator::add() {
	int daysOfMonth[12] = { 31,28+isLeapYear(year),31,30,31,30,31,31,30,31,30,31 };
	if (day + changeDays <= daysOfMonth[month - 1])		//�����H�[��U�Ӥ�
	{
		day = day + changeDays;
		changeDays = 0;
	}
	else
	{
		changeDays -= daysOfMonth[month - 1] - day;
		day = daysOfMonth[month - 1];	//���Nday���]���o�Ӥ�멳
		while (changeDays > daysOfMonth[month % 12])	//changeDays�����[��U�Ӥ�멳
		{
			if (month == 12)	//12��t�~�Q��
			{
				year++;
				daysOfMonth[1] = 28 + isLeapYear(year);		//�P�_�s���@�~�O���O�|�~
				changeDays -= 31;	//����1�몺�Ѽ�
				month = 1;		//�ܦ��@�멳
			}
			else
			{
				changeDays -= daysOfMonth[month];	//�����U�Ӥ몺�Ѽ�
				month += 1;		//�]���U�Ӥ�
			}
		}
		if (changeDays == 0);
		else		//�ѤU���Ѽ��~��[
		{
			if (month == 12)	//12��t�~�Q��
			{
				month = 1;
				year++;
				day = changeDays;
			}
			else
			{
				month++;
				day = changeDays;
			}
		}
	}
}

void DateCalculator::minus() {
	int daysOfMonth[12] = { 31,28 + isLeapYear(year),31,30,31,30,31,31,30,31,30,31 };
	if (day - changeDays >= 1)		//�����H����W�Ӥ�
	{
		day = day - changeDays;
		changeDays = 0;
	}
	else
	{
		changeDays = changeDays - (day - 1);
		day = 1;	//���Nday���]��1
		while (changeDays > daysOfMonth[month == 1 ? 11 : month - 2])	//��������W�Ӥ���
		{
			if (month == 1)		//1��t�~�Q��
			{
				changeDays = changeDays - 31;
				month = 12;
				year -= 1;
				daysOfMonth[1] = 28 + isLeapYear(year);		//�P�_�s���@�~�O���O�|�~
			}
			else
			{
				changeDays -= daysOfMonth[month - 2];
				month -= 1;
			}
		}
		if (changeDays == 0);
		else		//�ѤU���Ѽ��~��
		{
			if (month == 1)		//1����}�Q��
			{
				month = 12;
				year--;
				day = 31 - changeDays + 1;
			}
			else
			{
				day = daysOfMonth[month - 2] - changeDays + 1;
				month -= 1;
			}
		}
	}
}

bool DateCalculator::isLeapYear(int year_) {
	//TODO: 
	//Determine whether year_ is a leap year.
	return(year_ % 400 == 0 || (year_ % 4 == 0 && year_ % 100 != 0));
}

void DateCalculator::showDay() {
	//TODO: 
	//The function output the date on the screen.
	//Hint: You can use setw() to set the length of the number.
	//      You can use setfill('c') to fill 'c' to the empty space.
	//      Two functions of above is in iomanip header file. 
	cout.fill('0');
	cout << setw(4) << year << "/" << setw(2) << month << "/" << setw(2) << day << endl;
}