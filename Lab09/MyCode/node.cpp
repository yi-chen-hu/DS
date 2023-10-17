#include "node.h"
void Node::setNext(Node* node)
{
	this->next = node;
}

int Node::getValue()
{
	return this->value;
}

Node* Node::getNext()
{
	return this->next;
}