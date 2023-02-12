#include <iostream>
// a pointer is a variable whose value is an address in memory, this can be on the stack or on the heap
// to create a pointer, we put a * after the type name
// to initalise a pointer variable to an address on the stack, we have to assign an address to it &
// heap memory alloacted using the new keyword followed by the type
//new returns the address at the start of the memory
// the new keyword calls teh default constructor for the class

// memory from the heap remains allocated to the program until it is released
// the operating system can restrict the amount of memory a program is allocated

// pointers created using new is on the stack, accessing memory on the heap
// stack pointers are destroyed once they go out of scope

// the delete operator releases the memory that was allocated by new
// delete ptr would have worked for the below
// this calls the destructor for the object in memory, then releases the memory
// the p pointer variable still exists but represents memory that is no longer accessible, it is a dangling pointer
//attempting to access p now will reuslt in undefined behaviour


// we can also allocate a block of memory and access it like it was an array
void badfunc() {
    int * ptr = new int {65}; //create a pointer on the stack to a heap address and initialise
    // if the function ends here, and we didnt delete ptr, and now the pointer has gone out of scope so we can't acces the memory
    //memory leak!
    delete ptr; //much better!
    return;
}

int main(){
    int * p1 = new int;  // undefined int memory
    //p1 points to memory allocated from the heap
    int * p2 = new int {65}; //we can also initialise memory using new

    int i{1}; //created i and initialised it
    int * p3 = &i; //create pointer p3 to point to i, on the stack
    std::cout << p3 << std::endl;
    std::cout << *p3 << std::endl;

    int * arrayptr = new int[5]{1,2,3,4,5}; // you can also initialse them with the list initialisation!
    // you have to initialise an array with a size
    //for (int i = 0; i <5; i++){   // arrayptr is then a pointer to the first element in this array
      //  arrayptr[i] = i;
         // fill in the array
   // }

    std::cout << arrayptr[0]; // we then use the pointer to access they array
    delete [] arrayptr; // this releases memory from the heap array
    // the arrayptr pointer variable will itself be deleted from the stack at the end of the program

    return 0; //0 means successful
}