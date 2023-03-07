# include <iostream>
# include <cstdlib>
# include <random> // c++11 classes in here to help us use random numbers
# include <vector>
# include <algorithm>

// random numbers are numbers that appear to have been chosen by chance

int main(){

//std::cout << std::rand(); // cstyle random numbers, now deprecated

std::default_random_engine eng; // create engine object - generates sequence

for (int i = 0; i < 5; ++i){
    std::cout << eng() << " ";  // call the functor of the object to get the next number
}

std::cout << std::endl;

std::uniform_int_distribution<int> idist(0,10); // we want random ints in the range 1 to 10

for (int i = 0; i < 5; ++i){
    std::cout << idist(eng) << " ";  // pass engine object into uniform distribution seed
}

// can do doubles using uniform_real_distribution<double>

// std::shuffle() calls uniform_int_distribution internally, rearranges an iterator range in a random order

std::cout << std::endl;

std::vector<int> vec {1,2,3,4,5};

std::shuffle(begin(vec),end(vec),eng);  // randomised!

for (auto i : vec){
    std::cout << i << " ";
}

// the above is actually implemented like so:

std::uniform_int_distribution<int> cdist(0, vec.size() -1);  // this is going to generate an index, and we need it to be in range, so the max is size -1
for (int i = 0; i < vec.size(); ++i){
    std::swap(vec[i], vec[cdist(eng)]);
}   // swapped all elements randomly

std::cout << std::endl;

for (auto i : vec){
    std::cout << i << " ";
}

}