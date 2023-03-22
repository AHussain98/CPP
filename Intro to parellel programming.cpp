#include <iostream>
#include <string>
#include <thread>


// a process is an instance of a coputer program that is being executed
// context is a collection of data about a process which allows processors to suspend or hold the execution of a process and restart the execution later
// context swithing -> a processor juggling multiple processes in round robin fashion, continuing where it left off each time
// a thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler
// a thread is a component of a process, every process has atleast one thread called main thread, which is the entry point for the program
// threads (of the same process) run in a shared memory space, while processes run in seperate memory spaces
// task level paralellism -> different tasks being done concurrently on same data or different data
// data level parallelism -> same tasks being done concurrently on different data
// running in parallel -> multiple cores running processes at the same time, each process done via different core, ont actually achieveable in practice due to lack of cores and high number of threads
// running concurrently -> one core context switching between multiple tasks, this is actually sequential
// learning how to program concurrently is essential to getting the most out of modern multi=processor computer hardware
// Heterogeneous computing refers to systems that use more than one kind of processor or core. These systems gain performance or energy efficiency not just by adding the same type of processors, but by adding dissimilar coprocessors, usually incorporating specialized processing capabilities to handle particular tasks.
//A general-purpose GPU (GPGPU) is a graphics processing unit (GPU) that performs non-specialized calculations that would typically be conducted by the CPU (central processing unit). 
// the thread that runs the main function is referred to as the main thread

class callable_object {
public:
	void operator() () {
		std::cout << "Hello from the callable_object class " << std::this_thread::get_id() << std::endl; // get_id() returns a unique identifier for each thread
	}

};

void foo() {

	std::cout << "Hello! from foo() " << std::this_thread::get_id() << std::endl;
}
void run() {
	std::thread thread1(foo); // launch a thread by creating a callable object via thread class constructor
	// we can pass the function to the thread object, as soon as you create the thread object, it will call teh callabe object and execute on its own thread, you then have to decided whether ot wait for it to finish or let it run on teh beackground
	// if the thread finishes executing and returns before you've called detach() or join() on it, the program will terminate
	callable_object obj;
	std::thread thread2(obj); // pass in the class object we just created
	
	// provide a lambda expression
	std::thread thread3([] {std::cout << "Hello from lambda! " << std::this_thread::get_id() << std::endl; }); // lambda with empty capture list
	
	thread1.join(); // forces main thread to wait until the thread its called on finished its execution
	// we can pass any callable object to the thread class constructor, such as a function calls, lambda expressions and classes with function calls
	thread2.join(); 
	thread3.join();
	std::cout << "Hello from main() " << std::this_thread::get_id() << std::endl;
	
}

int main() {
	run();
}