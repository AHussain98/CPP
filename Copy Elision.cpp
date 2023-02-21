# include <iostream>

// copy elision means the compiler is allowed to skip over a call to the copy constructor in some cases, the compiler can initialise the target object directly
// this usually occurs when copying  temporary variables during function calls, either copying temporary variables into function arguments or into return values
// this applies even if the copy constructor has side effects, which will change the behaviour of the program
// normally, the compiler cannot perform optimisations that change the function of the program, this is called the as-if rule
// as-if rule -> compiler can only make optimisations that make the program run faster, but not chnage any functionality


// return value optimisation is when the copy of a returned temporary object is elided, return Test(), temporary Test object copied into return area
// without elision, you would create a temporary object, copy it into the return space and destroy the temporary object
// with elision, you create the object directly in the return space, this avoids a call to the copy constructor and to the destructor

// copy elision takes places when a variable is created, Test test = func(), returned Test object is copied into variable test
// without elision, you'd call the copy constructor with the temporary object as an argument, initialse the variable and destroy the temporary object
// with elision, you create the object directly in the variable's memory, this avoids a call to the copy constructor and to the destructor

// copy elision also occurs when a temporary object is passed by value

class Test{
    public:
        Test() { std::cout << "default constructor \n";  // create a default constructor because the compiler will not synthesize one if we already have a copy constructor, IMPORTANT
        // so we have to put in a defaault constructor, otherwise the code wouldnt compile
        }
        Test(const Test& other){ std::cout << "Copying \n"; //copy constructor with side effect
        }
};

Test func(){  // func class that returns a Test object
return Test(); // returns this temporary object, this gets copied in to the return space, so the copy constuctor should be called twice

}

// return value optimisation for a named object is harder for compilers to do than for temporaries

// Test func2(){
//   Test test;
//    return test;    copy elision here may not even be done in all cases, unlike the above, so the copy constructor may be called

int main(){

      Test test = func(); // copy constructor should be called here with the temporary object in the retunred function space as the argument but copy constructor not called
      // the reason is because copy elision has taken place twice to replace the copy constructor calls






}