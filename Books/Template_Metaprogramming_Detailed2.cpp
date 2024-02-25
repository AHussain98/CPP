# include <iostream>
# include <string>
# include <array>
# include <vector>
# include <map>

// a template specialisation is the definition created from a template instantiatiom
// the template being specialised is called the primary template
// there are two forms of template specialisation, explicit (full) specialisation and partial specialisation
// explicit specialisation occurs when you provide a definition for a template instantiation with the full set of template arguments

template <typename T>
struct is_floating_point  // primary template
{
	constexpr static bool value = false;  // note, static const integral types can be defined in the class, if not const or integral but still sttic, they must be defined outside
};

template <>
struct is_floating_point<float>  // full specialisation
{
	constexpr static bool value = true;
};

template<>
struct is_floating_point<double>  // full specialisation
{
	constexpr static bool value = true;
};

template<>
struct is_floating_point<long double>  // full specialisation
{
	constexpr static bool value = true;
};

// these new definitions change the way value is being initialised
// clearly, static class members can be fully specialised. However each specialisation has its own copy of any static members:

template <typename T>
struct foo
{
	static T value;
};
template <typename T> T foo<T>::value = 0;  // initialise the static variable with a primary template
template <> int foo<int>::value = 42;  // initialise the static variable with a specialised template

// explicit specialisation must appear after the primary template declaration.
// the primary template decleration does not need to be fully defined, only declared, and then the specialisation can follow after
// template specialisations can also be only declared without being defined

// when specialisaing a function template, if the compiler can deduce a template argument from the type of the function arguement, then that type of the argument is optional
template<typename T>
struct foo_1 {

};

template <typename T>
void func(foo_1<T>) {
	std::cout << "primary template" << std::endl;
}

template <>
void func(foo_1<int>) {
	std::cout << "int specialisation" << std::endl;
}

// definitions of function template or member function templates are not allowed to contain default function arguments

// explicit specialisation requires all arguments to be specified 
template<typename T, typename U>
void double_func(T a, U b) {
	std::cout << "primary template " << sizeof(b) << std::endl;
}

template<>
void double_func(int a, std::string b) {
	std::cout << "int and string specialisation" << std::endl;
}

template<>
void double_func(int a, const char* b) {
	std::cout << "int and char pointer specialisation! \n";
}

// partial specialisation occurs when we specialise a primary template but only specify some of the template arguments
// only classes can be partially specialised
// partially specialised classes have a template parameter list (after the template keyword) and a template argument list (which follows the template name)

template <typename T, int S>
struct collection
{
	void operator() () {
		std::cout << "primary template \n";
	}
};

template <typename T>  // take T from primary
struct collection<T,10>
{
	void operator() () {
		std::cout << "partial specialisation<T,10> \n";
	}
};

template <int S>  // take int S from primary
struct collection<int, S>
{
	void operator() () {
		std::cout << "partial specialisation <int, S> \n";
	}
};

template<typename T, int S>  // take T A=and int S from primary
struct collection<T*,S>  // when T is a pointer type
{
	void operator() () {
		std::cout << "partial specialisation <T*, S> \n";
	}
};

// we have a primary template called collection that has two template arguments (a type template argument and a non-type template argument)
// we have 3 partial specialisations

collection<char, 42> a;  // primary template
collection<int, 42> b; // partial specialisation <int, S>
collection <char, 10> c; // partial specialisation <T,10>
collection<int*, 20> d;  // partial specialisation <T*, S>

// some combinations are not possible because they are unambigous and the compiler cannot select which template instantiation to use:
/*  collection<int,   10> e; // error: collection<T,10> or 
                         //        collection<int,S>
collection<char*, 10> f; // error: collection<T,10> or 
                         //        collection<T*,S>   */


// when defining specialisations of a primary template, keep in mind:
// parameters in the template arameters list of the partial specialisation cannot have default values

// when a class template has partial specialisations, the compiler must decide what is the best match to generate a definition from
// the compiler compares template arguments of teh specialisation with the template argument list of teh primarytemplate and the partial specialisations
// If no match is found, a definition is generated from the primary template.
// If a single partial specialization is found, a definition is generated from that specialization.
// If more than a single partial specialization is found, then a definition is generated from the most specialized partial specialization but only if it is unique.

// However, partial specializations are not found by name lookup and are considered only if  the primary template is found by name lookup

// create a function that formats the content of an array in a nice way and output sit to stream, char elements should not be seperated by comma but should be in brackets

template <typename T, size_t S>
std::ostream& pretty_print(std::ostream& os, const std::array<T, S>& arr)
{
	os << '[';
	if (S > 0)
	{
		size_t i = 0;
		for (; i < S - 1; ++i)
		{
			os << arr[i] << ',';
		}
		os << arr[S - 1];
	}
	os << ']';

	return os;
}

// this prints chars with commas, we dont want that, so lets make a specialisation

template<size_t S>  // the one we're keeping from the primary
std::ostream& pretty_print(std::ostream& os, const std::array<char, S>& arr)
{
	os << '[';
	for (auto& e : arr)
	{
		os << e;
	}
	
	os << ']';

	return os;
}

// this second implementation specialises the std::array class, not the function itself
// remember that function templates cannot be specialised

// variables can also be templates, intoduced in c++ 14
// variable templates allow us to define variables that are templates either at namespace scope, where they represent a family of global variables, or at class scope where they represent static data members

template <class T>
constexpr T Pi = T(3.1418592);

template <typename T>
T sphere_volume(const T r)
{
	return 4 * Pi<T> *r * r * r / 3;
}

// now no matter the type of r, we will have the same Pi type, which avoids any compiler warnings

// remember that in a global content, variable templates represent a family of values
// but in a class, they represent static data members and need to be declared with the static keyword

struct math_constructs
{
	template<class T>
	static constexpr T Pi = T(3.141592);
};

template <class T>
T sphere_volume_class(const T r)
{
	return 4 * math_constructs::Pi<T> *r * r * r / 3;
}

/*
You can declare a variable template in a class and then provide its definition outside
the class. Notice that in this case, the variable template must be declared with static
const and not static constexpr, since the latter one requires in-class initialization:
struct math_constants
{
   template<class T>
   static const T PI;
};
template<class T>
const T math_constants::PI = T(3.1415926535897932385L);  */

// alias templates:
// an alias is a name used to refer to a type that has been previously defined, whether a built-in type or a user defined type
// this is usually done to shorten long template names, and can be done with typedef or using statements

using index_t = int;
using NameValueList = std::vector<std::pair<int, std::string>>;
using fn_ptr = int(*)(int, char);

// using statements allow us to create alias templates
// an alias template is a name that refers to a family of types
// remember that a template is not a class, a function or variable but a blueprint that allows us to create a family of these

template <typename T>
using customer_addresses_t = std::map<int, std::vector<T>>;  // alias template
// since std::vetcor<T> is not a type but a family of types, customer_addresses_t<T> defines a family of types
struct delivery_addresses {};
struct invoice_addresses {};
// now we can define some type aliases
using customer_delivery_addresses = customer_addresses_t<delivery_addresses>;
using customer_invoice_addresses = customer_addresses_t<invoice_addresses>;

// alias templates can appear at namespace or class scope
/*
On the other hand, they can neither be fully nor partially specialized. However, there are
ways to overcome this limitation. A solution is to create a class template with a type alias
member and specialize the class. Then you can create an alias template that refers to the
type alias member.*/

// lambda expressions are a simplified way to define fucntion objects in the place where they are needed
/* Lambda expressions are syntactic sugar, a simplified way of defining anonymous function 
objects. When encountering a lambda expression, the compiler generates a class with 
a function-call operator */

// C++ 14 introduced generic lambdas which allow us to use the auto specifier instead of explicitly specifying types
// this transforms the generated function object into one with a template function call operator
// C++20 introduced template lambdas, which allow us to use template syntax to explicitly specify the shapre of the templatized function call operator

auto l1 = [](int a) {return a + a; };  // c++11 lambda
auto l2 = [](auto a) {return a + a; }; // c++14 generic lambda
auto l3 = []<typename T>(T a) { return a + a; }; // c++20, templated lambda

/*
auto v1 = l1(42);                      // OK
auto v2 = l1(42.0);                    // warning
auto v3 = l1(std::string{ "42" });     // error
auto v5 = l2(42);                      // OK
auto v6 = l2(42.0);                    // OK
auto v7 = l2(std::string{"42"});       // OK
auto v8 = l3(42);                      // OK
auto v9 = l3(42.0);                    // OK
auto v10 = l3(std::string{ "42" });    // OK
*/

/*
Generic lambdas, introduced in C++14, help us avoid writing the same lambdas
for different types. The lambda templates for C++20 allow us to specify the form of
the generated call operator with the help of template syntax and semantics.

templated lambdas give us more control over types than generic ones, e.g. T a, T b makes it clear a and b are of the same type so this functor is only instantiated once. auto a, ayto b does not, so many can be instantiated

*/

// variadic templates

int main() {

	foo<double> a;
	foo<double> b;  // a.value=0, b.value=0
	foo<int> c;        // c.value=42

	a.value = 100;     // a.value=100, b.value=100, c.value=42

	std::cout << a.value << std::endl;  // 100
	std::cout << b.value << std::endl;  // 100
	std::cout << c.value << std::endl;  // 42

	foo_1<int> f;
	func(f);  // no <int> needed for function, it can work out specialisation automatically

	double_func(1, 'a');
	std::string s1{ "Yo!" };
	double_func(1,"Yo!");  // this passes int and const char *
	double_func(1, s1);

	std::array<int, 9> arr{ 1, 1, 2, 3, 5, 8, 13, 21 };
	pretty_print(std::cout, arr);  // [1,1,2,3,5,8,13,21]

	std::array<char, 9> str{'t', 'e', 'm', 'p', 'l', 'a', 't', 'e'};
	pretty_print(std::cout, str);
}