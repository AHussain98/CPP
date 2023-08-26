# include <iostream>
# include <thread>

/* a properly constructed thread object represents an active thread of execution at a hardware level, such a thread is joinable
for any joinable thread, we must call either the join() or detach() function
after we make such a call, the thread then becomes non-joinable
if you forget to join or detach on a joinable thread, then at time of destructor call on that thread object, std::terminate will be called
if any program has an std::terminate call, we refer to such a program as an unsafe program

 we can only call join or detach once in a threads lifecycle, this is why it's critical to check if a thread is joinable first before calling join or detach
  
  to construct a thread object properly, we have to pass a callable object to the thread class constructor, including any arguments

  we can call detach function as soon as we launch a thread, as detach does not block the calling thread
  in some occasions, we cannot call join function as soon as we launch a thread, as join call blocks the calling thread



*/

void sum(int &x, int y) {  // function with parameters
	 std::cout << (x + y) << std::endl;
	 return;
}


void test() {
	std::cout << "Hello from test!" << std::endl;

}

void foo() {
	std::cout << "This has been detached! Main thread is still going!" << std::endl;
}


int main() {

	std::thread thread1(test); // as soon as we launch thread1 in this way, thread1 represents an active thread of execution. thread1 is now in a joinable state
// if we fail to call join() or detach() on a thread object after we create it (or when it is in a joinable state), an exception will be thrown
// to know if a thread is joinable, we can use the joinable() member function which returns a boolean

	if (thread1.joinable()) {
		thread1.join();  //  now it will work, main thread will pause while thread1 executes
	}

// the join fucntion call introduces a synchronize point between the called thread and the thread that it launched from
// this then blocks the execution of the thread that calls the join fucntion until the joined threads execution completes

// on the other hand, the detach function call will seperate the launched thread from the thread object which it launched from, allowing execution to happen independently
// main thread will continue along with the detached thread, at the same time
	std::thread thread2(foo);
	thread2.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));  // put main thread to sleep 
	  // we have to introduce a sleep in main thread because since we used detach, main thread will continue alongside thread2
	  // this means that if main thread concludes, all the threads launched by main thread will also conclude immediately
	  // so thread2 may not execute all its instructions before that ghappens, hence why we include the sleep in main thread

	int x = 10;

	std::thread t3(sum, std::ref(x), 10);  // passing in parameters
	// thread constructors take in values by value as default, so wrap the input with std::ref to make sure its a reference
	x = 20;
	t3.join();  // 30 is printed, not 20

	// because we passed x by reference, we can change it here and call the join again

	//be careful when detaching threads within fucntions, as after the fucntion is finished executing, the memory and objects created in the function are destroyed
	// so the detached thread may be referencing objects that have already been destriyed, leading to exceptions
	// remember that a detached thread can outlive the lifetime of the objects in the thread that it detached from
	// in that scenario, you have to pass variable by value instead of reference

	// the thread class has no copy constructor but it does have default and move 
	// we can use the move constructor to transfer ownership of a thread

	std::thread t4(test);
	std::thread t5 = std::move(t4);  // move constructed thread, explicit move 
	t5.join();
	// t4 now no longer owns any thread object 
	// you cant call the move constuctor on a thread variable that already owns a thread object

	std::cout << "Hello!" << std::endl;

	std::cout << "the id of t5 is now: " << t5.get_id() << std::endl;  // 0

	// any threads which hav not been properly constructed will have a thread_id of 0
	// also after joining a thread, that thread does not represent an active thread of execution, so its id will also return 0

	// the sleep_for function blocks the execution of the current thread for at least the specific sleep_duration
	// this function may block for longer than sleep_duration due to scheduling or resource contention delays

	// the std::this_thread::yield() function gives up the current time slice and re-inserts the thread into the scheduling queue.
	// the amount of time that expires untli the thread is executed again is ussually entirely dependent upon the scheduler

	std::cout << std::thread::hardware_concurrency() << std::endl; // returns the number of concurrent threads supported by the implementation.
	// this value should be considerd only a hint
	// in a computer, there are a limited number of cores, so if we use more threads than there are cores, the cores perform task switching which takes some overhead
}
