# include <iostream>
# include <algorithm>
# include <string>
# include <vector>

// modern c++ has lambda expressions
// these can be thought of as anonymous local functions
// when the compiler encounters a lambda expression, it will generate code that defines a functor
// the functor will have a unique name chosen by the compiler, the functor call operator will have the same body as the lambda expression
// It will have the same return type as the lambda expression
// The compiler will add code to create a fucntor object

// lambda expressions are anonymous and defined inline ( you just write the code where the lambda expression is)
// to define a lambda expression, we put [] for the function name
// we write arguments in the usual way
// we write the function body the same was as for an inline function
// if we write this as a single statement that returns a value, the compiler will always be able to deduce the return type

// e.g. [] (int n) {return (n&2 == 1);} // return type is deduced as bool

// this statement causes the compiler to create a functor object, the functor will be equivalent to is_odd

/* example of a lambda expression as the predicate:
auto odd_it = find_if( cbegin(vec), cend(vec), [] (int) { return (n&2 == 1);} );    // return type is deduced as vool, lambda expression with one argument
*/

// lambda expression is used to replace the callable object

bool equal_strings( const std::string& str1, const std::string& str2){
    return equal(cbegin(str1),cend(str1),cbegin(str2),cend(str2), [] (char lc,char rc) {return toupper(lc) == toupper(rc);});     // lambda function written
    }

void test(const std::string& str1, const std::string& str2) {
    std::cout << str1 << " and " << str2 << " are " << (equal_strings(str1,str2) ? "" : "not") << " equal";
}

// a lambda expression has access to non-local variables, it also has access to static variables in the same scope
// by default, lambda expressions have very limited access to local variables, this is in the scope where the algorithm is being called
// a lambda expression can read but not modify local variables which are integers or enums and were initialised with a constant expression
// a lambda expression can access local variables which are references and were initalised with a constant expression
// the two above statements depend on the compiler, some compilers may not allow this



int main(){
// the equal() algorithm compares elements in two containers
// e.g. bool cmp = equal(cbegin(ct1), cend(ct1), cbegin(ct2), cend(ct2));
// this iterates through each element in ct1 and compares it to the corresponding element in ct2
// it returns false as soon as it encounters a mismatch ( if ct1 has more elements, it always returns false, if ct2 has more elements, the extra elements are ignored)
// by default, the == operator is used to compare the elements, if the containers are std::string, the comparison will be case-sensitive
// there is an overload of the equal() algorithm which takes a predicate, the predicate will be called instread of the == operator, we use the predicate to define what we mean by equality
// we can write a lambda expression for the predicate, this will be passed one character from each string as arguments, converts both characters to uppercase and returns true if they're equal, false otherwise


  test("Asad","Asad");
  std::cout << std::endl;
  test("Asad","Aisha");
  std::cout << std::endl;
// if a lambda expression needs full access to local variables, it can capture them, this is done by putting the local variables inside the []
  std::vector<std::string> people {"Asad", "Zareen", "Mahreen", "Misha", "Alayna", "Iddy"};
  int n {5};  // declare a local variable
  auto result = find_if(cbegin(people),cend(people), [n](const std::string& str) {return str.size() > n;});
  // by putting variable n within the [], we can use it in the lambda expression, it has been captured
  if (result != cend(people)){
      std::cout << *result << std::endl;
  }
// a lambda with capture is implemented as a "functor with state"
// this functor has a private data member which stores the variable, it is initialised in the functor' ocnstructor, the data member is available in the operator() body
// by default the captured variable is passed to the constructor by value and the data member is const

// but imagine we wanted to keep a counter of the indexes so we could know chih index contains our result
// you wouldnt be able to update the counter in the lambda by default because the captured varibles are const
// but we can declare the lambda to be mutable to mitigate this

  int counter {-1};
  auto result2 = find_if(cbegin(people),cend(people), [n, &counter] (const std::string& str) mutable {++counter; return str.size() > n;});  // make the actual instructions mutable
  // pass counter by address because we aactually want to change the value, not just make a copy
 std::cout << counter;

}