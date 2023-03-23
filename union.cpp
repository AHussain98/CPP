# include <iostream>
# include <variant>

// a union is a compound data structure, each member must have a distinct type
// all the members are stored at the same address, ony one member can be in use at a time
// this is useful for processing data which is made of different types

// all members of a union are public by default, unions can have member functions, but not virtual member functions
// unions cannot be used as base or derived classes

// if we assign to a data member, that member in now in use
// only one member can be in use at any one time, the other members have undefined values
// it is ony safe to read from a member if it is currently in use

// The enum classes ("new enums", "strong enums") address three problems with traditional C++ enumerations:
//conventional enums implicitly convert to int, causing errors when someone does not want an enumeration to act as an integer.
//conventional enums export their enumerators to the surrounding scope, causing name clashes.
//the underlying type of an enum cannot be specified, causing confusion, compatibility problems, and makes forward declaration impossible.
//The new enums are "enum class" because they combine aspects of traditional enumerations (names values) with aspects of classes (scoped members and absence of conversions).

enum class Tokentype {Char, Int, Double};    // enumerate allowed types using enum class

union Token{     // members are public by default
    char c;
    int i;
    double d;
    Tokentype type;   // tag field to indicate which member is in use

};

// use of standard unions is highly error prone, the programmer has to remember which type is in use
// unions can be made safer by adding a "tag" data member
// this indicates which member is in use
// this is known as a "tagged" union
// a tagged union requires the programmer to check before accessing a member
// the programmer must also set the type when bringing a member into use
// for greater safety, wrap the tagged union inside a class, the union is a provate member of the class
// it can only be accessed through the classes public member functions
// these perform the necessary setting and checking of the tag member, the member functions can perform suitable error handling
// this enforces correct use of the union

class TokenWrapper{             // so we can create member functions that set and get the union members, checking which ones are in use
    Token token;
    public:
        void set_char(char c){
            token.type = Tokentype::Char;  // char member now in use
            token.c = c;
        }
        double get_double(){
            if (token.type == Tokentype::Double){
                return token.d;
            }
            else {
                throw std::invalid_argument("Double member not in use");
            }
        }
};

int main(){
   //  Token token;
   //  token.c = 'z'; // char c is now in use

   TokenWrapper tw;
   tw.set_char('Z');

   // check if safe to access double member
   try{
       std::cout << tw.get_double();
   }
   catch(std::exception& e){
           std::cout << "caught exception! " << e.what() << std::endl;
   }

   std::variant<char,int,double> v;
   v = 'Z'; // char is now in use
 }

 // c++17 provides an std::variant type
 // this is similar to a wrapped tagged union but is typesafe, can have different "alternatives" with the same type
 // automatically calls constructors and destructors when requires
 // simpler to use

 // variants are useful for parsing source codem where a variable can have one of multiple types
 // also configuration files where a parameter can only be a string, number or boolean
