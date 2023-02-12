#include <iostream>
#include <string>
using namespace std;
//casting performs an explicit conversion
// this can mean converting an expression to a different type, const to non const, data in a buffer to untyped binary, pointer to base class object and pointer to derived
// casting should rarely be necessary if code is well written

void print(char * x){
    cout << x;
}

int main(){

    // below is c style casting
    int c = 'A';
    cout << c << endl; // prints the numeric conversion
    cout << (char)c << endl; //prints the alphabetic char

    // we can also do static and const casting, which is more modern, shown below

    cout << static_cast<char>(c) << endl;

    // then const cast which is used to remove the const-ness from references and pointers that ultimately refer to something that is not const
    const char * i = "Asad";

    //print(i);  // not allowed as i is const
   print(const_cast<char *>(i)); // allowed as we've casted i to no longer be const here


//dynamic casting is used to convert a pointer to a base class object to a pointer to a derviced class object
}