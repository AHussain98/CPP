# include <iostream>
# include <algorithm>
# include <string>

// spaces, punctuation and capitalization are ignored, we're just looking at the actual letters
// first, lets normalize the string, make a copy and only keep the alphabetical characters
// convert all remaining characters to the same case
// for the actual work of comparing the string, we can use std::mismatch()
// the return value from mismatch() is a pair of iterators, these point to the first mismatched element in each range
// if there is no mismatch, these will be equal to end(), then the string is a valid pallindrome
// if teh returned iterators are not equal to end(), the input string is not a palindrome, there is a mismatch between the character at p.first and the character at p.second

// return a copy of the alphabet string with non-alphabetical characters removed, converted to lower case

std::string normalize(const std::string& str){

    std::string retval {""}; // empty string to return a value

    std::copy_if(cbegin(str), cend(str), back_inserter(retval), [] (char c) { return std::isalpha(c); // return is true if its alphabetical
    });
    std::transform(begin(retval), end(retval), begin(retval), [] (char c) { return tolower(c); // target container is retval again, we're iterating over it
    });

    return retval;
}

int main(){

std::string s {""}; // empty string
std::cout << "Please enter your pallindrome" << std::endl;

std::getline(std::cin,s); // take in input

// input string with punctuation and spaces removed

std::string  fixedInput {normalize(s)};

// call mismatch to compare the string to its reverse
// use a reverse iterator

auto p = std::mismatch(cbegin(fixedInput),cend(fixedInput),crbegin(fixedInput));

// return value of mismatch is a pair of iterators, these point to the first mismatched element in each range

if (p.first == cend(fixedInput) && p.second == crend(fixedInput)){
    // there is no mismatch, the string is the same in both directions
    std::cout << fixedInput << " is a pallindrome!";
}
else {
    std::cout << fixedInput << " is not a pallindrome!";

    std::string str2 {""};       // lets make a copy of the string, up to the mismatch
    std::copy(cbegin(fixedInput), p.second.base(), back_inserter(str2)); // .base() can be used to turn a reverse iterator to a forward iterator
    std::cout << std::endl << *(p.first) << " does not match " << *(p.second) << " at " << str2;
}




}