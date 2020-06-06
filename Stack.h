/*
		Author: Hayden Gemeinhardt
		Stack.h
		Since: 5/30/2020
*/
#include <iostream>

using namespace std;

template <class T>
class Stack
{
private:
	struct Node
	{
		T value;
		struct Node* next;
	};
	int length;
	Node* topNode;
public:
	Stack()
	{
		length = 0;
		topNode = NULL;
	};
	~Stack()
	{
		while (topNode != NULL)
		{
			Node* temp = topNode;
			topNode = topNode->next;
			delete temp;
		}
	};
	void push(T newItem);
	bool pop();
	T top();
	bool empty();
};


/* Pushes an item onto a stack. It sets the newItem to the newNode If the top node is NULL, then the next node
 * has to be set to null. Then, the topNode becomes the newNode */
template <class T>
void Stack<T>::push(T newItem)
{
	Node* newNode = new Node;

	if (topNode == NULL)
	{
		newNode->value = newItem;
		newNode->next = NULL;
		topNode = newNode;
	}
	else
	{
		newNode->value = newItem;
		newNode->next = topNode;
		topNode = newNode;
	}
	length++;
}

/* Checks if the stack is empty. Then, decrements length, creates a temp node equal to the topNode,
 * changes the value of the top node to the next node, and deletes the node that used to be the topNode. */
template <class T>
bool Stack<T>::pop()
{
	if (length == 0)
		return false;
	length--;
	Node* tempNode = topNode;
	topNode = topNode->next;
	delete tempNode;
	return true;
}

/* Returns the top node's value */
template <class T>
T Stack<T>::top()
{
	return topNode->value;
}

/* Checks if the stack is empty */
template <class T>
bool Stack<T>::empty()
{
	if (topNode == NULL)
		return true;
	return false;
}