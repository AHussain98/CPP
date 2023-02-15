# include <iostream>
# include <fstream>

// we can open a file in a number of ways by passing the file mode as an optional second argument
//by default, files are opened in text mode
// by default, output files are opened in truncate mode, any data previously written in the file will be wiped and new data is written from the start of the file
// we can append to a file by opening an ofstream in append mode, when we write to a file, its current data will be preserved, our data will be added after


int main(){

std::ofstream ofile;
ofile.open("text.txt", std::fstream::app); //this is the argument for appending

if (!ofile){
    std::cout << "could not open file" << std::endl;
    return -1;
}

ofile << "some more data";  // appended more data to the file using the output stream object
ofile.close();

// other modes are trunc, in for input, out for output, ate (similar to append but output can be written anywhere


// we can combine modes by putting | between them e.g
//file.open( "both.txt", std::fstream::in | std::fstream::out); this file is opened in such a way that we can read from it and write to it
}