#include <iostream>
#include <fstream>
#include <string>

// there are some applications where stream buffering is not acceptable
// sometimes we may want to flush the buffer as much as possible
// othertimes we may want to skip the buffer entirely
// eg in a network, data must be transmitted as packets of a specific size and at specific times, so we dont want buffers interrupting this//

int main(){
// streams have member functions for reading or writing data, one character at a time
// get() fetches the next character from an input stream
// put() sends its arguments to an output stream
// these both take a char argument

//char c;
//while(std::cin.get(c)){ // reads a character until we get the end-of-input character which is ctrlz on windows
//    std::cout.put(c);
//}

// for reading and writing many characters, there are the read() and write() member functions
// as we are not using a buffer managed by the stream, we have to provide our own buffer

// for write(), our buffer will contain all the data we want to send
// for read(), our buffer must be large enough to store all the data we want to recieve

// both of these member functions take two arguments, the address of the buffer and number of chars in the buffer

const int filesize{12}; // size of memory buffer
char filebuf[filesize]; //memory buffer, an array of 10 chars
std::string filename {"text.txt"};

std::ifstream ifile(filename);
if (!ifile){
    std::cout << "Could not open" << filename << std::endl;
}
ifile.read(filebuf,filesize);
ifile.close();

std::cout << "File data: ";
std::cout.write(filebuf,filesize);
std::cout << std::endl;

// often, we want to know how much data an input stream has sent us, the gcount() member function will return the number of characters that were actually recieved

auto nread = ifile.gcount();
std::cout << nread;         // returns number of characters it read in the last read operation

}