#include <iostream>
#include <string>
#include <thread>
#include <chrono> // use this for time
#include <algorithm>
#include <atomic>
//#include "common.h"

// when you declare a variable thread_local, then each thread is going to have its own distinct object
// the storage duration is the entire execution of the thread in which it was created, and the value stored in the object is initialized when the thread is started

thread_local std::atomic<int> i = 0;  // global atomic integer type variable
// atomic variables are similar to normal variables except if one thread writes a value to it, that value will be visible to all other threads in this context

void foo() { // all this does is increase i
	// int i = 0;
	++i;
	std::cout << i;
} // sometimes 123 will be printed, sometimes 223 will be printed, this is due to race condition
// however, when i is changed to thread_local, each thread will have its own distinct object, so the output is always 111
// the thread_local object is only visible to that particular thread

int main() {
	std::thread t1(foo);
	std::thread t2(foo);
	std::thread t3(foo);

	t1.join();
	t2.join();
	t3.join(); // see how i increases each time, unless we make i thread_local
	std::cout << std::endl;


}