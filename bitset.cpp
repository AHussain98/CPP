# include <iostream>
# include <bitset>  // an abstraction which represents groups of bits

// c++ has operators for bitwise manipulation of integers
// std::bitset is a templated type
// the parameter is the number of bits

// size() member function gives the number of bits in the bitset, we can use subscript notation to access individual bts
// index 0 represents the least significant bit (furthest to the right)
// test() accesses a bit with bounds checking, returns the bit whose index corresponds with its argument

int main() {

std::bitset<8> b1 {"10101110"}; // initialise from string literal
// we can send bitset objects to streams
std::cout << b1 << std::endl;
// work out how large it is
std::cout << b1.size() << std::endl;

for (auto i = 0; i < b1.size(); ++i){ // prints in reverse order, as 0 is least significant bit
    std::cout << b1[i] << ",";
}

std::cout << std::endl;
// test for what the last element is

std::cout << b1.test(7) << std::endl;

std::bitset<8> b2 {"10101010"}; // create another bitset object

// ~b1 is the inverse of b1
std::cout << "reverse of b1 is " << ~b1 << std::endl;

// we can use the bitwise operators, and, or, and/or

std::cout << "b1 and b2 is " << (b1 & b2) << std::endl;
std::cout << "b1 or b2 is " << (b1 | b2) << std::endl;
std::cout << "b1 and/or b2 is " << (b1 ^ b2) << std::endl;

// there are bit member functions
// set() sets all bits to true, also set(0) sets bit 0 to true, set(0,false) seats bit 0 to false
// reset() sets all bits to false, reset(7) sets bit 7 to false
// flip() inverts all bits, flip(7) will invert just the 7th bit

}