# include <iostream>
using namespace std;

//local variables exist inside a scope {}
//it comes into existence where it is defined, memory is automatically allocated for it on the programs stack
//it will then be initalised, if we do not specify an inital value, it is 'default initalised'
//it is destroyed at the end of its scope
// * means pointer decleration or dereference depending on where its used
// & means address or declare a reference, depending on where its used


//by default, a variable passed into a fucntion is passed by value
//the copy is a local ariable whose scope is the body of the function
//by default, the return variable from a function is also copied from the return variable defined in the function

int func(int y){
       // address of y
       cout << &y << endl; // so firstly the address of the local copy is printed
       return y;  // because we didn't pass by address or reference, we're printing the address of the copy variable thats been created
   }
int func_point(int * y){   // this is passing by address, you pass a pointer
return *y; //return the dereferenced value of the pointer we passed
 // now we can actually change the value at the address of y, no copies are made
}

int func_reference(int &y){ // passing by reference

    return y;  // when passing by reference, the dereferncing is done automatically by the compiler, this is simpler than above
}

class MyClass{
    //create an empty class

};

void constFunc(const MyClass& mc){ //create a void function that takes in a const class object via reference
    cout << "do nothing!"; //const referencing means the function gets read only access to the object
}                           //mc is a reference to the callers object
// & is used as a reference here, just used to gain access to an area of memeory
// for read only access to class objects, passing by const reference is usually more efficient than passing by value

int main(){

    int x = 2;

    //the actual address of x is at &x


//    int z = func(x); // x remains the same, as we've have only passed a copy;
//    //to change x using the function, we could pass by reference, or pass via address
//    int * ptr = &x;
//   // int w =  func_point(&x); // this works the same as using &x or ptr
//    //this is because a pointer is just storing an address
    //so dereferncing a pointer will just show the value at that address
    // we're passing the address of x, so dereferncing an address can also return the value at that address

   // cout << w << endl; // prints 2, so we're pointing to the correct place
  //  int k = func_point(ptr);
   // cout << k << endl;
//
//    cout << ptr << endl; // the value of pointer is different from x's address, because a pointer is just an object that stores the address of x
//    cout << &ptr << endl; // this is teh address of the pointer variable itself on the stack
//    cout << *ptr << endl; //this is a dereferenced pointer, showing the value at the address the pointer points to

    int q = func_reference(x);

    cout << q << endl;
//
//    cout << &x;
//
//    MyClass myclass;
//    constFunc(myclass); // pass a class object to the function via reference, so its looking at the same area of memory
//    // but it cant make any changes

    return 0;
}