# include <iostream>
# include <vector>
# include <algorithm>

// merging algorithms take two iterator ranges, assume the elements in the range are sorted and then combine the elements and write them to a destination
// merge() combines two sorted iterator ranges into a destination
// the destination will contain all the elements from both ranges, in order, the < operator is used by default to order the elements
//merge(cbegin(vec1),cend(vec1),cbegin(vec2),cend(vec2),back_inserter(vec3)); // this will merge the elements of the sorted vectors vec1 & vec2 into vec3
// set_intersection() will combine two sorted iterator ranges into a destination, the destination will contain only the elements which are present in both ranges, in order, again < used by default to order the elements

// set_union will populate vec3 with elements that appear in vec1 and/or vec2, but they'll only appear in vec3 once
int main(){

std::vector<int> vec {1,2,3,4,5};
std::vector<int> vec2 {1,2,3,4,6,7,8};

std::vector<int> vec3;
std::vector<int> vec4;

std::merge(cbegin(vec),cend(vec),cbegin(vec2),cend(vec2),back_inserter(vec3)); // vec3 created by merging 1 and 2
std::set_intersection(cbegin(vec),cend(vec),cbegin(vec2),cend(vec2),back_inserter(vec4)); // vec 4 contains only the elements in vec1 and vec2
}



