# include <iostream>
# include <algorithm>
# include <string>

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

std::cout << str << std::endl;

std::sort(begin(str),end(str),[] (int m, int n) {return m > n;   // elements sorted in descending order
});

while(std::prev_permutation(begin(str),end(str))){
    std::cout << str << " ";
}


}