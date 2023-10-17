#pragma once
#include "node.h"
#include <iostream>
class Stack
{
private:
	Node* root;
public:
	Stack()
	{
		root = NULL;
	}

	void push(int num);
	void pop();
	void print();
};
