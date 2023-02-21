# include <iostream>
# include <string>

// a conversion operator is a member function that convers an object of a class into some other type
// the compiler will make this conversion automatically when it recognises that treating the object like a standard object won't work
//

class Test{
    int i {42};
    std::string str;
    public:
        // operator int() const {return i;} // this is implicit conversion operator, means the compiler will treat the object like a int if its standard behaviour becomes invalid
      explicit operator int() const {return i;} //explicit keyword used here, this stops the below implicit conversion from happening
      // using the explicit keyword will stop the compiler performing the fucntion operation implicitly, as before
      // however the conversion can still be done without a cast if the object is used as a bool in a conditional:
      // if (test}{
      //   cout << "yo!;}    this will still work, for example

      // a constructor with a single argument also acts as an implicit conversion operator
      /*
      class Test{ int i;
      public:
          Test(int i): i(i){}
      };

      Test test = 4; //this then becomes valid, only because there is a constructor with a single argument
      // explicit Test(int i): i(i){}    // explicit keyword stops this, make the constructor explicit
      */
};

int main(){

         Test test;
         
        // std::cout << test;  // normally, this would'nt work, but the compiler rethinks it and changes the type of the object into an int because of the above conversion operator
         // this is an implicit conversion, which can be suprising and are best avoided for that reason

         // we need to say we want to explicitly cast the object to an int
        // now if we explicitly cast the test object to an int, the explicit function will work and compiler will allow this, as we've explicitly defined it in the function

        std::cout << static_cast<int>(test);    // this works because it is explicit


    }
