# include <iostream>

// The process of generating code from a template by the compiler is called template instantiation.
// This happens by substituting the template arguments for the template parameters used in the definition of the template.For instance, in the example where we used vector<int>, the compiler substituted the int type in every place where T appeared.

/* Function templates are only blueprints for creating actual functions and only exist in 
source code. Unless explicitly called in your source code, the function templates will not 
be present in the compiled executable. However, when the compiler encounters a call 
to a function template and is able to match the supplied arguments and their types to 
a function template's parameters, it generates an actual function from the template and 
the arguments used to invoke it.


C++20 has introduced concepts and constraints. Constraints specify requirements on
template arguments. A named set of constraints is called a concept. Concepts can be
specified as type template parameters.

template parameters can be type, non-type and templates themselves

we can replace template syntax with an alias using the using keyword

lambdas can also be generic

*/

template <typename T>
T add(T const a, T const b) {
	return a + b;
}


// Class templates are declared in a very similar manner, with the template keyword and the template parameter list preceding the class declaration.

template <typename T>  // this template runs for the entire class, not just for the function
class wrapper {
public:
	wrapper(T input) : value(input) {}

	const T& get_value() const{
		return value;
	}

private:
	T value;
};

/*  type template parameters are parameters representing types supplied as arguments 
during the template instantiation. They are introduced either with the typename
or the class keyword.  */


template <typename T = int> // default type
class temp_test {
	// will use int by default
};

template <typename... X>  // C++11 has introduced variadic templates, which are templates with a variable number of arguments.A template parameter that accepts zero or more arguments is called
// a parameter pack. parameter pack, variable number of template types
class param_pack_test {

};

/* Template arguments don't always have to represent types. They can also be compile-time 
expressions, such as constants, addresses of functions or objects with external linkage, 
or addresses of static class members. Parameters supplied with compile-time expressions 
are called non-type template parameters. This category of parameters can only have 
a structural type. The following are the structural types:
• Integral types
• Floating-point types, as of C++20
• Enumerations
• Pointer types (either to objects or functions)
• Pointer to member types (either to member objects or member functions)
• Lvalue reference types (either to objects or functions)
• A literal class type that meets the following requirements:
 All base classes are public and non-mutable.
 All non-static data members are public and non-mutable.
 The types of all base classes and non-static data members are also structural types 
or arrays thereof*/ 

template <typename T, size_t S>
class buffer {
	T data[S];  // private buffer of the size of the non-type template parameter S that holds elements of type T, therefore S must be a compile time value
public:
	constexpr const T* data() const { return data; }  // constexpr, function can be computed at compile time
	// When a function call is evaluated at compile-time, the compiler will calculate the return value of the function call, and then replace the function call with the return value.
	// According to the C++ standard, a constexpr function that is eligible for compile-time evaluation must be evaluated at compile-time if the return value is used where a constant expression is required. 
	// Otherwise, the compiler is free to evaluate the function at either compile-time or runtime.
	constexpr T& operator[] (size_t const index) {
		return data[index];
	}
	constexpr T& const operator[] (size_t const index) const {
		return data[index];
	}
};

// template template types
template <typename T> 
class simple_wrapper {
public:
	T value;
};

template <typename T>
class fancy_wrapper {
public:
	fancy_wrapper(const T v) : value(v){}

	const T& get() const { return value; }

	template <typename U>
	U as() const {
		return static_cast<U>(value);
	}

private:
	T value;
};

template <typename T, typename U, template <typename> typename W = fancy_wrapper>  // passed in a template as the template, with its default being fancy_wrapper
class wrapping_pair {
public:
	wrapping_pair(T const a, U const b) : item1(a), item2(b){}
	W<T> item1;
	W<U> item2l
};

// templates can be instantiated implicitly or explicitly
// the compiler is not required to instantiate any templated class or function if it is not used

// A template specialization is the definition created from a template instantiation. The template that is being specialized is called the primary template.
// You can provide an explicit specialized definition for a given set of template arguments, therefore overwriting the implicit code the compiler would generate instead.
// This is the technique that powers features such as type traits and conditional compilation

template <typename T, int S>
struct collection
{
	void operator()()
	{
		std::cout << "primary template\n";
	}
};

template <typename T>
struct collection<T, 10>
{
	void operator()()
	{
		std::cout << "partial specialization <T, 10>\n";
	}
};
template <int S>
struct collection<int, S>
{
	void operator()()
	{
		std::cout << "partial specialization <int, S>\n";
	}
};
template <typename T, int S>
struct collection<T*, S>
{
	void operator()()
	{
		std::cout << "partial specialization <T*, S>\n";
	}
};
// We have a primary template called collection that has two template arguments
// (a type template argument and a non - type template argument) and we have three partial
// specializations, as follows :
// • A specialization for the non - type template argument S with the value 10
// • A specialization for the int type
// • A specialization for the pointer type T*
// These templates can be used as shown in the following snippet :
// collection<char, 42> a;  // primary template
// collection<int, 42> b;  // partial specialization <int, S>
// collection<char, 10> c;  // partial specialization <T, 10>
// collection<int*, 20> d;  // partial specialization <T*, S>

// chapter 3: Variadic Templates
// template with a varible number of arguments
// Variadic function templates are template functions with a variable number of arguments. 
// They borrow the use of the ellipsis(...) for specifying a pack of arguments, which can have different syntax depending on its nature.

// A template or function parameter pack can accept zero, one, or more arguments.The
// standard does not specify any upper limit for the number of arguments, but in practice,
// compilers may have some.What the standard does is recommend minimum values for
// these limits but it does not require any compliance on them.These limits are as follows :
// • For a function parameter pack, the maximum number of arguments depends on the
// limit of arguments for a function call, which is recommended to be at least 256.
// • For a template parameter pack, the maximum number of arguments depends on the
// limit of template parameters, which is recommended to be at least 1, 024.

template <typename T, typename... Args>
T sum(T a, Args... args) {
	if constexpr (sizeof...(args) == 0) {
		return a;
	}
	else return a + sum(args...)
}
/* Notice that sizeof…(args) (the function parameter pack) and sizeof…(Args) (the 
template parameter pack) return the same value. On the other hand, sizeof…(args)
and sizeof(args)... are not the same thing. The former is the sizeof operator 
used on the parameter pack args. The latter is an expansion of the parameter pack args
on the sizeof operator. */

// chapter 3: Variadic Templates
// template with a varible number of arguments
// Variadic function templates are template functions with a variable number of arguments. 
// They borrow the use of the ellipsis(...) for specifying a pack of arguments, which can have different syntax depending on its nature.

// A template or function parameter pack can accept zero, one, or more arguments.The
// standard does not specify any upper limit for the number of arguments, but in practice,
// compilers may have some.What the standard does is recommend minimum values for
// these limits but it does not require any compliance on them.These limits are as follows :
// • For a function parameter pack, the maximum number of arguments depends on the
// limit of arguments for a function call, which is recommended to be at least 256.
// • For a template parameter pack, the maximum number of arguments depends on the
// limit of template parameters, which is recommended to be at least 1, 024.

template <typename T, typename... Args>
T sum(T a, Args... args) {
	if constexpr (sizeof...(args) == 0) {
		return a;
	}
	else return a + sum(args...)
}
/* Notice that sizeof…(args) (the function parameter pack) and sizeof…(Args) (the 
template parameter pack) return the same value. On the other hand, sizeof…(args)
and sizeof(args)... are not the same thing. The former is the sizeof operator 
used on the parameter pack args. The latter is an expansion of the parameter pack args
on the sizeof operator.

The term name binding refers to the process of finding the declaration of each name
that is used within a template. There are two kinds of names used within a template:
dependent names and non-dependent names. The former are names that depend
on the type or value of a template parameter that can be a type, non-type, or template
parameter. Names that don’t depend on template parameters are called non-dependent.

name lookup happens differently
for dependent names (those that depend on a template parameter) and non-dependent
names (those that do not depend on a template parameter, plus the template name and
names defined in the current template instantiation). When the compiler passes through
the definition of a template it needs to figure out whether a name is dependent or
non-dependent. Further name lookup depends on this categorization and happens either
at the template definition point (for non-dependent names) or the template instantiation
point (for dependent names). Therefore, instantiation of a template happens in two phases:
• The first phase occurs at the point of the definition when the template syntax is
checked and names are categorized as dependent or non-dependent.
• The second phase occurs at the point of instantiation when the template arguments
are substituted for the template parameters. Name binding for dependent names
happens at this point.

The std::declval is a utility type operation function, available in the <utility>
header. It’s in the same category as functions such as std::move and std::forward
that we have already seen. What it does is very simple: it adds an rvalue reference to its
type template argument.

 in templates, rvalue references work slightly differently, and sometimes they are
rvalue references, but other times they are actually lvalue references.
References that exhibit this behavior are called forwarding references. However, they are
often referred to as universal references. This was a term coined by Scott Meyers shortly
after C++11 when there was no term in the standard for this type of reference. In order to
address this shortcoming, and because it didn’t feel the term universal references properly
described their semantics, the C++ standard committee called these forwarding references
in C++14


Name binding is the process of finding the declaration for each name that is explicitly or implicitly used in a template. The compiler might bind a name in the definition of a template, or it might bind a name at the instantiation of a template.
a dependent name is a name that depends on the type or the value of a template parameter
*/

template <class T> 
class U : A<T> {
	typename T::B x;
	void f(A<T>& y) {
		*y++;
	}
};

// dependent names above are base class A<T>, typename T::B and variable y

// the compiler binds dependent names what a template is instantiated
// the compiler binds non-dependent names when a template is defined

void f(double) { cout << "Function f(double)" << endl; }

template <class A> struct container { // point of definition of container
	void member1() {
		// This call is not template dependent, 
		// because it does not make any use of a template parameter.
		// The name is resolved at the point of definition, so f(int) is not visible.
		f(1);
	}
	void member2(A arg);
};

void f(int) { cout << "Function f(int)" << endl; }

void h(double) { cout << "Function h(double)" << endl; }

template <class A> 
void container<A>::member2(A arg) {
	// This call is template dependent, so qualified name lookup only finds
	// names visible at the point of instantiation.
	::h(arg);
}

template 
struct container<int>; // point of instantiation of container<int>

void h(int) { cout << "Function h(int)" << endl; }

int main(void) {
	container<int> test;
	test.member1();
	test.member2(10);
	return 0;
}
/* The point of definition of a template is located immediately before its definition. 
In this example, the point of definition of the template container is located immediately before the keyword template. 
Because the function call f(1) does not depend on a template parameter, the compiler considers names declared before the definition of the template container. 
Therefore, the function call f(1) calls f(double). 
Although f(int) is a better match, it is not in scope at the point of definition of container.

The point of instantiation of a template is located immediately before the declaration that encloses its use. 
In this example, the point of instantiation of container<int> is the location of the explicit instantiation. 
Because the qualified function call ::h(arg) depends on the template argument arg, the compiler considers names declared before the instantiation of container<int>. 
Therefore, the function call h(arg) calls h(double). It does not consider h(int), because this function is not in scope at the point of instantiation of container<int>.

Point of instantiation binding implies the following:
A template parameter cannot depend on any local name or class member.
An unqualified name in a template cannot depend on a local name or class member.*/

/*
reference collapsing rule. The rule is very simple. & always wins. So & & is &, and so are && & and & &&. The only case where && emerges from collapsing is && &&. 
You can think of it as a logical-OR, with & being 1 and && being 0.

given a function template like:
*/
template <class T>
void func(T&& t){}

/*  Don't let T&& fool you here - t is not an rvalue reference. 
When it appears in a type-deducing context, T&& acquires a special meaning. 
When func is instantiated, T depends on whether the argument passed to func is an lvalue or an rvalue. 
If it's an lvalue of type U, T is deduced to U&. If it's an rvalue, T is deduced to U  */

func(4);            // 4 is an rvalue: T deduced to int

double d = 3.14;
func(d);            // d is an lvalue; T deduced to double&

float f() { ... }
func(f());          // f() is an rvalue; T deduced to float

int bar(int i) {
	func(i);          // i is an lvalue; T deduced to int&
}

/*
In C++, perfect forwarding is the act of passing a function’s parameters to another function while preserving its reference category. 
It is commonly used by wrapper methods that want to pass their parameters through to another function, often a constructor.

In perfect forwarding, std::forward is used to convert the named rvalue reference t1 and t2 to unnamed rvalue reference.

*/
template <typename T1, typename T2> 
void outer(T1&& t1, T2&& t2)  // if T1 is a lvalue reference, it gets forwarded as an lvalue reference, same as if its const or templated
{ // ordinarily, it would be passed as an lvalue reference to T1 if t1 was an rvalue, but std::forward is ensuring its sent on as an rvalue
	inner(std::forward<T1>(t1), std::forward<T2>(t2));
}

// If you use a named rvalue reference in an expression it is actually an lvalue(because you refer to the object by name).Consider the following example :

void inner(int&, int&);  // #1
void inner(int&&, int&&); // #2
// Now, if we call outer like this
outer(17, 29);
// we would like 17 and 29 to be forwarded to #2 because 17 and 29 are integer literals and as such rvalues.
// But since t1 and t2 in the expression inner(t1, t2); are lvalues, you'd be invoking #1 instead of #2. 
// That's why we need to turn the references back into unnamed references with std::forward.So, t1 in outer is always an lvalue expression while forward<T1>(t1) may be an rvalue expression depending on T1.
// The latter is only an lvalue expression if T1 is an lvalue reference.And T1 is only deduced to be an lvalue reference in case the first argument to outer was an lvalue expression.


int main() {
	std::cout << add<float>(2.9, 3.6) << std::endl;  // If the type of the two parameters is ambiguous, the compiler will not be able to deduce them automatically. These are both floats so <float> can be removed

	wrapper<int> w1(52);

	std::cout << "w1's value is " << w1.get_value() << std::endl;

	buffer<int, 25> b1;  // create a buffer of ints with size 25

	wrapping_pair<int, double, simple_wrapper> w2(42,42.0);  // W is therefore a simple_wrapper in this instantiation, so item1 and item2 are simple_wrapper objects



}
