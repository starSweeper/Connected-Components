#pragma once

#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST


#include<string>
using namespace std;

class SLLNode { //For nodes in the list
public:
	SLLNode() {
		next = 0;
	}
	SLLNode(int el, SLLNode *ptr = 0) {    
		element = el; next = ptr;
	}
	char element;
	SLLNode *next;
};

class SLList { //For access to the list
public:
	SLList() {
		head = tail = 0;
	}
	~SLList();
	int isEmpty() {
		return head == 0;
	}
	void sortedAdd(char);
	bool isInList(char) const;//Search for reservation (search for passenger)
	void addSet(SLList*);
	char getElement(int);
	int getAllElements(char[]);

private:
	SLLNode *head, *tail;
};

#endif