#include <iostream>
#include <thread>
#include <mutex>
#include <list>
// if we share memory across multiple threads, we have to provide a valid locking mechanism, otherwise the resultant output is invalid
// invariants are statements that are always true for a particular data structure, e.g. for a list, the size variable contains the number of elemnets in the list, for a doubly linked list, the next pointer in node a should point to node b, and prev pointer in node b should point to a
// the most common problem of multithreaded applications is broken invariants while updating e.g. two threads try to delete the same node in a list, each thread sees the list different at different times, this could invalidate the whole data structure

// in concurrency, race condition is anything where the outcome is dependent on the relative ordering of execution of operations on two or more threads
// many times, this ordering wont matter
// but if the race condition results in broken data structures or broken invariants etc..., then we refer to such race conditions as problematic race conditions

// we can address problematic race conditions via mutexes
// a mutex class is a synchronization primitive that can be used to protect shared data from being simultaenously accessed by multiple threads, it provides mutual exclusivity to that data

//lets try this on a list, important to note that most if not all data structures in the STL are not thread safe at all, pushing an element to a list is not an atomic operation
// lets try this for adding a new node onto the head of a list, imagine two threads are trying to push vallues onto the head of a list simultaenously
// both threads create new nodes and point the next pointer to the current head of the list, in the end, only one change takes effect, the node from the other thread will be lost
// to avoid this, we are going to use the mutex class

// the mutex class has 3 member functions, lock, try_lock and unlock
// lock locks the mutex, blocks if the mutex is not available
// try_lock tries to lock the mutex, returns if the mutex is not available
// unlock unlocks the mutex

std::list<int> mylist;
std::mutex m; //create a mutex object

// as we have used the same mutex for both of the following functions, access to the functions will be mutually exclusive
// this means that even if multiple threads try to access these functions, only one thread will be allowed to succeed, as mutex provides the mutually exclusive access

void add_to_list(int const& x) {
	//m.lock();
	std::lock_guard<std::mutex> lg(m); // can also just use this lock guard object, valid for this scope
	mylist.push_front(x);
	//m.unlock;
}

void size() {
	m.lock(); // lock the mutex
	int size = mylist.size();
	m.unlock(); // unlock the mutex
	std::cout << "size of the list is " << size << std::endl;
}

int main() {
	std::thread thread1(add_to_list, 4); // both threads attempt to access the function, but only one will be able to succeed after acquiring the mutex lock, the other thread must wait until it is unlocked
	std::thread thread2(add_to_list, 11);

	thread1.join();
	thread2.join();


}
// the class lock_guard is a mutex wrapper that provides a convenient RAII-style mechanism for owning a mutex for the duration of a coped block
// when a lock_guard boject is created, it attempts to take ownership of the mutex it is given. When control leaves the scope in which the lock_guard object was created, the lock_guard is destructed and mutex is released
// lock_guard provides scope based RAII style protecteion for lock management

// when using mutexes, be careful when returing a pointer or reference to the protected area
// also when passing code to the protected data structure which you don't have direct control over
// make sure the code you're passing is thread safe
