#include <iostream>
#include <string>
#include <thread>
#include <chrono> // use this for time

// a properly constructed thread object represents an active thread of execution on the hardware level, such a thread object is joinable
// for any joinable thread, we must call either join or detach functions
// after we make such a call, that thread object becomes non joinable
// if you forgot to join or detach on joinable thread, the at the time of destructor call to that thread object, std::terminate function will be called
// if any programs have std::terminate calls, we refer to such programs as an unsafe program

void test() {
	std::cout << "Hello from joined test! \n";
}

void test2() {
	std::cout << "Hello from detached test! \n";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // you can also make the thread sleep for a particular amount of time
}

void run() {
	std::thread thread1(test); // execute a thread called thread1, it will call the test function
// as soon as we launch thred1 in this way, thread1 represents an active thread of execution
// so thread1 is currently in a joinable state, we have to call either join() or detach() functions for any joinable threads in our program, or the program terminates
// joinable() returns a boolean to show if the thread is joinable or not
if (thread1.joinable()) {
	std::cout << " can join thread1 \n";
}
thread1.join();
if (!thread1.joinable()) {
	std::cout << "cannot join thread1 \n"; // after the join() call, the thread will no longer be joinable
}
}

void run_detached() {

	std::thread thread2(test2);
	thread2.detach(); // will now run independently alongside main thread
	std::cout << "Hello from main! \n";
}

// properly constructed thread objects represent an active thread of execution on a hardware level, such a thread object is joinable
// to construct a thread properly, we have to pass a callable object into the constructor of the thread object
// if that callable object takes parameters, you have to pass those parameters aswell
// we can only call join() or detach() once in a threads lifecycle
// if we create a thread object and do not put a callable object in its constructor, it will not be joinable
int main() {

	run_detached(); // won't cause main thread to stop
	run(); // will cause main thread to stop
	

	

}

// join() introduces a synchronize point between the launched thread and the thread that it launched from
// it blocks the execution of the thread that calls the join() function, until the launched thread's execution is finished

// on the other hand, detach() seperates the launched thread from the thread object that it launched from, allowing execution to continue independently
// any allocated resources inside the detached thread will be freed once the thread exits
// so if thread1.detach() is run, thread1 will execute, independent of main thread
// new thread will be able to continue executing even after first thread finishes

// however, the program will stop if main thread finishes, even if the thread we've detached hasn't finished executing
// keep this timing in mind