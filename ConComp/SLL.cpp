#include<iostream>
#include"SLL.h"


SLList::~SLList() {
	for (SLLNode *p; !isEmpty();) {
		p = head->next;
		//delete head;
		head = p;
	}
}

//Adds new nodes in alphebetical order. Heavily relies on code found here http://stackoverflow.com/questions/4825030/c-add-to-linked-list-in-sorted-order
void SLList::sortedAdd(char el) {
	SLLNode* temp = new SLLNode(el);
	temp->element = el;

	SLLNode* temp2 = head;
	SLLNode** temp3 = &head;
	while (temp2 != 0 && temp2->element < temp->element)
	{
		temp3 = &temp2->next;
		temp2 = temp2->next;
	}
	*temp3 = temp;
	temp->next = temp2;
}

//Adds another set (list) to the current set
void SLList::addSet(SLList *set) {
	SLLNode *tmp;
	for (tmp = set->head; tmp != tail; tmp = tmp->next) {
		if (isInList(tmp->element) == false) {
			sortedAdd(tmp->element);
		}
	}
}

//Returns size of list and fills 'set[]' with every node in list
int SLList::getAllElements(char set[]) {
	SLLNode *tmp;

	int i = 0;
	for (tmp = head; tmp != tail; tmp = tmp->next) {
		set[i] = tmp->element;
		i++;
	}

	return i;
}

 //Search for node
bool SLList::isInList(char el) const {
	SLLNode *tmp;
	for (tmp = head; tmp != tail && !(tmp->element == el); tmp = tmp->next);
	return tmp != 0;
}

//Allows the ability use list in for loops
char SLList::getElement(int el) {
	SLLNode *tmp;
	tmp = head;

	if (el != 0) {
		for (int i = 0; i != el; i++) {
			tmp = tmp->next;
		}
	}

	return tmp->element;
}
