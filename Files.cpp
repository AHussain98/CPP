# include <iostream>
# include <fstream>
# include <string>
# include <vector>
// a file is just a sequence of bytes, identified by a filename, where dont need to know how the data is stored or where
// file interactions are represented by fstream objects, they always access files 'sequentially' (a sequence of bytes accessed in order), fstreams do not understand file formats
// with an fstream object, we can open them, read, write and close them
// each of these operations is done by the file object calling a function in the os api
// the file must be opened before we can use it, and should be closed after use
// as data passes between the program and the file, it may be temporarily stored in a memory buffer, this makes large data transfers more efficient but slower
// ofstream is file stream used for writing
// ifstream is file stream used for reading
// you need to associate a filestream object with the file you're using

int main(){
std::string filename {"text.txt"};
std::ifstream ifile (filename); //define ifile as an ifstream variable, giev the file a name

if (ifile){ // this means if ifile is valid, it exists
        std::string text {" "}; //create a string object called text
        while (getline(ifile,text)){  // read a word from the file and output it, when there's no more data, this will return false
           // getline function is best way to take input, arguments are file stream object and string object reads line by line of input, reads it into the string object
            std::cout << text << ", ";
        }
        // getline() returns true when there is  line of text, and false when there is no more, so will be false when the file is empty

        std::cout << '\n';
        ifile.close();  // cut off the connection with the file, the stream object is now empty
}
else{
    std::cout << "File cannot be opened" << '\n';
}

// to write to a file, we need to declare an ofstream object
std::ofstream ofile {"text.txt"}; // this represents a 'communication channel' which is used to send data to the file name we've passed it
// we should check the stream state before using it, as before
if (ofile){ //true if the file is ready for data to be written to it
std::cout << "Successfully opened the file for writing\n";
}
// we can use ofile the same way as cout
std::vector<std::string> words {"we","got","this!"};

for (auto word : words){ // so for strings in the vector above, push them into the file
    ofile << word << ',';
}

ofile.close(); // close the binding between ofile and text.txt
}

// when fstreams destructor is called, the file is automatically closed, this causes any unsaved data to be written to the file
// however, it is good practice to explicity close files, as above
