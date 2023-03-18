# include <iostream>
# include <vector>

// a catch block can only come after a try block, we can have more than one catch block for the same try block
// if we want to handle exceptions with different static types, we add another catch block for each type (we need to have one catch block for each static type)
// the exception will be handled by the first catch block that can handle it

void get_file(){
 std::vector<int> vec;
 std::cout << vec.at(2); // this code will throw an exception
}

void catcher(){
    try{ get_file();   // put the call to the exception throwing function in a try block
    }

    catch (const std::exception& e){
        std::cout << "caught in another function! :" << e.what();
    }
    catch(...) {    // catch all handler, must be the catch last block for a particular try block
        std::cout << "caught with unknown handler";
    }
}


int main(){

//std::vector<int> vec; // vector of unknown size
//
//try { // possible error ridden code put in try block
//    std::cout << vec.at(2) << std::endl; // so try to output something at an index that doesnt exist
//}
//
//catch ( const std::exception& e){ // handles all sub classes of std::exception
//std::cout << "std::exception" << std::endl;
//}
//catch (const std::out_of_range& e) { // only handles exceptions of type std::out_of_range
//std::cout << "std::out_of_range" << std::endl;
//}

// the first catch block will be thrown, because its the first catch block that can handle the exception
// even though teh second one is more specific, the compiler will come across the base exception class first, so will throw that
// so if we're using the std::exception hierarchy, we should put the catch blocks in reverse order, with the most specific catch blocks coming first and then the base class catch block at the bottom
// the exception handler should take the exception object by reference, this allows polymorphism to work (what() is a virtual member function)
// unless you need to modify the exception object, make it a const reference

// when the program is executing inside a catch block, it may not be in a stable state, so we should avoid allocating memory, creating new variables, calling functions or using non-built-in types
// in an exception block, never do anything that might throw a new exception, keep the code simple
// we can put a try/catch block inside another try/catch block, if the inner block cannot handle the exception, the program will look for one in the outer catch block

// we sometimes want an exception to be handled in a different function from where it happened
// to do this, we put the function call of the function where we expect the exception in a try block within the different function
// see below

catcher();

// we can write a catch handler with ... as the exception type, this can handle an exception of any type, including built in tupes, library types and custom classes
// catch(...)
// it can be useful to put catch al handlers after other catch blocks to catch any exceptions that may have been missed, but of course we can't know what these are because there is no exception obkect to call what() on
// it can also be useful to put a catch all handler in main(), if the handler exceutes, we know the program terminates due to an uncaught exception rather than some other bug, this tells us we are missing a catch block
// may not capture a os error
}