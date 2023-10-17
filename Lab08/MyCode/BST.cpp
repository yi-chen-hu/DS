#include "BST.h"
#include<iostream>
#include<queue>
using namespace std;

void BST::insert(Node* insertNode) {
	//TODO: insert a node to BST
	if (root == NULL)
		root = insertNode;
	else
	{
		bool flag;
		Node* prev = NULL;
		Node* curr = getRoot();
		while (curr)
		{
			if (insertNode->getValue() < curr->getValue())
			{
				prev = curr;
				curr = curr->getLchild();
				flag = 0;
			}
			else
			{
				prev = curr;
				curr = curr->getRchild();
				flag = 1;
			}
		}
		if (flag)
			prev->setRchild(insertNode);
		else
			prev->setLchild(insertNode);
	}
}

void BST::InOrder_traversal(Node* root)
{
	//TODO: Inorder traversal
	if (root)
	{
		InOrder_traversal(root->getLchild());
		cout << root->getValue() << " ";
		InOrder_traversal(root->getRchild());
	}
}

void BST::LevelOrder_traversal(Node* root)
{
	//TODO: Level order traversal
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		Node* node = q.front();
		cout << node->getValue() << " ";
		q.pop();
		if (node->getLchild())
			q.push(node->getLchild());
		if (node->getRchild())
			q.push(node->getRchild());
	}

}


Node* BST::getRoot() {
	//TODO: return root of BST
	return root;
}