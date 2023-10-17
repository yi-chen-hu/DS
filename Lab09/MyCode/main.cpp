#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"

using namespace std;



int main()
{
	fstream file;
	file.open("input2.txt");

	if (!file.is_open())
	{
		cout << " Fail to open the file" << endl;
		return 0;
	}
	
	int  TestCase = 0;
	file >> TestCase;

	while (TestCase)
	{
		char container;
		int step = 0;
		file >> container >> step;
		if (container == 'S')
		{
			Stack stack;
			for (int i = 0; i < step; i++)
			{
				string op;
				int val;
				file >> op;
				if (op == "push")
				{
					file >> val;
					stack.push(val);
				}
				else if (op == "pop")
				{
					stack.pop();
				}
				else if (op == "print")
				{
					stack.print();
				}
			}
		}
		else if (container == 'Q')
		{
			Queue queue;
			for (int i = 0; i < step; i++)
			{
				string op;
				int val;
				file >> op;
				if (op == "en")
				{
					file >> val;
					queue.enqueue(val);
				}
				else if (op == "de")
				{
					queue.dequeue();
				}
				else if (op == "print")
				{
					queue.print();
				}
			}
		}
		cout << endl;
		TestCase--;
	}
	return 0;
}