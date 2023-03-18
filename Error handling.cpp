# include <iostream>
# include <vector>

// even perfect code may suffer from errors in the real world, reading nonexistent files, networks being down etc...
// there are situations which arise as runtime when the environment does not behave as the program expected
// we need to communicate the issue to the user, and give them useful information
// only exit the program as a last resort
// we need to have a specific area of code that can handle errors, the error needs to be passed from the place where the error occurs to the code that handles it

// in c, the only way to communicate an error condition wi with an error code
// the fucntion returns a coded number that corresponds to the error, the caller checks the return vale and either handles the error itself or returns the error code to its own caller or returns a different error code
// usually the way to handle these returned errors is via a switch statement, where you have a case for the error
//however, error codes make code more complicated (each error case would need an if statement, return statement and cleanup code)
// error codes often cause maintenance problems (you'd have to update the switch statement often and it could grow massive) and do not work well with callback functions
// c++ constructors cannot return an error code

// as an alternative, c++ provides exeptions
// code which could cause a run-time error is put inside its own scope
// if an error occurs, create an exception object and exit the current scope
// find a handler for the exception, depending on its type
// the handler processes the exception object
//  the programmer specifies the type of the exception object and provides a handler for it
// the programmer specifies when to create the exception object
// the compiler will generate the code to create the exceptioon object and invoke the correct handler for it

// exceptions avoid a lot of tedious and error prone coding, the compiler and runtime take care of control flow, the type system prevents us using teh wrong handler and theres no switch statement to maintain
// if there is no suitable handler, the program terminates immediately
// an exception is an object of a class so can convey more information than a number, and constructors can throw exceptions

// handling exceptions requires extra code to be ran at run-time
// throwing an exception takes much longer than returning an error code
// in some environments, the overhead from exceptions is not acceptable, some c++ coding standards forbid exceptions

// Runtime is a piece of code that implements portions of a programming language's execution model. In doing this, it allows the program to interact with the computing resources it needs to work. Runtimes are often integral parts of the programming language and don't need to be installed separately.

// std::exception is a class for providing a consistent interface to exceptions, its the base class of an inheritance heirarchy, it has a number of sub-classes such as std::out_of_range()
// it has a what() virtual member function which returns a c-style string describing the error
// the exception mechanism requires some code to manage exceptions at runtime, this code is added by the compiler, but we need to tell the compiler to generate it
// to do this, we put code that could throw an exception into a try{} block
// the code to handle the exception goes in a catch block after the try block
// the type of exception we are going to handle goes into brackets after the catch keyword
// if we put a bae class here, all its subclasses willbe handles aswell
// if we put a reference to base, dynamic binding will be used so we get the specific error in the subclass

// normally we put a catch block right after a try block
// if an exception is not handled by any of the catch blocks after the try block, the program will try to find one in teh enclosing scope ( the fuunction that the try block is in)
// if it does not find one, it will jump out of the current fnction and try to find one in the functions caller
// if it still does not find one, it jumps to that functions caller ans so on. If there is no suitable handler, the program terminates

int main(){

std::vector<int> vec; // vector of unknown size
try { // possible error ridden code put in try block
    std::cout << vec.at(2) << std::endl; // so try to output something at an index that doesnt exist
}
catch (const std::exception& e){  // will handle all subclasses of std::exception, uses dynamic binding so we get the specific error in the subclass
     std::cout << "Caught an error: " << e.what() << std::endl; // print out a description of the error
}


}