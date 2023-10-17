#include<iostream>
#include<fstream>
#include<string>
#include"LinkedList.h"

using namespace std;


int main() {
	ifstream File;
	File.open("input2.txt");

	if (!File.is_open()) {
		cout << "Can't open txt file" << endl;
		return 0;
	}

	int TestCase = 0;
	File >> TestCase;

	while (TestCase) {

		LinkedList List;
		int num_op = 0;
		File >> num_op;
		for (int i = 0; i < num_op; i++) {
			char op;
			int val;
			int index;
			int index2;

			File >> op;

			switch (op)
			{
			case 'b':
				File >> val;
				List.Push_back(val);
				break;
			case 'f':
				File >> val;
				List.Push_front(val);
				break;
			case 'i':
				File >> index;
				File >> val;
				List.Insert(index, val);
				break;
			case 'd':
				File >> index;
				List.Delete(index);
				break;
			case 'r':
				List.Reverse();
				break;
			case 's':
				File >> index;
				File >> index2;
				List.Swap(index, index2);
				break;
			default:
				break;
			}
		}
		List.Print();

		cout << endl;
		TestCase--;
	}

	system("pause");
	return 0;
}