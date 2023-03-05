# include <iostream>
# include <algorithm>
# include <string>
# include <vector>
// a re=ordering algortihm re-arranges the elements inside an iterator range, it does not change thier values
// reverse() takes the elements in an iterator range and reverses their order, there is also a _copy() version


int main(){

std::vector<int> vec {1,2,3,4,5};
int vecEnd {vec.size() -1};
// reverse a vector using a loop
for (int i = 0; i <= (vec.size()/2) ; ++i){
    int temp {vec[i]}; // use a temporary variable to store the current value at index i
    vec[i] = vec[vecEnd - i];   // give index i a value of the corresponding index value on the other side of the vector
    vec[vecEnd - i] = temp;   // make the value on the end equal to temp, which is the original value at index i

    // even easier, int the loop we could just do:
    // std::swap(vec[i], vec[vecEnd - i]);
}


for (auto i : vec){
    std::cout << i << " "; // swapped!
}

// even easier than the above loop, we could just call the reverse fucntion

std::cout << std::endl;

std::reverse(begin(vec),end(vec));

for (auto i : vec){
    std::cout << i << " "; // swapped back!
}


// rotate() performs a rotation about a given element, all the elements before the pivot are moved after and the pivot and all the elements after are moved to the front of the iterator range
// rotate() takes three arguments, the beginning, pivot and end of the range, the return value is an iterator to the original first element

auto pivot = begin(vec);
advance(pivot,2); // pivot is an iterator to the middle of the vector, advanced to the third element
// remember avdance() increments iterator by n elements
auto res = std::rotate(begin(vec),pivot,end(vec));

std::cout << std::endl;

for (auto i : vec){
    std::cout << i << " "; // pivoted about 3!
}

std::cout << std::endl;
std::cout << *res; // res is an iterator to the element in vec with value 1, remember rotate() returns an iterator to the original first element

// rotate() also has a copy version

}