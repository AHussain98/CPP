# include <iostream>
# include <string>

int main(){
// the append member function adds its argument to the end of the string
std::string s1 {"Hello"};
s1.append(" World!");
std::cout << s1 << '\n'; // now added
// we cna also add substrings
s1.append("Wowwww!!!!",0,3);
std::cout << s1 << '\n';
// we can also insert, takes an offset index of where the insertion happens
s1.insert(5,"Asad");
std::cout << s1 << '\n';

// we can insert a substring, insert a char, or insert the end of a find call

// inserting elements may fill up the strings memory buffer, in that case, it will allocate a new buffer and copy its data into the new buffer
// before adding the new element, any saved iterators will be pointing to the old buffer

// the erase member function takes two arguments, removes caharacters from the string, the first argument gives the index of the first element to be erased, the second gives the number of elements to erase
s1.erase(0,3);
std::cout << s1 << '\n';

// with an iterator, the erase() function will erase the corresponding element
// with an iterator range, the fucntion will erase all elements in the range

// there is also a replace() function, replaces the element at the first argument index, second argument is number of characters to be replaced, third is the characters that will replace them

s1.replace(0,0,"hello");
std::cout << s1 << '\n';
// again, this works with iterators

auto start = begin(s1);

std::cout << s1.replace(start, start + 3, "YoYoYo") << '\n';  // replace the first 3 elements with this string

// we can just completely ressign a string, deleting its current characters and replacing them with the assign() finction
s1.assign("New string!");
std::cout << s1 << '\n';

// we can convert from strings to numbers and backwards
//for converting numbers to strings, we can use to_string(), this overloads ints and floats, returns its argument as an std::string

std::string pi = std::to_string(3.14159);
 //pi converted to a string object called pi
std::cout << pi << '\n'; // pi as a string object

//stoi() takes an std::string argument and returns it as an int, only works on numeric characters and ignores withespace in the middle
std::string pie {"3.14159"};
int intpie = std::stoi(pi); // stored the string pi as an int

 // stoi() takes an optional second argument called &n_processed, (passed by reference) which gives us the number of chars processed
 // if the whole string is processed successfully, then n_processed and the string.size() will be equal
// there's also stod and stol for doubles and longs

// sta::string and std::vector have a data() member function, this returns a pointer to the containers internal memory buffer
// for std::string, this is null-terminated
// e.g. for a vector called numbers, we can access the pointer to it by using numbers.data(), and then pass this to a function etc...

// std::string and std::vector both have swap members, for swapping values of strings or vectors
// for string s1 to swap with string s2, we can do s1.swap(s2)
// there's also a global swap function, swap(s1,s2), but this is done using copy constructor, which causes temporary object instantiation and memory allocation
// expensive and wasteful, stick to the member swap function, just just swaps header pointers directly


// remember that the std::string class has a 'header', this is a pointer to the character data of the string, with an integer of teh character count
// the swap member function just reassigns the headers of two strings, no need for expensive copying of data
std::string s2 {"Don't swap me please!"};
s1.swap(s2);
std::cout << s2 << '\n';
}