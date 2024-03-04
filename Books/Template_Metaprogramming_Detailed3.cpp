# include <iostream>
# include <functional>
# include <array>


// variadic templates are templates with a variable number of arguments
// they use ... to specify a pack of arguments, which can have different syntax depending on its use

// following example works using compile time recursion and function overloading for the base case
template <typename T>
T min(T a, T b)  // function template with two parameters that returns the minimum, base case
{
	return a < b ? a : b;
}
//and now an overload for the min function
template <typename T, typename... Args>  // ellipsis used here to specify a pack of parameters function template with variable number of arguments
T min(T a, Args... args)  // pack of parameters specified in the function parameter list
{
	return std::min(a, min(args...));  // expand the pack in the body of the function, function recursively calls itself with expansion of parameter pack
	// the result of the expansion is a comma seperated list of zero or moee values, important note: comma seperated!!!!!
}

// variadic functions rely on overloaded functions
// template parameter packs can be defined for type templates, non-type templates and template template parameters

// the above generates a bunch of overloads such that min(1, 5, 3, -4, 9) expands to min(1, min(5, min(3, min(-4, 9))))

// in practice, compilers perform a lot of optimisations such as inlining as much as possible so that there will be no actual function calls
// the evaluation of the call to min(1,5,3,-4,9) is done at compile time and the result loaded directly inot the register
// it can be done at compile time since everything is known at compile time
// taking in arguments at runtime prevents this obviously

// the standard does not have a limit for the number of arguments in a parameter pack
// the number of arguments in a parameter pack can be retrieved at compile time with a sizeof... operator which returns a constexpr value of size_t type

template <typename T, typename... Args>
T sum(T a, Args... args)
{
	if constexpr (sizeof...(args) == 0)
		return a;
	else
		return a + sum(args...);
}

// so if the number of args in the pack is zero, just return the value, otherwise we add the first argument to the sum of the remaining ones
/*
Notice that sizeof…(args) (the function parameter pack) and sizeof…(Args) (the
template parameter pack) return the same value. On the other hand, sizeof…(args)
and sizeof(args)... are not the same thing. The former is the sizeof operator
used on the parameter pack args. The latter is an expansion of the parameter pack args
on the sizeof operator.

sizeof...(args) tells how many elements in the param pack
sizeof(args)... gives sizeof(arg1), sizeof(arg2) etc for every param in the pack


*/

// typically the param pack is the last parameter of a function or template, but it can also not be if the compiler can work out the divison
template <typename... Ts, typename... Us>
constexpr auto multipacks(Ts... args1, Us... args2)
{
	std::cout << sizeof...(args1) << " " << sizeof...(args2) << "\n";
}
// this function can work on different types, or the same 

// multiple parameter packs are not specififc to variadic function templates
// they can also be used for variadic class templates in partial specialisation, provided the compiler can deduce the template arguments

template <typename, typename>
struct func_pair;

// specialisation
template <typename R1, typename... A1, typename R2, typename... A2>
struct func_pair<R1(A1...), R2(A2...)>
{
	std::function<R1(A1...)> F;  // R1 is function return type and A1 is expanded function parameters
	std::function<R2(A2...)> G;
};

bool twice_as(int a, int b)
{
	return a >= b * 2;
}

double sum_and_div(int a, int b, double c)
{
	return (a + b) / c;
}


// possible contexts for parameter pack expansion:
// template parameter list:
template<typename... T>
struct outer
{
	template<T... args>  // use parameter pack to specify parameters for the template
	struct inner {};
};

// template argument list
template <typename... T>
struct tag {};

template<typename T, typename U, typename... Args>
void tagger()
{
	tag<T, U, Args...> t1;  // different methods of unpacking the parameter pack will lead to different instantiations of tag{}
	tag<T, Args..., U> t2;
	tag<Args..., T, U> t3;
	tag<U, T, Args...> t4;
}

// function parameter list, specifying parameters for a function template
template <typename... Args>
void make_it(Args... args)  // pack of parameters specified in the function args
{
	std::cout << "There were " << sizeof...(args) << " arguments! \n";
}

// function argument list, when the expansion pack appears inside the parenthesis of a fucntion call, the largest expression or brace initialisation list to the left of the ellipsis is the pattern that is expanded
template <typename T>
T step_it(T value)
{
	return value + 1;
}
template <typename... T>
int sum(T... args)
{
	return (... + args);  // how does this work?
}
template <typename... T>
void do_sums(T... args)
{
	auto s1 = sum(args...);  // sum 1,2,3,4
	auto s2 = sum(42, args...);  // sum(42,1,2,3,4)
	auto s3 = sum(step_it(args)...);  // sum(step_it(1),step_it(2),...., here since step_it() is to the left of the ellipsis, this si what is expanded
	std::cout << s1 << " " << s2 << " " << s3;
}


// parenthesized initializers: when the expansion pack appers inside the parenthesis of a direct initializer, function sytle cas, member initialiser, new expression, the rules are the same as for the function argument lists
template <typename... T>
struct sum_wrapper
{
	sum_wrapper(T... args)
	{
		value = (... + args);
	}
	std::common_type_t<T...> value;
};

template <typename... T>
void parenthesized(T... args)
{
	std::array<std::common_type_t<T...>, sizeof...(T)> arr{ args... }; // std::array<int,4> {1,2,3,4}
	sum_wrapper sw1(args...);  // value = 1 + 2 + 3 + 4
	sum_wrapper sw2(++args...);  // value = 2 + 3 + 4 + 5
}

// base specifiers and member initalisation lists: a pack expansion may specify the list of base classes in a class decleration. In addition, it may also appear in the member initaliser list, as this may be necessary to call the constructors of the base class
struct A {};
struct B {};
struct C {};

template<typename... Bases>
struct X : public Bases...
{
	X(const Bases& ... args) : Bases(args)... {}
};

// the capture clause of a lambda expression may contain a parameter expansion
template <typename... T>
void captures(T... args)
{
	auto l = [args...]() {return sum(step_it(args)...); };
	auto s = l();
	std::cout << s << '\n';
}



int main()
{
	std::cout << min<double>(14.5, 9.0) << std::endl;
	std::cout << min<int, int, int, int, int>(1, 2, 4, 6, -19, 0) << std::endl;  // compile time auto deduction, dont need to use templated function call

	multipacks<int>(1, 2, 3, 4, 5);  //1,4, compiler deduces the first int is in specified parameter pack, rest must be in second
	multipacks<int, int, int, int, int>(1, 2, 3, 4, 5);  //5,0, 5 ints clearly given in templateed function call therefore other pack is zero
	multipacks<int, double>(1, 2, 3.3, 4.4, 5.5);//2,3, defferent types so compiler can use that to work out which is which
	multipacks(1, 2.2f, 3.14);  // 0,3 compiler assumes all aere part of second parameter pack

	func_pair<bool(int, int), double(int, int, double)> funcs{ twice_as, sum_and_div }; // create the object and bind the member functions to these two

	std::cout << funcs.F(42, 12) << '\n';
	std::cout << funcs.G(42, 12, 10.0) << '\n';
	make_it(1, 2, 'd');

	do_sums(1, 2, 3, 4);
	parenthesized(1, 2, 3, 4, 5);

	A a;
	B b;
	C c;
	X x(a, b, c);
	std::cout << std::endl;
	captures(1, 2, 3, 4, 5);
}
