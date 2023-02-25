# include <iostream>
# include <vector>
# include <fstream>
# include <string>

// so lets try to create a class that allows us to create and modify complex numbers

class Complex{
    double real {0.0};  // create the private member functions and give them inital values
    double imag {0.0};
          public:
              Complex(double r, double i) : real(r), imag(i) { //create a constructor
              }
              Complex(double r) : real(r) { // constructor that takes a single argument and is non explicit, this will allow us to make type conversions where appropriate
              }

              // lets define the += operator as a member function, as this will cactually modify the object

              Complex& operator+= (const Complex& rhs){  // returns a refrence to a Complex object, NOT A CONST REFERENCE BECAUSE WE'RE CHANGING THE OBJECT, for an overloaded binary operator, the args for the second operand go in the ()
              real += rhs.real;   // assign new values of real and imag members
              imag += rhs.imag;  //here, real and imag refer to the member variables of the object calling the operator
              return *this; //return modified object
              }
              void print(){
                  std::cout << "(" << real << "," << imag << ")" << '\n';
              }

              Complex& operator++(); // prefix operator
              Complex operator ++(int); //postfix operator, this returns a copied object by value rather than a reference and takes a dymmy argument

              // create a member function that prints out data member of the test class, but this version will work with any output stream, not just cout
              // we pass the output stream by reference as it will be modified inside the function, function is going to push data onto the stream, and remember that ostreams cannot be copied, so pass must be by reference for these reasons

              void truePrint(std::ostream& os) const{ // const here means do not modify the object that calls this function
                  os << "real = " << real << ", imaginary = " << imag << std::endl;
              }
              // we can create an overload of the << operator to do this even more cleanly

              // the standard library provides standalone functions which overload the << operator for all the built-in and library types
              // << is a binary operator, so it is not a member function of ostream
              // e.g. int {1};
              // cout << i;  //this is invoked as operator<<(cout,i)
              // the reason we can do nested << calls is because the return value of the << operator is a reference to the ostream
              // because ostreams cannot be copied, operator << must return a reference to the ostream, so its prototype must be ostream& operator<< (ostream&, int)
              // so we can implement this, but it must be outside the class, because its not a member function of the ostream or Complex classes
};

// now outside of the class we can define the addition operator, do this outside because we may want to make implicit type conversions of objects that are not Complex objects

std::ostream& operator<< (std::ostream& os, const Complex& test){
      test.truePrint(os); // overloaded operator << which prints the data members of the Complex class, this calls the Complex class's truePrint method and returns the stream
}

Complex operator+ (const Complex& lhs, const Complex& rhs){   // return an object, not a reference
    Complex temp {lhs}; // call copy constructor for the temp object that will be replacing the lhs, we want a copy so odnt pass by reference
    temp += rhs; // add the rhs argument to it using the overloaded += operator we defined earlier
    return temp; //return the modified object
}

// prefix operator
Complex& Complex::operator++(){  // now define the function
      ++real; // just add to real and then return a reference to the calling object
      return *this;   // return the updated object itself, remember that operator overloading is just a function, we're returning the updated object to the return space where it is called
}

// postfix operator
Complex Complex::operator ++(int){ // define it
Complex temp = *this; // so create a copy of the calling object
++real; //  increment the real value of the actual calling object, the copy we just created remains the same
return temp; // return the copy
}

// overload the function call operator
// function call operator overloads can take any number of arguments and return anything
// invoke it by just putting the name of the object followed by brackets ()
// take the example class below
class check{
  public:
      bool operator() (int n) { // now we can call this overloaded function whenever we create a check object
          return (n % 2 == 0);  // only return true if the number is exactly divisible by 2
           // remember functions will return true if they're called successfully by default, so don't put this line in an if statement and make it return true f the condition is met, you'll get false positives if you do this unless you also add an else statement
           }
};

void do_it(const std::vector<int>& vec, check test1){
    for (auto i : vec){
       if (test1(i)){  // so if our overloaded function call function returns true
           std::cout << i << " is even, ";
       }
    }
}
int main(){

         Complex obj1(0,1);
         Complex obj2(5,1);

         obj1 += obj2;
         obj1.print();

         Complex obj3 = 2 + obj2; // 2 will be converted into an object of type Complex because the overloaded + operator takes in two args of Complex type, and the Complex class has a single argument constructor that can allow this conversion
         obj3.print();

         Complex obj4 = obj3++;  // returns the postfix copy object and assigned to obj4
         obj4.print(); // still the same amount, as the copy has been returned
         obj3.print(); // increased by 1

       check test1;   // create a functor object
       std::cout << std::boolalpha << test1(6) << '\n';   // even modified the stream to make it look nicer

      std::vector<int> vec {1,2,3,4,5,6,7,8,9,10};
      do_it(vec,test1);

      obj3.truePrint(std::cout); //so we can use the truePrint function to print the data members of the class using any stream we want to pass in, cout here for example
      // or if we wanted to create an output file stream object and bind it to a file, we could pass that object into the function to write to a file instead


}


// equality operator == takes two types and returns a bool
// inequality operator != takes two types and returns true if the two objects are not equal
// if a class defines one of these, it should also define the other one

// less than operator <  takes two arguments and returns a bool
// standard library uses the less than operator for sorting and ordering
// if we try to sort a container and its elements do not implement the < operator, the code will not compile, same problem when inserting elements into a sorted container
// the result of the < operator should be consistent with the equality operators
// c++ defines a sort() function in <algorithm> which sorts elements in an iterator range, so sort the elements of a vector, we pass return values from begin() and end()

//  overloading the () operator allows us to create functions just using objects of a class
// c++ classes can define a function call operator
// this allows us to make callable objects, an object of such a class is treated as a data variable, meaning the object can be called like a function
// a c++ class which implements a function call operator is called a "functor"
// functors are classes so they could contain member functions and data members, but to keep things simple, they should only be used to "wrap" functions
// they can however have data members to store values which need to be kept in between function calls, "states", which keep their values between function calls, could be static

//  << is an operator that is already overloaed by the output stream class, it returns a reference to the ostream (reference because we're modifying the stream and you cant make copies of an ostream), which is why we can chain them << with more <<
// notice how for the complex class above, we're using a member print function to print out data members of the class by sending them to output stream
// Complex test;
// cout << test; //this doesn't work, as there is no overload on << to be able to take a Complex object argument,
// print member function works but is rather limited because we can only use it with cout
// lets implement an output stream print statement above




// prefix operator performs the increment and returns a reference to the incremented object
// postfix operator makes a copy of the calling object, increments the calling objects and then returns its untouched copy
