#ifndef INTEGER_H
#define INTEGER_H 

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Integer
{
private:
	vector<int> num;  //store the number
	char sign;
	string answer;
public:
	//constructor
	Integer(char s = ' ', string number = "0");	//default constructor

	//operation overload 
	Integer operator +(const Integer& b);
	Integer operator -(const Integer& b);

	//output overload
	friend ostream& operator << (ostream& out, const Integer& i);

	int getSize();
	void setSize(int);
	void show_hex();
	void show_num();
};
#endif
