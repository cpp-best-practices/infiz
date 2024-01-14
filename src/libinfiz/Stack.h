#ifndef INFIZ_STACK_H
#define INFIZ_STACK_H

// Stack.h

#include <vector>
#include <cassert>
#include <cstddef>

/**
* A Class that allows allows void * to be
* pushed onto an popped off of a stack.
*/

template<typename Contained>
class Stack
{
public:
	Stack(){}
	
	
	Contained pop() {
		assert(!data.empty());
		Contained toReturn = data.back();
		data.pop_back();
		return toReturn;
	}
		
	void push(const Contained &newElem) {
		data.push_back(newElem);
	}
	
	const Contained * peek() const {
		if (data.empty()) {
			return NULL;
		} else {
			return &data.back();
		}
	}
private:
	std::vector<Contained> data;
};

#endif