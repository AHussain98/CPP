#include <iostream>
#include <string>
#include <thread>
#include <chrono> // use this for time
//#include "common.h"

// if one thread creates a variable, then detaches a second thread who is passed a reference to that variable, both threads will access the same shared variable memory
// however, if the original thread returns, and the memory for its variables is reclaimed, you'll get an error, as thread 2 is looking to use memory that no longer exists, it died with thread 1
// in such scenarios, its better to pass variables by value rather than by reference, so they get thier own copies, or use lock instead of detach, so thread 2 gets access for as long as it needs

// to transfer ownership of a thread, we use move constructors

void foo() {
	std::cout << "Hello from foo! \n";
}

void bar() {
	std::cout << "Hello from bar! \n";
}

void run() {
	std::thread thread1(foo);

	// std::thread thread2 = thread1; // this doesnt work, compiler errors because threads deliberately do not have copy constructors or assignment operators
	// we can move threads however, as the move constructor exists

	std::thread thread2(std::move(thread1)); // compiles, lvalue thread1 changed to rvalue reference
	// remember that thread1 now no longer owns any thread object, it's data has been moved to thread2

//	thread2.join();

	// you can't move to a thread object that already is assigned a callable object, so if a thread object owns a thread, we can't then overwrite it
	thread1 = std::thread(bar); // this is acceptable, uses the move constructor of the std::thread class, treats bar as an rvalue reference
	thread1.join();
	thread2.join(); // remember you have to either join or detach, otherwise terminate() is called
}

int main() {
	run();
}