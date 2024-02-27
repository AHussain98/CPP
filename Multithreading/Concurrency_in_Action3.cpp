# include <iostream>
# include <thread>
# include <mutex>
# include <vector>
# include <chrono>
# include <condition_variable>
# include <queue>

// synchronise concurrent operations
// sometimes we don't need to just protect the data, we also need to synchrnoise actions on seperate threads
// one thread might need to wait for another thread to complete a task before the first thread can complete its own, for example
// in general, its common to want a thread to wait for a specific event to happen or a condition to become true
// you can do this by constantly polling or checking for a "task complete" flag or something similar, this is far from optimal
// we can synchronise operations between threads like this through the use of condition_variables and futures.

// if one thread is waiting for a second thread to complete a task, it has several options
// first, it could keep checking a flag in shared memory (protected by a mutex) and have the second thread set the flag when it completes the task
// this is wasteful, the first thread wastes computation by continoually checking the flag and when the mutex is locked by the waiting thread, it can't be locked by any other thread
// the waiting thread is then taking away computation resources from the thread being waited on, and reducing performance by holding the mutex so the flag can't be changed

// a second option is to have the waiting thread sleep for short periods between the checks using the std::this_thread::sleep_for() function

bool flag;
std::mutex m;
void wait_for_flag() {
	std::unique_lock<std::mutex> lk(m);  // unique lock created but not locked yet
	while (!flag) {
		lk.unlock();  // unlock the mutex before sleeping, so another thread gets the chance to acquire it and set the flag
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		lk.lock();  // relock the mutex
	}
}

// this is an improvement because the thread doesn't waste processing time while it's sleeping but it's hard to get the sleep period right

// the third and preferred option is to use the standard library to wait for the event itself
// the most basic mechanism for waiting for an event to be triggered by another thread (such as the presence of additional work in the pipeline mentioned previously is the condition variable
// a condition variable is associated with an event or other condition, and one or more threads can wait for that condition to be satisfied
// when a thread has determined that the condition is satisfied, then it can notify one or more of the threads waiting on the cindition variable in order to wake them up and allow them to continue processing

// the standard library provides two implementations of a condition variable, std::condition_variable and std::condition_variable_any, both defined in <condition_variable>
// they need to work with a mutex in order to provide appropriate synchronisation
// std::condition_variable needs to work with only std::mutex, and std::condition_variable_any can work with any type that meets the minimal criteria for being mutex-like
// std::condition_variable is therefore lower cost

// waiting for data to process with std::condition_variable
std::mutex mut;
std::queue<data_chunk> data_queue;  // queue used to pass the data between the two threads
std::condition_variable cond;

void data_preperation_thread()
{
	while (more_data_to_prepare())
	{
		data_chunk const data = prepare_data();
		{
			std::lock_guard<std::mutex> lk(mut);
			data_queue.push(data);
		}
		cond.notify_one();
	}
}

void data_processing_thread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(mut);
		cond.wait(lk, [] {return !data_queue.empty(); });
		data_chink data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		process(data);
		if (is_last_chunk(data)) break;
	}
}



int main()
{




}