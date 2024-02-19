# include <iostream>

// template metaprogramming is a technique that uses templates as blueprints for the compiler to generate code and help developers avoid writing repetitive code
// callbacks are functions passed as arguments that will be invoked when necessary

// templated version of the max function
template <class T>
T max(const T arg1, const T arg2)
{
	return arg1 > arg2 ? arg1 : arg2;
}

// T is called a type template parameter, T is a parameter so it can have any name
// the template that you put into the source code is only a blueprint, the compiler will generate code from it based on its use
// more precisely, the compiler will generate a function overload for each type the function is used with, as long as that type has overloaded the > operator

// the syntax for declaring templates is the same whether they represent functions, classes or variables
// function template is the term used for a templated function, an example is the max template seen previously
// class template is the term used for a templated class (or struct or union)
// variable template is the term used for templated variables, such as arg1
// alias template is the term used for templated type aliases

// templates are parameterised with one or more parameters, these are called template parameters and can be of 3 categories:
// type template parameters, such as typename T, where the parameter represents a type specified when the template is used
// non type template params, such as size_t or int or float or pointer or lvalue reference or enum
// templated type parameters, where the type of a parameter is another template

// templated can be specialised by providing alternate implementations. There are two forms of specialisation:
// partial specialisation, where some of the parameters are specialised
// full specialisation, when all the template arguments are provided

// the process of generating code from a template by the compiler is called teplate instantiation
// this happens by substituting the template arguments for teh template parameters used in the definition of the template, so int gets places everywhere T appeared when vector<int> is instantiated, for example

// template instantiation can be either implicit or explicit
// implicit instantiation: this occurs when the compiler instantiates a template due to its use in code. This only happens for the arguments that are in use in code.  For instance, if the compiler encounters the use of vector<int> and 
// vector<double>, it will instantiate the vector class template for the types int and double and nothing more.

// explicit instantiation: we can tell the compiler exactly which types to instantiate, even if these types are not explicitly used in our code

// templates help us to avoid writing repetitive code
// however they can be difficult to write and understand, potentially also increaing the size of the binary and longer compilation time
// its also hard to validate code that the compiler is writing, this means we need thorough unit testing

// function templates are defined in a similar way to functions but the function decleration is preceded by the template with angled brackets for the template parameters
template<class T>
T add(T const a, T const b)
{
	return a + b;
}

// remember that function templates are only blueprints for creating actual functions, and only exist in source code
// unless explicitly called in source code, the function templates will not be present in the compiled executable
// when the compiler encounters a call to a function template, and is able to match the supplied arguments and their types to a function templates parameters, it generates an actual function from the template and the arguments used to invoke it

auto a = add(5, 6);  // compiler type auto deduction, don't need to specify template types
// this is the same:
//auto a = add<int>(42, 21);
//auto a = add<>(42, 21);  // both valid ways to call the templated function

// if the two arguments had different types, this would be a compilation error as the compiler is not able to match the function 
// auto d = add(41.0, 2)  // error

/*
As long as the two arguments have the same type and the + operator is available for
the type of the arguments, you can call the function template add in the ways shown
previously. However, if the + operator is not available, then the compiler will not be
able to generate an instantiation, even if the template parameters are correctly resolved.
*/

// defining class templates is done in a similar manner

template <typename T>
class wrapper
{
public:
	wrapper(T const v) : value(v){}  // parameterised constructor
	const T& get() const { return value; }
private:
	T value;
};

// if this class template is not used anywhere in code, the compiler will not generate code for it
// to generate this code, the class must be instantiated with the correct parameters to match the template:

wrapper<int> w1(5);  // instantiation of templated class, wraps an int
//wrapper w2(2.17);  // class template argument deduction, no need to specify, since C++17
//wrapper w3("Hi"); // wraps a const char *

// class templates can be declared without being defined
// however, a class template must be defined at the point where template instantiation occurs (when an object is created) otherwise compiler will error
// this means the definition of a templated class must come before the first instantiation is executed!

// class member functions can also be templated
class composition {
public:
	template <typename T>
	T add(const T a, const T b)  // member function is templated but class is not
	{
		return a + b;
	}
};


composition c1;
//c1.add<int>(1, 2);
int val = c1.add<int>(1, 2);  // we use the templated version of the function since the class is not templated
// if the class was templated, we would have to define the templated type when instantiating the class, and wouldn't be able to use CTAD for this function
int val2 = c1.add(2, 3);  // works because only function is templated, not class, so comiler can figure out what templated type is

// we can have member functions of class templates and classes with templated functions
// we can also have member function templates of class templates
// the template parameters of the member function template must differ from the template parameters of the class template, otherwise the compiler generates an error

template <typename T>
class wrapper_2 {
public:
	wrapper_2(const T v) : value(v) {}

	const T& get() const { return value; }

    template <typename U>
	U as() const {
		return static_cast<U>(value);
	} // cast value from T to U
private:
	T value;
};

// these parameters represent types supplied at instantiation explicitly by the user or implicitly by the compiler when it can deduce them
// these kind of template parameters are called type parameters
// templates can also have non-type template parameters and template type template parameters






int main()
{
	wrapper_2<double> a(5.5);

	std::cout << a.as<int>();  // loses the 0.5




}