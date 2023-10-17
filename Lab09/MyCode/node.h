#pragma once
#include <iostream>
class Node
{
private:
	int value;
	Node* next;

public:
	Node(int val)
	{
		value = val;
		next = NULL;
	}

	void setNext(Node* node);

	int getValue();
	Node* getNext();
};