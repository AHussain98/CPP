# include <iostream>
# include <vector>
# include <set>

// C++ templates allow programmers to write generic code, which works without modification on different data types, 
// templates can be used to avoid having to write computationally expensive OOP techniques, such as design pattern
// a template is a mechanism to generate parameterised code, so that different versions of the same programming definition (class or function) can be generated for each parameter
// even single variables can be templated
// one of the applications of templated is to perform compile time computations. Performing these at compile time instead of runtime is a performance enhancing technique that can save computation and make the application run smoother
// templates save us casting or time consuming polymorphic techniques

// templates can be used to implement compile time polymorphism, they avoid the need to perform run time type checking like in dynamic polymorphism
// templates with an empty parameter list symbolise this is a specialisation of a previously defined member. template<> means specialisation

template<typename T>
class normalisation {
	public T type;
	static void normalise(T& arg);
};

// lets create specialised versions of the normalise function

template<>  // empty parameter list, specialisation of a templated member function
void normalisation<std::vector<double>>::normalise(std::vector<double>& v)
{
	// call normalisation fucntion that's specific to arrays
}

template<>
void normalisation<std::set<int>>::normalise(std::set<int>& s)
{
	// call normalusation function that's specific to set
}

// at compile team, only the one that's used will be generated

// template fucntions are c++ functions that can be parameterised with one or more integral types
template <typename T>
T generic_max(T a, T b) // most generic version
{
	return a > b ? a : b;  // this will work as long as type T has the > and < operators overloaded
}

// partial specialisation is a version of a template where one or more of the parameters has been substituted by concrete types or values
template <> // specialisation hint
const char* generic_max(const char* a, const char* b)
{
	if (strcmp(a, b) > 0)
	{
		return a;
	}
	else return b;
}

// the parameter type const char * is substituted directly in the function implementation

int main()
{

}