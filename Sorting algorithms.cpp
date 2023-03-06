# include <iostream>
# include <algorithm>
# include <vector>
# include <string>

// sorting algorithms put the elements in an iterator range into order
// by default, the elements < operator is used, we can ovveride this by providing our own comparison function

// sort() orders the elements in ascending order, usually implemented as a quicksort (fastest algorithm in the general case)
// elements which have the same key may have their order changed
// stable_sort() will do the same sort but keeps teh elements in the same order if they have the same sorting value
// is_sorted() returns a bool depending on whether the iterator range is sorted
// is_sorted_until() returns an iterator to the first element which is not in order

// sometimes we only need to sort part of a container, e.g. display the first 20 results only, in this case we can do a partial sort
// std::partial_sort(), this is faster than doing a complete sort
// partial_sort() takes an extra iterator, the offset of this iterator gives th enumber of elements we want in the result
// e.g. begin(vec) + 5 will sort the first 5 elements (of all the elements in the string)
int main(){

std::vector<int> vec {2,6,3,99,4,2,6};

std::sort(begin(vec),end(vec));

for (auto i : vec){
    std::cout << i << " ";
}

if (std::is_sorted(cbegin(vec),cend(vec))){
    std::cout << std::endl << "vec is sorted!" << std::endl;
}

std::string str {"qaveblszcd"};

std::partial_sort(begin(str),begin(str) + 3, end(str));  // only sort the first 3 elements in the string

std::cout << str;

// so only sort 3 characters at a time, we could do auto it = begin(str);, advance(it,3); and then use it as the middle argument in the partial sort algorithm

// there is also partial_sort_copy, which will store the result in a destination, it will sort and store as many elements that fit in the destination container
// if the destination is large enough, the entire string will be sorted and copied

// nth_element() takes an iterator to an element in the range, it rearranged the elements so that the iterator points to the element that would be in that position if the ange was sorted
// so if the iterator is begin() + 4, the iterator will point to the element that ranks 4th if the range was sorted
// it then performs a partition with this element as the partiion point, all the elements before it have lower value and after it have a higher value
}