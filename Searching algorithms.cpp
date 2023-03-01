# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
// these are algorithms that search within iterator ranges
// std::string has a member function find_first_of() that returns the index of first occurance of whatever string you pass it
// there is a generic algorithm function, std::find_first_of(), this can be used with anything that supports iterator ranges and returns an iterator to the first occurance
// by default, the == operator of the element type is used

int main(){
std::string str {"Hello world"};
std::string vowels {"aeiou"};

// returns an iterator to the first character in vowels

auto it = std::find_first_of(cbegin(str),cend(str),cbegin(vowels),cend(vowels));
if (it != cend(str)){

std::cout << "The first vowel in str is " << *it << " at position " << std::distance(cbegin(str), it) << std::endl;
}
// because there was a match, it returned an iterator to that element
// if there was no match, it would return an iterator to just after the last element, this is cend()

// if we want to find the next vowel in the series, we need to search again
// but now we can start from the position after it, since we need to search the rest of the string
// we can do this by passing the iterator range (next(it), cend(str))

auto it2 = std::find_first_of(next(it),cend(str),cbegin(vowels),cend(vowels));

if (it2 != cend(str)){

std::cout << "The second vowel in str is " << *it2 << " at position " << std::distance(cbegin(str), it2) << std::endl;
}

// std::adjacent_find() looks for two neighbouring elements that have the same value
// it returns an iterator to the first element of the first match

auto match = std::adjacent_find(cbegin(str),cend(str));
if (match != cend(str)){
    std::cout << "there are two adjacent elements of " << *match << " at position " << std::distance(cbegin(str),match) << std::endl;
}

// std::search_n() looks for a sequence of n successive elements which have the same given value
// it returns an iterator to the first element of the sequence

std::vector<int> vec {1,2,3,3,4,5,6,6,6};
auto it3 = std::search_n(cbegin(vec),cend(vec),2,3); // looking for two 3's in a row in the vector vec
std::cout << *it3 << std::endl;

// there is also std::search(0 which takes two iterator ranges, it looks for an occurance of the second iterator range inside the first
// simsilar to finding a substring in a string
// it returns an iterator to teh first occurance

std::vector<int> vec2 {4,5};

auto it4 = std::search(cbegin(vec),cend(vec),cbegin(vec2),cend(vec2));
std::cout << "vec2 appears in vec 1 at position " << std::distance(cbegin(vec),it4);


    return 0;
}