# include <iostream>
# include <string>
# include <algorithm>
# include <vector>

// the c++ library provides some function objects
// these are generic operators for arithmetic, logical and relational operations
// they are implemented as templated functors, they are completely generic and will work for any type that supports the operator

// for example, the less<T>() library functio operator implements the less than operator as a callable object

int main(){
std::vector<std::string> vec {"Asad", "Misha", "Alayna", "Iddy"};

std::cout << "Vector before sort() \n";
for (auto i : vec){
    std::cout << i << ",";
}
std::cout << std::endl;

std::sort(begin(vec),end(vec), std::less<std::string>()); // here, less<T>() is used as the predicate
// upon seeing this, the compiler will generate a functor such as this :
/*     template<typename T>
        class less{
          public:
          bool operator() (T arg1, T arg2) {
          return arg1 < arg2;
      }
  };  */

std::cout << "vector after sort() \n";
for (auto i : vec){          // objects now sorted in ascending alphabetical order
    std::cout << i << ",";
}

// there are many of these available in the standard library
    return 0;
}