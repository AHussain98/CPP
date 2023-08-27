// lets try creating a parallel implementation of the accumulate algorithm
# include <iostream>
# include <thread>
# include <vector>
# include <algorithm>
# include <numeric>
# include <functional>
# include <atomic>

#define MIN_BLOCK_SIZE 1000;  // define preprocessor directive


template <typename iterator, typename T>
void accumulate(iterator start, iterator end, T& ref) { // we take iterators to the beginning and end of the dataset and the initial value as an argument

// the reference here is not used as an inital value but as a data transfer mechanism
	ref = std::accumulate(start, end, 0);  // we are updating the value that exists at the ref memory location, we can then pass this between threads

}



template <typename iterator, typename T>
T parallel_accumulate(iterator start, iterator end, T& ref) { // we take iterators to the beginning and end of the dataset and the initial value as an argument

	// first lets find the number of elements in the dataset
	int input_size = std::distance(start, end);
	// divide input size by minimum block sie to get the number of data blocks
	int allowed_threads_by_elements = input_size / MIN_BLOCK_SIZE;
	int allowed_threads_by_hardware = std::thread::hardware_concurrency();

	int num_threads = std::min(allowed_threads_by_elements, allowed_threads_by_hardware);

	int block_size = (input_size + 1) / num_threads; // size of each block we pass to each thread

	// we need vectors to store the results of the threads and the threads themselves
	std::vector<T> results(num_threads);
	std::vector<std::thread> threads(num_threads - 1);

	iterator last;
	for (int i = 0; i < num_threads - 1; ++i) {
		last = start;
		std::advance(last, block_size);  // increment the last iterator by block size amount
		// now lets launch a new thread with these last and start iterators
		threads[i] = std::thread(accumulate<iterator, T>, start, last, std::ref(results[i]));
			start = last;

	}
	results[num_threads - 1] = std::accumulate(start, end, 0);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	return std::accumulate(results.begin(), results.end(), ref);
}


void run() {

	const int size = 8000;
	int* my_array = new int[size];
	int ref = 0;
	for (int i = 0; i < size; ++i) {
		my_array[i] = i;
	}
	int rer_val = parallel_accumulate<int*, int>(my_array, my_array + size, ref);
	std::cout << "Parallel accumulated value is: " << rer_val;

}

//std::atomic<int> i = 0; // code produces 123,  atomic integer is similar to normal integer variable but if one thread writes a value to it, that value will be visible to all other threads in this context
// Objects of atomic types are the only C++ objects that are free from data races; that is, if one thread writes to an atomic object while another thread reads from it, the behavior is well-defined.
//In addition, accesses to atomic objects may establish inter - thread synchronization and order non - atomic memory accesses as specified by std::memory_order.

// so if i is global (and atomic but just for safety), the 3 threads below produce increasing values of i

// however if i is made thread_local, each thread gets its own copy, and the increased value of i is not passed onto the next thread
thread_local std::atomic<int> i = 0; // now code produces 111
// thread_local means each thread gets its own distinct object

void foo() {
	++i;
	std::cout << i << std::endl;
}

int main() {

//	run();

	std::thread t1(foo);
	std::thread t2(foo);
	std::thread t3(foo);

	t1.join();
	t2.join();
	t3.join();



}

// when you declare a variable thread_local, then each thread is going to have its own distinct object
// the storage duration is the entire execution of the thread in which it was created, and the value stored in the object is initialised when the thread is started
