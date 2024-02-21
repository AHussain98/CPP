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
	wrapper(T const v) : value(v) {}  // parameterised constructor
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
class foo {};

template <int V = 42>  // default value used, non-type template parameter
class foo {};

template<int... V>  // parameter pack
class foo {};

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
template <typename Command, void (Command::* action)() >
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

template <typename T>
class simple_wrapper
{
public:
	T value;
};

template <typename T>
class fancy_wrapper
{
public:
	fancy_wrapper(T const v) : value(v)
	{

	}

	const T& get() const { return value; }

	template<typename U>
	U as() const
	{
		return static_cast<U> (value);
	}

private:
	T value;
};


// the simple wrapper class is a class template to hold a value of type T
// fancy wrapper hides the wrapped value and provides member functions for accessing the value
// next we can implementa class template called wrapping pair that contains two values of a wrapping type

template<typename T, typename U, template<typename> typename W = fancy_wrapper>  // third argument is how to define a template template parameter
class wrapping_pair
{
public:
	wrapping_pair(const T a, const U b) : item1(a), item2(b) {}
	
	W<T> item1;
	W<U> item2
};

// wrapping pair class template has 3 parameters, T and U are type template parameters, W is a template template parameter that has a default value which is the fancy wrapper type

wrapping_pair<int, double> pair1(1,1.5);  // create object with default W type, fancy wrapper, item1 and item2 are fancy_wrappers
wrapping_pair<int, double, simple_wrapper> pair2(5, 5.6);  // create a wrapper around two simple wrapper objects

// default template arguments are specififed similarly to default function argumenrs, in the parameter list after the = sign
// they can't be used with parameter packs
// a template parameter with a default argument cannot be followed with a non default argument when defining a class template. This restriction does not apply with functions
template <typename T = int, typename U>
class bar { };   // error
template <typename T = int, typename U>
void func() {}   // OK

// a template may have multiple declartions but only one definition
// the default template arguments from all the declerations and the definition are merged, this is also done for default function arguments

template<typename T, typename U = int>
void foo();
template<template T = int, typename U>
void foo();

// this is symantically the same as declaring foo with the template <T = int, U = int> 
// Another restriction on default template arguments is that the same template parameter cannot be given multiple defaults in the same scope.
// so we cannot give T the same default in two declerations in the same scope, otherwise an error is thrown

// when a default template argument uses names from a class, the member access restrictions are checked at the decleration, not at the instantiation of the template



// instantiation
// templates are only blueprints from which the compiler creates actual code when it encounters their use
// the act of creating a definition for a function, a class, or a variable from the template decleration is called template instantiation
// templates can be instantiated implicitly or explicitly

// implicit instantiation occurs when the compiler generates definitions based on the use of templates and when no explicit instantiation is present
template<typename T>
struct foo
{
	void f();
};

foo<int> foo1;  // define a variable of type foo<int> but don't use any members
// because it encounters a foo with type int, the compiler implicitly instantiates a specialisation of foo for the int type
// because f() is delcared but not defined, the compiler may or may not define it as void f() {} in compiled code
// some compilers will ignore parts of the template that are not used, so VC++ for example will not compile the f() function at all
// other compilers will create empty functions and will check that the function decleration is semantically valid before instantiating

// For function templates, implicit instantiation occurs when the user code refers to a function in a context that requires its definition to exist, such as calling the function

// For class templates, implicit instantiaion occurs when the user code refers to a template in a context when a complete type is required or when completeness of the type affects the code
// one example is an object being constructed 
// this is not the case when declaring pointers to a class template however

foo<int> foo2;  // implicit instantiation of foo with int must be done here, as we have created an object
foo<double> * footPtr;  // pointer to foo<double> instance, this does not instantiate the foo<double> type, as pointer is not pointing to an instance as yet

// if we were to call fooPtr->f(), then the compiler would have to create an instance of foo<double> and also create its foo<double>::f() function

// however, if you are converting a pointer, the compiler will implicitly instantiate the class you were converting from.

/*
template <typename T>
struct control
{};
template <typename T>
struct button : public control<T>
{};
void show(button<int>* ptr)
{
   control<int>* c = ptr;
}
In the function show, a conversion between button<int>* and control<int>*
takes place. Therefore, at this point, the compiler must instantiate button<int>.

*/

// when a class template contains static members, these members are not implicitly instantiated when the compiler implicitly instantiates the class template, only when the compiler needs their definition
// every specialisation of the class has its own version of the static data

// explicit instantiation is where we explicitly tell the compiler to instantiate a class template or a function template, this can be definition and decleration
// an explicit instantiation definition may appear anywhere in the program but after the definition of the template it refers to

/*
• The syntax for class templates is as follows:
template class-key template-name <argument-list>  // class key can be class, union or struct

• The syntax for function templates is as follows:
template return-type name<argument-list>(parameter-list);
template return-type name(parameter-list)*/

// for both class and function templates, an explicit instantiation definition with a given argument list can only be given once on the entire program

namespace ns
{
	template<typename T>
	struct wrapper {
		T value;
	};

	template struct wrapper<int>;   // explicily instantiate the integer version of wrapper
}

template struct ns::wrapper<double>;  // explicitly instantiate the double version of wrapper

// explicit instantiation must appear in the same namespace as the template it refers to, or otherwise the name must be fully qualified. Both of these are therefore legal.

// function explicit instantiation definition

namespace ns {
	template<typename T>
	T add(T const a, T const b)
	{
		return a + b;
	}

	template int add(int, int);  // explicit instantiation of the int type
}
template double ns::add(double, double);  // explicit instantiation of the double type


// If the explicit instantiation definition is not in the same namespace as the template, the name must be fully qualified.
// The use of a using statement does not make the name visible in the current namespace.

// When class members are used for return types or parameter types, member access specification is ignored in explicit instantiation definitions.
// this is unlike default template arguments, which cannot bypass private or protected access 

// explicit instantiation can be useful in libraries, where we want every type to be created and shared, even those the compiler may not create implicitly

// explicit instantiation decleration
// this is the way you can tell the compiler that the definition of a template instantiation is found in a different translation unit and that a new definition should not be generated
// syntax is the same as explicit instantitation definition, but with the word extern in front

/*
When you do explicit template declarations, keep in mind that a class member function
that is defined within the body of the class is always considered inline and therefore it
will always be instantiated. Therefore, you can only use the extern keyword for member
functions that are defined outside of the class body.
*/

// template specialisation





int main()
{
	wrapper_2<double> a(5.5);

	std::cout << a.as<int>();  // loses the 0.5

	hello_command cmd;


	//auto w3 = std::make_unique<smart_device<hello_command, &hello_command::say_hello_in_english>>(cmd);
	//w3->output();

	//auto w4 = std::make_unique<smart_device<hello_command, &hello_command::say_hello_in_spanish>>(cmd);
	//w4->output();

	std::cout << pair1.item1.as<double>();
}

