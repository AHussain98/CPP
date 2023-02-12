#include <iostream>
#include <string>
#include <vector>

// templates are useful when we need to write code that is functionally the same but operates on different data types
// c++ allows us to write code that works with any type, this is generic programming which complies with c++'s stringly types style
// when we use the template with data of a particular type, the compiler generates code needed for that particular type, this is called am instantiation of the template
// vector<int> will cause the compiler to define a clas that is a vector of ints and insert the source code into that translation unit
// when we write a template, we use a dummy type called a template parameter to show the compiler what the code looks like, this is either a function or class template

template <class T>   // this is a function template, now the function can be used with different data types, we cna use the keyword typename or class in the parameters, same thing
T Max(const T& t1, const T& t2){
    if (t1 > t2){
        return t1;
    }
    return t2;
}
// for a template function, the compiler must be able to see the full deifnition when it is called

template <class U>
class Test{
    public: U data;
    Test(const U& data){
        this->data = data;
        std::cout << data;
    }
};

int main(){
    std::cout << Max(1,2);
    std::cout << Max(1.2,1.6); // these two methods make the compiler work out which data type to use

    std::cout << Max<double>(1.77,2.76); // now we're telling teh compiler to pick double, with functions its optional but preferred to specify the type we're instantiating
    // with a class, however, it is mandatory to define the data types we're using

    Test<int> Asad(24); //instantiate a class and make clear what the data type I'm using is
    Test<std::string> Aisha("Aisha");

    std::vector vec {1.1,1.2,1.3};

    // originally the class keyword had to be used for a template parameter, the typename parameter was added later
    // you can use either, no difference
}