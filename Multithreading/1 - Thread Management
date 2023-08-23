# include <iostream>
# include <thread>

// a process is an instance of a computer program that is being executed
/* context is a collection of data about proceses which allows the processor to suspend or hold the execution of a process and restart it later, memory addresses and program counters
* when a program starts, the memory for it is loaded into ram and the cpu core begins executing the programmes instructions
* if we have multiple processes running but only one processsor, that processor will execute the process instructions in round robin fashion, time slices (this is what happens in Python)
 this time slicing algorithm has the appearance of executing the processes simultaenously, but in reality, the processor picks which process to compute and does them sequentially
 this type of execution is possible due to context switching, the processor loads context of a process it was executing previously to restart execution, this is expensive

 a thread is a component of a process. Every process has a main thread which is the entry point for the program
 the thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler
 a thread is a much more lightweight version of a process
 the main thread kicks off child threads, the main thread is the captain of the ship, the crew are the worker threads, sailing the ship is the process

 The typical difference between the threads and process is that threads of the same process run in shared memory space, while processes run in seperate memory spaces
 This means that each process has its own heap memory, each thread has its own local stack memory but every thread of a process has access to the processes' heap memory

 concurrency is a processor core juggling multiple threads from multiple processes
 paralellism is each cpu core having its own process to run, then each thread or process will run actually in parallel 

 paralellism can be task level and data level
 task level: different task on same or different data
 data level: same task on different data

 To the thread class constructor, we can provide any callable object, such as functions, lambdas, functors
*/

void foo() {

	std::cout << "Hello there from foo! " << std::this_thread::get_id() << std::endl;  // std::this_thread::get_id() is how we get printable thread id
}

void run() {  // this run function will be called by the main thread
	std::thread thread1(foo);  // to launch a thread, we have to pass a callable object to the thread object constructor
	// the name of a function is a callable object
	thread1.join(); // join function forces the calling thread to wait until the joined thread completed its execution


}

class callable_class {  // lets try creating a callable class and passing it to a thread
public:
	void operator()() {
		std::cout << "Hello there from callable class! " << std::this_thread::get_id() << std::endl;
	}


};

int main() {  // main thread runs this, all other threads will be kicked off by the main thread due to instructions in the main function

	run();  
	std::cout << "Hello there from main! " << std::this_thread::get_id() << std::endl;

	callable_class obj;  // you have to construct an object of the callable class
	std::thread thread2(obj); // pass it to the thread object
	thread2.join();

	std::thread thread3([] {std::cout << "hello from lambda! " << std::this_thread::get_id() <<  std::endl; });  // thread object created via lambda function
	thread3.join();

	std::cout << "All done from main!" << std::endl;  // now the main thread will print this


	return 0;
}
