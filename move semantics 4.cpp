# include <iostream>

/* function arguments and move semantics:
pass by value: copy constructor called, function has its own copy of callers object, callers object is unmodified
pass by const reference: function has read only access to callers object, callers object is unmodified
pass by non-const reference and pass by address: function has full access to callers object and callers object may by modified
pass by move: move constructor called, function now owns the caller objects data, caller's object is now unusable unless reassigned

when passing an object to a function which will not modify it, the most efficient way is to:
pass an lvalue by const reference, this only copies once
pass an rvalue by rvalue reference, this only moves once

programmers cannot directly create a nested reference e.g. int& &x = y is a compiler error
however the compiler can do this internally for a type alias or a template parameter

rvalue references can also appear in nested references, the result is an rvalue reference only if they are both rvalue references
rvalue reference collapsing is an and operation

sofar, the && argument has always been a specific type, e.g. func(test&& x)
where they type of paramater x is a rvalue reference to a test object
x can only be bound to an rvalue, be it xvalue or prvalue

if we use a template argument instead of a specific type, && has completely different effects e.g.

template <class T>
func(T&& x);      // x is now a "forwarding" reference, it can be bound to an rvalue or an lvalue
when decucing the type of the argument for a forwarding reference, the compiler first examines the value category
if an lvalue is passed to func(), T is deduced as lvalue reference to test, reference collapsing is then applied (T is test& and x is T&& which collapes into test&
if an rvalue is passed to func(), T is kept as test, and x is T&&, so the reference is rvalue test&&


we've found that the two constructors below are the most efficient ways to implement constructors for lvalue and rvalues
now if we have many paramters, or even a variable number we'd have to write multiple different constructors,
with forwarding references, we only need to write the constructor once, the compiler will instantiate overloads as needed


a function that passes some or all of its arguments to another function is said to "forward" them
void f(int x){
g(x); }     // f() forwards the argument x to g()

with "perfect forwarding", the properties of the passed objects are preserved:
if x is midifiable in f(), it is modifiable in g()
if x is unmodifiable in f(), it is unmodifiable in g()
if x was moved into f()'s argument, it will be moved into g()'s argument

uses of perfect forwarding:
perfect forwarding is used to write functions which call constructors e.g. make_pair()
if a passed object into make_pair() is an rvalue, the more efficient move constructor will automatically be called
perfect forwardding is also used by variadic templates to dispatch their arguments to functions which process them

std::forward() casts its argument to rvalue reference
std::forward<T>(x)  equivalent tp static_cast<T&&>(x)
reference collapsing provides the required behaviour:
if x is of type T&, it will be left as an lvalue reference to T
if x is of type T or T&&, it will be cast to an ravlue reference to T
std::forward() does not cast its argument if it is an lvalue reference
std::forward<T>() requires a template parameter, std::move does not


*/
using int_ref = int&;
using rval_ref = int&&;


class test{
    public:
    test() = default; // default constructor

    test(const test& x){
        std::cout << "passed by lvalue reference!" << std::endl;
    }

    test(test&& x){
        std::cout << "passed by rvalue reference!" << std::endl;
    }

};

template< class T>
void func(T&& x){
    std::cout << "we can print this no matter what because the compilers smart !" << std::endl;
}

void g(test&& x){
    std::cout << "move version of g called" << std::endl;
}

template <class M>
void f(M&& x){
  //  g(std::forward<M>(x));
  g(x);
}

int main() {

    int i {0};
    int_ref j = i; // j is a reference to int
    int_ref& x = i; // x is a reference to (reference to int)
    // the type of the result is determined by reference collapsing, this type will collaps into reference to int

    rval_ref&& ri = 3; // rvalue reference to (rvalue reference to int), collapses into rvalue reference to int

     func(test());

     test t1;
     func(t1); // compiler executes the function regardless if its passed an rvalue reference or an lvalue
     // passing an lvalue collapses teh T&& to an lvalue reference to test
     // this reference collapsing only happens when we use templates
     func(std::move(t1));


     std::cout << "calling f() with lvalue argument" << std::endl;
     f(t1);

     const test t2;
     std::cout << "calling f() with const lvalue argument"  << std::endl;   // will decay into lvalue reference when forwarded
     f(t2);

     std::cout <<  "calling f() with rvalue argument" << std::endl;
     f(std::move(t1));


}