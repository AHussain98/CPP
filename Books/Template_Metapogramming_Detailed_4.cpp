# include <iostream>
# include <string>
# include <vector>

// name binding is the process of finding the declaration of each name that is used within a template
// names within a template can be dependent or non-dependent
// dependent names  are names that depend on the type or value of a template parameter that can be a type, non - type, or template parameter
// names that dont depend on template parameters are called non-dependent

// name lookup is performed differently for dependent and non-dependent names:
// for dependent names, its performed at the point of template instantiation
// for non-dependent names, its performed at the point of the template definition

void handle(double value)
{
	std::cout << "Processing a double: " << value << std::endl;
}

template<typename T>
struct Processor   // template definition
{
	void run()
	{
		handle(42);  //  the name handle is not a dependent type of the template because it does not depend on any template parameter, so binding is done here at definition, it will call the double version of handle
	}
};

// handle must be a known function at this point and the double version is the only match

void handle(int value)  // even though this is a better fit for the call in run(), it will not be binded because binding has already occured at definition
{
	std::cout << "processing a int: " << value << std::endl;
}

// dependent names:
template <typename T>  // template definition
struct handler
{
	void handle(T value)
	{
		std::cout << "handler<T>: " << value << std::endl;
	}
};

template <typename T>
struct dependent_parser  // template definition
{
	void parse(T arg)
	{
		arg.handle(42);  // handle is a dependent name because arg is a template parameter, dependent names are looked up at the point of template instantiation so handle is not bound at this point
	}
};

template <>  
struct handler<int>  // template specialisation, this is a better match for the dependent name
{
	void handle(int value)
	{
		std::cout << "handler<int>: " << value << std::endl;
	}
};


// instantiation of a template happens in two phases:
// the first phase occurs at the point fo definition when the template syntax is checked and names are categorised as dependent or not dependent
// the second phase occurs at the point of instantiation when the template arguments are substituted for the template parameters. Name binding for dependent names occurs at this point 

/*
template <typename T>
struct base_parser
{
   void init()
   {
	  std::cout << "init\n";
   }
};

template <typename T>
struct parser : base_parser<T>
{
   void parse()
   {
	  init();        // error: identifier not found
	  std::cout << "parse\n";
   }
};

int main()
{
   parser<int> p;
   p.parse();
}
In this snippet, we have two class templates: base_parser, which contains a public
method called init, and parser, which derives from base_parser and contains a
public method called parse. The parse member function calls a function called init
and the intention is that it’s the base-class method init that is invoked here. However,
the compiler will issue an error, because it’s not able to find init. The reason this
happens is that init is a non-dependent name (as it does not depend on a template
parameter). Therefore, it must be known at the point of the definition of the parser
template. Although a base_parser<T>::init exists, the compiler cannot assume
it’s what we want to call because the primary template base_parser can be later
specialized and init can be defined as something else (such as a type, or a variable,
or another function, or it may be missing entirely). Therefore, name lookup does not
happen in the base class, only on its enclosing scope, and there is no function called
init in parser.
This problem can be fixed by making init a dependent name. This can be done either by
prefixing with this-> or with base_parser<T>::. By turning init into a dependent
name, its name binding is moved from the point of template definition to the point of
template instantiation. In the following snippet, this problem is solved by invoking init
through the this pointer:

template <typename T>
struct parser : base_parser<T>
{
   void parse()
   {
	  this->init();        // OK
	  std::cout << "parse\n";
   }
}

*/


// remember that non dependent names don't get looked up in the base class, only in the enclosing scope

// dependent types can be functions, member functions or types


/*
In the examples seen so far, the dependent name was a function or a member function.
However, there are cases when a dependent name is a type. This is demonstrated with the
following example:

template <typename T>
struct base_parser
{
   using value_type = T;
};

template <typename T>
struct parser : base_parser<T>
{
   void parse()
   {
	  value_type v{};                       // [1] error
	  // or
	  base_parser<T>::value_type v{};       // [2] error
	  std::cout << "parse\n";
   }
};

In this snippet, base_parser is a class template that defines a type alias for T called
value_type. The parser class template, which derives from base_parser, needs
to use this type within its parse method. However, both value_type and base_
parser<T>::value_type do not work, and the compiler is issuing an error. value_
type does not work because it’s a non-dependent name and therefore it will not be
looked up in the base class, only in the enclosing scope. base_parser<T>::value_
type does not work either because the compiler cannot assume this is actually a type.
A specialization of base_parser may follow and value_type could be defined as
something else than a type.

In order to fix this problem, we need to tell the compiler the name refers to a type.
Otherwise, by default, the compiler assumes it’s not a type. This is done with the
typename keyword, at the point of definition, shown as follows:
template <typename T>
struct parser : base_parser<T>
{
   void parse()
   {
	  typename base_parser<T>::value_type v{}; // [3] OK
	  std::cout << "parse\n";
   }
};


*/



// dependent template names
// the dependent name can also be a template, such as a function or class template. The default behviour of the compiler is to interpret the dependent name as a non-type
// this can cause errors concerning the usage of the comparison operator <
/*

template <typename T>
struct base_parser
{
   template <typename U>  // templated function
   void init()
   {
	  std::cout << "init\n";
   }
};

template <typename T>
struct parser : base_parser<T>
{
   void parse()
   {
	  // base_parser<T>::init<int>();        // [1] error
	  base_parser<T>::template init<int>();  // [2] OK
	  std::cout << "parse\n";
   }
};

This is similar to the previous snippets, but the init function in base_parser is also
a template. The attempt to call it using the base_parser<T>::init<int>() syntax,
as seen at point [1], results in a compiler error because the compiler interprets the dependent name as non-type by default. Therefore, we must use the template
keyword to tell the compiler the dependent name is a template. This is done as shown at point [2].

Keep in mind that the template keyword can only follow the scope resolution operator
(::), member access through pointer (->), and the member access (.). Examples of
correct usage are X::template foo<T>(), this->template foo<T>(), and obj.template foo<T>().

The dependent name does not have to be a function template. It can also be a class
template, shown as follows:

template <typename T>
struct base_parser
{
   template <typename U>
   struct token {};
};

template <typename T>
struct parser : base_parser<T>
{
   void parse()
   {
	  using token_type =  base_parser<T>::template token<int>; // [1]
	  token_type t1{};
	  typename base_parser<T>::template token<int> t2{};
													 // [2]
	  std::cout << "parse\n";
   }
};
The token class is an inner class template of the base_parser class template. It can
be either used as in the line marked with [1], where a type alias is defined (which is
then used to instantiate an object) or as at line [2], where it is used directly to declare
a variable. Notice that the typename keyword is not necessary at [1], where the using
declaration indicates we are dealing with a type, but is required at [2] because the
compiler would otherwise assume it’s a non-type name.
The use of the typename and template keywords is not required in some contexts
of the current template instantiation being observed. 

*/


// template recursion
// calculate factorial at compile time using function template

template <unsigned int n>
constexpr unsigned int factorial()
{
	return n * factorial<n - 1>();
}

template <>
constexpr unsigned int factorial<1>() {return 1; }

template <>
constexpr unsigned int factorial<0>() { return 1; }


// we have a primary template that calls the factorial function template recursively, with two full specialisations for values 1 and 0

// function template argument deduction
// the compiler can sometimes deduce the template arguments from the context of the function call, so we can avoid specifying them
// when the compiler tries to deduce the template arguments, it performs the matching of the types of the template parameterswith the types of the arguments used to invoke the function
// the compiler can match:
// • Types (both cv-qualified and non-qualified) of the form T, T const, T volatile:
// • Pointers (T*), l-value references (T&), and r-value references (T&&):
// • Arrays such as T[5], or C[5][n], where C is a class type and n is a non-type 
//  etc

/*
refresher on pass by address
What is a Pointer?
A pointer is a variable that stores a memory address.  Pointers are used to store the addresses of other variables or memory items.  Pointers are very useful for another type of parameter passing, usually referred to as Pass By Address.  Pointers are essential for dynamic memory allocation.
Declaring pointers:
Pointer declarations use the * operator.  They follow this format:
  typeName * variableName;

 int n;        // declaration of a variable n
 int * p;      // declaration of a pointer, called p
In the example above, p is a pointer, and its type will be specifically be referred to as "pointer to int", because it stores the address of an integer variable.

Note:  Sometimes the notation is confusing, because different textbooks place the * differently.  The three following declarations are equivalent:

 int *p;
 int* p;
 int * p;
All three of these declare the variable p as a pointer to an int.

De-referencing pointers:
Once a pointer is declared, you can refer to the thing it points to by "dereferencing the pointer".
 int * p;
Now that p is declared as a pointer to an int, the variable p stores the address.  To dereference the pointer, use the * operator:

 cout << p;        // this will print out the address stored in p
 cout << *p;       // this will print out the data being pointed to
The notation *p now refers to the target of the pointer p.

Note:  The notation can be a little confusing. If you see the * in a declaration statement, a pointer is being declared for the first time. AFTER that, when you see the * on the pointer name, you are dereferencing the pointer to get to the target.

Pointers don't always have valid targets. If the pointer is storing a 0, for instance, this is known as the NULL pointer.  It never has a valid target.  If you try to dereference a pointer that does not have a valid target, your program will experience an error called a "segmentation fault" and will probably crash.  The null pointer is the only literal number you may assign to a pointer, since it is often used to initialize pointers or to be used as a signal. You may NOT assign arbitrary numbers to pointer variables:

 int * p = 0;    // okay.  assignment of null pointer to p
 int * q;
 q = 0;          // okay.  null pointer again.
 int * z;
 z = 900;        // BAD!  cannot assign other literals to pointers!
Pointer types:
Although all pointers are addresses (and therefore represented similarly in data storage), we want the type of the pointer to indicate what is being pointed to.  Therefore, C++ treats pointers to different types AS different types themselves.
 int * ip;
 char * cp;
 double * dp;
These three pointer variables (ip, dp, cp) are all considered to have different types, so assignment between any of them is illegal.  The automatic type coercions that work on regular numerical data types do not apply:

 ip = dp;        // ILLEGAL
 dp = cp;        // ILLEGAL
 ip = cp;        // ILLEGAL
As with other data types, you can always force a coercion by re-casting the data type.  Be careful that you know what you are doing, though, if you do this!

 ip = static_cast<int *>(dp);
The "address of" operator:
There is another use of the & operator.  We saw that when it is used in a declaration, it creates a reference variable. When the & is used in regular statements (not reference declarations), the operator means "address of". Example:
 int n;
 cout << &n;    // this prints out &n, the "address of n".
This operator is useful in attaching pointers to data items! Consider the following:

 int n;        // integer
 int * p;      // pointer to an integer
At this point, we don't know what p is pointing to. It might not even be pointing to a valid target at the moment! It contains some random value from memory right now, because we haven't initialized it. However, we can point p at n by using the & operator.

 p = &n;        // assigns the "address of n" to the pointer p

Pass By Address:
We've seen Pass By Value and Pass By Reference.  
If you declare a formal parameter of a function as a pointer type, you are passing that parameter by its address.  
The pointer is copied, but not the data it points to.  
So, Pass By Address offers another method of allowing us to change the original argument of a function (like with Pass By Reference).  
Don't pass in the argument itself -- just pass in its address.
Example:

 void SquareByAddress(int * n)
 {  *n = (*n) * (*n);  }

 int main()
 {
   int num = 4;
   cout << "Original = " << num << '\n';
   SquareByAddress(&num);
   cout << "New value = " << num << '\n';
 }


*/


// c++17 standard introduced class template argument deduction

/*
The way template argument deduction works for class templates is different than for
function templates but it relies on the latter. When encountering the name of a class
template in a variable declaration or function-style cast, the compiler proceeds to build
a set of so-called deduction guides.

There are fictional function templates representing constructor signatures of a fictional
class type. Users can also provide deduction guides and these are added to the list
of compiler-generated guides. If overload resolution fails on the constructed set of
fictional function templates (the return type is not part of the matching process since
these functions represent constructors), then the program is ill-formed and an error is
generated. Otherwise, the return type of the selected function template specialization
becomes the deduced class template specialization

To understand this better, let’s see how the deduction guides actually look. In the following
snippet, you can see some of the guides generated by the compiler for the std::pair
class. The actual list is longer and, for brevity, only some are presented here:
template <typename T1, typename T2>
std::pair<T1, T2> F();
template <typename T1, typename T2>
std::pair<T1, T2> F(T1 const& x, T2 const& y);
template <typename T1, typename T2, typename U1,
	typename U2>
std::pair<T1, T2> F(U1&& x, U2&& y);
This set of implicitly deduced guides is generated from the constructors of the class
template. This includes the default constructor, the copy constructor, the move
constructor, and all the conversion constructors, with the arguments copied in the exact
order. If the constructor is explicit, then so is the deduction guide. However, if the class
template does not have any user-defined constructor, a deduction guide is created for
a hypothetical default constructor. A deduction guide for a hypothetical copy constructor
is always created.

User-defined deduction guides can be provided in the source code. The syntax is similar
to that of functions with a trailing return type but without the auto keyword. Deduction
guides can be either functions or function templates. What is important to keep in mind
is that these must be provided in the same namespace as the class template they apply to.
Therefore, if we were to add a user-defined deduction guide for the std::pair class,
it must be done in the std namespace. An example is shown here:
namespace std
{
   template <typename T1, typename T2>
   pair(T1&& v1, T2&& v2) -> pair<T1, T2>;
}
The deduction guides shown so far were all function templates. But as mentioned
earlier, they don’t have to be function templates. They can be regular functions too.
To demonstrate this, let’s consider the following example:
std::pair  p1{1, "one"};    // std::pair<int, const char*>
std::pair  p2{"two", 2};    // std::pair<const char*, int>
std::pair  p3{"3", "three"};
					// std::pair<const char*, const char*>
With the compiler-degenerated deduction guides for the std::pair class, the deduced
types are std::pair<int, const char*> for p1, std::pair<const char*,
int> for p2, and std::pair<const char*, const char*> for p3. In other
words, the type deduced by the compiler where literal strings are used is const char*
(as one should expect). We could tell the compiler to deduce std::string instead of
const char* by providing several user-defined deduction guides. These are shown in
the following listing:
namespace std
{
   template <typename T>
   pair(T&&, char const*) -> pair<T, std::string>;
   template <typename T>
   pair(char const*, T&&) -> pair<std::string, T>;
Class template argument deduction 159
   pair(char const*, char const*) ->
	  pair<std::string, std::string>;
}
Notice that the first two are function templates, but the third one is a regular function.
Having these guides available, the deduced types for p1, p2, and p3 from the previous
example are std::pair<int, std::string>, std::pair<std::string,
int> and std::pair<std::string, std::string> respectively.

Class template argument deduction only works if no template arguments are provided.

Class template argument deduction may not always produce the expected results. Let’s
consider the following example:
std::vector v1{ 42 };
std::vector v2{ v1, v1 };
std::vector v3{ v1 };
The deduced type for v1 is std::vector<int> and the deduced type for v2 is
std::vector<std::vector<int>>. However, what should the compiler deduce
for the type of v3? There are two options: std::vector<std::vector<int>> and
std::vector<int>. If your expectation is the former, you will be disappointed to learn
that the compiler actually deduces the latter. This is because deduction depends on both
the number of arguments and their type.
When the number of arguments is greater than one, it will use the constructor
that takes an initializer list. For the v2 variable, that is std::initializer_
list<std::vector<int>>. When the number of arguments is one, then the type
of the arguments is considered. If the type of the argument is a (specialization of)
std::vector – considering this explicit case – then the copy-constructor is used and
the deduced type is the declared type of the argument. This is the case of variable v3,
where the deduced type is std::vector<int>. Otherwise, the constructor that takes
an initializer list (with a single element) is used, as in the case of variable v1, for which the
deduced type is std::vector<int>.

*/


// forwarding references
//  lvalues are values that refer to a memory location and, therefore, we can take their address with the& operator. lvalues can appear both on the leftand right sides of an assignment expression.
// rvalues are values that are not lvalues. They are defined by exclusion. rvalues do not refer to a memory location and you can’t take their address with the& operator. rvalues are literalsand temporary objectsand can only appear on the right side of an assignment expression.

// references are aliases to existing objects or functions
// lvalue references such as &x are references to lvalues
// rvalue references such as &&x are references to rvalues

// non-const references may only be bound to lvalues
// lvalues cannot be bound to rvalue references

// one purpose of rvalue references is to enable move semantics
// another is to enable perfect forwarding

/*
void g(foo& v)  { std::cout << "g(foo&)\n"; }
void g(foo&& v) { std::cout << "g(foo&&)\n"; }
void h(foo& v)  { g(v); }
void h(foo&& v) { g(v); }
In this snippet, the implementation of g is identical to the one seen earlier. However, h
also has two overloads, one that takes an lvalue reference and calls g and another one that
takes an rvalue reference and also calls g. In other words, the function h is just forwarding
the argument to g. Now, let’s consider the following calls:
foo x{ 42 };
h(x);          // g(foo&)
h(foo{ 42 });  // g(foo&)
From this, you would expect that the call h(x) will result in a call to the g overload taking
an lvalue reference and the call to h(foo{42}) will result in a call to the g overload
taking an rvalue reference. However, in fact, both of them will call the first overload of g,
therefore printing g(foo&) to the console. The explanation is actually simple once you
understand how references work: in the context h(foo&& v), the parameter v is actually
an lvalue (it has a name and you can take its address) so calling g with it invokes the
overload that takes an lvalue reference. To make it work as intended, we need to change
the implementation of the h functions as follows:

void h(foo& v)  { g(std::forward<foo&>(v)); }
void h(foo&& v) { g(std::forward<foo&&>(v)); }

The std::forward is a function that enables the correct forwarding of values. What the
function does is as follows:
• If the argument is an lvalue reference, then the function behaves just as a call to
std::move (changing the semantics from an lvalue to an rvalue).
• If the argument is an rvalue reference, then it does nothing.
*/

/*
in templates, rvalue references work slightly differently, and sometimes they are
rvalue references, but other times they are actually lvalue references.
References that exhibit this behavior are called forwarding references. However, they are
often referred to as universal references. This was a term coined by Scott Meyers shortly
after C++11 when there was no term in the standard for this type of reference. In order to
address this shortcoming, and because it didn’t feel the term universal references properly
described their semantics, the C++ standard committee called these forwarding references
in C++14. Yet, both terms are equally present in literature. For the sake of being true to
the standard terminology, we’ll call them forwarding references in this book


To begin the discussion on forwarding references, let’s consider the following overloaded
function templates and class templates:

template <typename T>
void f(T&& arg)               // forwarding reference
{ std::cout << "f(T&&)\n"; }

template <typename T>
void f(T const&& arg)         // rvalue reference
{ std::cout << "f(T const&&)\n"; }

template <typename T>
void f(std::vector<T>&& arg)  // rvalue reference
{ std::cout << "f(vector<T>&&)\n"; }

template <typename T>
struct S
{
   void f(T&& arg)            // rvalue reference
   { std::cout << "S.f(T&&)\n"; }
};

We can make calls to these functions as follows:
int x = 42;
f(x);                   // [1] f(T&&)
Forwarding references 167
f(42);                  // [2] f(T&&)
int const cx = 100;
f(cx);                  // [3] f(T&&)
f(std::move(cx));       // [4] f(T const&&)
std::vector<int> v{ 42 };
f(v);                   // [5] f(T&&)
f(std::vector<int>{42});// [6] f(vector<T>&&)
S<int> s;
s.f(x);                 // [7] error
s.f(42);                // [8] S.f(T&&)

From this snippet, we can notice that:
• Calling f with an lvalue or rvalue at [1] and [2] resolves to the first overload,
f(T&&).

• Calling f with a constant lvalue at [3] also resolves to the first overload, but calling
f with a constant rvalue at [4] resolves to the second overload, f(T const&&),
because it’s a better match.

• Calling f with an lvalue std::vector object at [5] resolves to the first overload,
but calling f with an rvalue std::vector object at [6] resolves to the third
overload, f(vector<T>&&), because it’s a better match.

• Calling S::f with an lvalue at [7] is an error because lvalues cannot be bound to
rvalue references, but calling it with an rvalue at [8] is correct.

All the f function overloads in this example take an rvalue reference. However, the &&
in the first overload does not necessarily mean an rvalue reference. It means an rvalue
reference if an rvalue was passed or an lvalue reference if an lvalue was passed. Such a
reference is called a forwarding reference. However, forwarding references are only present
in the context of an rvalue reference to a template parameter. It has to have the form T&&
and nothing else. T const&& or std::vector<T>&& are not forwarding references,
but normal rvalue references. Similarly, the T&& in the f function member of the class
template S is also an rvalue reference because f is not a template but a non-template
member function of a class template, so this rule for forwarding references does not apply

forwarding references are made possible by reference collapsing
Prior to C++11, it was not possible to take a reference to a reference. However, that is now
possible in C++11 for typedefs and templates. Here is an example:
using lrefint = int&;
using rrefint = int&&;
int x = 42;
lrefint&  r1 = x; // type of r1 is int&
lrefint&& r2 = x; // type of r2 is int&
rrefint&  r3 = x; // type of r3 is int&
rrefint&& r4 = 1; // type of r4 is int&&

The rule is pretty simple: an rvalue reference to an rvalue reference collapses to an rvalue
reference; all other combinations collapse to an lvalue reference

any other combinations do not involve reference collapsing rules 

Forwarding references work not only for templates but also with auto deduction rules.
When auto&& is found, it means a forwarding reference. The same does not apply for
anything else, such as cv-qualified forms like auto const&&. Here are some examples:
int x = 42;
auto&& rx = x;          // [1] int&
auto&& rc = 42;         // [2] int&&
auto const&& rcx = x;   // [3] error
std::vector<int> v{ 42 };
auto&& rv = v[0];       // [4] int&
In the first two examples, rx and rc are both forwarding references and are bound to
an lvalue and an rvalue respectively. However, rcx is an rvalue reference because auto
const&& does not denote a forwarding reference. Therefore, trying to bind it to an lvalue
is an error. Similarly, rv is a forwarding reference and is bound to an lvalue.

the purpose of forwarding or universal references is perfect forwarding

We have seen the concept of perfect forwarding earlier but in a non-template
context. It works, however, in a similar manner with templates. To demonstrate this, let’s
redefine the function h as a template function. It would look as follows:
void g(foo& v)  { std::cout << "g(foo&)\n"; }
void g(foo&& v) { std::cout << "g(foo&&)\n"; }
template <typename T> void h(T& v)  { g(v); }
template <typename T> void h(T&& v) { g(v); }
foo x{ 42 };
h(x);          // g(foo&)
h(foo{ 42 });  // g(foo&)
The implementation of the g overloads is the same, but the h overloads are now function
templates. However, calling h with an lvalue and an rvalue actually resolves to the same
call to g, the first overload taking an lvalue. This is because in the context of the function
h, v is an lvalue so passing it to g will call the overload taking an lvalue.

The solution to this problem is the same as what we already saw before discussing
templates. However, there is a difference: we no longer need two overloads, but a single
one taking a forwarding reference:
template <typename T>
void h(T&& v)
{
   g(std::forward<T>(v));
}
This implementation is using std::forward to pass lvalues as lvalues and rvalues as
rvalues. It works similarly for variadic function templates. The following is a conceptual
implementation of the std::make_unique function that creates a std::unique_
ptr object:
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
   return std::unique_ptr<T>(
		   new T(std::forward<Args>(args)...));
}
To summarize this section, remember that forwarding references (also known as universal
references) are basically a special deduction rule for function template arguments. They
work based on the rules of reference collapsing and their purpose is to enable perfect
forwarding. That is passing forward to another function a reference by preserving its
valueness semantics: rvalues should be passed as rvalues and lvalues as lvalues.



*/


// decltype returns the type of an expression
// usually used in templates with the auto keyword

/*
 It can be used with
different expressions, and it yields different results based on the expression. The rules are
as follows:
1. If the expression is an identifier or a class member access, then the result is the
type of the entity that is named by the expression. If the entity does not exist,
or it is a function that has an overload set (more than one function with the same
name exists), then the compiler will generate an error.
2. If the expression is a function call or an overloaded operator function, then the
result is the return type of the function. If the overloaded operator is wrapped in
parentheses, these are ignored.
3. If the expression is an lvalue, then the result type is an lvalue reference to the type
of expression.
4. If the expression is something else, then the result type is the type of the expression.

To understand these rules better, we’ll look at a set of examples. For these, we will consider
the following functions and variables that we will use in decltype expressions:
int f() { return 42; }
int g() { return 0; }
int g(int a) { return a; }
struct wrapper
{
   int val;
   int get() const { return val; }
};
int a = 42;
int& ra = a;
const double d = 42.99;
long arr[10];
long l = 0;
char* p = nullptr;
char c = 'x';
wrapper w1{ 1 };
wrapper* w2 = new wrapper{ 2 };

The following listing shows multiple uses of the decltype specifier. The rule that applies
in each case, as well as the deduced type, is specified on each line in a comment:
decltype(a) e1;             // R1, int
decltype(ra) e2 = a;        // R1, int&
decltype(f) e3;             // R1, int()
decltype(f()) e4;           // R2, int
decltype(g) e5;             // R1, error
decltype(g(1)) e6;          // R2, int
decltype(&f) e7 = nullptr;  // R4, int(*)()
decltype(d) e8 = 1;         // R1, const double
decltype(arr) e9;           // R1, long[10]
decltype(arr[1]) e10 = l;   // R3, long&
decltype(w1.val) e11;       // R1, int
decltype(w1.get()) e12;     // R1, int
decltype(w2->val) e13;      // R1, int
decltype(w2->get()) e14;    // R1, int
decltype(42) e15 = 1;       // R4, int
decltype(1 + 2) e16;        // R4, int
decltype(a + 1) e17;        // R4, int
decltype(a = 0) e18 = a;    // R3, int&
decltype(p) e19 = nullptr;  // R1, char*
decltype(*p) e20 = c;       // R3, char&
decltype(p[0]) e21 = c;     // R3, char&

• decltype(f) only names a function with an overloaded set, so rule 1 applies.
decltype(g) also names a function but it has an overloaded set. Therefore,
rule 1 applies and the compiler generates an error.
• decltype(f()) and decltype(g(1)) are both using function calls for
the expression, so the second rule applies, and even if g has an overload set, the
declaration is correct.
• decltype(&f) uses the address of the function f, so the fourth rule applies,
yielding int(*)().
• decltype(1+2) and decltype(a+1) use the overloaded operator +
that returns an rvalue, so the fourth rule applies. The result is int. However,
decltype(a = 1) uses the assignment operator that returns an lvalue, so the
third rule applies, yielding the lvalue reference int&

The preceding rules mentioned are not the only ones used for determining the type. There
are several more for data member access. These are as follows:
• The const or volatile specifiers of the object used in the decltype expression
do not contribute to the deduced type.
• Whether the object or pointer expression is an lvalue or an rvalue does not
affect the deduced type.
• If the data member access expression is parenthesized, such as
decltype((expression)), then the previous two rules do not apply. The
const or volatile qualifier of the object does affect the deduced type, including
the valueness of the object.
The first two rules from this list are demonstrated with the following snippet:
struct foo
{
   int          a = 0;
   volatile int b = 0;
   const int    c = 42;
};
foo f;
foo const cf;
volatile foo* pf = &f;
decltype(f.a) e1 = 0;       // int
decltype(f.b) e2 = 0;       // int volatile
decltype(f.c) e3 = 0;       // int const
decltype(cf.a) e4 = 0;      // int
decltype(cf.b) e5 = 0;      // int volatile
decltype(cf.c) e6 = 0;      // int const
decltype(pf->a) e7 = 0;     // int
decltype(pf->b) e8 = 0;     // int volatile
decltype(pf->c) e9 = 0;     // int const
decltype(foo{}.a) e10 = 0;  // int
The decltype specifier 175
decltype(foo{}.b) e11 = 0;  // int volatile
decltype(foo{}.c) e12 = 0;  // int const

The deduced type for each case is mentioned on the right side in a comment. When
the expression is parenthesized, these two rules are reversed. Let’s take a look at the
following snippet:

foo f;
foo const cf;
volatile foo* pf = &f;
int x = 1;
int volatile y = 2;
int const z = 3;
decltype((f.a)) e1 = x;       // int&
decltype((f.b)) e2 = y;       // int volatile&
decltype((f.c)) e3 = z;       // int const&
decltype((cf.a)) e4 = x;      // int const&
decltype((cf.b)) e5 = y;      // int const volatile&
decltype((cf.c)) e6 = z;      // int const&
decltype((pf->a)) e7 = x;     // int volatile&
decltype((pf->b)) e8 = y;     // int volatile&
decltype((pf->c)) e9 = z;     // int const volatile&
decltype((foo{}.a)) e10 = 0;  // int&&
decltype((foo{}.b)) e11 = 0;  // int volatile&&
decltype((foo{}.c)) e12 = 0;  // int const&&


Here, all the expressions used with decltype for declaring variables e1 to e9 are
lvalues, so the deduced type is an lvalue reference. On the other hand, the expression
used to declare the variables e10, e11, and e12 is an rvalue; therefore, the deduced
type is an rvalue reference. Furthermore, cf is a constant object and foo::a has
the type int. Therefore, the result type is const int&. Similarly, foo::b has the
type volatile int; therefore, the result type is const volatile int&.
These are just a few examples from this snippet, but the others follow the same rules
for deduction


The real purpose of decltype is to be used in templates where the return value of a function depends on its template arguments and is not known before instantiation
we could write a function template that takes two arguments of potentially
different types and returns the minimum of the two. This can look as follows:

template <typename T, typename U>
??? minimum(T&& a, U&& b)
{
   return a < b ? a : b;
}

The question is, what is the return type of this function? This can be implemented
differently, depending on the standard version you are using.
In C++11, we can use the auto specifier with a trailing return type, where we use the
decltype specifier to deduce the return type from an expression. This would look
as follows:

template <typename T, typename U>
auto minimum(T&& a, U&& b) -> decltype(a < b ? a : b)
{
   return a < b ? a : b;
}

This syntax can be simplified if you’re using C++14 or a newer version of the standard.
The trailing return type is no longer necessary. You can write the same function as follows:

template <typename T, typename U>
decltype(auto) minimum(T&& a, U&& b)
{
   return a < b ? a : b;
}
It is possible to simplify this further and simply use auto for the return type, shown
as follows:

template <typename T, typename U>
auto minimum(T&& a, U&& b)
{
   return a < b ? a : b;
}


but decltype(auto) and auto do not always have the same effect
Let’s consider the following example where we have a function returning
a reference, and another function that calls it perfectly forwarding the argument:

template <typename T>
T const& func(T const& ref)
{
   return ref;
}

template <typename T>
auto func_caller(T&& ref)
{
   return func(std::forward<T>(ref));
}

int a = 42;
decltype(func(a))        r1 = func(a);        // int const&
decltype(func_caller(a)) r2 = func_caller(a); // int

The function func returns a reference, and func_caller is supposed to do a perfect
forwarding to this function. By using auto for the return type, it is inferred as int in the
preceding snippet (see variable r2). In order to do a perfect forwarding of the return type,
we must use decltype(auto) for it, as shown next:

template <typename T>
decltype(auto) func_caller(T&& ref)
{
   return func(std::forward<T>(ref));
}

int a = 42;
decltype(func(a))        r1 = func(a);        // int const&
decltype(func_caller(a)) r2 = func_caller(a); // int const&

This time, the result is as intended, and the type of both r1 and r2 in this snippet is
int const&.
As we have seen in this section, decltype is a type specifier used to deduce the type
of an expression. It can be used in different contexts, but its purpose is for templates
to determine the return type of a function and to ensure the perfect forwarding of it

The std::declval is a utility type operation function, available in the <utility>
header. It’s in the same category as functions such as std::move and std::forward
that we have already seen. What it does is very simple: it adds an rvalue reference to its
type template argument. The declaration of this function looks as follows:
template<class T>
typename std::add_rvalue_reference<T>::type declval() noexcept;

*/

// type traits and conditional compilation
// type traits allow us to inspect properties of types or to perform transformations of types at compile time
// type traits are themselves templates, overloaded with a single static const bool member whoch returns true or false based on the templated type thats given

// type traits are small class templates that contain a constant value which is the answer to a question we ask about the type
// can combine them with static asserts to check for correct types at compile time

/*

Let’s see how we can build a type trait that tells us, at compile-time, whether a type is
a floating-point type:
template <typename T>
struct is_floating_point
{
   static const bool value = false;
};
template <>
struct is_floating_point<float>
{
   static const bool value = true;
};
template <>
struct is_floating_point<double>
{
   static const bool value = true;
};
template <>
struct is_floating_point<long double>
{
   static const bool value = true;
};

There are two things to notice here:
• We have defined a primary template as well as several full specializations, one for
each type that is a floating-point type.
• The primary template has a static const Boolean member initialized with the
false value; the full specializations set the value of this member to true.
There is nothing more to building a type trait than this. is_floating_point<T>
is a type trait that tells us whether a type is a floating-point type or not. We can use it
as follows:
int main()
{
   static_assert(is_floating_point<float>::value);
   static_assert(is_floating_point<double>::value);
   static_assert(is_floating_point<long double>::value);
   static_assert(!is_floating_point<int>::value);
   static_assert(!is_floating_point<bool>::value);
}

so type traits can be implemented manually and we can use them at compile time to restrict types and select between one implementation and another

SFINAE is used for a similar purpose
When we write templates, we sometimes need to restrict the template arguments
e.g we have a function template that should work for any numeric type, therefore ints and floats, but not for anything else
or we have a function template overload that should work with some types only, such as ints and another overload that should work with floats

there are different ways to achieve this goal, and type traits are involved with all of them in one way or another
SFINAE is one way to achieve this 

SFINAE means substitution failure is not an error
when the compiler encounters the use of a function template, it substitutes the arguments in order to instantiate the template
if an error occurs at this point, it is not regarded as ill informed code, only as a deduction failure
the function is removed from the overloaded set instead of causing an error. Only if there is no match in the overload set does an error occur

imagine the two function overloads below

*/

template <typename T>
auto begin(T& c) { return c.begin(); }   // [1]

template <typename T, size_t N>
T* begin(T(&arr)[N]) { return arr; }      // [2]

// one function will work with c style arrays and the other with anything that implements iterators such as std::array
/*
The first overload calls the member function begin and returns the value. Therefore, this
overload is restricted to types that have a member function begin; otherwise, a compiler
error would occur. The second overload simply returns a pointer to the first element of the
array. This is restricted to array types; anything else would produce a compiler error.

We can use these overloads as follows:

std::array<int, 5> arr1{ 1,2,3,4,5 };
std::cout << *begin(arr1) << '\n';       // [3] prints 1

int arr2[]{ 5,4,3,2,1 };
std::cout << *begin(arr2) << '\n';       // [4] prints 5

If you compile this piece of code, no error, not even a warning, occurs. The reason for that
is SFINAE. When resolving the call to begin(arr1), substituting std::array<int,
5> to the first overload (at [1]) succeeds, but the substitution for the second (at [2])
fails. Instead of issuing an error at this point, the compiler just ignores it, so it builds an
overload set with a single instantiation and, therefore, it can successfully find a match for
the invocation. Similarly, when resolving the call to begin(arr2), the substitution of
int[5] for the first overload fails and is ignored, but it succeeds for the second and is
added to the overload set, eventually finding a good match for the invocation. Therefore,
both calls can be successfully made. Should one of the two overloads not be present, either
begin(arr1) or begin(arr2) would fail to match the function template and
a compiler error would occur.

SFINAE only applies in the so-called immediate context of a function. The immediate
context is basically the template declaration (including the template parameter list, the
function return type, and the function parameter list). Therefore, it does not apply to the
body of a function.

template <typename T>
void increment(T& val) { val++; }

int a = 42;
increment(a);  // OK

std::string s{ "42" };
increment(s);  // error

There are no restrictions on the type T in the immediate context of the increment
function template. However, in the body of the function, the parameter val is
incremented with the post-fix operator++. That means, substituting for T any type for
which the post-fix operator++ is not implemented is a failure. However, this failure is
an error and will not be ignored by the compiler.

Let’s say we want to have two function template overloads, one that
handles arrays of even sizes and one that handles arrays of odd sizes. A solution to this is
the following:

template <typename T, size_t N>
void handle(T(&arr)[N], char(*)[N % 2 == 0] = 0)  // N % 2 == 0 is either true or false, so this becomes either 1 or 0
{
   std::cout << "handle even array\n";
}

template <typename T, size_t N>
void handle(T(&arr)[N], char(*)[N % 2 == 1] = 0)
{
   std::cout << "handle odd array\n";
}

int arr1[]{ 1,2,3,4,5 };
handle(arr1);

int arr2[]{ 1,2,3,4 };
handle(arr2);

The template arguments and the first function parameter are similar to what we saw with
the begin overload for arrays. However, these overloads for handle have a second
anonymous parameter with the default value 0. The type of this parameter is a pointer
to an array of type char and a size specified with the expressions N%2==0 and N%2==1.
For every possible array, one of these two is true and the other is false. Therefore, the
second parameter is either char(*)[1] or char(*)[0], the latter being an SFINAE
error (an attempt to create an array of size zero). Therefore, we are able to call either one
of the other overloads without generating compiler errors, thanks to SFINAE.

The last example that we will look at in this section will show SFINAE with an attempt to
use a member of a class that does not exist. Let’s start with the following snippet:

template <typename T>
struct foo
{
   using foo_type = T;
};

template <typename T>
struct bar
{
   using bar_type = T;
};

struct int_foo : foo<int> {};
struct int_bar : bar<int> {};

Here we have two classes, foo, which has a member type called foo_type, and bar,
which has a member type called bar_type. There are also classes that derive from these
two. The goal is to write two function templates, one that handles the foo hierarchy of
classes, and one that handles the bar hierarchy of classes. A possible implementation is
the following:

template <typename T>
decltype(typename T::foo_type(), void()) handle(T const& v)  // trick used here with the comma operator
{
   std::cout << "handle a foo\n";
}

template <typename T>
decltype(typename T::bar_type(), void()) handle(T const& v)
{
   std::cout << "handle a bar\n";
}

Both overloads have a single template parameter and a single function parameter of
type T const&. They also return the same type, and that type is void. The expression
decltype(typename T::foo_type(), void()) may need a little consideration
to understand better. We discussed decltype in Chapter 4, Advanced Template Concepts.
Remember that this is a type specifier that deduces the type of an expression. We use the
comma operator, so the first argument is evaluated but then discarded, so decltype
will only deduce the type from void(), and the deduced type is void. However, the
arguments typename T::foo_type() and typename T::bar_type() do use
an inner type, and this only exists either for foo or bar. This is where SFINAE manifests
itself, as shown in the following snippet:

int_foo fi;
int_bar bi;
int x = 0;
handle(fi); // OK
handle(bi); // OK
handle(x);  // error

Calling handle with an int_foo value will match the first overload, while the second
is discarded because of a substitution failure. Similarly, calling handle with an int_bar
value will match the second overload, while the first is discarded because of a substitution
failure. However, calling handle with an int will cause substitution failure for both
overloads so the final overload set for substituting int will be empty, which means there
is no match for the call. Therefore, a compiler error occurs.
SFINAE is not the best way to achieve conditional compilation. However, in modern C++
it’s probably best used together with a type trait called enable_if.

*/

// there are two categories of type traits
// type traits that enable us to query properties of types at compile-time
// type traits that enable us to perform type transformations at compile-time (such as adding or removing cv , adding or removing pointers or references from a type), these are called metafunctions

// one type trait from the second category is std::enable_if
// this is used to enable sfinae and remove candidates from the functions overload set
// enable_if enables the removal of a function overload or template specialisation from overload resolution

/*

A possible implementation is shown in the next snippet:
template <typename T, typename std::enable_if<uses_write_v<T>>::type* = nullptr>
void serialize(std::ostream& os, T const& value)
{
   value.write(os);
}
template <typename T, typename std::enable_if<!uses_write_v<T>>::type* =nullptr>
void serialize(std::ostream& os, T const& value)
{
   os << value;
}

There are two overloaded function templates in this implementation. They both have
two template parameters. The first parameter is a type template parameter, called T. The
second is an anonymous non-type template parameter of a pointer type that also has the
default value nullptr. We use enable_if to define the member called type only
if the uses_write_v variable evaluates to true. Therefore, for classes that have the
member function write, the substitution succeeds for the first overload but fails for the
second overload, because typename * = nullptr is not a valid parameter. For classes
for which the operator<< is overloaded, we have the opposite situation.
The enable_if metafunction can be used in several scenarios:
• To define a template parameter that has a default argument, which we saw earlier
• To define a function parameter that has a default argument
• To specify the return type of a function


even better than enable_if is constexpr if, a compile time version of the if statement
// if constexpr (condition) , the condition must be a compile-time expression

constexpr if enables us to discard a branch at compile time based on the value of the expression

template <typename T>
void serialize(std::ostream& os, T const& value)
{
   if constexpr (uses_write_v<T>)
	  value.write(os);
   else
	  os << value;
}

The constexpr if statements can be useful in many situations. The last example
presented in this section is a function template called are_equal, which determines
whether the two supplied arguments are equal or not. Typically, you’d think that using
operator== should be enough to determine whether two values are equal or not. That
is true in most cases, except for floating-point values. Because only some of the floatingpoint numbers can be stored without a precision loss (numbers like 1, 1.25, 1.5, and
anything else where the fractional part is an exact sum of inverse powers of 2) we need
to take special care when comparing floating-point numbers. Usually, this is solved by
ensuring that the difference between two floating-point values is less than some threshold.
Therefore, a possible implementation for such a function could be as follows:

template <typename T>
bool are_equal(T const& a, T const& b)
{
   if constexpr (std::is_floating_point_v<T>)
	  return std::abs(a - b) < 0.001;
   else
	  return a == b;
}

When the T type is a floating-point type, we compare the absolute value of the difference
of the two numbers with the selected threshold. Otherwise, we fall back to using
operator==. This enables us to use this function not just with arithmetic types, but also
any other type for which the equality operator is overloaded.
are_equal(1, 1);                                   // OK
are_equal(1.999998, 1.999997);                     // OK
are_equal(std::string{ "1" }, std::string{ "1" }); // OK
are_equal(widget{ 1, "one" }, widget{ 1, "two" }); // error
We are able to call the are_equal function template with arguments of type int,
double, and std::string. However, attempting to do the same with values of the
widget typ


standard type traits are in <type_traits>
there are several categories, such as for querying the type category, type opertions, type relationships etc...
// we can check if a type is void, null, class, object etc...
// theres also is_const, is_empty, is_abstract
and then the type trait metafunctions which can add and remove constness of the type, change it to a reference, remove references etc...





*/



// std::decay and std::conditional


// polymorphism means many forms
// in programming, its the ability of objects of different types to be treated as if they were the same type
// a polymorphic class is a class that inherits or declares a virtual function
// polymorphic objects generate information associated with each object that make it possible to determine that objects type at runtime
// this refers to dynamic polymorphism (late binding) which is done by virtual functions and interfaces
// there is also static polymorphism (early binding) which is done by function overloads and templates at compile time

struct game_unit
{
	virtual void attack() = 0;  // pure virtual function, must be overriden
};

struct knight : public game_unit
{
	void attack() override { std::cout << "draw sword \n"; }
};

struct mage : game_unit
{
	void attack() override { std::cout << "spell magic curse\n"; }
};


void fight(const std::vector<game_unit*>& vec)  // full of pointers to base
{
	for (auto i : vec)
	{
		i->attack();  // dynamic binding, so we can call attack without knowing the exact type 
	}
}

// operator overloading is an example of static polymorphism

/*
overloaded functions and
templates are the mechanisms to implement static polymorphism in the C++ language.
Dynamic polymorphism incurs a performance cost because in order to know what
functions to call, the compiler needs to build a table of pointers to virtual functions (and
also a table of pointers to virtual base classes in case of virtual inheritance). So, there is
some level of indirection when calling virtual functions polymorphically. Moreover,
the details of virtual functions are not made available to the compiler who cannot
optimize them

*/

// CRTP allows us to get the benefits of dynamic polymorphism without the runtime performance penalty
// the patterm has a base class that defines the static interface
// derived classes are themselves the template argument for the base class template
// member functions of the base class call member fucntions of its type template parameter (which are the derived classes)

/*
template <typename T>
struct game_unit
{
   void attack()
   {
	  static_cast<T*>(this)->do_attack();
   }
};
struct knight : game_unit<knight>
{
   void do_attack()
   { std::cout << "draw sword\n"; }
};
struct mage : game_unit<mage>
{
   void do_attack()
   { std::cout << "spell magic curse\n"; }
};

The game_unit class is now a template class but contains the same member function,
attack. Internally, this performs an upcast of the this pointer to T* and then invokes
a member function called do_attack. The knight and mage classes derive from the
game_unit class and pass themselves as the argument for the type template parameter T.
Both provide a member function called do_attack.
Notice that the member function in the base class template and the called member
function in the derived classes have different names. Otherwise, if they had the same
name, the derived class member functions would hide the member from the base since
these are no longer virtual functions.

The fight function that takes a collection of game units and calls the attack function
needs to change too. It needs to be implemented as a function template, as follows:
template <typename T>
void fight(std::vector<game_unit<T>*> const & units)
{
   for (auto unit : units)
   {
	  unit->attack();
   }
}
Using this function is a little different than before. It goes as follows:
knight k;
mage   m;
fight<knight>({ &k });
fight<mage>({ &m });

We have moved the runtime polymorphism to compile-time. Therefore, the fight
function cannot treat knight and mage objects polymorphically. Instead, we get two
different overloads, one that can handle knight objects and one that can handle mage
objects. This is static polymorphism.
Although the pattern might not look complicated after all, the question you’re probably
asking yourself at this point is: how is this pattern actually useful? There are different
problems you can solve using CRT, including the following:
• Limiting the number of times a type can be instantiated
• Adding common functionality and avoiding code duplication
• Implementing the composite design pattern
In the following subsections, we will look at each of these problems and see how
to solve them with CRTP

*/

// type erasure describes a pattern in which type information is removed, allowing types thata re not necessarily related to ve treated in a generic way
// true type erasure is achieved with templates
// type erasure is an idiom that combines inheritance from object orietnted programming with templates to create wrappers that can store any type 

/*
type erasure pattern by putting the abstract base class
and wrapper class template within another class:
struct game
{
   struct game_unit
   {
	  virtual void attack() = 0;
	  virtual ~game_unit() = default;
   };

   template <typename T>
   struct game_unit_wrapper : public game_unit
   {
	  game_unit_wrapper(T& unit) : t(unit) {}
	  void attack() override { t.attack(); }
   private:
	  T& t;
   };

   template <typename T>
   void addUnit(T& unit)
   {
	  units.push_back(
		 std::make_unique<game_unit_wrapper<T>>(unit));
   }

   void fight()
   {
	  for (auto& u : units)
		 u->attack();
   }

private:
   std::vector<std::unique_ptr<game_unit>> units;
};

The game class contains a collection of game_unit objects and has a method for adding
new wrappers to any game unit (that has an attack member function). It also has
a member function, fight, to invoke the common behavior. The client code is,
this time, the following:
knight k;
mage m;
game g;
g.addUnit(k);
g.addUnit(m);
g.fight();
In the type erasure pattern, the abstract base class is called a concept and the wrapper that
inherits from it is called a model. If we were to implement the type erasure pattern in the
established formal manner it would look as follows:
struct unit
{
   template <typename T>
   unit(T&& obj) :
	  unit_(std::make_shared<unit_model<T>>(
			   std::forward<T>(obj)))
   {}
   void attack()
   {
	  unit_->attack();
   }
   struct unit_concept
   {
	  virtual void attack() = 0;
	  virtual ~unit_concept() = default;
   };
   template <typename T>

   struct unit_model : public unit_concept
   {
	  unit_model(T& unit) : t(unit) {}
	  void attack() override { t.attack(); }
   private:
	  T& t;
   };
private:
   std::shared_ptr<unit_concept> unit_;
};
void fight(std::vector<unit>& units)
{
   for (auto& u : units)
	  u.attack();
}
In this snippet, game_unit was renamed as unit_concept and game_unit_
wrapper was renamed as unit_model. There is no other change to them apart from
the name. They are members of a new class called unit that stores a pointer to an object
that implements unit_concept; that could be unit_model<knight> or unit_
model<mage>. The unit class has a template constructor that enables us to create such
model objects from knight and mage objects.
It also has a public member function, attack (again, this can have any name). On
the other hand, the fight function handles unit objects and invokes their attack
member function. The client code may look as follows:
knight k;
mage m;
std::vector<unit> v{ unit(k), unit(m) };
fight(v);

If you’re wondering where this pattern is used in real-world code, there are two examples
in the standard library itself:
• std::function: This is a general-purpose polymorphic function wrapper
that enables us to store, copy, and invoke anything that is callable, such as
functions, lambda expressions, bind expressions, function objects, pointers to
member functions, and pointers to data members. Here is an example of using
std::function:
class async_bool
{
   std::function<bool()> check;
public:
   async_bool() = delete;
   async_bool(std::function<bool()> checkIt)
	  : check(checkIt)
   { }
   async_bool(bool val)
	  : check([val]() {return val; })
   { }
   operator bool() const { return check(); }
};
async_bool b1{ false };
async_bool b2{ true };
async_bool b3{ []() { std::cout << "Y/N? ";
					  char c; std::cin >> c;
					  return c == 'Y' || c == 'y'; } };
if (b1) { std::cout << "b1 is true\n"; }
if (b2) { std::cout << "b2 is true\n"; }
if (b3) { std::cout << "b3 is true\n"; }


*/



int main()
{
	Processor<int> p1;
	p1.run();  // double called

	handler<int> h1;  // template instantiation
	dependent_parser<handler<int>> dp1;  // template instantiation, binding happens here
	dp1.parse(h1);  // this calls the integer version of handler, because even though its declared after, the arg param in parse() is a dependent type because it comes from a parameter
	// 


}