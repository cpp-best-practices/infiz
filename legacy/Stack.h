#ifndef INFIZ_STACK_H
#define INFIZ_STACK_H

// Stack.h


/**
 * A Class that allows allows void * to be
 * pushed onto an popped off of a stack.
 */

class Stack
{
public:
	Stack();
	~Stack();
	void * pop();
	void push(void * stackElem);
	void * peek();
	int moreThanOne();

private:

	
	struct stackElem {
		void * data;
		stackElem * next;
	};
	
	void deleteStack(stackElem * head);
	stackElem * head;

};
	
#endif