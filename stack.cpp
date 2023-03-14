# include <iostream>
# include <stack>

// stacks are LIFO, can only add or remove one element at a time
// element at top is always the last one added, element at bottom is first one added
// stack is a data structure in which elements are stored in the order which they are inserted
// when new elements are added to the stack, they are inserted at the top, only the element at the top can be accessed
// as a stack is processed, the element at the top is removed and the element below it as now the top
// elements are removed in teh reverse order they were added

// the c++ stack is implemented using deque
// std::stack has a similar interface to priority_queue
// push, pop, top, empty, size are all functions we can use with stacks
// top() returns but does not modify the element at the top, returns via reference to const
//

int main(){

std::stack<int> s;
s.push(1);
s.push(2);
s.push(3);
std::cout << s.top() << std::endl;
s.pop();
std::cout << s.top() << std::endl;


// stacks are used by the c++ runtime for managing local variables 
// stacks are used for parsing expressions in compilers, checking unbalanced parenthesis on source code
// implementing undo functionality and storing hisroty for back/forward buttons in web browsers

}