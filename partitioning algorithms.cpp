# include <iostream>
# include <algorithm>
# include <vector>
# include <string>

// partitioning algorithms partition the elements in a container into two groups
// elements which have some property are at the front of the container, elements which do not have that property are at the back of the container
// the partition point marks the boundary between the two groups

// partitioning is very useful in interactive applications, such as displaying items selected by the user above those that were not

// partition() takes an iterator range and a predicate function
// all elements for which the predicate function returns true are moved to the front of the range
// all elements for which the predicate function returns false are moved to the back of the range
// the elements in each group may not be in order

// stable_partition() will do the same thing but the elements within a group will remain in the same order

// is_partitoned() takes a iterator range and a predicate function, it returns a bool depending on whether or not the range of elements is already partitioned by that predicate function

// partition_point() takes the same arguments as is_partitoned() and will return an iterator to the first element that returns false for teh predicate
// this element is the initial partition point

int main(){

auto is_odd = [] (int n) { return (n%2) == 1;};   /// store this lambda function for later

std::vector<int> vec {1,2,3,4,5,6};

std::partition(begin(vec),end(vec), [] (int i) { return (i%2) == 0;}); // move everything that is divisible by 2 to the front of the vector

for (auto i : vec){
    std::cout << i << " ";
}

std::cout << std::endl;

if (std::is_partitioned(cbegin(vec),cend(vec),[] (int i) { return (i%2) == 0;})) {
    std::cout << "vec has been partitoned!" << std::endl;
}

if (!std::is_partitioned(cbegin(vec),cend(vec),is_odd)) {
    std::cout << "vec has not been partioned by is_odd" << std::endl;
}
}