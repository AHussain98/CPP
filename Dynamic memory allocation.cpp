#include <iostream>
using namespace std;

int main() {
	int i = 10;
	int j = 10;
	int k = 10;
	int k1 = 10;
	int k3 = 10;
	int *p = &k3;
	int arr[100];

	//each of the above variables take up specific space in the memory, this is known as stack memory
	//previously, we weren't able to declare an array like int arr[n], because we neded to giveit an initial value
	//this was to compensate for the fact we didn't know how big i should be
	//the compiler doesn't know what n should be, it will take a random value whoch may not be sufficient
	//arr is also kept on the stack
	//there is also another memory area allocated by the operating system called the heap
	//The stack is the memory set aside as scratch space for a thread of execution. When a function is called, a block is reserved on the top of the stack for local variables and some bookkeeping data. When that function returns, the block becomes unused and can be used the next time a function is called. The stack is always reserved in a LIFO (last in first out) order; the most recently reserved block is always the next block to be freed. This makes it really simple to keep track of the stack; freeing a block from the stack is nothing more than adjusting one pointer.
	//The heap is memory set aside for dynamic allocation. Unlike the stack, there's no enforced pattern to the allocation and deallocation of blocks from the heap; you can allocate a block at any time and free it at any time. This makes it much more complex to keep track of which parts of the heap are allocated or free at any given time; there are many custom heap allocators available to tune heap performance for different usage patterns.
	//Each thread gets a stack, while there's typically only one heap for the application (although it isn't uncommon to have multiple heaps for different types of allocation).
// The OS allocates the stack for each system-level thread when the thread is created. Typically the OS is called by the language runtime to allocate the heap for the application.
//The stack is attached to a thread, so when the thread exits the stack is reclaimed. The heap is typically allocated at application startup by the runtime, and is reclaimed when the application (technically process) exits.
//The size of the stack is set when a thread is created. The size of the heap is set on application startup, but can grow as space is needed (the allocator requests more memory from the operating system).
//The stack is faster because the access pattern makes it trivial to allocate and deallocate memory from it (a pointer/integer is simply incremented or decremented), while the heap has much more complex bookkeeping involved in an allocation or deallocation.
//Also, each byte in the stack tends to be reused very frequently which means it tends to be mapped to the processor's cache, making it very fast. Another performance hit for the heap is that the heap, being mostly a global resource, typically has to be multi-threading safe, i.e. each allocation and deallocation needs to be - typically - synchronized with "all" other heap accesses in the program.

//heap memory accessed by using keyword new
int * p1 = new int;
//as soon as you write the above, an address on the stack is written, stored in p1 for a memory address on the heap
*p1 = 10; //p1 is stored on the stack, pointing to an address on the heap
cout << *p1 << endl;
//we can access the value stored on the heap by using *, as before
*p1 = *p1 + 1;
cout << *p1 << endl;


//so for an array, we can set a pointer in teh stack to an array on the heap of some undefined size
int *v = new int[5];
//so say for example, that n is 5, an array of size 5 is made on the heap
//for an array of an undefined size, there is no memory wastage unlike before when we had to explicitly declare a value of an array
cout << v << endl;
 //printing address on the heap
 // we can then access the values in the array via the pointer
 v[0] = 10;
 v[1] = 20;

 cout << v[1] << endl;

 //so we can then build up the array as before, with a dynamic size

 int n;
 cout << "enter size of dynamic array" << endl;
 cin >> n;

 int *f = new int[n];
 cout << "enter your array values" << '\n';
 for (int i = 0;i<n;i++) {
 	cin >> f[i] ;
 }

for (int i = 0;i<n;i++) {
	cout << f[i] << endl;
}
	//new array created on the heap, size taken dynamically
//importantly, the pointer is created and stored on the stack, pointing to the array on the heap
//we access the heap array via the stack pointer
//*(p+1) means p[1]


//imagine a function print(a,n) that takes arguments a and n, as soon as this function completes, the a and n created on the stack are deleted internally automatically
//however anything created with the new keyword is created on the heap, and will not be automatically destroyed once the program finishes running
//f has the address of the array on the heap. pointer f is on the stack, once the program finishes, pointer f will be deleted and the stack empties
//the array is still on the heap however, memory must be deleted from the heap when you don't need it, use the delete keyword to do this
//this is done by writing delete f; this deletes whatever is at the address stored in pointer f, this doesn't delete p1
//f will be deleted once int main() {} is finished

cout << "value of f before using delete: " << endl;
cout << * f << endl;

delete [] f; // this is how to delete an array from the heap, if f was just an int and not an array, this would be delete f;

//pointer f is still on the stack, this will exist until the main function finishes
cout << " f after: " << endl;
cout << * f << endl; // pointer still has an address, however it has a garbage value there due to teh deletion


int * test = new int [];
}