# include <iostream>
# include <vector>
# include <iterator>
// an output stream iterator inserts data into an output stream
// an insert iterator adds new elements to a container
// to add a new element, we assign to the insert iterator

// there are three types of iterator, whoch add an element at different positions
// std::back_insert_iterator adds an element at the bacl
// std::front_insert_iterator adds an element at the front
// std::insert_iterator adds an element at any given position

// to get an insert iterator, we call an "inserter" function
// we pass the container object as the argument to the inerster, the function returns an insert operator for that object
// back_inserter() returns a back_insert_iterator
// front_inserter() returns a front_insert_iterator
// inserter() returns an insert_iterator

// to add a new element at the back of the container, we assign a value to back_insert_iterator
// the push_back() member function of the container will be called
// the value we assign will be passed as teh argument to push_back()
// every time we assign to this iterator, a new element is added at the back of the container

//  the front_insert_iterator is similar, except it calls push_front() when we assign to it
// this does not work with std::vector or std::string

// inserter() takes a second argument, which is a positional iterator
// this iterator represents the position where new elements will be added

int main(){

std::vector<int> vec; // create an empty vector
auto it = back_inserter(vec); //create a rear insert iterator for the vector
*it = 99;
*it = 88; // we've not called teh push_back() function for teh vector vec, 99 and 88 have been pushed onto teh back of teh vector

std::cout << vec.size() << std::endl;
for (auto v : vec){
    std::cout << v << ",";
}

auto el2 = next(begin(vec)); // get an iterator to the second element of vec
auto it2 = inserter(vec,el2); //we now have an insert iterator for the second element of vec

*it2 = 56; // assign to the second element of vec using the inserter iterator, this calls the insert member function of the vector
std::cout << std::endl;
std::cout << vec.size() << std::endl;
for (auto v : vec){
    std::cout << v << ",";
}

// an important note is that after you've used the inertion iterators to insert, the state of teh vector has now changed
// this means that the insertion oterator swill likely no longer be valid and you shouldnt use them again
// e.g. it and el2 above should not be used again since we've already inserted using them


// insert iterators can be used anywhere where a positional iterator is expected
// insert iterators are useful for populating contains, and as srguments to algorithms that copy iterator ranges
// they can also be used in conjunction with stream iterators
// the advantage of using an insert iterator is that the container will always expand to make more room, using a standard iterator may cause overflow

// insert iterators also make it easier to work with streams, see below

std::istream_iterator<std::string> iis(std::cin); //input stream iterator which is bound to teh standard input, iterator to read strings
std::istream_iterator<std::string> eof;  // empty iterator

std::vector<std::string> vec2;   // vector to store input
auto it3 = back_inserter(vec2);   // back insert iterator, so when we derefence it3 below, we're calling pushback on teh vector

while(iis != eof){     // while the input is not empty, compare teh two iterators, if there's input, then store it in the vector
    it3 = *iis;     // this is the bit that actually takes multiple inputs, we dereference the input stream iterator to get the input and store it
    ++iis;         // move onto teh next input
} // dereferencing the input stream iterator is what gives us our next bit of input
// entering ctrl+z is regarded as 0 input, so the iterator pointing there is pointing to nothing, then the considion becomes false
// so data is read form the stream and stored in teh vector
// and when we reach the end of teh loop, teh data entered into teh stream should be the same as was entered into the keyboard

for (auto i : vec2){
    std::cout << i << ",";
    std::cout << std::endl;
}

}