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



int main() {
	std::cout << add<float>(2.9, 3.6) << std::endl;  // If the type of the two parameters is ambiguous, the compiler will not be able to deduce them automatically. These are both floats so <float> can be removed

	wrapper<int> w1(52);

	std::cout << "w1's value is " << w1.get_value() << std::endl;

	buffer<int, 25> b1;  // create a buffer of ints with size 25

	wrapping_pair<int, double, simple_wrapper> w2(42,42.0);  // W is therefore a simple_wrapper in this instantiation, so item1 and item2 are simple_wrapper objects



}