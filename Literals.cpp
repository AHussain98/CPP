#include <iostream>
#include <string>

using namespace std;
using namespace literals;

int main(){
//    int x = 8;
//    char y = 'h';
//    std::cout << sizeof(x); // 4 bytes
//    std::cout << sizeof(y); // fixed as 1, byte size of machine
//
//    // fixed size ints are used, these reserve an exact amount of memory, based on bits:
//
//    uint8_t a = 16; // now one byte, 8 bits
//    std::cout << sizeof(a);
//
//    //the u means unsigned, so value can only be positive
//
//    // hexadecimal numbers can be used, these have 0x or 0X in front
//
//    int hexa = 0x2a;
//    std::cout << hexa;

    // octal numbers have 0 in front

    // we can use the ' seperator in numeric literals

    // a traditional string literal is an array of chars terminated by a null character

    // we can create std::string literals instead of just objects, using the literals namespace

    std::string name {"Asad Hussain"s}; //create a literal using the s character after the closing bracket

    cout << "Asad\n"s + "Hussain"s; // now we can add them, they're not treated like arrays of chars

    // raw strings, start with R, this means \ and " characters in the string won't be processes

    cout << R"(now we can use "these" in our string \n does nothing)";

}