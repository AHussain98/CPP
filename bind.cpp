# include <iostream>
# include <functional>
# include <string>

// c++11 defines std::bind in <functional>
// bind() takes a callable object as its first argument, bind() performs a partial function call
// it "binds" the remaining arguments to this object and returns a new callable

// so you can pass it a function and then the arguments you want to pass, and it will return that as a callable object
// we need to sat where these arguments will appear, we do this by using a placeholder argument such as _1 or _2
// so _1 is replaced by the first argument, _2 is replaced by second argument etc... until we pass in the argument we want to bind
// probably easier to do this as a lambda

// a callable object supports the () operator
// c++ provides several different callable objects, pointer to non-member function, functors, lambda expressions, objects returned from calling bind()
//  c++11 provides std::function in <functional>
// this class has a private member which stores a callable object, this can be any callable object which has a given signature
// this is a templated class, the objects signature is the parameter, it is implemented using inheritance
// std::function performs type erasure, the objecst original type cannot be recovered

// this can be useful because we can declare a function argument as type std::fucntion, this can be passed any kind of callable object
// we can also create a container whose elements are of type std::function, so this container could be populated with any type of callable object

// limitations of std::function: the function prototype must match the template parameter, does not support overloading
// runtime overhead, invoking the callable object involves indirection, similar overhead to a virtual function
// may perform a memory allocation, the std::function object has a fixed size, if the callable object is too large, it allocated the necessary memory on the ehap

// std::function should only be used when we need a polymorphic function object
// for storing a callable object in a variable, use auto
// the callable object retains its original type
// it will be called directly, without any runtime overhead

//we can define a pointer to a member function of a class
// member function pointers cannot be called directly, they must be explicitly dereferenced, this is why they're not callable objects
// to call a member function pointer, we first need an object
// we access the pointer as a member of the object, thwne we dereference it
// to do this we use the .* operator
// there is also a ->* operator, for pointers to objects

using namespace std::literals;

class test{
    public:
        void func(int a, const std::string& b) {
            std::cout << "func called with the arguments " << a << " and " << b <<std::endl; // create a functor
        }
};

int main(){
// define pfunc as a pointer to a member function of test
void (test::*pfunc) (int, const std::string&); // we need the extra parentheses

// make pfunc point to the member function
pfunc = &test::func; // the & is not optional

std::cout << "with test object: \n";
test t1;
(t1.*pfunc)(42, "HELLO"s);

std::cout << "through pointer to test: \n";
test *ptest = &t1;
(ptest->*pfunc)(42, "hello"s);

// member fucntion pointers are used to run member functions in their own thread, for runtime desicion making
// member function pointers allow you to choose which object is used, use bind() to bind the arguments to a member function call
// or use a placeholder for the caller to provide the object
// you can choose which member function is called by making a container of member function pointers and useing a switch/else statement to make the decision

}