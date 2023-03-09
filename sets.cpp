# include <iostream>
# include <set>

// a set is a unstructured collection of elements, available in <set>
// this is an associative container
// an element consists only of a key, which must be unique, no duplicated allowed
// the elements of std::set are stored in order, by default the < operator of the key is used to order them
// for efficiency, std::set is implemented as a tree, usually a red-black tree
// we use insert() to add an element, the set will add the new element in the right place in the tree
// we use erase() to remove an element
// these operations may cause the tree to become rebalanced
// the tree will check if it has become unbalanced during any operation, if so then it stops the operation and rebalances itself, then continues, the operation takes longer than normal in that case
// if we try to insert an element into an std::set that is already present, the insert will fail, this is because insert() returns a pair, the second member is a boolean which is true or false depending on whether the insert ducceeded
// the first member is an itertaor to an element: the newly added element if successful, the existign element with that key if unsuccessful



int main(){

std::set<int> asad {1,2,3,4,5};  // create a set object (can be empty but initialised in this case)

for (auto i : asad) {
    std::cout << i << " ";
}

std::cout << std::endl;

asad.insert(17);     // insert using a unique key we want to push into teh tree

auto ret = asad.insert(15); // insert() returns a pair
if (ret.second) {
    std::cout << " 15 inserted succesfully" << std::endl;
}

auto ret2 = asad.insert(3);
if (!ret2.second){
    std::cout << "3 already exists!";
}

// find() returns an iterator to the element with the key we pass to it
// count() returns the number of elements with the key passed to it, since there are no duplicates, this can only be 0 or 1

// the elements of std::set are const otherwise we could change teh keys, we can't change them using iterators, and they cannot be reordered because the set maintains its own internal ordering,
// so we can only use algorthms that just read data and don't attempt to change or reorder elements

// sets are very fast at accessing an arbitrary element, insertion and deletion are usually very fast as long as the tree does not get unbalanced
// sets are useful for checking membership or non membership, and when duplicate data is not wanted


}