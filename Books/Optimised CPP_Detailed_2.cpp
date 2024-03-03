# include <iostream>
# include <cassert>
# include <string>
# include <vector>
# include <algorithm>
# include <list>
# include <functional>

// there are other elements of error handling that are important to consider before exceptions
// there are programming errors and runtime errors (recorverable and unrecoverable), stack overflowis an example of an unrecoverable runtime error
// when an unrecoverable error occurs, the program typically terminates immediately, so there is no point in signalling these types of error

// when designing and implementing an API, you should always reflect on what type of error you are dealing with
// deciding which errors are programming errors or runtime errors can be done by using a methodology called design by contract

// a contract is a set of rules between the caller of some function and the function itself (the callee)
// c++ allows us to explicitly specify some runes using the c++ type system:
// int func(float x, float y);
// it specifies that func() is returning an integer (unless it throws an exception) and the caller has to pass two floating-point values
// however it doesnt say anything about which floating point values are allowed
// there may be some required relationship between x and y that cannot easily be expressed in the type system
// when we talk about contracts in c++, we ususally refer to rules that exist between a caller and callee that cannot be easily expressed using the type system

// a precondition specifies the responsibilities of the caller of a function, there may be constraints on the parameters passed or if its a member fucntion, the object must be in a specific state before calling the function
// e.g. calling pop_back() on a vector, its the responsibility of the caller to ensure the vector is not empty when this happens

// a postcondition specifies the responsibilities of the function upon returning. If its a member function, in what state does the function leave the object?
// if its a member function, in what state does the functionleave the object, e.g. the std::list@::sort function postcondition is that the elements in the list are in order

// an invariant is a condition that must always hold true.
// a loop invariant is a condition that must be true at the beginning of every loop iteration
// a class invariant defines the valid states of the object, e.g. a vector size() must be less or equal to capacity()
// explicitly stating invariants around code can give us a better understanding of the code, they are also a tool that can be used when proving some algorithm does what its supposed to do

// a class invariant defines the valid states of an object
// it specifies the relationship between the data members inside a class
// an object can temporarily be in an invalid state during teh time a member function is executed
// the important thing is that the invariant is upheld whenever the function passes control to some other code that can observe the state of the object
// this can happen when the function returns, throws an exception, invokes a callback fucntion, calls some other function taht might observe the state of the currrently calling object (such as passing this to some other function)

// the class invariant is an implicit part of the precondition and postcondition for every member fucntion of a class
// if a member function leaves an object in an invalid state, the postcondition has been fulfilled
// similarly, due to precondition, the member fucntion can assume always that the object is in a valid state when the function is called
// the exception to this rule is the constructors and destructors of a class

class Widget {
	Widget(){ // initialise object and check invariants
	}
	~Widget(){ // check class invariants and destroy object
	}
	auto some_func() {// check precondition including invariants
	                  // do the work
	                  // check postcondition (including class invariants)
	}
};

// copy and move constructors left out but they should do same thing

// remember that explicitly creating a copy constructor, copy assignment or destructor will prevent implicit creation of the move constructor/assignnment

// when an object has been moved from, the object may be in some empty state
// this is also a valid state of teh object and is therefore part of the class invariant
// you cannot call pushback or size but you can call clear to reset the object to a useable state
// when using moved from objects, you should always implement classes so they moved from objects are reset to thier default state 

// to write meaningful class invariants, the class must have high cohesion and few possible states
// If you find it hard to define a class invariant, it's usually because your class has too many responsibilities and handles too many states.Therefore, defining class invariants usually means that you end up with well - designed classes

// contracts are part of the API that you design and implement, they're not built into c++ yet but there are some things we can do:
// use Boost.Contract
// Document the contracts (can be out of date and subject to change and not checked at runtime)
// static_assrt() and assrt() macro defined in <cassert>
// custom macro library

// two standard ways to assert in C++, static_assrt and assert()
// static_assert() is validated during compilation of the code and requires an expression that can be checked at compile time, failing this results in compilation error
// assert() is a runtime check that is active during debugging and testing but disabled when the program is built in release mode

#ifdef NDEBUG
#define assert(condition) ((void)0)
#else
#define assert(condition) /* implementation defined */
#endif
// this means we can remove all the asserts and the code checking the conditions by defining NDEBUG

// if we find a violation of a contract, we have found an error in our program
// if the error is that a precondition is not met in source code, this is a programming error
// on the other hand, if the postcondition cannot be met due to something outside our program, this is a runtime error
auto load_record(std::uint32_t id)
{
	assert(id != 0); // precondition
	//auto record = read(id);  // read from disk, may throw
	assert(record.is_valid());  // postcondition
	//return record;

}
/*  There is no bug in the source code, but the 
function cannot return the record found on disk because of some disk-related error. 
Since the postcondition cannot be fulfilled, a runtime error has to be reported back to 
the caller, unless the caller can recover from it itself by retrying and so on.*/

// don't write code that signals and handles bug sinto your code
// instead use asserts to make teh developer ware of issues in the code, you should only use exceptions or error coeds for recoverable runtime errors
// all the assumptions about your code are clearly handles by asserts
// assrts resuce performance at runtime but should not be use din the final version of the program

/* To summarize, programming errors should be detected when testing the program. 
There is no need to use exceptions or some other error handling mechanism for 
dealing with programming errors. Instead, a programming error should preferably 
log something meaningful and terminate the program to inform the programmer 
that the bug needs to be fixed. Following this guideline dramatically reduces the 
number of places we need to handle exceptions in our code. We will have better 
performance in our optimized build and hopefully fewer bugs since they have been 
detected by failed asserts. However, there are situations where errors can occur 
at runtime, and those errors need to be handled and recovered by the code we 
implement.*/

// if a fucntion cant uphold the postcondition, a runtime error has occured and needs to be signalled to some place in teh code that can handle it
/*
 For the signaling part we can choose between C++ exceptions, error codes,
returning a std::optional or std::pair, or using boost::outcome or
std::experimental::expected.
• Preserving the valid state of the program without leaking any resources.
Deterministic destructors and automatic storage duration are the tools that
make this possible in C++.
*/

// c++ was designed to be used with exceptions
// constructors that fail can only signal this via exceptions
/* A function that is guaranteed to not throw an exception can be 
marked as noexcept. It's important to understand that the compiler does not verify 
this; instead, it is up to the author of the code to figure out whether their function 
could throw an exception.
A function marked with noexcept makes it possible for the compiler to generate 
faster code in some cases. If an exception would be thrown from a function marked 
with noexcept, the program will call std::terminate() instead of unwinding the 
stack. The following code demonstrates how to mark a function as not throwing:
*/
auto add(int a, int b) noexcept {
	return a + b;
}

// always use const and noexcept where possible, we need to get asmch information to the compiler as possible

// exception safety guarantees mean when a fucntion is called, one of two thing smust happen
// either the function executes fully and returns or throws an exception and a complete rollback is performed and teh state of teh object should be excactly as it was before the function was called

void func(std::string& str)
{
//	str += f1();  // could throw
	//str += f2();  // could throw
}

// function appends f1 and f2 results to str
// if the exception was thrown after f1 called but before or during f2, the str would only append f1
// we want str untouched if an exception occurs
// this can be fixed by applying an idiom called copy and swap
// it means we perform the operations that might throw an exceptions on temporary copies before we et teh applications state be modified by non-throwing swap() function

void func2(std::string& str) {
	auto tmp = std::string(str);  // copy
	//tmp += f1();  // mutate copy
	//tmp += f2();
	std::swap(tmp, str); // swap never throws
}

// this same pattern can be used in member functions to preserve the valid state of an object

// lambdas can be stored in std::function object
// a lambda is a convientient way of constructing a function object

// external values can be caputured by teh lambdas by putting them in the []
auto count_value_above(const std::vector<int>& v, int x)
{
	auto is_above = [&x](int i) {return i > x; };  // x captured externally by erference
	return std::count_if(v.begin(), v.end(), is_above);
}

// we need to be careful about the lifetime of objects we capture by reference using the lambda, as we could at some point be referring to out of scope objects or objects that have been mutated

// lambda expressions generate function objects
// function objects are instances of a class that have the call operator() defined
// function objects are classes that consist of one member function, teh capture clause is a combination of the class's member variables and its constructor
// we can initialise member variables inside a lambda, these will only be visible within the lambda

auto some_func = [numbers = std::list<int>{ 4,2 }]() {  // no data type for numbers, notice we dont put types in capture clauses even when defining a new variable
	for (auto i : numbers) {
		std::cout << i << std::endl;
	}
};

//It's also possible to move an object inside a lambda, which is necessary when using 
//move - only types such as std::unique_ptr.Here is how it can be done :
//auto x = std::make_unique<int>();
//auto some_func = [x = std::move(x)]() {
//	// Use x here..
//};

// if we want to change any variable we've copied into the lambda or defined in it, we have to make the lambda mutable
// this is because the lambda function call operator is const by default, so to mutate the lambda object, such as when changing the member variables (not ferenced ones), we need to specify mutable

auto mut_lambda = [x = 5]() mutable {x++; std::cout << x << std::endl; };  // lambda identified as mutable, changes it member varibe

// we can capture all lambdas in scope by reference by using [&] or copying by using [=]
// we can also use [this] to capture the entire object by refernce or by copy using [*this] when declaring a lambda in a member function

class Foo {
public:
	auto member_function()
	{
		auto a = 0;
		auto b = 1.0f;
		// Capture all variables by copy 
		auto lambda_0 = [=]() { std::cout << a << b; };
		// Capture all variables by reference 
		auto lambda_1 = [&]() { std::cout << a << b; };
		// Capture object by reference 
		auto lambda_2 = [this]() { std::cout << m_; };  // can mutate m_ which is out of scope
		// Capture object by copy 
		auto lambda_3 = [*this]() { std::cout << m_; };  // copy of m_ which is out of scope
	}
private:
	int m_{};
	};


// Note that using [=] does not mean that all variables in the scope are copied into the lambda; only the variables actually used inside the lambda are copied.

// since c++20, lambdas without captures are default constructible and assignable
// decltype keyword allows us to construct different lambdas with te same type

auto lam = [] {};  // lambda without captures
auto lam2 = lam;  // assigned
decltype(lam2) lam3;  // lam3 created using type of lam2

// however this only applied to lambdas without captures, lambdas with captures have their own unique type
// even if two lambda functions with captures are plain clones of each other, they still have thier own unique type therefore its not possible to assign a lambda with captures to another

// lambdas with captures (stateful lambdas) cannot be assigned to each other since they have unique types even if they look the same
// To be able to store and pass around lambdas with captures, we cn use std::function to hold a function object constructed by a lambda expression

// an std::function returning bool and having int and string as parameters:
auto example_func = std::function<bool(int, std::string)>{};

// lambda functions sharing the same signature (parameters and return type) can be held by the same type of std::function objects, the std::function can also be assigned at runtime
// lambdas with and without captures can be assigned to the same std::function object

auto func4 = std::function<void(int)>{};  // empty std::function object

// std::function has performance losses compared to function objects created via lambdas directly
/*
When it comes to lambdas, the compiler has the ability to inline the function
call; that is, the overhead of the function call is eliminated. The flexible design
of std::function make it nearly impossible for the compiler to inline a function
wrapped in a std::function. The prevention of inline optimizations can have a
negative impact on the performance if small functions wrapped in std::function are
called very frequently.

If a std::function is assigned to a lambda with captured variables/references, the
std::function will, in most cases, use heap-allocated memory to store the captured
variables. Some implementations of std::function do not allocate additional
memory if the size of the captured variable is below some threshold.
This means that not only is there a performance penalty due to the extra dynamic
memory allocation, but also that it is slower, as heap-allocated memory can increase
the number of cache misses (read more about cache misses in Chapter 4, Data
Structures).

Calling a std::function is generally a bit slower than executing a lambda, as a little
more code is involved. For small and frequently called std::functions, this overhead
may become significant.

*/

// there are also generic lambdas in c++20
// only the parameters are template variables, not the captured variables

auto autolam = [](auto v) {return v + 1; };
auto templatelam = []<typename T>(T v) { return v + 1; };  // templated version of above

// this makes it possible to refer to the type of the parameter varible v within the lambda function














int main()
{

	// lambdas can be tied to variables or can be placed directly into expressions
	auto lam = [](int v) {return v > 3; };  // stateless lambdas, dont copy or reference any variables from outside the lambda
	std::vector<int> vec{ 1,2,3,4,5 };
	std::cout << std::count_if(vec.begin(), vec.end(), lam) << std::endl; // lambda passed in

	some_func();  // call the lambda

	func4 = [](int i) {std::cout << i; };  // assign the std::function to a lambda without capture
	func4(12);

	int num = 50;
	func4 = [num](int i) {std::cout << num + i; };  // reassign the std::function object to a lambda with a capture
	func4(75);
	// even though each stateful lambda has its own unique type, as long as they share the same signature, we can store them and pass them around in std::function objects
}