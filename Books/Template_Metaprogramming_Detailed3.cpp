# include <iostream>
# include <functional>
# include <array>
# include <utility>
# include <tuple>
# include <vector>


// variadic templates are templates with a variable number of arguments
// they use ... to specify a pack of arguments, which can have different syntax depending on its use
// 
// IMPORTANT NOTE: template<typename... T> means that T can actually be of several different types!

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
template <typename... T> // T is a list of types, this indicates that the function deals with a list of types
struct sum_wrapper
{
	sum_wrapper(T... args)  // capture the list of types T and refer to them as arg
	{
		value = (... + args);  // fold expression, unpack the args
	}
	std::common_type_t<T...> value;  // expand type T in template parameter list, std::common_type_t<T...> will expand to the equivalent of a comma seperated list of template arguments
};

template <typename... T>
void parenthesized(T... args)
{
	std::array<std::common_type_t<T...>, sizeof...(T)> arr{ args... }; // std::array<int,4> {1,2,3,4}, args... is expanding the values of parameter pack args, which is the comma seperated list of arguments
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


// brace enclosed initializers
template <typename... T>
void brace_enclosed(T... args)
{
	int arr1[sizeof...(args) + 1] = { args...,0 };  // compile time array created // arrg1{1,2,3,4,0}
	int arr2[sizeof...(args)] = { step_it(args)... }; // arr2: {2,3,4,5}
}


// class templates may also have a varable number of template arguments, this is how we can build tuples and variants, which reside in the standard library
// a tuple is a type that represents a fixed-size collection of heterogenous values, can store objects of multiple types
// when implementing a variadic function template, we used a recursion pattern with two overloads, one for the general case and another for the base case
// the same approach has to be taken with variadic class templates, except that we need to use specialisation for this purpose


// primary template, two parameters, type template and parameter pack, so there must be atleast 1 type specified for instantiating this template
template <typename T, typename... Ts>
struct tuple  
{
	tuple(T const& t, const Ts&... ts) : value(t), rest(ts...){}  // rest takes in the expansion of the arguments, because its another tuple, the first argument will be T and the second will be a tuple with the remainder of the Ts arguments

	constexpr int size() const { return 1 + rest.size(); }

	T value;
	tuple<Ts...> rest;  // expansion of the template type arguments, rest is another tuple
	
};

template <typename T>  // tuple with a single element, partial specialisation, this is the base case
struct tuple<T>
{
	tuple(const T& t) : value(t) {}
	constexpr int size() const { return 1; }
	T value;
};

/* The primary template tuple has two member variables: value, 
of the T type, and rest, of type tuple<Ts…>. This is an expansion of the rest of the 
template arguments. This means a tuple of N elements will contain the first element and 
another tuple; this second tuple, in turn, contains the second element and yet another 
tuple; this third nested tuple contains the rest. And this pattern continues until we end up 
with a tuple with a single element. This is defined by the partial specialization tuple<T>. 
Unlike the primary template, this specialization does not aggregate another tuple object. */


// fold expressions
// a fold expression is a expression imvolving a parameter pack that reduces 9or folds) the elements of the parameter pack over a binary operator

template<typename... T>  // pack of types
int sum_again(T... ts)   // pack of args
{
	return (... + ts);  // unary left fold, this does the operation on arg1 and arg2, then the result of thet with arg3, all the way to argN
}

// no need for overloaded functions anymore, the expression (... + args) represents the fold expression, which upon evaluation becomes ((((arg0 + arg1) + arg2) + … ) + argN)

// unary fold expressions must have non empty expansions
// binary fold expressions do not have this issue


template<typename... T>
int sum_from_zero(T... ts)
{
	return (0 + ... + ts);
}


// fold expression to insert multiple elements into a vector at once
template<typename T, typename... Args>
void push_back_many(std::vector<T>& v, Args... args)
{
	(v.push_back(args), ...);  // parenthesis are very important for fold expressions
}

/* The parameter pack args is used with the v.push_back(args) expression that 
is folded over the comma operator. The unary left fold expression is (v.push_
back(args), ...)  */







int main()
{
	std::cout << min<double>(14.5, 9.0) << std::endl;
	std::cout << min<int, int, int, int, int>(1, 2, 4, 6, -19, 0) << std::endl;  // compile time auto deduction, dont need to use templated function call

	multipacks<int>(1, 2, 3, 4, 5);  // 1,4, compiler deduces the first int is in specified parameter pack, rest must be in second
	multipacks<int, int, int, int, int>(1, 2, 3, 4, 5);  // 5,0, 5 ints clearly given in templateed function call therefore other pack is zero
	multipacks<int, double>(1, 2, 3.3, 4.4, 5.5);// 2,3, defferent types so compiler can use that to work out which is which
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


	// tuples have a member function called get which allows us to access elements within them

	tuple<int> one(42);
	tuple<int, double> two(42, 42.0);
	tuple<int, double, char> three(42, 42.0, 'a');

	//std::cout << get<0>(one) << std::endl;

	std::cout << three.rest.rest.value << std::endl;  // real tuples have get function so we dont need to do this.The template arguments are the index and a parameter pack of the tuple types. 
	sum_again(1, 2, 3, 4, 5); 
	//sum_again();  // throws error
	sum_from_zero(); // no error




}
