#include <iostream>
using namespace std;


//classes are private by default, structs are public by default, this is the biggest difference between classes and structs
//structs are used to represent data structures, you can bind multiple data members into one data strcuture
// otherwiose pretty much same as class functionally
struct mystruct{
    int i;
    string name;
    bool b;

    void test(){
        cout << "Test" << endl;
    }
};

int main(){

    struct mystruct a;
    a.test();
}