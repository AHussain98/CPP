# include <iostream>
# include <queue>

// a queue is a data structure in which elements are stored in the order they are inserted
// as a queue is processed, the element at the front is removed and the element behind in moves to the front
// new elements are inserted at teh back of teh queue
// elements can only be removed from the front, in the same order they were added

// c++ has an std::queue implementation in std::queue, this is a FIFO data strcuture
// a queue is usually implemented as a deque, because there's a lot of operations at the front of the container
// no support for iterators for queues

int main(){

std::queue<int> values;

values.push(23);
values.push(46);
std::cout << values.front() << std::endl;
values.pop();
std::cout << values.front();

// queues are mainly used for temporarily storing data in the order it arrived
// these could be network data packets waiting for cpu time, must be processed in sequence
// another example could be an inventory system for perishable goods, oldest goods must be shipped first

// queues are useful for processing events in the order they occur
// we can only access the front element, if we need access to other elements, use a vector or a map (with arrival order as key) instead of a queue
// no provision for queue jumping, which is often needed in real world applications



}