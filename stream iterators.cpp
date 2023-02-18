  # include <iostream>
  # include <iterator>
  # include <string.h>
  # include <vector>

  using namespace std;

// the standard library provides iterators which work on streams, these are defined in <iterator>
// the data must all have the same type
// istream_iterator reads an input stream, ostream_iterator writes an output stream
// assigning to an ostream_iterator will put an object on the stream
// dereferencing an istream_iterator will get the object at the current position in the stream
// incrementing the istream_iterator will move the stream to the next object

// ostream_iterator must be bound to an output stream, and everytime we assign to this iterator, data is pushed into the stream

int main(){

 ostream_iterator<int> oi(cout,"\n"); //create the output stream iterator, we can pass in a second argument to the iterator constructor, this is the delimiter

for (int i = 0; i < 10; i++){
      oi = i; //assign i to the iterator
}

// now lets create an input stream iterator
istream_iterator<int> ii(cin); // pass in the input stream object cin, <int> because we're reading in ints
int x = *ii;  // this reads a number from cin into the variable x
cout << "you entered " << x << endl;

// to read multiple inputs, we use a loop
// we need to know when to stop reading
// we can detect end of input by checking if our iterator is empty
// we create an empty iterator by not binding it to a input object

istream_iterator<string> iis(cin); //iterator to read input
istream_iterator<string> eof; //empty iterator

std::vector<string> vs; // vector to store input

while (iis != eof){ // so while the input iterator is not the same as the empty iterator, on windows, empty input means using ctrlZ, you have to use ctrl!!!
vs.push_back(*iis); //push back the dereferenced value of the iterator
iis++; //move the iterator along to read the next input
}

for (auto v: vs){
    cout << v;
}

}