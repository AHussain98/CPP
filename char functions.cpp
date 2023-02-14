# include <iostream>
# include <string>
# include <cctype>
// case insensitive string equality

bool equal_strings(const std::string& s1, const std::string& s2){ // return a bool, take in references because we don't want to make copies
// first we can compare the length of the two strings, if they're not the same, we can return here
if (s1.size() != s2.size()){
    return false;
}

// we now know our strings are of the same length
// get iterators to the first element of each string

auto lhs = cbegin(s1); //const beginning as we don't want to make changed
auto rhs = cbegin(s2);

// We iterator over the two strings, comparing the current character of each and the upper case versions of each
// if either iterator is equal to cend() we know we have seen all the characters and the loop terminates
// if a character is different, we can terminate the loop and return false
while (lhs != cend(s1) && rhs != cend(s2)){

if (toupper(*lhs) != toupper(*rhs)){
    return false;
}
++lhs;
++rhs;

}

return true; //if we get to this point, then we know the strings are the same and we can return true 
}
// character functions stored in the <cctype> header
// isupper(), islower(), ispunct(), isspace()


int main() {

std::string greeting {"Hello there!"};
for (auto i : greeting){
    if (isupper(i)){
        std::cout << i << " is upper case" << '\n';
    }
    if (islower(i)){
        std::cout << i << " is lower case" << '\n';
    }
    if (ispunct(i)){
        std::cout << i << " is punctuation!" << '\n';
    }
    if (isspace(i)){
        std::cout << i << " is a whitespace" << '\n';
    }
}

// can use the toupper() and tolower() functions to return the opposite of thier characters case, but in integer form
for (int i = 0; i < greeting.length(); i++){
std::cout << (char)toupper(greeting[i]);
}

// operations using std::string are case sensitive, the string One and one have different data

// to compare strings without caring about case, its easiest to convert all strings to a single case and then compare them


}