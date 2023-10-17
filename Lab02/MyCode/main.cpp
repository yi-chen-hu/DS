#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

class PrimeFactorization {
private:
	int num1, num2;
	vector<int> num1_factor, num2_factor;
	int gcd, lcm;

public:
	PrimeFactorization() {
		num1 = 1;
		num2 = 1;
	}
	PrimeFactorization(int _a, int _b) {
		num1 = _a;
		num2 = _b;
	}
	void Get_Prime_Factorization() {
		int n1 = num1;
		int n2 = num2;
		if (n1 == 1) num1_factor.push_back(1);
		while (n1 % 2 == 0)
		{
			num1_factor.push_back(2);
			n1 /= 2;
		}
		for (int i = 3; i * i <= n1; i = i + 2)
		{
			while (n1 % i == 0)
			{
				num1_factor.push_back(i);
				n1 /= i;
			}
		}
		if (n1 > 2) num1_factor.push_back(n1); 

		if (n2 == 1) num2_factor.push_back(1);
		while (n2 % 2 == 0)
		{
			num2_factor.push_back(2);
			n2 /= 2;
		}
		for (int i = 3; i * i <= n2; i = i + 2)
		{
			while (n2 % i == 0)
			{
				num2_factor.push_back(i);
				n2 /= i;
			}
		}
		if (n2 > 2) num2_factor.push_back(n2);
	}

	void Print_Prime_Factorization() {
		cout << "num1_Prime_factor:\"";
		for (int i = 0; i < num1_factor.size(); i++) {
			if (i == num1_factor.size() - 1)
				cout << num1_factor[i] << "\"" << endl;
			else
				cout << num1_factor[i] << " ";
		}
		cout << "num2_Prime_factor:\"";
		for (int i = 0; i < num2_factor.size(); i++) {
			if (i == num2_factor.size() - 1)
				cout << num2_factor[i] << "\"" << endl;
			else
				cout << num2_factor[i] << " ";
		}
	}

	void Print_GCD() {
		int min;
		gcd = 1;
		for (int i = 0; i < num1_factor.size(); i++)
		{
			if (i >= 1 && num1_factor[i] == num1_factor[i - 1]) continue;
			for (int j = 0; j < num2_factor.size(); j++)
			{
				if (j >= 1 && num2_factor[j] == num2_factor[j - 1]) continue;
				if (num1_factor[i] == num2_factor[j])
				{
					count(num1_factor.begin(), num1_factor.end(), num1_factor[i]) <= count(num2_factor.begin(), num2_factor.end(), num2_factor[j]) ?
						min = count(num1_factor.begin(), num1_factor.end(), num1_factor[i]) : min = count(num2_factor.begin(), num2_factor.end(), num2_factor[j]);
					gcd = gcd * pow(num1_factor[i], min);
				}
			}
		}
		cout << "GCD:" << gcd << endl;
	}

	void Print_LCM() {
		cout << "LCM:" << num1/gcd*num2 << endl;
	}

	void Get_Member() {
		cout << "num1 = " << num1 << endl;
		cout << "num2 = " << num2 << endl;
	}

};

int main() {
	int n, a, b;
	cin >> n;
	vector<PrimeFactorization> PF;
	PF.reserve(n);
	for (int i = 0; i < n; i++)
	{	
		cin >> a >> b;
		PF.push_back(PrimeFactorization(a,b));
	}
	for (int i = 0; i < n; i++) {
		
		PF[i].Get_Member();
		PF[i].Get_Prime_Factorization();
		PF[i].Print_Prime_Factorization();
		PF[i].Print_GCD();
		PF[i].Print_LCM();

		cout << endl;

	}

	system("PAUSE");
	return 0;
}
