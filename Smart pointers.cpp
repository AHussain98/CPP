# include <iostream>
# include <memory>

// the traditional pointer was inherited from c, it is a built-in type
// a pointer varibable stores a binary data member which represents an address in memory
// pointers can represent the address of a stack variable, be used to manage memory allocated on the heap (new/delete) and implement polymorphism (base * pb = new derived);

// traditional pointers have their drawbacks:
// no concept of owneship: any code that uses a pointer can reassign it, overwrite it or invalidate it // no destructor, allocate memory can be released twice, or not at all

// from c++11, traditional pointers are very rarely needed:
// for working with stack memory, we can use references instead of pointers
// we can use std::vector instead of variable-size arrays
// we can use smart pointers for working with heap memory
// for dynamic binding (poymorphism), we can use smart pointers or references

// smart pointers are classes which encapsulate allocated memory:
// the class has a private data member which is a pointer to the memory
// the smart pointer object has ownership of the encapsulated memory
// the allocated memory can only be accessed through public member functions
// pointer arithmetic is not allowed

// smart pointers are implemented using RAII, the memory is allocated in the constructor and released in the destructor, this guarantees memory is released, even if an exception is thrown
// smart pointers save programmers a lot of work when coding and debugging

//  std::unique_ptr appeared in c++11, a unique_ptr object cannot be copied or assigned to, however the memory can be moved from one unique_ptr object to another
// if we want to transfer the memory allocation, we have to do it explicitly using std::move(), this makes clear that the source object is now invalid
// we cannot accidentally transfer the memory, code that tries to copy a unique_ptr will not compile

// std::shared_ptr also appeared in c++11
// a shared_ptr object can share its memory allocation with othe shared_ptr objects
// reference coutning is used to manage the memory, the memory is only released when the last object which is using it is destroyed
// similar to a garbage collected object in other languages
// shared_ptr has more overhead than unique_ptr and should only be used when extra features are needed

// in most situations, unique_ptr is the best replacement for traditional pointers which manage heap memory:
// it allocates heap memory in its constructor and has sole ownership of it
// it automatically releases the memory when it goes out of scope
// this allows heap-allocated memory to be used like a stack object
// unique_ptr has the usual advantage of smart pointers, the programmer does not need to manage the memory, the pointer to the memory cannot be overwritten, no issues with "shallow copying"
// unique_ptr is very lightweight, a unique_ptr object has no more overhead than a traditional pointer

// unique_ptr is defined in <memory>
// unique_ptr is a template class with a traditional pointer as its member
// the public member functions of the class implement some of the operations on traditional pointers
// its template parameter is the type of the pointed-to data e.g. std::unique_ptr<int> p;
// unique_ptr is a move only class, moving a unique_ptr transfers the allocated memory from one object to another

// code for a c netwroking api:
struct destination{// ...
};
struct connection{//...
};

// function to open a connection
connection connect(destination dest){
    std::cout << "connecting " << std::endl;
    connection conn;
    return conn;
}

// fucntion to close a connection
void disconnect (connection conn){
    std::cout << "disconnecting " << std::endl;
}

// end of code for c networking api

// custom deleter to close network connection
auto end_connection = [] (connection *conn) {disconnect(*conn);};

// get_data function
void get_data( const destination &d) {
    connection conn = connect(d);
    std::unique_ptr<connection, decltype(end_connection)> p(&conn, end_connection); // pass in the types for the stack pointer and deleter, then pass in the pointer and deleter into teh unique_ptr p's constructor
    throw std::out_of_range("Oops"); // make it throw an exception so we can test the deleter
    std::cout << "getting data ";
} // so now when p is deleted, it will call end_connection
// we use decltype for the typeof the lambda expression because we're not sure what the compiler will give it and its easier
// for the above smart pointer, end_connection will be called instead of the destructor


struct Point{
    int x;
    int y;
};

void func(std::unique_ptr<Point> upp){   // argument will be moved into upp, the variable on the stack will become empty
    std::cout << upp->x << ", " << upp->y << std::endl;
}

// make a function to return a unique_ptr object

std::unique_ptr<Point> point_ptr(int x, int y){
    Point p {x , y}; //create a Point object
    auto ptr{std::make_unique<Point>(p)}; // create a unique_ptr object to that Point object
    return ptr; // the allocated memory is transferred from p to the return object , we don't need to cast to an rvalue here because the compiler will always move a return value if possible
}


int main(){

// in c++11, we have to provide the pointer by calling new() explicitly
std::unique_ptr<int> p1 {new int(42)};  // allocated a single int with value 42, p1 now points to this int on the heap
// we can also create a fixed-size array on the heap and point to its first element
std::unique_ptr<int []> p2 {new int[6]}; // created an array of 6 elements on the heap, pointed at by p2
// though its usually better to use std::array or std::vector
// the only time we should use the unique_ptr generated array above is if we want a fixed size array on the heap, as std::array is allocaed on the stack and vectors are on the heap but not fixed size

// c++14 has make_unique which calls new() internally to accolate the memory and uses perfect forwarding to send its arguments to the constructor
auto p3 {std::make_unique<int> (42)}; //p3's member points to the int on the heap

std::cout << p2[0] << std::endl; // arrays can be indexed
std::cout << *p3 << std::endl;   // single objects can be dereferenced

// but we cannot do any pointer arithmetic, or make p1=p2, or make a copy of the pointers, unique_ptrs can only be moved
// std::unique_ptr<int> p4(p3); // doesnt compile, not allowed
// single objects cannot be index and arrays cannot be dereferenced

std::unique_ptr<int> p4 (std::move(p3)); // this works

// std::unique_ptr(int) p6 (std::move(p2)); // error, incompatible types

p1 = nullptr; // calls delete on the pointer member and sets the pointer to nullptr

// we can pass unique_ptr objects to functions using pass-by-move

auto p5 {std::make_unique<Point> (Point{5,7})}; // create a unique_ptr object
func(std::move(p5));  // cast to rvalue when you call it using std::move(), this forces the move constuctor to be called, not the copy constrctor

// remember that now the data has been moved, not copied, so accessing the ptr below will giev undefined behaviour (likely crashing the program)
//std::cout << p5->x;  // nothing there, pointer has been moved out of the object

// we can also return unique_ptr objects from functions, the object is moved into the functions return space
// this transfers ownership of the allocated memory
// the object is then moved again, into a variable in the caller

auto upp{point_ptr(3,6)};   // the unique pointer generated by teh fucntion is moved here and then moved again into upp


destination dest;
try {

get_data(dest);            // this works! the disconnect message appears before caught!
}
catch (...){
    std::cout << "caught!";
}
}