#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class complex
{
private:
	char command;
	int a, b, c, d, Re, Im;
public:
	void in(void)
	{
		cin >> command;
		command == 'p' ? cin >> a >> b : cin >> a >> b >> c >> d;
	}
	void out(void)
	{
		switch (command)
		{
		case 'p':
			if (b == -1)
				a == 0 ? cout <<"-i" << endl : cout << a << "-i" << endl;
			else if (b == 0)
				a == 0 ? cout << 0 << endl : cout << a << endl;
			else if (b == 1)
				a == 0 ? cout << "i" << endl : cout << a << "+i" << endl;
			else if (b > 0)
				a == 0 ? cout << b << "i" << endl : cout << a << "+" << b << "i" << endl;
			else
				a == 0 ? cout << b << "i" << endl : cout << a << "+" << b << "i" << endl;
			break;
		case '+':
			Re = a + c;
			Im = b + d;
			if (Im == -1)
				Re == 0 ? cout << "-i" << endl : cout << Re << "-i" << endl;
			else if (Im == 0)
				Re == 0 ? cout << 0 << endl : cout << Re << endl;
			else if (Im == 1)
				Re == 0 ? cout << "i" << endl : cout << Re << "+i" << endl;
			else if (Im > 0)
				Re == 0 ? cout << Im << "i" << endl : cout << Re << "+" << Im << "i" << endl;
			else
				Re == 0 ? cout << Im << "i" << endl : cout << Re << "+" << Im << "i" << endl;
			break;
		case '*':
			Re = a * c - b * d;
			Im = a * d + b * c;
			if (Im == -1)
				Re == 0 ? cout << "-i" << endl : cout << Re << "-i" << endl;
			else if (Im == 0)
				Re == 0 ? cout << 0 << endl : cout << Re << endl;
			else if (Im == 1)
				Re == 0 ? cout << "i" << endl : cout << Re << "+i" << endl;
			else if (Im > 0)
				Re == 0 ? cout << Im << "i" << endl : cout << Re << "+" << Im << "i" << endl;
			else
				Re == 0 ? cout << Im << "i" << endl : cout << Re << "+" << Im << "i" << endl;
			break;
		default:
			cout << "Invalid" << endl;
		}
	}
};
int main(void)
{
	int i, n;
	cin >> n;
	std::vector<complex> x;
	x.reserve(n);
	for (i = 0; i < n; i++)
	{
		x.push_back(complex());
	}
	for (i = 0; i < n; i++)
	{
		x[i].in();
	}
	for (i = 0; i < n; i++)
	{
		x[i].out();
	}
	return 0;
}