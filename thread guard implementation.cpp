#include <iostream>
#include <string>
#include <thread>
#include <chrono> // use this for time
#include "common.h"

// we can call the detach function as soon as we launch a thread, as detach call does not block the calling thread
// in some circumstances, we cannot call the join() function as soon as we launch a thread, as join calls block the calling thread
// however, we need to mitigate the risk that an exception will be called in between launching the thread and joining it, as this would cause the thread object to call terminate()
// To do this, we use RAII, constructor acquires resource, destructor destroys it
// here, we have a simple example using a thread guard

void foo() {
	std::cout << "Hello from foo! \n";
}

void other_operations() {
	std::cout << "this is other operation \n";
	throw std::runtime_error("this is a runtime error \n"); // intentionally throw an error, if we don't find a way to deal with this, the join() call below will skip
}

void run() {
	std::thread foo_thread(foo); // launch a thread with the foo function, it starts immediately
	thread_guard tg(foo_thread); // pass the thread object to the new thread_guard object 
	try {
		other_operations();
	}
	catch (...) {

	}
} // when the program executes, it will throw an exception in the other_operation function call, and the main thread will go out of scope (stack unwindding)
// when main thread goes out of scope, objects which are created inside this function will be destroyed in the reverse order that they were created
// so thread guard gets destroyed first, then the destructor of thread_guard will cause the foo_thread object to join, which starts that thread
// so there will not be any std::terminate call happening for the foo_thread
// 

int main() {

	run();

}