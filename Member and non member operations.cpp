# include <iostream>
# include <string>

// most operators can be implemented as either member functions or non member functions
// usually they should be implemented as member functions, they can get direct access to private data, and this keeps all class related code together
// however some operators cannot be implemented as member functions
// operators which change the state of the object should be implemented as memebr functions
// operators which are closely related to member types are best implemented as member functions
// some operators can only be defined as member functions, there are = [] () ->
// binary operators which may require a type conversion of eother argument should be non member functions
// input and output operators << and >> should be non member functions for compatibility with syntax
// see below

class String{
  std::string s;  // private data member
  public: // constructors
         String(const char * str) : s(str) {};
         String(const std::string& str): s(str) {}; //define constructors for the old C style string and new c++ string class object

        // String operator+ (const String& arg){
          //   return arg.s + s; //so when we use + between two String class objects, add thier s values and return this
        // }
        friend String operator+(const String& s1, const String& s2); // make the fucntion a friend function, define it outside the class
         void print(){ std::cout << s;
         }
};
         String operator+ (const String& s1, const String& s2){   // defien it outside so it works with non class members
              return s1.s + s2.s;
          }


int main(){
     String w{"world"},bang{"!"}; //define some string objects
     String wbang = w + bang;  // add thier s values using the overloaded + function
     wbang.print(); //  print the new strings s value , this works

    //  String hi = "hello" + wbang;   // this will not work, there's a compiler error because we've only deifned the + operator overload to work with String objects, whoch are objects of the class String
      // because this string literal "hello" is not, the overload does not work and the compiler rejects it
      // but if we make the overloaded + fucntion a non member function, the program will work as expected

      String hi = "hello" + w; // this will work because the compiler will convert "hello" into a String object using the first constructor for a C style string, passing it in automatically and creating the object itself
      // we learned previously that c++ compilers will automatically change the type of a literal to an object type if there is a constructor with a single parameter, thats whats happening here, the hello string is converted into a String object
      // if we made the first constructor explicit, then this conversion would not happen and the code would not compile
}     // this only works because we've defined the overload function outside the String class, so the compiler knows it doesn't need to use String objects explicitly
