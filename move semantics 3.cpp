# include <iostream>

// to make a move-only class, implement teh move operators and make the copy operators deleted
// so for class test below, we can move test objects but not copy from them
class myClass{
};

class test{
    private:
        int i {0};
        myClass m;
    public:
        test() = default;
        test(const test& arg) = delete; // delete copy constructor, means that if the compiler tries calling them, itll produce an error
        test& operator= (const test* arg) = delete; // delete copy assignment operator


        test(test&& arg) noexcept : i(arg.i), m(std::move(arg.m)){ // we can copy teh built in members (i) as they are, but for the class object member m, we need to call t  hier move constructor, so we need to call thier rvalue as argument
        // because m has a name and an address, we need to convert it to an rvalue by putting it inside the call to move() and then this will cll the move constructor for the m object
        std::cout << "move constructor called" << std::endl; }

        test& operator= (test&& arg) noexcept{ // for moves, we take teh rvalue reference
        std::cout << "move assignment operator called" << std::endl; // move assignmnet operator
        if (this != &arg){ // self assignent check
          i = arg.i;   // move assignment operator called for the built in type and the object class type
          m = std::move(arg.m);  // force move assignment operator to be called
        }
        return *this; //return the modified object
    }
};

// c++ has some types that cannot be copied, but can be moved, fstream, iostream, multithreading classes, smart pointer classes, these types follow the raii idiom
// raii : only one object can be given resource instance at a time, the object acquires ownership of the resource in the constructor and relases ownership in the destructor
// the ownership of the resource can be transferred from one object to another using move semantics
// fstream has a file handle as a data member, the fstream constructor opens the file, the fstream destructor closes it, the fstream object cannot be copied but it can be moved
// the moved from object no longer owns the file handle, it has a null handle, the moved-to object beomes the owner of the handle, the file will be closed when the moved-to object is destroyed

//c++11 lambda expressions are not good at capturing move-only objects
// however, c++14 has generalized lambda capture, this means a variable in the outer scope can be moved into a lambda-local variable
/* e.g.   fstream fs("output.txt")
          [lfs = std::move(fs)] // now owned by lambda body's local variable lfs */
          // this allows capture by move, lfs is deduced as fstream, the move constructor is called to initalise lfs, it takes ownership of the file handle



int main(){

test test1; // call default constructor


      std::cout << "moving temporary: " << std::endl;
      test test3 = test(); // (this statement has actually been optimised out by the compiler)  call move constructor by using temporary object  (using default constructor)

      std::cout << "moving rvalue reference " << std::endl;
      test test4(std::move(test3)); // call move constructor by casting test3 to rvalue

      test test6;
      std::cout << "assigning from temporary" << std::endl;
      test6 = test();


}

// c++11 has two new special member fucntions, the move constructor and move assignment operator
// these are optimised versions of teh copy constructor and assignment operator
// they move their argument instead of copying it, they're automatically called when the argument is a moveable rvalue
//  the compiler will only synthesize a move operator if the class does not define a copy constructor, assignment operator or destructor, or every data member of the class is either a built in type, user defined type with move operators or a static data member (not moved)
// the synthesized move constructor will call the move constructor for each member
// the synthesized move assignment operator will call yhe move assignment operator for each member

// if a class defines a move operator, both the copy operators will be defined as deleted
// the class should define its own copy operators if it needs them
// otherwise the class will be move only

// so the rule of three for special member fucntions is now the rule of 5
// if a class needs to implement a destructor to function properly, then it probably needs to implement the copy and move operators aswell

// e.g. a class which allocates memory with "new" in its constructor needs:
// destructor to call delete when objects are destroyed
// copy constructor to perform a deep copy when copying
// assignment operator to call a deep copy when assigning
// move operators to set the arguments pointer to nullptr


// more guidance on special member functions:
/* if a class does not need to declare a destructor, it does not need to delcare cope or move operators either
for most classes, the rule of zero is sufficient, do not declare any special member functions, the compiler synthesized defaults will be sufficient
the compiler will also synthesize a default constructor unless we declare one ourselves, sometimes its useful to declare a default construtor to give member functions sensible values

if we need a destructor, e.g. to release memory, the compiler generated copy operators will not be correct
in this case, we need to provide our own destructor, copy constructor and copy assignment operator
we will probably need to provide a constructor to allocate memory
for performance, we should also add move operators, otherwise the copy operators will be used which won't reallocate memory or change file handle etc... properly

// sometimes we need to declare a destructor, but we do not want to copy the object e.g. a class which manages a network connection, the the destrcutor closes the connection, we do not want to create a duplicate of the connection
to make a class move only, we provide our own destructor, move constructor and move assignment operator
we will probably need to porvide a constructor aswell, to open the connection etc...
the compiler will synthesize the copy operators as deleted, for clarity, we can explicitly declare them as = delete

we can make a class that is immovable and uncopyable, objects of this class cannot be passed or returned to a function
to do this, delete the copy operators, the compiler will not synthesize the move operators
we can also declare a class that can only be copied and not moved, just make the move operators = delete

even though an operator is deleted, the compiler can still choose it as best match
for this reason, copy-only classes are not recommended, as the compiler can still decide to use the move operator if necessary
