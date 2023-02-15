# include <iostream>
#include <fstream>
#include <iomanip>

// we can push a manipulator onto a stream to affect the streams behaviour, such as std::flush and std::endl
// most manipulators are in <iostream>, those that atke arguments are in <iomanip>


int main(){
// for example, bool is an integer type with two values, true (stored as 1), or false (stored as 0)
// when we print a boolean, we onlly see 1 or 0, not true or false, but we can manipulate this behaviour using boolalpha

int x {2};
bool is_negative = x<0; //this is false

std::cout << "The value of is_negative is " << is_negative << std::endl;
std::cout << "is negative is " << std::boolalpha << is_negative << std::endl;  // now prints as false
std::cout << "x == 2 is " << (x == 2) << std::endl; // will now print as true, as the state of the stream has changed
std::cout << "5 > 1 is " << std::noboolalpha << (5 > 1) << std::endl; // will return the stream to default


// by default, output streams do not format the data, but we can manipulate this too
// setw() allows us to set the width of the following field, defined in <iomanip>
// the argument is the width of the field and this only affects the next data item on the stream

std::cout << std::setw(15) << "Pengiuns " << 5 << '\n';  // so take 15 chars to output each line
std::cout << std::left << std::setw(15) << "Polar Bears " << 2 << '\n'; // start the data on the lhs of the 15 char field

// left is whats known as a sticky manipulator, this is a manipulator that will stick until the opposite manipulator is applied
// so if we apply std::right, this will return to default behaviour

// a non sticky manipulator only affects the next stream operation, setw() is non sticky, for example

// we can also add padding using the sticky manipulator setfill(), to cover the gaps between the field edge and field content

std::cout << std::setfill('@') << std::left << std::setw(15) << "Polar Bears " << 2 << '\n';
}






