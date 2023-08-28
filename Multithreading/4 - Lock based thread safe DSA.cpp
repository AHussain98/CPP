# include <iostream>
# include <algorithm>
# include <execution>  // used for parallel algorithms in the library
# include <vector>
# include <list>
# include <future>

// when implement data structures for concurrent access, our concerns are that invariants are upheld, race conditions and deadlocks are avoided and exception scenarios are handled
// we can implement a fully thread safe concurrent queue using a linked list

// parallel quick sort
template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {

	// make sure the size is correct, this is the recursive return condition
	if (input.size() < 2) {
		return input;
	}

	// select the pivot value, move the first element in the list to result list and take it as a pivot value
	std::list<T> result;
	result.splice(result.begin(), input, input.begin());  // splice transfers elements from one list to another, there's not copy or move operations, only the internal pointers of the list nodes are reappointed
	T pivot = *result.begin(); // pivot is the first value of the result

	// partition the input array
	auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });

	// move the lower part of the list to a seperate list so that we can make the recursive call
	std::list<T> lower_list;
	lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

	// now rearrange both parts of the list 
	auto new_lower(parallel_quick_sort(std::move(lower_list)));
	std::future<std::list<T>> new_upper_future(std::async(&parallel_quick_sort<T>, std::move(input)));  // the future object will hold the upper half of the recursive call

	result.splice(result.begin(), new_lower);
	result.splice(result.end(), new_upper_future.get());  // called get so we're waiting on the future
	return result;
}

// parallel for each algo

template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
	unsigned long const length = std::distance(first, last);
	if (!length) { return; }  // return condition of the recursive loop

	unsigned long const min_per_thread = 25;

	if (length < 2 * min_per_thread) { std::for_each(first, last, f); }
	else {
		Iterator const mid_point = first + length / 2;
		std::future<void> first_half = std::async(&parallel_for_each<Iterator, Func>, first, mid_point, f);  // do the first half asynchronously and store the result in this futures object
		parallel_for_each(mid_point, last, f); // do the second half using the current thread
		first_half.get();
	}
}

// packaged_task<> object is invoked, it calls the associated function or callable object
//and makes the future ready, with the return value stored as the associated data.This
//can be used as a building block for thread pools(see chapter 9) or other task management schemes, such as running each task on its own thread, or running them all
//sequentially on a particular background thread.If a large operation can be divided
//into self - contained sub - tasks, each of these can be wrapped in a std::packaged_
//task<> instance, and then that instance passed to the task scheduler or thread pool.
//This abstracts out the details of the tasks; the scheduler just deals with std::packaged
//_task<> instances rather than individual functions.

// parallel asynchronous find algo
template <typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match, std::atomic<bool>* done_flag) {

	try {
		unsigned long const length = std::distance(first, last);
		unsigned long const min_per_thread = 25;

		if (length < 2 * min_per_thread) {
			for (; (first != last) && done_flag; ++first) {
				if (*first == match) {
					*done_flag = true;
					return first;
				}
			}
			return last;
		}
		else {  // we only make the recursive call if the length is long enough
			Iterator const mid_point = first - length / 2;
			std::future<Iterator> async_result = std::async(&parallel_find<Iterator, MatchType>, mid_point, last, match, std::ref(done_flag));  // call the async function on the last half of the input
			
			Iterator const direct_result = parallel_find(first, mid_point, match, done_flag);

			return (direct_result == mid_point) ? async_result.get() : direct_result;
		}
	}
	catch (const std::exception&){
		*done_flag = true;
		throw;
	}
}

	// factors affecting the performance of concurrent code:
	// 
	// how many processors (oversubscription, excessive task switching) -> more processors means more opportunity for concurrency, we usually launch less threads than the number of cores
	// std::async has application level visibility of the number of threads launched from our application, it is preferable to launch threads from this for that reason
	// If multiple multithreaded applications are running in the machine, we need global visibility for launching threads
	// std::packaged_task<> ties a future to a function or callable object. When the std::

	// data contention and cache ping pong, two threads working on shared data can have their caches be slow to update in response to each others changes
	// 
	// false sharing -> multiple threads have to share the same cache line
	// 
	// closeness of data -> when data for a single thread is spread across memory, then that single thread has to load multiple cache lines for operations
	// at the extreme end, there will be more data in the cache that we don't care about than we do
	// 
	// division of array elements -> when calculating a matrix block with a single thread, its cheaper to calculate a square block than to calculate whole rows or columns



