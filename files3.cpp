#include <iostream>
#include <fstream>
# include <limits>
// we bind a file when we pass its name to the stream consrtuctor

int main(){
//   std::ofstream ofile {"hello.txt"}; //create an output stream and bind it to the file hello.txt, using the default mode, no file mode given to the constructor so default trunc applied
//   // or we can also bind the output stream object to the file using the open() method
//   std::ofstream o2file; // create another ouput stream object
//   o2file.open("hello.txt"); // bind the stream object to the file
//   o2file << "This is just some data I'm writing!"; // write some data to the file
//   // in both cases, when ofstream binds the file, the file mode will be applied and if the output file doesnt already exist, it will be created
//   o2file.close(); // it seems you can onlu have one stream object attached to a file at one time
////   // c++ streams have member functions to check the state of the stream
//   // good() returns true if the input was read successfully
//   // fail() returns true if there was a recoverable error, such as reading wrong type of data
//   // bad() returns true if there was an unrecoverable error, such as disc failure
//
//
//   // we can try this out by reading in some data from cin
//
////   char x;
////
////   std::cin >> x;          // even if you enter an int, it will still be good, as ints can be converted to chars, but not the otehr way around
////   if(std::cin.good()){ // the streams state generally referes to the last operation we performed on it, e.g. taking in data here
////       std::cout << "data was good";
////   }
////   if(std::cin.fail()){
////       std::cout << "data was bad, try entering an int";
////   }
//
//   // clear() restores the streams state to valid
//
//   // eof() returns true if the end of file has been reached
//
//   std::ifstream ifile;
//   ifile.open("hello.txt");
//
//   if(ifile){
//       std::cout << "not failed!";
//   }
//   std::string text {" "};
//   while (getline(ifile,text)){ // while there's data in teh file, attach it to the text object and print it
//       std::cout << text;
//   }

   int x {0};

   std::cin >> x;  // the stream will go through the characters in its input and interperet them as ints, only stopping when it encounters whitespace
   //  if a character cannot be converted into an int, it will leave it in teh buffer and continue, but it does not flush, this process will repeat itself endlessly

   bool success{false};

   while (!success){ //while success is false
     if(std::cin.good()){
         std::cout << "Well put!";
         success = true;
     }
     else if (std::cin.fail()){
         std::cin.clear(); // restores the stream state to valid but there are still soem characters in the buffer, unprocessed
         // so we need to force cin to flush its buffer
         // because currently, the next time the program reads from cin, the stream does not need to wait for user input as it already has this trapped data in its buffer to work on
         // hence why we need to flush the buffer
         // unfortunately, input streams do not support flushing, so we need to use the ignore function which will remove characters from teh buffer
         // it takes two arguments, the max number of chars to move and a delimiter that when encountered stops it from removing characters
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // remove the whole size of the buffer or everything up to newline

         std::cout << "Try entering a number";
         std::cin >> x;
     }

   }







}