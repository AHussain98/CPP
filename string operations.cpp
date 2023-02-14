#include <iostream>
#include <string>

// interface for std::strings same as for the standard library containers

int main(){
std::string s1 = "Asad";
std::string s2 = "Hussain";

// we can assign strings
s1 = s2;
// we can append strings
s1 += s2;
// we can concatenate strings
s1 + s2; //returns a new object containing s1's data followed by s2
// we can compare strings, where cmp is ==, !=, <, >, <= or >=

std::cout << s1;

// std::string has a member fcuntion c_str() which returns a copy of the strings data as a c-style string, an array of chars terminated by a null character
const char * arr = s1.c_str();

// the substr() method returns a substring, starting at the idnex corresponding to its argument
std::string s3 = s1.substr(2);
std::cout << s3 << '\n';

// cstyle strings are typically difficult to change, however string objects are not

s1[1] = 'g';
std::cout << s1 << '\n';

// you can construct a string in a number of ways
std::string s4 {"This is one way"};
std::string s5 {'T','h','i','s'};
std::string s6 (5,'g'); //creates a string ggggg
// we can also initialse a string from a substring
std::string s7(s6,1,3); //  create s7 which is just ggg
std::cout << s7 << '\n';

// the find() member function looks for the first occurence fo its argument in the string, the search is case sensitive

std::cout << s1.find('a') << '\n'; // found at index 4
// if it cant find the character, it returns string::npos
int i = s1.find('a');
if (i != std::string::npos){ // useful to check if a value is in a string
    std::cout << "The first appearance of a is at index "<< i << '\n';
}

// the rfind() function returns the index of the last occurance of a char in a string

// the find_first_of() function gives us the first  occurance of any character from the argument string, find_last_of() gives us the last
std::cout << s1.find_first_of('Hussain') << '\n';
std::cout << s1.find_last_of('Hussain') << '\n';

// then we can use find_first_not_of() and find_last_not_of() for the first/last occurence of any character not in the argument




}