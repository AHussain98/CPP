 # include <iostream>
# include <string>

 // in a swap() function, we can save time by exchanging data instead of copying, with move semantics, we can save time by moving data in and out of function calls
 // c++ by default uses value semantics, in which data is copied , this is in fucntion calls (by deafault, fucntion arguments are assed and returned by value) and in STL containers (which by default copy data into their elements)
 // value semantics avoids the need for a garbage collecteor, however it equires copying objects which increases execution time
 // c++11 introduced move semantics, this is an optimization over copying objects, if the source object is an rvalue, its data can be moved into the target instead of being copied
 // similar to moving files into a folder instead of copying them

 // in c++, an object can either be an lvalue or an rvalue
 // originally, an lvalue could appear on the left of an assignment, an rvalue could only appear on the right, x=2, x is lvalue and 2 is an rvalue (because we cannot say 2 equals something)
 // however, in modern c++, an lvalue represents a named memory location, it has a name, we can take its address using the & operator, since &x is legal, x is lvalue
 // anythinf else is an rvalue, 2 is an rvalue, 2 has no name, &2 is not legal, same with function return values
 // lvalues and rvalues can behave differently when we pass them as function arguments
 // lvalues can be passed by value and also by pointer/reference, rvalues can only be passed by value because we cannot take the address of an rvalue, we can however bind a const lvalure reference to an rvalue
 // pass by address/pointer and pass by non-const reference are used when the function wants to modify the argument, this makes no sense for rvalues, so it is not allowed

 // we can pass rvalues by const reference, this is a more efficient way to passing large objects by value e.g.

 /* int get() {return 2;} // function returning an int
 void func(const int&); // function taking int by const reference
 func(get()); //return value from get() is an rvalue, the rvalue is passed by const reference  */

 // in older c++, an argument is always copied by default :  void func(Type obj); //the func fucntion will make its own copy of obj
 // in c++11, the argument can be moved if obj is an rvalue and its Type is "moveable", this is true for all c++ library types apart from some
 // obj will be copied if obj is an lvalue or the type is not moveable (includes built-in types)
 // this provides compatibility with old code

 // a function argument can be an rvalue reference, the passed object will be moved into the argument if the object is an rvalue and its type is moveable otherwise the code does not compile
 // this allows us to overload the fucntion to bahve differently depending on whether or not the passed object is an lvalue or rvalue
 // if we want to pass an lvalue to a function which takes an rvalue reference, we have to cast it to rvalue. std::move() will cast its argument to rvalue

 // in summation, for each different type of argument of a fucntion() :
 // Lvalue: we can pass an lvalue, the function has a copy of the passed objects data, or we can pass a moveable rvalue, the function now owns the passed objects data e.g. func (int x); this takes lvalye and rvalues
 // Lvalue reference: we can pass an lvalue but not an rvalue, the function can modify the passed objects data through the reference e.g. func( int& x) cannot take rvalues
 // const Lvalue reference: we can pass an lvalue or an rvalue, the function cannot modify the passed objects data through the reference  e.g. func(const int& x) can accept both l and r values
 // Rvalue reference: we can pass a moveable rvalue, but not an lvalue, the function now owns the passed objects data e.g. func(int&& x); // can also pass an lvalue but we have to cats it to an rvalue using std::move()

 void func(int&& x){ // funcs argument is an rvalue reference, this tells teh compiler that the argument must be a moveable rvalue
     std::cout << x << std::endl;
 }
  void func(std::string&& x){ // funcs argument is an rvalue reference, this tells teh compiler that the argument must be a moveable rvalue, overloaded for string
     std::cout << x << std::endl;
 }

 void test(int x){
     std::cout << "from basic lvalue: " << x << std::endl;
 }
 void test1(const std::string& x) {
     std::cout << "from const lvalue reference " << x << std::endl;
 }

 int main() {

  // a reference to an lvalue is typically implemented as a pointer, the compiler adds code to dereference the pointer as needed
 int x;
 int& y = x; //this is the same as int * y = &x; the compiler just adds code to dereference the pointer as needed
 y=3;
 std::cout << x << std::endl;
 // this requires that x has a name and an address, therefore x must be an lvalue, this is known as an lvalue reference

// we cannot bind an lvalue reference to an rvalue unless the refrence is const
// int& a = 5; // error, not allowed
const int& b = 5; // allowed
// the compiler will add code which makes this appear to work like a const reference to an lvalue

// c++11 has the concept of an rvalue reference, this is a syntactic device which indicates that a function argument must be a moveable vallue, an rvalue reference has && after its type

  func(2);  // func takes rvalues and works
  //func(y); // wont't work, only takes rvalues
 func(std::move(y));  // this works because we have casted y into an rvalue
 // this has moved y's data into the function argument x, this should only be done if you don't want to keep the data in y, as its data has now been transferred to x
 // this should only be done if y's data is expendable, after calling func(std::move(y)), y's data may be empty or unusable, if we want to use y again we must reassign its data
 // this can be very useful when we're using variables we only need to copy from ro have n use after some time

test(2); // works, moveable rvalue is passed into the function taht takes lvalues
std::string&& s {"Asad"}; // a string object thats a rvalue reference
test1(s); // we can pass rvalue refrences via lvalue address function args, this is because s is a variable with a name and an address, so s is actually an lavlue, even if its declared as an rvalue reference

func(std::string {"Temp"});    // rvalue reference version used, this string doesnt have a name or address therefore qualifies as an rvalue
 }

 // lvalues represent persistent objects (they survive for more than one statement), these occupy memory which is accessible to the programmer, either on the stack or the heap
 // lvalues remain valid until they go out of scope or are deletes, they can take the shape of local varibales, gloabl variables, static variables and fucntion arguments

 // rvalues are stored in locations that are not accessible to the programmer, such as processor registers (which is why we can't take their address), they are temporary objects which generally are destroyed in the same statement in which they are created
 // rvalues can take the shape of literals such as 2 or 'c'

 // c++17 has three value categories, there are literals, temporary objects and lvalues
 // literals: these have no name and cannot be referred to again, they are called pure rvalues or prvalues
 // temporary objects: these represent an object and their data can be moved, they are known as xvalues (x for expriring )
 // lvalues

 // so rvalues can be either xvalues (temporary objects) or prvalues (literals)

 // lvalues and xvalues are objects, their dynamic type can be different from their static type
 // they are collectively known as generalized values or glvalues

 //