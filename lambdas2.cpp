# include <iostream>
# include <algorithm>

// to change a captured variable, we need to capture it by reference
// to do this, we put an & before the captured variable

/*   int n {2}
   [&n] (int arg) { return n*arg}  // captures local variable n by reference */

// a lambda with capture by reference is also implemented as a "functor with state"
// however, the member variable is a reference to the captured variable
// the captured variable will be passed to the functor constructor by reference

// we can make a lambda function capture all variables in scope, [=] captures all variables in scope by value and [&] by reference
// safer to just capture everything by value and anything we want to change by reference
// e.g. [=, &x] is capture everything by value but only x by reference

// lambda functions can be used with member functions, not just in an algorithm case, where we were using the lambda as a callable object
// member functions are always called on some object, we can write a lambda expression within that member function, the pointer to this object is actually passed as an extra argument to the member function that we don't actually see in the signature
/* for example, take the member function test.do_it()
    this is called as Test::do_it(&test);
    &test is available in the member function body as "this" */
    //  if we call the member function of an object, the address of the object is passed implcitly as the first argument
// in effect, "this" is a variable in the scope of the member function
// when we have a lambda expression inside a member function, it is allowed to capture "this"
// this allows the lambda expression to access data members and call other member functions of the class
// to capture the class object, we put [this] or [&] or [=]
// these all capture the object by reference, even the =

class Test{
    int time {10}; //data member
    public:
        void countdown()
        {  [this] () {     // member function calls a lambda expression, class object captured by reference
        if (time > 0){
            std::cout << time << std::endl;
        }
        else { std::cout << "Liftoff!";
        }
        time--;
        }(); // we have to put this pair of brackets after the deifnition of the lambda expression, this is what causes the code to execute after the functor class is created
        // the () at the end tells the compiler to create an object of the fucntor class and call the function call operator
        }

};  // in c++ 17, we also have the option of doing [*this], which will capture the object by value
// so the lambda expression has an immutab;e copy of the object, this prevents it from accidentally canging the object

// lambda expressions are mainly used for implementing temporary functions, however lambda expressions are first class objects, we can store them in variables and pass them to functions
int max {10};
auto is_longer_than = [max] (const std::string& str) {return str.size() > max;}; // store this lambda function in a variable, type has to be auto as its compiler defined
// so we can pass this as a callable object to an algorithm call
// auto res = find_if(cbegin(words),cend(words), is_longer_than)

// we can also return a lambda expression from a function
/* auto greeter(const string& salutation){

return [salutation] (const string& name) {return salutation + " , "s + name;};

calling this function will return a lambda which captures salutation, the lambda takes an argument itself
store the lambda function in a variable:  auto greet = greeter("Hello"s);
greet is a lambda which takes a name as argument and adds a greeting to it

greet("Asad"s); // this will print Hello, Asad
*/

// we can use lambdas to partially eveluate data, this reduces computation and makes processing simpler and more efficient
// we canuse lambda expresions with capture to implement this, as we ahve done above
// when we call greeter(), it performs a partial evaluation
// it processes the salutation part of the greeting, but not the name
// the code which issues a greeting only has to provide a name, it does need to process the salutation or know how it is processed
// the salutation processing is written once, instead of every time someone is greeted

// remember that returning a reference to a loal variable is dangerous
// this is because local variables are destroyed when they go out of scope, so calling thier reference can cause undefined behaviour and crash programs
/* eg.   int& func() {  // dangling reference
          int x {7};
          return x;
      }               // x is destroyed when the function returns
 so this function will return a reference to an object that no longer exists, which can be dangerous

 the same can happend with lambdas, ensure when you call a stored lambda that the variable it has captured is still in scope (when you have captured by reference) */

//In C++, we can declare a function as inline. This copies the function to the location of the function call in compile-time and may make the program execution faster.
// labdas are liek the manual version of this

int main(){

       Test test;
       for (int i = 0; i < 12; ++i){
           test.countdown();
       }


}