# include <iostream>
# include <algorithm>
# include <string>
using namespace std::string_literals;

// a permutation is a possible arrangement of some elements
// there are stl algorithm functions to find the next and previous permutation in the sequence
// next_permutation() takes an iterator range and reorders the elements to give the next permutation in ascending order
// it returns a bool, depending on whether there is a next permuattion. e.g. the next permutation of abc is acb
// next_permutation uses < by default, but we can supply it with a predicate

// prev_permutation() will reorder elements to give the previous permutation
// to get all the permutations in reverse, the elements must be sorted in descending order

// is_permutation() takes two iterator ranges and returns true if both ranges contain th esame elements, even if they are in a different order

int main(){
std::string str {"abc"};

while (std::next_permutation(begin(str),end(str))){
    std::cout << str << " ";
}

std::cout << str << std::endl; // returned to abc

std::sort(begin(str),end(str),[] (int m, int n) {return m > n;   // elements sorted in descending order
});                                                                // otherwise prev_permutation won't work

while(std::prev_permutation(begin(str),end(str))){
    std::cout << str << " ";
}

std::cout << str << std::endl;

// there are a number of min and max algorithms in the c++ library, they return the largest and/or smallest element
// by default, the elements < operator is used

int demo {1};
int demo2 {2};

std::cout << std::max(demo,demo2) << std::endl;

// we can also provide a predicate

std::string str1 {"abcdeaaaa"};
std::string str2 {"fbhibtec"};

std::cout << std::max(str1,str2, [] (std::string lhs, std::string rhs) { return lhs.size() < rhs.size();});

// std::minmax() will return a std::pair, first is the max and second is the min

// std::min_element() and std::max_element() will take an iterator range and return an iterator

// std::minmax_element() returns an std::pair of iterators, first is an iterator to the max and seocnd to the min

std::cout <<  std::endl;

auto max_init = std::max({12,5335,3,45,900000009});
std::cout << max_init << std::endl;

auto max_string = std::max(str1,str2);  // string max when not overloaded gives a different answer
std::cout << max_string;


}

