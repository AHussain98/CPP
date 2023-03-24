# include <iostream>
# include <algorithm>
# include <list>

// template classes work very much like other classes
// template classes can be part of inheritance hierarchies, base or derived classes
// template classes can be composed

// a templated member function of a class is called a "member template", the class does not have to be templated to have a member template
// a member template can have different parameters from the class
// a member template cannot be virtual

// although the parameters are different when there is a member template, there is a coupling between the class and member templates
// the member template has to be able to operator on objects of the type of teh class template
// c++20 has concepts, which allow us to express this requirement as a template definiion

// templates are generic, when we write a class or function template, we will get the same behaviour for every type that we instantiate it with
// sometimes we may wish to have different behaviour for some types, we may want to handle some types differently
// we can do this with a template specialisation
// this is done by leaving the <> empty : template<> , and then writing the paramter types nd implementing however you want
// usually the specialisation comes immediately after the generic template
// if the specialization comes before the generic template, it will not compile
// if the generic template is not visible, the specialization will not compile
// if the specialization is not visible to code that uses it, the compiler will instantiate the generic template instead

// when a template is instantiated, the compiler has to choose which version to use
// it will always choose the most specific alternatic which matches
// e.g. vector<bool> is more specific then vector<T> with T == bool
// the compiler will instantiate the bool specialisation


// generic vector class
template<typename T>
class Vector{
    public:
        void identify(){
            std::cout << "Vector<T> \n";
        }
};

// specialisation of vector class for bool type
template<>
class Vector<bool>{ // put the specialisation parameter in angled brackets here, after name of class
    public:
        void identify(){ std::cout << "Vector<bool> \n";
        }
};

// now lets try this with functions
// generic reverse function
template<typename T>
void Reverse( T& container){
    std::cout << "calling generic reverse \n";
    std::reverse(begin(container),end(container));
}

// specialisation of reverse function for std::list, list is itself a class template
// the element type is part of the lists type
// we need to provide a template parameter for std::lists element type
template <typename Elem>
void Reverse(std::list<Elem>& container){
std::cout << "calling specialisation of reverse for list<Elem> \n";
container.reverse(); // more efficient to call the lists member function
// we want this to work for any type of list, and the type of the list depends on the type of the element, so make the element the specialisation
}

// template specialisation requires a single type per parameter
// occasionally, we may want to have a family of types instead of a single type
// we can use partial specialization for this, only allowed for class and value templates (not for function templates), there are a number of limitations on the arguments
// we can do partial specialisation by putting the specialzed type in <> immediately after the generic template call

// partial specialization of vector class for pointers
template <typename T>
class Vector<T*> { // so partial specialzation is using pointers instead
public:
  void identify(){
        std::cout << "Vector<T *> \n";
    }
};


int main(){

Vector<bool> v;
v.identify();    // calls the specialised version
Vector<int> x;
x.identify(); //generic


std::list<int> lis {1,6,3,19,9,4,3,5};
Reverse(lis); // call specialised reverse
for (auto i : lis){
    std::cout << i << ", ";
}

std::cout << std::endl;

Vector<int *> vec; // of type pointer
vec.identify();
}