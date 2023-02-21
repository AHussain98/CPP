# include <iostream>

// modern c++ allows programmers to force the compiler to synthesize special member functions
// this is done by putting =default after the function parameter list

/*
Test()=default // synthesized default constructor
Test(const Test&)=default  // synthesized copy constructor
Test& operator= (const Test&)=default  //synthesized assignment operator

*/

// this is useful because we can look at a class and see which special member functions the class has, and documents that the member function has been deliberatley defaulted
// also, if data members are added or removed, the compiler will automatically update the definition


// we can prevent programs from using copy constructors and assignment operators by defining them as private within the class
// in modern c++, we can do the same thing more elegantly by using the keyword delete
/*
Test(const Test&)=delete;    //deleted copy constructor, you can't use the copy constructor for the test class now
Test& operator=(const Test&)=delete;  // we've deleted the assignment operator, can't instantiate Test objects via this method now
*/


// a deleted function is defined but cannot be called, if it is called, the compiler will throw an error
// unlike =default, any function can be deleted, even non member functions, but this is mostly used for copy, default and assignment operators
int main(){



}