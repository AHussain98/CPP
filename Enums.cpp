#include <iostream>
using namespace std;

// enum is short for enumeration, it just means a set of values
// all an enum is is a way to give a name to a bunch of values
// an enum is just a way to name values
enum Example {

//if you don't initialse the values, they will start from 0, so A would be 0 and then increase by 1 for each
//enums are generally used to collect ints as a group
A = 0, B = 101, C = 2 //you declare them in a comma seperated list
};   //theyre ints by default

int main() {

        Example value = B;
        cout << value;

}
