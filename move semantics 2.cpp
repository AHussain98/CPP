# include <iostream>

// Despite their names, lvalues and rvalues are classifications of expressions, not of values.
// Most function call expressions are rvalues. Only function calls that return a reference are lvalues.
//One indication for the latter is that function calls that return a reference can appear on the left side of a built-in
//assignment operator just fine. Prime examples are the subscript operators (operator[]()) and at() functions of your typical container.

// we cn overload a function so it behaves different depending on whether its argument is moved
// two ofthe most useful fucntions to overload this way are the copy constructor and assignment operator
// these member functions typically copy all the members of the class, often they create a new copy of a resource. Moving instead of copying improves performance

// c++11 added special member functions for this purpose, move constructor and move assignment operator
// they are called automatically if the passed object is a moveable rvalue
// these are overloads of the copy constructor and assignment operator which take rvalue references
// the assignment operator is now called the copy assignment operator, to avoid confusion with the move assignment operator

class myClass{ // spare class
};

class test{
    private:
        int i {0};
        myClass m; // a myClass object is a member of the test class
    public:
        test() = default; // default constructor, needed since defining a custom copy constructor means a default constructor is not implicitly created

        test(const test& arg) : i(arg.i), m(arg.m){
        std::cout << "copy constructor called" << std::endl;} // copy constructor

        test(test&& arg) noexcept : i(arg.i), m(std::move(arg.m)){ // we can copy teh built in members (i) as they are, but for the class object member m, we need to call t  hier move constructor, so we need to call thier rvalue as argument
        // because m has a name and an address, we need to convert it to an rvalue by putting it inside the call to move() and then this will cll the move constructor for the m object
        std::cout << "move constructor called" << std::endl; } // move constructor

        test& operator= (const test& arg){
        std::cout << "copy assignment operator called" << std::endl; //copy assignment operator
        if (this != &arg){
            i = arg.i;
            m = arg.m;
        }
        return *this; // return the modified object
        }

        test& operator= (test&& arg) noexcept{ // for moves, we take teh rvalue reference
        std::cout << "move assignment operator called" << std::endl; // move assignmnet operator
        if (this != &arg){ // self assignent check
          i = arg.i;   // move assignment operator called for the built in type and the object class type
          m = std::move(arg.m);  // force move assignment operator to be called
        }
        return *this; //return the modified object
    }

};

// the move operator argument cannot be const (it will be moved from)
// the move operators should not throw exceptions, no simple way to recover from a part-complete move and stl containers will only call an elements move operator if it is noexcept

// the move assignmnet operator returns the assigned-to object by lvalue reference


int main(){

      test test1; // call default constructor
      std::cout << "copying " << std::endl;
      test test2 = test1; // call copy constructor

      std::cout << "moving temporary: " << std::endl;
      test test3 = test(); // call move constructor by using temporary object  (using default constructor)

      std::cout << "moving rvalue reference " << std::endl;
      test test4(std::move(test3)); // call move constructor by casting test3 to rvalue

      test test5;
      std::cout << "assigning" << std::endl;
      test5 = test2;

      test test6;
      std::cout << "assigning from temporary" << std::endl;
      test6 = test();

}

// when writing a move operator for a derived class, we should call the corresponding operator for the base class
// to do this, we must pass the argument as an rvalue

// copy constructor:
// derived(const derived& arg) : base(arg) {...}

// move constructor:
// derived(derived&& arg) : base(std::move(arg)) noexcept {...}

// if we copy an rvalue object which does not have a move constructor, the copy constructor will be called instead, same with the move assignment operator