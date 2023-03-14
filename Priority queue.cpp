# include <iostream>
# include <queue>

// with a standard queue, the elements are arranged strictly in arrival order, we often need to process some elements out of sequence
// e.g. VIP messages should go to the front of the queue, these can be implemented using a priority queue
// a priority queue us very similar to a queue, however it orders its eements with the most important at the front and least important at the back
// c++ provides a priority queue, the < operator of the element type is used to order the queue
// if two elements have equal priority, by default teh queue does not list them by arrival time

// elements are added into the priority queue based on their priority, so an element with highest priority will be added directly to teh front of the queue
// highest priority element is always the one removed
// std::priority_queue can be implemented as a vector or a deque, it has a similar inetrface to std::queue
// use push() to add an element to the queue, it will be inserterd in fornt of all the other elements with lower priority
// pop() removed the element from teh front of the queue, element with next highest priority becomes the new front element
// top() returns the element with highest priority
// empty() returns true if there are no elements in the queue
// size() returns the number of elements in the queue

// priority queues are useful for processing data which needs to be prioritised
// examples are operating system scheduleres, message protocols, management systems

// we can only access the "top" element, if we need access to other elements, use a map instead
// the maps key is priority, value is data
// elements with the same priority are not guaranteed to be in arrival order
// if ordering by arrival time is important, use a nested map:
// the outer maps key is priority, the inner maps key is arrival time, value is data


int main(){

std::priority_queue<int> pq;
pq.push(1);
pq.push(5);
pq.push(7);
pq.push(2);
pq.push(100); // moves to top of queue

std::cout << pq.top() << std::endl;


}