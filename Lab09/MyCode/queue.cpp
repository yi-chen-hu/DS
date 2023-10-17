#include "queue.h"
#include <iostream>

using namespace std;

void Queue::enqueue(int num)
{
	if (root == NULL)
	{
		root = new Node(num);
	}
	else
	{
		Node* newNode = new Node(num);
		newNode->setNext(root);
		root = newNode;
	}
}

void Queue::dequeue()
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		Node* prev = NULL;
		Node* curr = root;
		while (curr->getNext()!= NULL)
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

void Queue::print()
{
	if (root == NULL)
	{
		cout << "The values in the queue : " << endl;
	}
	else
	{
		Node* prev = NULL;
		Node* curr = root;
		cout << "The values in the queue : ";
		while (curr != NULL)
		{
			cout << curr->getValue() << " ";
			prev = curr;
			curr = curr->getNext();
		}
		cout << endl;
	}
}