#include <iostream>
#include <string>
#include <vector>
using namespace std;

// for iterating through a sequence, array or container from the stl, we use an iterator
// this avoids the use of any dangling pointers or undefined behaviour
// you define an iterator of the same class as the container or sequence, point it at the start of the sequence and stop the loop at the end

int main(){

string str {"Asad"};
string::iterator it = str.begin();   // begin function returns an iterator to the first element

while (it != str.end()){ // end returns an element correcsponding to the element after last, this is an invalid iterator which must not be dereferenced
 // each iterator is specific to the object, they must not be mixed with iterators to other objects
    cout << *it;  // dereference the iterator to get the value of the element
    it++;
}

//now for a vector

vector<int> v {1,2,3,4,5}; // with vectors, you always have to define the type
for(vector<int>::iterator it = v.begin(); it != v.end(); it++){ //  we've included the std namespace, so this is actually std::vector::iterator
    cout << *it;
}

// there are actually several different types of iterator

// if we want to prevent the loop from modifying the string, we can use a const_iterator

string::const_iterator cit = str.begin();

while (cit != str.end()){
    std::cout << *cit; // the * comes before the name when dereferencing
    cit++;
 // use it just like a regular iterator
 // useful when iterating and you want to be sure you don't accidentaly change anything
 // also if you have a const container, you must use a const iterator
 // so in a function body, containers are commonly passed by const reference, a const iterator must therefore be used to loop through them
}

// we can also use a reverse iterator to reverse backwards from the last element
string::reverse_iterator rit = str.rbegin(); // you use rbegin and rend functions for this
while(rit != str.rend()){   // rbegin() returns a reverse iterator to the last element, rend() returns a reverse iterator to the element before the first
    cout << *rit;
    rit++;
}

// c++ also has const forms of begin(), end(), rbegin() and rend()
// you have to use a const_iterator to use these

for (string::const_iterator conin = str.cbegin(); conin != str.cend(); conin++){
    cout << *conin; // we could just use auto instead of string::const_iterator
}

  // there are also  built in begin and end global functions we can use with arrays
  // useful for arrays where we dont have member functions because arrays arent a class
  int arr[5] {1,2,3,4,5};
  for(auto it = begin(arr); it != end(arr); it++){    /// we can also use rbegin and rend, as well as cbegin and cend, crbegin() and crend()
      cout << *it;
  }

// we also have ranged for loops where we can use special concise syntax for iterating over containers

for (auto i : str){
    cout << i; // we can iterate over the string very easily using this technique
    // i is a copy of the current element, therefore changes to i do not affect the container elements
    // remember c++ has value sematics by default, not reference semantics
}

// so to make changes to the container values using this technique, lets use the reference operator &
for (auto& i : str){ // auto won't include any referenced by default remember
    i+=2;
    cout << i; // these changes will be performed on the actual str container, not on a copy, as we've passed by reference
}

// using these loops is recommended if we wish to visit every element once, in order, without adding or removing elements
}