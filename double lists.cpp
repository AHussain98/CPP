# include <iostream>
# include <list>

// in a double linked list, each node has a link to the previous node as well as to the next node
// a double linked list can be easily traversed backwards as well as forwards, by following the pointer to the previous node
// the c++ standard library provides std::list to implement double linked lists
// when we get to the last element, the next pointer is NULL, and at the first element, the previous pointer is NULL

// to add an element at the back of the list, crate a node for it
// make the last node's "next" link point to it
// make out "previous" link point to the last node
// the added node is now the last node, the other elements are left untouched

// to insert a node in the middle of a linked list
// make the new nodes "next" link point to the following node and make the new nodes "prev" link point to the before node
// make the before node point to the new node and make the following nodes "previous" pointer point to the new node
// the other elements are left untouched

// to remove an element from a linked list, make the next link of the previous node skip the node
// make teh following nodes previous link point to teh node before
// destroy the node, again the other elements are left untouched

// adding or removing elements from the middle of a list is faster than for a vector, we don't need to move element around/reallocate the memory block unlike with a vector
// lists do not support indexing or subscript notation
// accessing an element is slower than for a vector, you cant just jump to that element like with a vector, you have to access each node one at a time
// lists use more memory to store an element than vectors do, due to needing pointers with nodes
// lists are useful where we expect to add or remove a lot of elements frequenctly, especially in the middle of the list

int main(){

    std::list<int> list {3,3,2,2,1,1}; // create a double linked list

    for (auto i : list){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto last = list.end(); // create an iterator pointing to the last element
    advance(last,-1); // last now points to the element before the last one

  auto two = list.insert(last,65); // add 65 to be the second last element, the insert function returns an iterator to the inserted element

    for (auto i : list){
        std::cout << i << " ";
    }

       std::cout << std::endl;
 list.erase(two); // erase the newly inserted elements

   for (auto i : list){
        std::cout << i << " ";
    }

     std::cout << std::endl;
//
//     // lists support many of the operations we would expect for a sequential container, we can use push_back and push_front() to add elements
//     // we can use iterators to loop over the elements of a list
//     // However, lists do not support random access, we cannot jump straight to a particular element, for example
//     // we have to start at the beginning of the list and iterate the required number of times
//
//     // functions in the <algorithm> header that require random access will not work
//
//     // so instead of using sort() algorithm, we can use the lists built in sort member function
//
     list.sort();
//
//      for (auto i : list){
//          std::cout << i << " ";
//      }
//
//      // in some cases, the list member functions of algorithms are faster than the generic equivalents
//      // the generic version of remove() shuffles the removed elements to the end of the container, the list member fucntion deletes the elements immediately by changing the pointers, no need to call erase()
//
   list.remove(3); // remove the node with data value 3
//
//     // in general, if you're going to move members around, its much better to use teh list member functions rather than generic algorithms
//     //  .reverse() reverses the order of elements
//     // .remove() removes certain elements from the list
//     // .remove_if() deletes elements from the list which match certain criteria
//     // .unique() deletes duplicate elements form teh list
//
//     // these all modify the object they are called on
//
     list.unique();
//
    list.reverse();
//
  std::cout << std::endl;
//
    for (auto i : list){
          std::cout << i << " ";
     }
//
//     // merge() will remove elements from the argument list and merge them into the "this" list
//     // the list will be sorted in ascending order, provided both lists were sorted before the operation
   std::cout << std::endl;
     std::list<int> list2 {22,33,44};
//
     list.merge(list2);

    for (auto i : list){
          std::cout << i << " ";
     }
//
//    // splice() moves elements from another list into a list
//    // the first argument is an iterator to an element in "this" list, the elements will be inserted just before that element
//    // the second argument is the list to be spliced in
//
//  std::forward_list implements splice_after() instead of splice()
// this works almost the same way, however the elements are spliced in after teh iterator argument, not before it

}