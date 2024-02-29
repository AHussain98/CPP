# include <iostream>
# include <thread>
# include <vector>
# include <string>
# include <mutex>
# include <list>
# include <algorithm>
# include <stack>
# include <memory>
# include <set>

class Team {
public:
	Team(std::string leader) : leader_(leader) {}
	auto& leader() const { return leader_; }  // const version of the leader function, auto will be const string&
	auto& leader() { return leader_; }  // normal version of the leader function, returns an object that may be mutates, auto is string&
private:
	std::string leader_;
};

// C++ programmers should leave memory handluing to containers and smart pointers, and not rely on manual memory handling
// std::shared_ptr is a smart pointer based on a reference counting algorithm that will leak memory if objects have cyclic dependencies
// minimising shared ownership makes the resultant code easier to use

// destruction of objects is deterministic in C++, we can know exactly when an object is being destroyed

// internally, a reference is a pointer that is not allowed to be null or repointed, therefore no copying is involved when passing it to a function

class bagel {
public:
	bagel(std::set<std::string> ts) : toppings_(ts) {}  // set copied into class
private:
	std::set<std::string> toppings_;
};


// arguments passed as references indicate that null values are not allowed
auto get_volume(const int rad)
{
	auto cube = std::pow(rad, 3.f);  // f makes it clear to compiler its a float and not a double
	auto pi = 3.14f;
	return (pi * 4.f / 3.f) * cube;
}

auto get_volume2(const int* rad)  // arguments passed by pointer can be checked to see if they're null
{
	auto s = rad ? *rad : 0;  // dereference is on the left
	auto cube = std::pow(s, 3);
	auto pi = 3.14f;
	return (pi * 4.f / 3.f) * cube;
}


// essential c++ techniques

// use auto often, improves readability
// remember that auto can include const aswell

// decltype(auto) can be used when we don't know the return type of a generic function

// use auto for local variables
auto i = 0;
// auto z = std::mutex{};

// c++17 introduced guaranteed copy elision, so auto x = foo{} is the same as foo x{}, there's no copying of a temporary object anymore
// auto is also useful because uninitialised auto variables cannot compile

/*
// all return ints
auto val() const // a) auto, deduced type
auto val() const -> int // b) auto, trailing type
int val() const // c) explicit type

// all return const int&
auto& cref() const // a) auto, deduced type
auto cref() const -> const int& // b) auto, trailing type
const int& cref() const // c) explicit type

// all return int&
auto& mref() // a) auto, deduced type
auto mref() -> int& // b) auto, trailing type
int& mref() // c) explicit type
*/


// a const reference, denoted by const auto&, has the ability to bind to anything. The original object cannot be mutated through such a reference
// const reference should be the default choice for objects that are potentially expensive to copy
// if the const reference is bound to a temporary object, the temporary object's lifetime will match the reference

void some_func(const std::string& a, const std::string& b)
{
	const auto& str = a + b;  // str will go out of scope at end of function, temporary object returned by a + b will be destroyed
}

// better to be explicit, use const auto& to denote a constant reference and use auto& to denote a mutable reference, which should only be used when you want to change an object

// auto&& or T&& is a forwarding referemce, also called a universial reference, it can bind to anything
/* It's important to note that auto&& and T&& are only forwarding
references if used in a function template where T is a template
parameter of that function template. Using the && syntax with
an explicit type, for example std::string&&, denotes an rvalue
reference and does not have the properties of a forwarding reference */

// by using the keyword const, we can inform the compiler about which objects are immutable. The compiler can then check that we don't try to mutate objects that aren't intended to be changed
// however, const initialised objects can still manipulate values that member functions point at

class Foo {
public:
	Foo(int* ptr) : ptr_(ptr) {}
	auto set_ptr_val(int v) const {
		*ptr_ = v;  // compiles despite function being declared as const!
	}
private:
	int* ptr_{};
};

// resource acquisition and the rule of 5
// one of the basic concepts in C++ is that a class should completely handle its resources
// this means when a class is copied, moved, copy assigned or move assigned or destructed, the class should make sure its resources are handled accordingly
// the necessity of implementing these 5 functions is called the rule of 5
// how the rule of 5 can be implemented in a class handling an allocated resource:

class Buffer {
public:
	Buffer(const std::initializer_list<float>& values) : size_{ values.size() } {
		ptr_ = new float[values.size()];
		std::copy(values.begin(), values.end(),ptr_);
	}
	auto begin() const { return ptr_; };
	auto end() const { return ptr_ + size_; };
private:
	size_t size_{ 0 };
	float* ptr_{ nullptr };
};

// in this class, the handled resource is a block of memory allocated in the constructor of the buffer class
// copy constructor
Buffer::Buffer(const Buffer& other) : size_(other.size_)
{
	ptr_ = new float[size_];
	std::copy(other.ptr_, other.ptr_ + size_, ptr_);
}

// copy assignment
Buffer& Buffer::operator=(const Buffer& other) {
	delete[] ptr_;  // delete whatever ptr is currently pointing at
	ptr_ = new float[other.size_];
	size_ = other.size_;
	std::copy(other.ptr_, other.ptr_ + other.size_, ptr_);
	return *this;
}

// destructor
Buffer::~Buffer()
{
	delete[] ptr_;  // it is still valid to delete a nullptr
	ptr_ = nullptr;
}

// although a correct implementation of these three functions is all that is required for a class to handle its internal resources, there are two issues
// 1. unnecessary copies, such as returning a Buffer from a function (the entire array would need to be copied)
// 2. Resources that cannot be copied, what if we had a unique_ptr for example, or an std::thread

// the solution is move semantics
// in addition to the copy-constructor and copy-assignment operator, we can add a move-constructor and move-assignment operator
// instead of taking const reference&, they must take rvalue references &&
// the && modifier indicates the parameter is an object we intend to move from instead of copying
// whereas the copy() function copies an object, the move equivalents move resources from one object to another, freeing the moved-from object from the resource

// move assignment and move constructor functions can be marked as noexcept, they won't work if they're not
// we can make these noexcept becaue they do not allocate memory or do something that may throw exceptions, unlike copy versions

// move constructor
Buffer::Buffer(Buffer&& other) noexcept : size_(other.size_), ptr_(other.ptr_)
{
	other.ptr_ = nullptr;
	other.size_ = 0;
}

// move assignment
Buffer& Buffer::operator=(Buffer&& other) noexcept {
	ptr_ = other.ptr_;
	size_ = other.size_;
	other.ptr_ = nullptr;
	other.size_ = 0;
	return *this;
}

// now when the compiler detects that we perform what seems to be a copy, such as returning a Buffer from a function, but the copied form isnt used anymore, it will utilise the no-throw move-constructor / move-assignkment operator instead of copying
// as the class has move semantics implemented explicitly, the compiler handles this automatically
/* Do not forget to mark your move-constructors and move-assignment 
operators as noexcept (unless they might throw an exception, of 
course). Not marking them noexcept prevents standard library 
containers and algorithms from utilizing them, instead resorting to 
using a regular copy/assignment under certain conditions. */

// the compiler is allowed to nove objects instead of copying when the object can be categorised as an rvalue.
// an rvalue is an object that is not tied to a named variable, either because its coming straight out of a function or because its been made an rvalue by using std::move()

// The object returned by make_buffer is not tied to a variable
// x = make_buffer(); // move-assigned
// The variable "x" is passed into std::move()
// y = std::move(x); // move-assigned

// lvalue corresponds to objects we can refer to by name in code
class Button {
public:
	Button(){} // if we only had this, we'd still generate all the below!
	Button(const Button&) = default;
	Button& operator=(const Button&) = default;
	Button(Button&&) noexcept = default;  // default implementations, remember to make the move constructor and move assignment operators noexcept
	Button& operator=(Button&&) noexcept = default;
	auto set_title(const std::string& s) { title_ = s; }
	auto set_title(std::string&& s) { title_ = std::move(s); }
	std::string title_;
	~Button() = default;  // remember to implement destructor for rule of 5
};

// we also need a free function returning a title and a Button variable
auto get_ok()
{
	return std::string("OK");
}

// as with the copy constructor and copy assignment, the move constructor and move assignment operator can be generated by the compiler
// we can simply force the compiler to default generate these with the default keyword

// if we do not declare any custom copy.move constructor/assignment or destructor, the move constructors and move assignment are created implicitly
// as soon as we add one of the 5 functions, this repevents the compiler from generating the others implicitly
// this does not apply for the default constructor, or parameterised constructor, compiler still generates the 5. Only of you create a custom version of one of the 5 will the others not be generated

// in practice, the cases where you have to write your own copy/move constructors, copy/move assignments and constructors should be very few
// writing classes so these special member functions don't need to be written explicitly or default declared is called the rule of zero
// This means that if a class in the application code base is required to have any of these functions written explicitly, that piece of code would probably be better off in the library part of your code base.

// writing an empty destructor can prevent the compiler from implementing certain optimisations, avoid this
// To summarize, use default destructors or no destructors at all in favor of empty destructors to squeeze a little bit more performance out of your application.

// as opposed to compound types, fundamental types such as int, float and bool are simply copied when moved, as they don't handle any resources
// when a simple type is mixed with a resource owning type, the move assignment becomes a mixture of move and copy
// an example of a class that will fail:
class Menu {
public:
	Menu(const std::initializer_list<std::string>& items) : items_(items)
	{}
	auto select(int i) { index_ = i; }
	auto selected_item() const { return index_ != -1 ? items_[index_] : ""; }
	Menu(Menu&& other) noexcept {
		std::swap(items_, other.items_);
		std::swap(index_, other.index_);
	}
	Menu& operator=(Menu&& other) noexcept {  // this way, the menu class can be safely moved while preserving the no-throw guarantee
		std::swap(items_, other.items_);
		std::swap(index_, other.index_);
		return *this;
	}
private:
	int index_{ -1 };  // initialise a private member like this with {}
	std::vector<std::string> items_;
};
// undefined behaviour if menu class is used like this:
//auto a = Menu{ "New", "Open", "Close", "Save" };
//a.select(2);
//auto b = std::move(a);
//auto selected = a.selected_item(); // crash

/* undefined behaviour happens as the items_ vector is moved and is therefore empty
the index_ on the other hand is copied and therefore still has value of 2 in the moved from object a
when selected_item() is called, the function will try to access items_ at index 2 and the program will crash
in these cases, the move constuctor/assignment operator is better off implemented as a std::swap*/


// in addition to being applied to objects, you can also add the && modifier to a member function of a class, just as you can apply the const modifier to a member function
// as with teh const modifier, a member function that has the && modifier will only be considered by overload resolution if the object is an rvalue

struct Foo {
	auto func() && {}
};
/*
auto a = Foo{};
a.func();  // does not compile, a is not rvalue
std::move(a).func();  // compiles
Foo{}.func(); // compiles
*/

// it may be tempting to use std::move() when returning a value from a function, like this
auto func() {
	auto f = Foo{};
	return std::move(f);  // don't, RVO is prevented
	// return f;  // this is fine, no copy made due to c++17 RVO guarantee
}
// however unless f is a move only type, we shouldn't be doing this
// this usage of std::move() prevents the compiler from using Return Value Optimisation (RVO) and theerby elides the copying of f, which is more efficient that moving it
// so when returning a newly created object by value, dont use std::move(), just return the object
// named objects being elided like this is called NRVO, RVO and NRVO are implemented by all major compilers

// pass by value when appropriate
// consider a function that converts an std::string to lowercase. In order to use the move-constructor where applicable, and the copy constructor otherwise, it may seem that two functions are required
// however by taking the std::string by value instead, we can write one function that covers both cases
auto str_to_lower(std::string s) -> std::string { // trailing return type
	for (auto& c : s) { c = std::tolower(c); }
	return s;
}
// this implementation of str_to_lower avoids unnecessary copying where possible
// when passed a regular varibles, the contents of str copy constructed into s prior to the function call, and then move assigned back to str when the function returns
auto str = std::string{ "ABC" };
//str = str_to_lower(str);  // str copy constructed into s, operated on, then move assigned to str

// when passed an rvalue, the content of str is move-constructed into s, operated on and then move assigned back to str
//str = str_to_lower(std::move(str)); // therefore no copy is made through the function call

// this technique is not applicable to all parameters and is not always optimal
// sometimes the pattern of accept by value and then move back will reduce performance
class widget {
	std::vector<int> data_{};
public:
	void set_data(std::vector<int> x) {
		data_ = std::move(x);
	}
};

// assume we call set_data and pass it an lvalue like:
auto v = std::vector<int>{ 1,2,3,4 };
widget w;
//w.set_data(v);  // pass an lvalue
// since we are passing a named object v, the code will copy construct a new std::vector object x, and then move assign that into the data_ member
// unless we pass an empty vector object to set_data(), the std::vector copy-constructor will perform a heap allocation for its internal buffer

// now compare this with the optimised version of set_data(), optimised for lvalues
//void set_data(const std::vector& vec) {
	//data_ = vec;  // reuse internal buffer of data_ if possible
//}
// here, there will nly be a heap allocation inside the assignment operator if the capacity of the current vector data_ is smaller than the source object, x
// in other words, the internal pre-allocated buffer of data_ can be reused in the assignment operator in many cases and save an extra heap allocation
// if we find it necessary to optimise set_data() for lvalues and rvalues, its better to provide two overloads
//void set_data(const std::vector<int>& x) {  // optimised for lvalues
//	data_ = x;
//}
//void set_data(std::vector<int>&& x) noexcept {  // optimised for rvalues
	//data_ = std::move(x);
//}

// finally when initialising class members in a constructor, we can safely use the pass-by-value-then-move pattern
// during the construction of a new object, there us no chance that there are pre-allocated buffers that could have been utilised to avoid heap allocations
// therefore we can copy the object into the constructor and move from the copy
class widget2 {
	std::vector<int> data_;
public:
	widget2(std::vector<int> vec) // vector copy constructed in
		: data_(std::move(vec)){}  // vector then moved into data_
};


int main()
{

	auto t = std::set<std::string>{};
	t.insert("salt");

	auto a = bagel(t);  // t is moved into a;

	t.insert("pepper");
	auto b = bagel(t);

	t.insert("oregano");
	for (auto& a : t) {
		std::cout << a << std::endl;
	}

	auto i = 0;
	//const auto foo = Foo(&i);
	//foo.set_ptr_val(42);  // this works because the pointer itself is not changing, it remains const. Only the value it points to is changing.
	// to prevent this, a wrapper called std::experimental::propagate_const has been added to the standard library which applies to pointers

	// without move semantics, the advantages of value based semantics would be lost since we'd have to perform redundant deep cloning operations with high performance costs and error prone swap operations

	// when copying an object handling a resource, a new resource needs to be allocated, and the resource from teh source object needs to be copied so that the two objects are completely seperated
	// allocation and copying are slow, and in many cases, teh source object is not needed anymore. The compiler can detect cases like this and can instead perform a move operation

	// with move semantics, the destintion object steals teh resource straight from the source object, and the source object is reset, its very similar to swapping except that the moved from object does not have to recieve the resources from the moved to object

	std::vector<int>* a_v = new std::vector<int>{ 1,2,3,4,5 };

	std::vector<int>* b_v = new std::vector<int>{ 5,6,7,8,9 };

	std::swap(a_v, b_v);  // now a points to b's vector and b to a's

	for (auto& i : *a_v) {
		std::cout << i << "\n";
	}

	auto c = std::move(a_v);  // resources from a_v are moved into c, vector pointed to by c is move constructed
	for (auto& i : *c) {
		std::cout << i << "\n";
	}

	// a is now reset, it's still in a valid state, and can potentially be reset but its up to us to implement this in the objects move constructor
	// moving objects only makes sense if the object owns a resource of some sort ( commonly heap allocated memory)
	// if all data is contained within the object itself rather than heap memory, its more efficient to just copy it

	Button b1;

	auto str = std::string("OK");
	b1.set_title(str);  // copy assigned
	b1.set_title(std::move(str));  // move assigned
	b1.set_title(get_ok());  // move assigned
	
	auto str2 = get_ok();
	b1.set_title(str2); // copy assigned

	const auto str3 = get_ok();
	b1.set_title(std::move(str3));  // copy assigned, even though std::move used to cast to rvalue, the move doesnt happen as the string is const, theerfore cannot be modified

	// as we can see, if the object has a name, its an lvalue and is copied, if it doesnt its an rvalue and is moved
	// std::move can be used to move an lvalue object but only if its not const



}