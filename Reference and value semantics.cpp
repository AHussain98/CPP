#include <iostream>
#include <string>
#include <vector>
using namespace std;

// c++ will create copies of variables passed to fucntions unless told not to via pointer or reference
// this is known as value semantics
// if we want reference semantics, we can pass arguments by reference so they act as an alias to an existing object, allocate objects to heap so they exist beyond their scope
// stack objects are destryed once they are out of scope
//c++ has its advantages being default value semantic:
// copying objects can be mitigated using the above techniques
// no garbage collection avoids overhead and speeds up compilation
// local variables are destroyed deterministically instead of randomly like with a grabage collector
//as soon as program reaches end of scope, objects are destroyed in the reverse order of creation and memory used by that object becomes available again

// traditional c++ uses NULL, but for pointers we can now use nullptr, which is compatible with any data type apart from integers
void func(int * i){
    cout << "Used the nullptr!!!";
}

//older versions of c++ would use typedef as the keyword for alias, we can now just use using:
using dbl = double;

void print(const vector<int>& v){  // best way to pass an object is we just want to look at its data
// takes in a reference to a vector made of ints, const so you can't change the vector, printing is ok
    for(auto i : v){  // this just means for int i in v, useful for containers, must be used with iterators
        cout << i << ", ";  // passed using a reference so no copy is made
    }   // made const so that we cant change what we're referencing
}

int main(){
    // {} brace initialisation can be used with any type
    int x {7}; //same as writing x = 7;
    string s {"This has been initialised!"};
    //even works with vectors and containers
    vector<int> v{1,2,3,4,5}; //declared and initialsed on the stack
    print(v);

   // int i = 7.7;
    // cout << i;

    dbl o = 1.1;  // changed double into dbl through keyword using
    cout << endl;
    cout << o << endl;   // compiler makes replacement


    func(nullptr);  // works because null pointer works as a pointer to an int, for just an int, you can use NULL
}