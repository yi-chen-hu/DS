#include "Integer.h"

Integer::Integer(char s, string number)
{
	//TODO: read the string and construct the huge integer
	answer = number;
	num.reserve(number.length());
	sign = s;
	int i = number.length() - 1;
	while (i >= 0)
	{
		switch (number[i])
		{
		case 'a':
			num.push_back(10);
			break;
		case 'b':
			num.push_back(11);
			break;
		case 'c':
			num.push_back(12);
			break;
		case 'd':
			num.push_back(13);
			break;
		case 'e':
			num.push_back(14);
			break;
		case 'f':
			num.push_back(15);
			break;
		default:
			num.push_back((int)(number[i] - 48));
		}
		i--;
	}
}

Integer Integer::operator +(const Integer& b) {
	//TODO: perform + opearion overloading	
	vector<int>sum; //存16進位的數字
	string answer;	//回傳值
	if (this->sign == ' ')//正加正
	{
		int carry = 0;
		int i;
		for (i = 0; i < this->num.size(); i++)
		{
			if (this->num[i] + b.num[i] + carry > 15)
			{
				sum.push_back(this->num[i] + b.num[i] + carry - 16);
				carry = 1;
			}
			else
			{
				sum.push_back(this->num[i] + b.num[i] + carry);
				carry = 0;
			}
		}
		if (carry == 1)	sum.push_back(1);	//還要再進位到最高位

		//用while把sum傳給answer，但不用加sign(正加正可以不用)。
		i = sum.size() - 1;
		while (i >= 0)
		{
			switch (sum[i])
			{
			case 10:
				answer += 'a';
				break;
			case 11:
				answer += 'b';
				break;
			case 12:
				answer += 'c';
				break;
			case 13:
				answer += 'd';
				break;
			case 14:
				answer += 'e';
				break;
			case 15:
				answer += 'f';
				break;
			default:
				answer += (char)(sum[i] + 48);	//ASCII。要加48。
			}
			i--;
		}
		return Integer(' ', answer);
	}
	else    //負加正
	{
		int flag = 0;
		for (int i = 1; i <= this->num.size(); i++)
		{
			if (b.num[b.num.size() - i] > this->num[this->num.size() - i])
			{
				flag = 1;
				break;
			}
			else if (b.num[b.num.size() - i] < this->num[this->num.size() - i])
				break;
		}
		if (flag)//b > a//line159
		{
			int carry;
			if (b.num[0] - this->num[0] < 0)
			{
				sum.push_back(b.num[0] - this->num[0] + 16);
				carry = 1;
			}
			else
			{
				sum.push_back(b.num[0] - this->num[0]);
				carry = 0;
			}
			for (int i = 1; i < b.num.size(); i++)
			{
				if (b.num[i] - this->num[i] - carry < 0)
				{
					sum.push_back(b.num[i] - this->num[i] -carry + 16);
					carry = 1;
				}
				else
				{
					sum.push_back(b.num[i] - this->num[i] - carry);
					carry = 0;
				}
			}
			for (int i = sum.size() - 1; i > 0; i--)
				if (sum[i] == 0)	sum.resize(i);
				else   break;

			int i = sum.size() - 1;
			while (i >= 0)
			{
				switch (sum[i])
				{
				case 10:
					answer += 'a';
					break;
				case 11:
					answer += 'b';
					break;
				case 12:
					answer += 'c';
					break;
				case 13:
					answer += 'd';
					break;
				case 14:
					answer += 'e';
					break;
				case 15:
					answer += 'f';
					break;
				default:
					answer += (char)(sum[i] + 48);	//ASCII。要加48。
				}
				i--;
			}
			return Integer(' ', answer);
		}
		else    //b <= a //-(a-b) //line 102
		{
			int carry = 0;
			if (this->num[0] - b.num[0] < 0)
			{
				sum.push_back(this->num[0] - b.num[0] + 16);
				carry = 1;
			}
			else
				sum.push_back(this->num[0] - b.num[0]);
			for (int i = 1; i < this->num.size(); i++)
			{
				if (this->num[i] - b.num[i] - carry < 0)
				{
					sum.push_back(this->num[i] - b.num[i] - carry + 16);
					carry = 1;
				}
				else
				{
					sum.push_back(this->num[i] - b.num[i] - carry);
					carry = 0;
				}
			}
			for (int i = sum.size() - 1; i > 0; i--)
				if (sum[i] == 0)	sum.resize(i);
				else    break;

			int i = sum.size() - 1;
			while (i >= 0)
			{
				switch (sum[i])
				{
				case 10:
					answer += 'a';
					break;
				case 11:
					answer += 'b';
					break;
				case 12:
					answer += 'c';
					break;
				case 13:
					answer += 'd';
					break;
				case 14:
					answer += 'e';
					break;
				case 15:
					answer += 'f';
					break;
				default:
					answer += (char)(sum[i] + 48);	//ASCII。要加48。
				}
				i--;
			}
			if (answer == "0")
				return Integer(' ', answer);
			else
				return Integer('-', answer);
		}
	}
}
Integer Integer::operator -(const Integer& b) {
	//TODO: perform - opearion overloading
	vector<int>sum;
	string answer;
	if (this->sign == '-')//-(a+b) //line 272
	{
		int carry = 0;
		int i;
		for (i = 0; i < this->num.size(); i++)
		{
			if (this->num[i] + b.num[i] + carry > 15)
			{
				sum.push_back(this->num[i] + b.num[i] + carry - 16);
				carry = 1;
			}
			else
			{
				sum.push_back(this->num[i] + b.num[i] + carry);
				carry = 0;
			}
		}
		if (carry == 1)	sum.push_back(1);	//還要再進位到最高位

		//用while把sum傳給answer，最後加負號。
		i = sum.size() - 1;
		while (i >= 0)
		{
			switch (sum[i])
			{
			case 10:
				answer += 'a';
				break;
			case 11:
				answer += 'b';
				break;
			case 12:
				answer += 'c';
				break;
			case 13:
				answer += 'd';
				break;
			case 14:
				answer += 'e';
				break;
			case 15:
				answer += 'f';
				break;
			default:
				answer += (char)(sum[i] + 48);	//ASCII。要加48。
			}
			i--;
		}
		return Integer('-', answer);
	}
	else//正減正//line 222
	{
		int flag = 0;
		for (int i = 1; i <= this->num.size(); i++)
		{
			if (this->num[this->num.size() - i] > b.num[b.num.size() - i])
			{
				flag = 1;
				break;
			}
			else if(this->num[this->num.size() - i] < b.num[b.num.size() - i])
				break;
		}
		if (flag)//a > b //line 339
		{
			int carry;
			if (this->num[0] - b.num[0] < 0)
			{
				sum.push_back(this->num[0] - b.num[0] + 16);
				carry = 1;
			}
			else
			{
				sum.push_back(this->num[0] - b.num[0]);
				carry = 0;
			}
			for (int i = 1; i < this->num.size(); i++)
			{
				if (this->num[i] - b.num[i] - carry < 0)
				{
					sum.push_back(this->num[i] - b.num[i] - carry + 16);
					carry = 1;
				}
				else
				{
					sum.push_back(this->num[i] - b.num[i] - carry);
					carry = 0;
				}
			}
			for (int i = sum.size() - 1; i > 0; i--)
				if (sum[i] == 0)	sum.resize(i);
				else   break;

			int i = sum.size() - 1;
			while (i >= 0)
			{
				switch (sum[i])
				{
				case 10:
					answer += 'a';
					break;
				case 11:
					answer += 'b';
					break;
				case 12:
					answer += 'c';
					break;
				case 13:
					answer += 'd';
					break;
				case 14:
					answer += 'e';
					break;
				case 15:
					answer += 'f';
					break;
				default:
					answer += (char)(sum[i] + 48);	//ASCII。要加48。
				}
				i--;
			}
			return Integer(' ', answer);
		}
		else    //a <= b//-(b-a) //line 283
		{
			int carry;
			if (b.num[0] - this->num[0] < 0)
			{
				sum.push_back(b.num[0] - this->num[0] + 16);
				carry = 1;
			}
			else
			{ 
				sum.push_back(b.num[0] - this->num[0]);
				carry = 0;
			}
			for (int i = 1; i < this->num.size(); i++)
			{
				if (b.num[i] - this->num[i] - carry < 0)
				{
					sum.push_back(b.num[i] - this->num[i] - carry + 16);
					carry = 1;
				}
				else
				{
					sum.push_back(b.num[i] - this->num[i] - carry);
					carry = 0;
				}
			}
			for (int i = sum.size() - 1; i > 0; i--)
				if (sum[i] == 0)	sum.resize(i);
				else    break;

			int i = sum.size() - 1;
			while (i >= 0)
			{
				switch (sum[i])
				{
				case 10:
					answer += 'a';
					break;
				case 11:
					answer += 'b';
					break;
				case 12:
					answer += 'c';
					break;
				case 13:
					answer += 'd';
					break;
				case 14:
					answer += 'e';
					break;
				case 15:
					answer += 'f';
					break;
				default:
					answer += (char)(sum[i] + 48);	//ASCII。要加48。
				}
				i--;
			}
			if (answer == "0")
				return Integer(' ', answer);
			else
				return Integer('-', answer);
		}
	}
}


ostream& operator << (ostream& out, const Integer& i) {
	out << i.sign << i.answer << endl;
	return out;
}


int Integer::getSize()
{
	return num.size();
}

void Integer::setSize(int size)
{
	num.resize(size);
}

void Integer::show_hex()
{
	cout << sign;
	int i = num.size() - 1;
	while (i >= 0)
	{
		switch (num[i])
		{
		case 10:
			cout << "a";
			break;
		case 11:
			cout << "b";
			break;
		case 12:
			cout << "c";
			break;
		case 13:
			cout << "d";
			break;
		case 14:
			cout << "e";
			break;
		case 15:
			cout << "f";
			break;
		default:
			cout << (char)(num[i] + 48);	//ASCII。要加48。
		}
		i--;
	}
	cout << endl;
}

void Integer::show_num()
{
	for (int i = num.size() - 1; i >= 0; i--)
	{
		cout << num[i] << " ";
	}
	cout << endl;
}
