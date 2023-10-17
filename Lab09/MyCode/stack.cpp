#include "stack.h"
#include <iostream>

using namespace std;

void Stack::push(int num)
{
	if (root == NULL)
	{
		root = new Node(num);
	}
	else
	{
		Node* prev = NULL;
		Node* curr = root;
		while (curr != NULL)
		{
			prev = curr;
			curr = curr->getNext();
		}
		prev->setNext(new Node(num));
	}
}

void Stack::pop()
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		Node* prev = NULL;
		Node* curr = root;
		while (curr->getNext() != NULL)
		{
			prev = curr;
			curr = curr->getNext();
		}

		if (curr == root)
		{
			delete root;
			root = NULL;
		}
		else
		{
			prev->setNext(NULL);
			delete curr;
		}
	}
}

void Stack::print()
{
	if (root == NULL)
	{
		cout << "The values in the stack : " << endl;
	}
	else
	{
		Node* prev = NULL;
		Node* curr = root;
		cout << "The values in the stack : ";
		while (curr != NULL)
		{
			cout << curr->getValue() << " ";
			prev = curr;
			curr = curr->getNext();
		}
		cout << endl;
	}
}