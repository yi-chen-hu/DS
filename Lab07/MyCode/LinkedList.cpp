#include "LinkedList.h"

LinkedList::LinkedList() {
	// Constructor
	Head = NULL;
}

void LinkedList::Push_back(int x) {
	// TODO : Insert a node to the end of the linked list, the node’s value is x.
	if (!Head)
	{
		Head = new ListNode(x);
		return;
	}
	ListNode* current = Head;
	while (current->next != NULL)
		current = current->next;
	current->next = new ListNode(x);
}

void LinkedList::Push_front(int x) {
	if (!Head) {
		Head = new ListNode(x);
		return;
	}
	ListNode* newNode = new ListNode(x);

	newNode->next = Head;
	Head = newNode;
}

void LinkedList::Insert(int index, int x) {
	// TODO : Insert a node to the linked list at position “index”, the node's
	// value is x. The index of the first node in the linked list is 0.
	int counter = 0;
	ListNode* prev = NULL;
	ListNode* curr = Head;
	while (counter != index)
	{
		prev = curr;
		curr = curr->next;
		counter++;
	}
	
	if (prev == NULL)
		Push_front(x);
	else if (curr == NULL)
		Push_back(x);
	else
	{
		ListNode* temp = prev->next;
		ListNode* newNode = new ListNode(x);
		prev->next = newNode;
		newNode->next = temp;
	}

}

void LinkedList::Delete(int index) {
	// TODO : Remove the node with index “index” in the linked list.
	int counter = 0;
	ListNode* prev = NULL;
	ListNode* curr = Head;
	while (counter != index)
	{
		prev = curr;
		curr = curr->next;
		counter++;
	}

	if (prev == NULL)
	{
		Head = Head->next;
		delete curr;
	}
	else 
	{
		prev->next = curr->next;
		delete curr;
	}
}

void LinkedList::Reverse() {
	// TODO : Reverse the linked list.
	// Example :
	//
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 4 -> 3 -> 2 -> 1 -> NULL
	ListNode* prev = NULL, * curr = Head, * next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;//把指標往前一個指
		//Move prev and curr one step forward
		prev = curr;
		curr = next;
	}
	Head = prev;
}

void LinkedList::Swap(int index_1, int index_2) {
	if (index_1 == index_2) return;

	// TODO : Swap two nodes in the linked list
	// Example : 
	// index_1 : 1   ,  index_2 : 3
	// 
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 1 -> 4 -> 3 -> 2 -> NULL
	ListNode* prev_1 = NULL;
	ListNode* curr_1 = Head;

	int counter = 0;
	//Searching for inde_1
	while (counter != index_1)
	{
		prev_1 = curr_1;
		curr_1 = curr_1->next;
		counter++;
	}

	ListNode* prev_2 = NULL;
	ListNode* curr_2 = Head;
	
	counter = 0;
	//Searching for index_2
	while (counter != index_2)
	{
		prev_2 = curr_2;
		curr_2 = curr_2->next;
		counter++;
	}

	if (prev_1 != NULL)
		prev_1->next = curr_2;
	else   //If index_1 is  Head
		Head = curr_2;

	if (prev_2 != NULL)
		prev_2->next = curr_1;
	else   //If index_2 is Head
		Head = curr_1;

	//Swap next pointer
	ListNode* temp;
	temp = curr_1->next;
	curr_1->next = curr_2->next;
	curr_2->next = temp;
}

void LinkedList::Print() {
	cout << "List: ";
	// TODO : Print all the elements in the linked list in order.
	ListNode* current = Head;
	while (current)
	{
		cout << current->val << " ";
		current = current->next;
	}
	cout << endl;	
}

LinkedList::~LinkedList()
{
	while (Head) {
		ListNode* temp = Head;
		Head = Head->next;
		delete temp;
	}
}
