# include <iostream>
# include <sstream>
# include <string>

using namespace std;

// the standard libary has classes that manage some resource
// this could be allocated memory, such as std::string and std::vector, or files such as std::fstream

// c++ classes which manage a resource follow a common idiom:
// the resource is stored as a private member of the class
// the class constructor acquires the resource
// the class public member functions control access to the resource
// the class destructor releases the resource

// these 4 tenets are known as RAII, resource acquistion is initialisation
// when an object is copied or assigned to, the target object (that is the result of the operation) acquires its own version of the resource
// so a class object creates a copy of the resource and manages it, each class object hets its own copy
// obtaining access to the resource is straightforward and deterministic, either the object is successfully created or the resource is not useable by the program
// using the resource is straightforward, just call the objects member functions
// releasing the resource is straightforward, this happens when the object goes out of scope, pr when an exeption is thrown
// only one object can own a given resource at a time


// it is possible to randomly access streams as c++ streams have a position marker, this keeps track of where the next read or write operation will be performed
// normally, the stream controls the markers position
// the marker is at the end of the stream for write operations and just after last read for read operations
// c++ has seek member fucntions which change the position of the marker, seekg sets the current position in an input stream and seekp does the same for output
// tellg returns the current position in input and tellp returns position in an output stream
// tell operations return a pos_type object that represents a position in the stream
// see below example

int main(){

ostringstream output; // open output stringstream
string data {"It is time to say "};
output << data; //write some data to the stream

auto marker = output.tellp(); // save the current position of the output stream
cout << data.size() << " characters written to stream \n";
cout << "Stream marker is " << marker << " bytes into the stream \n";

output << "hello"; //write some more data to the stream, marker should move forward 5 bytes
cout << "Stream marker is now " << output.tellp() << " bytes into the stream \n";

cout << output.str() << endl; // print out the data in the string

output.seekp(marker); // morve the position marker of the stream back to where it was previously

output << "goodnight"; // now we add more characters to the stream

cout << output.str();

// the best way to modify a file is to read it into a istringstream
// get the bound string and make changes to the data
// then overwrite the original file

}