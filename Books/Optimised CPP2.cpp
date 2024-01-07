# include <iostream>
# include <algorithm>
# include <vector>

/* With guaranteed copy elision introduced in C++17, the statement auto x = Foo{}
is identical to Foo x{}; that is, the language guarantees that there is no temporary 
object that needs to be moved or copied in this case. This means that we can now use 
the left-to-right initialization style without worrying about performance and we can 
also use it for non-movable/non-copyable types, such as std::atomic or std::mutex.

In contrast to a const reference, a mutable reference cannot bind to a temporary. As
mentioned, we use auto& to denote mutable references. Use a mutable reference only
when you intend to change the object it references.

determining whether an object is moved or copied is quite simple.
If it has a variable name, it is copied; otherwise, it is moved. If you are using
std::move() to move a named object, the object cannot be declared const.

Writing an empty destructor can prevent the compiler from implementing certain
optimizations.

Don't move when copies are elided anyway, moving is less efficient than not copying at all

the compiler moves an object when the object can be categorized as an
rvalue. The term rvalue might sound complicated, but in essence it is just an object
that is not tied to a named variable, for either of the following reasons:
• It's coming straight out of a function
• We make a variable an rvalue by using std::move()

Exceptions can be avoided because throwing and catching exceptions is relatively expensive and not deterministic
Exceptions increase the size of the binary program aswell


*/

auto x = 10;  // auto is useful because you can't leave an auto variable uninitialised
auto v = { 1,2,3,4,5 }
auto num_above_3 = std::count_if(v.begin(), v.end(), [](int i) {return i > 3; });  //  stateless lambda

int main() {

}