#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <stack>
#include <memory>

// reminder: stack is a last in first out data structure, commonly implemented via singly linked list
// if multiple threads access the same stack, we may see broken invariants and possibly races between operations
// we could see a race condition from two threads simulatenously pushing and popping from the top of the stack, for example


template <typename T>
class trivial_thread_safe_stack {

	std::stack<T> stk;
	std::mutex m; // data members are stack and mutex

public:
	void push(T element) {
		std::lock_guard<std::mutex> lg(m); // lock guard object for this function scope
		stk.push();
	}
	void pop() {
		std::lock_guard<std::mutex> lg(m); // only one thread allowed to proceed because only one thread can acquire teh lock accociated with this mutex object
		stk.pop();
	}
	T& top() {
		std::lock_guard<std::mutex> lg(m);
		return stk.top();
	}

};
// we have wrapped functionalityoes with a synchronization mechanism (mutex)
// by doing so, we have achieved thread safety, but we have limited true parallel access to the data structure
// even though many threads try to access it, only one can actually do any operation at once
// however, there is a still a race condition here, called race condition inherit from the interface
// so imagine two threads activating a top() and pop() function at different times, the outcome will be different depending on the order of execution -> race condition

// to avoid this, we can combine top() and pop()
// we can check if the stack is empty in that new combined function before calling top/pop and return null_ptr if there are no items in the stack
// lets implement this using shared_ptrs

template <typename Y>
class thread_safe_stack {
	std::stack < std::shared_ptr<Y> stk;
	std::mutex m;
public:
	void push(Y element) {
		std::lock_guard<std::mutex> lg(m);
		stk.push(std::make_shared<Y>(element));
	}

	std::shared_ptr<Y> pop() {
		std::lock_guard<std::mutex> lg(m);
		if (stk.empty()) { // in the pop function, first check if the stack is empty
			throw std::runtime_error("stack is empty");
		} // this way, we avoid the race condition between the top and empty function, because checking if the stack is empty is part of the pop() condition

		std::shared_ptr<Y> res(stk.top());
		stk.pop();
		return res; // return the shared pointer that points to the top element
	}


};



int main() {

}