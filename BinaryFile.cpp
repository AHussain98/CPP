#include <iostream>
# include <vector>
# include <iterator>
#include <cstdint>
# include <fstream>

// binary files are much closer to the computer than a text file, so we need to work with the computer
// binary files are opened using thier own mode, fstream::binary
// we should always use the read() and write() methods when working with binary files, << and >> are not suitable
// the best way of working with a binary file is to create a struct whose data members correspond to fileds in the file format
// modern hardware is optimised for accessing data which is "word aligned", on a 32 bit system, this means that the address of each object is a multiple of 4
// if this is not the case, accessing the data will be much slower, some systems can't infact access non word aligned data at all
// if a struct is not word-aligned, compilers will usually add extra bytes that place the struct members at the required offsets
// these are known as padding bytes

// if we actually want the data to be at different offests, these padding bytes will introduce a discrepancy and the resulting file will not be valid
// most compilers provide a non-standard #pragma directive to set alignment

using namespace std;

#pragma pack(push,1)   // push 1, so reduce the size of the gap between data members to 1, so data members come one after the other
struct point{
    char c;
    int32_t x;
    int32_t y; // we use fixed size integers to make sure we get the same resultd on all systems

};

# pragma pack(pop)

int main(){

// the first argument to read() and write() will be the address of the point object
// this needs to be converted to a pointer to char, we will use reinterpret_char with the address of the struct object
// the second argument will be the number of bytes in the struct object
     point p {'I',1,2};
     ofstream ofile("file.bin", fstream::binary);

     if (ofile.is_open()){
         ofile.write(reinterpret_cast<char *>(&p), sizeof(point));
         ofile.close();
     }

     ifstream ifile("file.bin", fstream::binary);
     point p2;

     if (ifile.is_open()){
         ifile.read(reinterpret_cast<char *>(&p2), sizeof(point));
         ifile.close();
     }

     cout << "Read " << ifile.gcount() << "bytes \n";  // reading without pragmas will cause 12 bytes to be read, 1 for the char, then 3 as a gap, then 4 each for the ints
     // reading with pragmas will only read 9 bytes, as the 1 char is foloowed immediately by the 8 ints
     cout << "Read x = " << p2.x << ", y = " << p2.y << endl;
}