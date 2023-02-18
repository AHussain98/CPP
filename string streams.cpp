# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <iomanip>
# include <vector>

// the basic c++ stream is represented by std::ios
// there is the <iostream> for input and output
// <fstream> for file reading and writing
// <sstream> for writing and reading strings

// stringstreams are defined in <sstream>, the stringstream class has an std::string data member
// it has the same member functions as the other stream classes
// in effect, it is a wrapper around std::string that makes it look like a stream object
// this is an example of the adapter design pattern
// an ostringstream has an empty std::string object, we can store data in this string using the same operations as for other output streams
// the str() member function will return a copy of the streams string
// we can use an ostream object to create a version of the std::to_string() function

using namespace std;

template <class T>
string To_String(const T& i){
    ostringstream os;
    os << i;
    return os.str();
}

int main(){

 std::string pi {To_String(3.14159)};
 std::cout << pi << '\n'; // now pi is a string

 // because its a string, we can do string concatenation

 std::string pi_is {"Pi is "};
 std::cout << pi_is + pi << '\n';

// we can also use ostringstream objects to build up input, using another design pattern, builder
// we can use this to build up an output string, and add to it iteratively

ostringstream ostr;
string text;

cout << "Please enter a word \n";
cin >> text; // take in input
ostr << setw(16) << text;  // send it to the output stream object
cout << "Please enter another word \n";
cin >> text;   // do the same
ostr << setw(12) << text;

cout << ostr.str() << endl; // now output the entire stream

// an istringstream object uses a copy of an existing string, the string is passed to the istringstream's constructor
// we can then read the data from the string, this is useful for procesing input
// we can use an istringstream object by reading input into an std::string object and validating the data
// then bind the string object to an istringstream and read the data from the istringstream


ifstream infile("data.txt");  // create ifstream object called infile, bind to the file data.txt

if (!infile){
    cout << "Could not open data.txt" << endl;
    return -1;
}

string text2;
vector<int> numbers;

while (getline(infile,text2)){  // read a line of input at a time from the file into a std::string
// validate the input and handle errors
  istringstream is(text2); // bind the string to the istream object by passing it into the constructor
  int num;
  while( is >> num){  // now read data into the num variable
      numbers.push_back(num); //each time we read a number, push it back onto the vector
  }
}

double sum {0.0};
for (auto n : numbers){
    cout << n << endl; // for every int in numbers, print it out and add it to the sum variable
    sum += n;
}

cout << "Average is " << sum / numbers.size();

    return 0;
}