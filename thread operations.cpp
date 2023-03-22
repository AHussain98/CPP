#include <iostream>
#include <string>
#include <thread>
#include <chrono> // use this for time
//#include "common.h"

// get_id() returns a unique thread id for each active thread of execution, returns 0 for all non active threads (if they havent been passed a callable object)
// so you can call thread1.get_id(), or within a fucntion, call std::this_thread::get_id()
// get_id() will also return 0 if you call it on a thread object after you have called join() on that object, the object is no longer active

// sleep_for() blocks the execution of the current thread for at least the specified sleep_duration
// the function may block for longer than sleep_duration due to scheduling or resource contention delays

// std::this_thread::yield(); -> yield will give up the current time slice and re-insert the thread into the scheduling queue.
// the amount of time that expires until the thread is executed agaon is usually dependent upon the scheduler
// this will allow other threads, which are waiting for time slices to become available, to perform their tasks

// std::thread::hardware_concurrency() -> returns the number of concurrent threads supported by the implementation, this value should be considered only a hint
// if you use more threads then there are cores available, the cores will need to context switch, which causes overhead
// it is best practice to launch a number of threads which is less than or equal to the number of parallel threads allowed by the system, otherwise the performance will be worse than if it was sequential
// this number is usually equal to the number of cores you have, but this may not always be true depending on your system implementation
// hardware_concurrency() queries this value

void foo() {
	std::cout << "Hello from foo! " << std::this_thread::get_id() << '\n';
}

void run() {
	std::thread thread1(foo);
	thread1.join();
	std::thread thread2(foo);
	thread2.join(); // you can call multiple thread objects that use the same callable object, this is valid
	std::cout << thread2.get_id() << '\n'; // returns 0, already called join
}

int main() {

	run();
	std::cout << std::thread::hardware_concurrency(); // returns 8
	
}