# include <iostream>
# include <memory>

// weak pointer is not a smart pointer
// weak pointers provide a safe way of aliasing a shared_ptr, this avoid the problems with traditional pointers which can dangle
// a weak_ptr is bound to a shared_ptr object, this does not affect the reference count
// the weak_ptr cannot access the shared memory directly, it has to be converted back to the shared_ptr
// this is only allowed if teh shared_ptr is still valid

// the lock() member function returns the shared_ptr if it is still valid, otherwise it returns nullptr
// alternatively we can copy the weak_ptr into a shared_ptr
// this will throw a std::bad_weak_ptr exception if valid
// to prevent a data race, lock() is implemented


int main(){

auto ptr{std::make_shared<int>(36)}; // create a shared pointer to an int of 36 on the heap, reference count is 1

// create weak_ptr alias to ptr
std::weak_ptr<int> wptr = ptr; // reference count is still 1

// release ptr's memory
ptr = nullptr; // ptr's reference count is 0

//wptr is an alias to ptr, is it still valid?

auto sp1 = wptr.lock();

if (sp1){
    std::cout << "valid!" << std::endl;   // not valid because we've released teh shared_ptrs memory
}

// weak pointers can be used in caches
// data stored in shared_ptr objects, cache can hold weak_ptrs to data
// use lock() to retrieve data, original data returned if not expired, otherwise need to fetch again

// weak pointers also prevent cycle prevention
}