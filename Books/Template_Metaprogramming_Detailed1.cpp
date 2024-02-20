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
		return static_cast<U = int>(value);  // default type is int
	} // cast value from T to U
private:
	T value;
};

// these parameters represent types supplied at instantiation explicitly by the user or implicitly by the compiler when it can deduce them
// these kind of template parameters are called type parameters
// templates can also have non-type template parameters and template type template parameters

// type template parameters are parameters representing types supplied as arguments during the template instantiation
// type template parameters are introduced with either the class or typename keywords
// types can also have default parameters, assigned with = like default function parameters

// c++11 introduced variadic templates, which have a variable number of arguments
// a template parameter that accepts zero or more arguments is called a parameter pack

// template arguments don't always have to represent types, they can also be compile type epressions, constants or addresses
// parameters supplied with compile time expressions are called non-type template parameters, this category of parameters can pnly have a structural type
// structural types: integrals, floating points, enum, pointer to object, function or member, lvalue reference to object or function
// cv qualified forms of these types can also be used for non-type template parameters

// examples of non-type template parameters:
template <int V>  // integral type used
class foo{};

template <int V = 42>  // default value used, non-type template parameter
class foo{};

template<int... V>  // parameter pack
class foo{};

// fixed size array class
template<typename T, size_t S>
class buffer {
	T data_[S];
public:
	constexpr T* data() const { return data_; }
	constexpr T& operator[] (const size_t index)
	{
		return data_[index];
	}
	constexpr const T& operator[] (const size_t index) const  // const version of the index operator
	{
		return data_[index];
	}
};

// instantiate 
buffer<int, 10> b1;  // instantiate the buffer, second parameter is non-type, can be exavluated at compile time
buffer<int, 2 * 5> b2; // second parameter is non-type, can be evaluated at compile time

// 10 and 2.5 are two expressions that evaluate to the same compile time value
// these two definitions are therefore equivalent, the compiler will generate the same class code to create these objects
// now specialisations:

template<>  // this indicates a specialisation of a templated type previously defined
class buffer<int, 10>  // explicit specialisation
{
	int data_[10];
public:
	constexpr int* data() const;
	constexpr int& operator[](const size_t index);
	constexpr const int& operator[](const size_t index) const;
};

// these two buffer types are different
// the use of structural types such as integer, floating point, or enums are encountered in practice more often 

struct device
{
	virtual void output() = 0;
	virtual ~device();
};

template <void (*action)()>  // function pointer is the template parameter
struct smart_device : device
{
	void output() override
	{
		(*action)();
	}
};

void say_hello_in_english()
{
	std::cout << "Hello, world! \n";
}

void say_hello_in_spanish()
{
	std::cout << "Hola mundo! \n";
}

auto w1 = std::make_unique<smart_device<&say_hello_in_english>>();  // create a unique pointer 
w1->output();

auto w2 = std::make_unique<smart_device<&say_hello_in_spanish>>();
w2->output();

// w1 and w2 are two unique ptr objects pointing to two different instances of the smart_device class

// lets try this again with pointer to member function
template <typename Command, void (Command::*action)() >
struct smart_device : device
{
	smart_device(Command& command) : cmd(command) {}
	void output() override
	{
		(cmd.*action)(); // call the function pointed to by the function pointer
	}
private:
	Command& cmd; // struct hello command then becomes a member of the class
};

struct hello_command
{
	void say_hello_in_english()
	{
		std::cout << "Hello, world! \n";
	}
	void say_hello_in_spanish()
	{
		std::cout << "Hola mundo! \n";
	}
};

// as of c++ 17, non-types can also be generated using the auto keyword
template <auto x>
auto foo()
{
	return x;
}

// foo<42> f1 returns 42
// the compiler deduces the template to instntiate as foo<int>

// by default, string literals cannot be used as arguments for non-type template parameters
// this means foo<"42"> f2 returns an error

template <size_t N>  // wrap the string literal in a structural literal class, store the chars of the string literal in a fixed length array
struct string_literal
{
	constexpr string_literal(const char(&str)[N])
	{
		std::copy_n(str, N, value);  // what does copy_N do?
	}

	char value[N];
};

template<string_literal x>  // foo template is then changed to string_literal
auto foo() {
	return x;
}
foo<"42"> f3;  // can now work


// the last category of template parameter is templates themselves
// as of cpp 17, both the class and typename keywords can be used to introduce a template template parameter
















int main()
{
	wrapper_2<double> a(5.5);

	std::cout << a.as<int>();  // loses the 0.5

	hello_command cmd;


	auto w3 = std::make_unique<smart_device<hello_command, &hello_command::say_hello_in_english>>(cmd);
	w3->output();

	auto w4 = std::make_unique<smart_device<hello_command, &hello_command::say_hello_in_spanish>>(cmd);
	w4->output();
}


