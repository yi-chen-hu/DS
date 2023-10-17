#pragma once
#include "node.h"
#include <iostream>
class Queue
{
private:
	Node* root;
public:
	Queue()
	{
		root = NULL;
	}
	void enqueue(int num);
	void dequeue();
	void print();
};
