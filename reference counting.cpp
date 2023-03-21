# include <iostream>
# include <memory>

// reference counting is a technique for allowing different objects to share the same resource, an integer is used to store the numer of objects which are sharing the resource
// this is known as a reference counter, initially the counter is 0, when an object is bound to the resrouce, the counter increases, and when an object is unbound, it decreases
// when there are no remaining bound objects, the counter is 0, the resource is now unbound

// lets try creating a fake string class and applying reference counting
// we need an integer to store the count, this must be visible to all the objects which bind to the shared memory
// we will allocate this integer on the heap
// the class will have a member which is a pointer to this integer
// the constructor allocates the counter, initally this has the value 0, as there are no objects bound
// we acquire the resource by allocating the shared memory
// we increment the counter, because there is now a bound object
// when an object is destroyed, it is no longer bound to the shared memory, we therefore decrement he counter
// if the counter is non-zero, there are still bound objects, we must not release the memory as it is still shared
// if the counter is 0, "this" is the only remaining bound object, we can and should release the memory as it is no longer shared

// when we copy-construct an object, the new object should have the same values as the argument, string s2(s1)
// s1 and s2 will share the memory allocation and counter, their pointers will have the same values, a shallow copy is good enough therefore
// the reference counter needs to be incremented, as a new object is bound to the shared memory

//  for assignment, we can also do a shallow copy and increment the counter, s1 = s2
// if s1 and s2 are bound to the same shared memory, this is sufficient
// if s1 and s2 are bound to different shared memory, first we must unbind s2 from its memory
// decrement s2's counter, if this beings s2's counter down to 0, we must release s2's shared memory
// check for self assignment before incrementing counter

// for the move operator, add a shallow copy of the counter pointer
// set the moved-from object's counter to null as well as the data pointer
// modify the rest of the code to check the counter before dereferencing it
// we do not increment the counter, a move operation does not change the number of references
// it just transfers the binding from one object to another

// std::shared_ptr was introduced in c++11, it uses reference counting
// this allows different shared_ptr objects to share a memory allocation
// when shared_ptr object is copied or assigned, there are no memory operations, the reference counter is incremented
// when one of the shared_ptr objects is destroyed, the counter is decremented
// when the last shared_ptr object is destroyed, the counter is equal to 0, the allocated memory is then released

// shared_ptr has a private data member which is a pointer to the allocated memory
// it has another private data member which is a pointer to its control block, the control block contains the reference counter

// shared_ptr is defined in <memory>
// to create a shared_ptr object, we can pass a pointer to its constructor, or call make_shared()
// we can also initialize a shared_ptr by moving a unique_ptr into it, this transfers the ownership of the unique_ptr's allocated memory
// can be useful when working with factory functions
// however, we cannot convert a shared_ptr to a unique_ptr

//  make_shared() performs a single allocation for the shared emory and the control block
// e.g. auto p1 {make_shared<int> (42)};

// if we call new() to allocate memory ourselves, the control block is allocated seperately, we need to make an extra call to new() and the shared memory and control block are probably not contiguous
// e.g. shared_ptr<int> p1 {new int(42)}; //less efficient, not reccomended

// when a shared_ptr is moved from, its memory allocation pointer is set to nullptr
// the value of its reference counter is unchanges, the target object takes the ownership of the memory allocation and control block

int main(){

std::shared_ptr<int> p1 {new int (42)}; // manual

auto p2 {std::make_shared<int>(42)}; // preferred method

std::cout << *p2 << std::endl;  // can be dereferenced

p1 = p2; //assigning is ok, shared pointer can be moved, assigned to and copied, but like unique_ptr, cannot perform pointer arithmetic

std::shared_ptr<int> p3(p2); // copying is ok

std::shared_ptr<int> p4 (std::move(p3)); // ok

}

// when different threads copy or assign shared_ptr objects which use the same control block, there is a data race
// this means there could be two shared_ptr objects which try to modify the reference counter concurrently
// to prevent this, the reference counter is atomic
// however, accesses to teh allocated memory must be protected by the programmer
// operations on atomic variables take much longer, even in non-threaded code

// unique_ptr has the same overhead as using a traditional pointer
// shared_ptr has more overhead, control block initialisation, the reference counter needs to be updated when copying, assigning or destroying an object
// a unique_ptr can be converted to a shared_ptr, but not vice versa
// only use a shared_ptr when needed

// shared pointers are useful where different objects need to have acces to the same area of heap memory
//a web browser where several tabs are displaying the same image, we can save memory by storing the image in a shared pointer, for example