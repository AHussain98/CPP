#include <iostream>
#include <fstream>

using namespace std;
//Input and output are performed using streams in C++. To output something, you write it to an output stream,
//and to input data, you read it from an input stream. A stream is an abstract representation of a source of data
//or a data sink. When your program executes, each stream is tied to a specific device that is the source of data
//in the case of an input stream and the destination for data in the case of an output stream


//C++ streams use buffering to minimise calls to the operating system
// data is temporarily held in a memory buffer during write operations, the size of the buffer is the maximum amount the operating system will accept
// when the buffer is full, the stream will remove the data from the buffer and send it to the OS
// this is known as flushing the output buffer
// we want to minimise calls to the OS because the programme is waiting while this happens
// ostream buffers are flushed depending on the terminal configuration, usually at the end of every line, cout is always flushed before the programme reads from cin
// ofstream is only flushed when the buffer is full
// there is no direct way to flush input streams
// std::flush allows us to control when the streams buffer is flushed, this is a stream manipulator
// all data in the buffer is immediately sent to its destination, this significantly affects performace and should only be used when data really needs to be up to date, e.g. a log file
//

int main() {
	ofstream ofile("log.txt");  // output file, so we're writing to a file
	if (!ofile) { // if file could not be connected to using stream object
		cout << "Could not open file! \n";
		return -1;
	}

	for (int i = 0; i < 1000000; i++) {
		cout << i << '\n';
        ofile << i << '\n'; // if we push << flush here, then the line will be flushed every time it is written, but the log will print every line fully
                              // endl is the equivalent of doing newline followed by flush, endl is a flushed function

		if (i == 66666) {  // this line appears in the terminal, as the display gets flushed after every line, but not in the log, because that buffer was not flushed in time
			terminate();  // function that stops the program immediately, log file only got to line 66651
		}

	}
	ofile.close();
}