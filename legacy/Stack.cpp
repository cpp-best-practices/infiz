// Stack.cpp

#include "Stack.h"
#include <stdio.h>

Stack::Stack() {
	head=NULL;
}

Stack::~Stack() {
	deleteStack(head);
}

void Stack::deleteStack(stackElem * head) {
	if (head!=NULL) {
		if(head->next != NULL) {
			deleteStack(head->next);
		}
		delete head->data;
		delete head;
	}
}

void * Stack::pop() {
	void * toReturn = NULL;
	stackElem * newhead;

	if (head != NULL) {
		toReturn = head->data;
		newhead = head->next;
		delete head;
		head = newhead;
	}

	return toReturn;
}

int Stack::moreThanOne() {
	if (head != NULL) {
		if (head->next!=NULL) {
			return 1;
		}
	}
	else 
		return 0;
	
	return 0;
}

void Stack::push(void * newElem) {
	stackElem * newelem;
	
	newelem = new stackElem;
	newelem->data = newElem;
	newelem->next = head;
	head = newelem;
}

void * Stack::peek() {
	if (head != NULL)
		return head->data;
	else
		return NULL;
}