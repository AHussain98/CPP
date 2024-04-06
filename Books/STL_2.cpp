# include <iostream>
# include <array>
# include <vector>
# include <deque>
# include <list>
# include <forward_list>
# include <set>
# include <map>
# include <unordered_map>
# include <unordered_set>

// core abilities of STL containers:
/*
all containers provide value rather than reference semantics.containers copy and /or move elements internally when they are inserted rather than managing references to them
 Thus, ideally, each element of an STL container must be able to be copied and moved. If objects you want to store don’t have a public copy constructor, or if copying is not useful — because, for example,
 it takes too much time or elements must be part of multiple containers — you might use only move operations, or the container elements must be pointers or pointer objects that refer to these objects.

 The elements inside a container have a specific order. Each container type provides operations
that return iterators to iterate over the elements. This is the key interface of the STL algorithms.
Thus, if you iterate multiple times over the elements, you will find the same order, provided that
you don’t insert or delete elements. This applies even to “unordered containers,” as long as you
don’t call operations that add or delete elements or force an internal reorganization.

 In general, operations are not “safe” in the sense that they check for every possible error. The
caller must ensure that the parameters of the operations meet the requirements these operations
have. Violating these requirements, such as using an invalid index, results in undefined behavior,
which means that anything can happen.
Usually, the STL does not throw exceptions by itself. If user-defined operations called by the
STL containers do throw, the behavior differs

*/

/*
every container class provides a default constructor, a copy constructor and a destructor

• You can initialize a container with the elements of another container:
std::list<int> l; // l is a linked list of ints
...
// copy all elements of the list as floats into a vector
std::vector<float> c(l.begin(),l.end());

you can use a move constructor to initialise a container:
std::vector<int> v1;
...
// move contents of v1 into v2, state of v1 undefined afterward
std::vector<int> v2 = std::move(v1);
As a result, the newly created container has the elements of the container used for initialization,
whereas the contents of the container used for the initialization is unspecified afterward. This constructor provides significant performance improvements because internally,
the elements are moved by switching some pointers instead of copying element by element. So whenever you no longer need a container, which gets copied, you should use the move constructor.

if you assign containers, you copy all elements of the source container and remove all old elements in the destination container. Thus assignment of containers is relatively expensive

all containers provide a swap() member function to swap contents
of two containers. In fact, it swaps only some internal pointers that refer to the data (elements,
allocator, sorting criterion, if any). So, swap() is guaranteed to have only constant complexity,
not the linear complexity of a copy assignment. Iterators and references to elements of a container
follow swapped elements. So, after swap(), iterators and references still refer to the elements they
referred to before, which, however, are in a different container then.
Note that for containers of type array<>, the behavior of swap() is slightly different. Because
you can’t internally just swap pointers, swap() has linear complexity, and iterators and references
refer to the same container but different elements afterward

all containers support an iterator interface, which means that range based for loops are supported, and these are the easiest way to get all elements
remember to get the elements in the range based for loop by const reference, otehrwise it will be copied

All containers except vectors and deques guarantee that iterators and references to elements remain
valid if other elements are deleted. For vectors, only the elements before the point of erase remain
valid.
If you remove all elements by using clear(), for vectors, deques, and strings any past-the-end
iterator returned by end() or cend() may become invalid.
If you insert elements, only lists, forward lists, and associative containers guarantee that iterators
and references to elements remain valid. For vectors, this guarantee is given if insertions don’t
exceed the capacity. For unordered containers, that guarantee is given to references in general but to
iterators only when no rehashing happens, which is guaranteed as long as with insertions the number
of resulting elements is less than the bucket count times the maximum load factor.

*/


/*
Arrays
std::array<> models a static array, wraps an orderinary c style static array, sequence of elements with static size
you cant add or remove elements to change size, only replacement of values is possible
safer and has same performance of regular array
random access iterators so any STL algo works, ordered collection

array has the best performance of any fixed sequence because memory is allocated on the stack (if possible), reallocation never happens, and we have random access

As for all other containers, array<> provides swap() operations. Thus, you can swap elements with
a container of the same type (same element type and same number of elements). Note, however, that
an array<> can’t simply swap pointers internally. For this reason, swap() has linear complexity
and the effect that iterators and references don’t swap containers with their elements. So, iterators
and references refer to the same container but different elements afterward.
You can use move semantics, which are implicitly provided for arrays.



*/
std::array<int, 5> arr{ 1,2,3,4,5 };


/*
Vectors

Vector models a dynamic array
A vector copies its elements into its internal dynamic array. The elements always have a certain
order. Thus, a vector is a kind of ordered collection. A vector provides random access. Thus, you
can access every element directly in constant time, provided that you know its position. The iterators
are random-access iterators, so you can use any algorithm of the STL.
Vectors provide good performance if you append or delete elements at the end. If you insert or
delete in the middle or at the beginning, performance gets worse. This is because every element
behind has to be moved to another position. In fact, the assignment operator would be called for
every following element

vectors allocate more memory than they need to contain all their elements
Vectors provide the usual size operations size(), empty(), and max_size()
An additional “size” operation is the capacity() function, which returns the number of
elements a vector could contain in its actual memory. If you exceed the capacity(), the vector has
to reallocate its internal memory.
The capacity of a vector is important for two reasons:
1. Reallocation invalidates all references, pointers, and iterators for elements of the vector.
2. Reallocation takes time.
Thus, if a program manages pointers, references, or iterators into a vector, or if speed is a goal, it is
important to take the capacity into account.
To avoid reallocation, you can use reserve() to ensure a certain capacity before you really need
it. In this way, you can ensure that references remain valid as long as the capacity is not exceeded:
std::vector<int> v; // create an empty vector
v.reserve(80); // reserve memory for 80 elements

*/

std::vector<int> vec(10);  // creates a vector of ints and fills it with 10 elements (calls the default int constuctor 10 times)
// types in the vector must provide a default constructor for this ability
//  But note that for complex types, even if a default constructor is provided, the initialization takes time.If the only reason for initialization is to reserve memory, you should use reserve().

/*

to avoid internal
fragmentation, many implementations allocate a whole block of memory (such as 2K) the first time
you insert anything if you don’t call reserve() first yourself. This can waste a lot of memory if
you have many vectors with only a few small elements.
Because the capacity of vectors never shrinks, it is guaranteed that references, pointers, and
iterators remain valid even when elements are deleted, provided that they refer to a position before
the manipulated elements. However, insertions invalidate all references, pointers, and iterators when
the capacity gets exceeded.
C++11 introduced a new member function for vectors: a nonbinding request to shrink the capacity to fit the current number of elements:
v.shrink_to_fit(); // request to shrink memory (since C++11)

capacity is the max number of elements without reallocation
size is the current number of elements
max_size is the maximum number of elements possible
shrink_to_fit reduces capacity to fit number of elements

 reserve() and shrink_to_fit() manipulate the vector because they invalidate references, pointers, and iterators to elements.

 [] has no range checking, at() has range checking and throws exceptions if out of range

 Regarding performance, you should consider that inserting and removing happens faster when
• Elements are inserted or removed at the end.
• The capacity is large enough on entry. (no reallocation)
• Multiple elements are inserted by a single call rather than by multiple calls. (one copy rather than mutiple)

Inserting or removing elements invalidates references, pointers, and iterators that refer to the following elements. An insertion that causes reallocation invalidates all references, iterators, and pointers.
Vectors provide no operation to remove elements directly that have a certain value. You must use an algorithm to do this (such as a call to remove passed to a call to erase)

Vectors provide only minimal support for logical error checking. The only member function for
which the standard requires that it may throw an exception is at(), which is the safe version of
the subscript operator (see Section 7.3.2, page 274). In addition, the standard requires that only the
usual standard exceptions may occur, such as bad_alloc for a lack of memory or exceptions of
user-defined operations.
If functions called by a vector (functions for the element type or functions that are user-supplied)
throw exceptions, the C++ standard library provides the following guarantees:

1. If an element gets inserted with push_back() and an exception occurs, this function has no
effect.
2. insert(), emplace(), emplace_back(), and push_back() either succeed or have no effect,
provided that the copy/move operations (constructors and assignment operators) of the elements
do not throw.
3. pop_back() does not throw any exceptions.
4. erase() does not throw if the copy/move operations (constructors and assignment operators) of
the elements do not throw.
5. swap() and clear() do not throw.
6. If elements are used that never throw exceptions on copy/move operations (constructors and
assignment operators), every operation is either successful or has no effect. Such elements might
be “plain old data” (POD). POD describes types that use no special C++ feature. For example,
every ordinary C structure is POD

All the above guarantees are based on the requirements that destructors dont throw

For Boolean elements, the C++ standard library provides a specialization of vector<>. The goal
is to have a version that is optimized to use less size than a usual implementation of vector<>
for type bool. Such a usual implementation would reserve at least 1 byte for each element. The
vector<bool> specialization usually uses internally only 1 bit for an element, so it is typically
eight times smaller. But such an optimization also has a snag: In C++, the smallest addressable
value must have a size of at least 1 byte. Thus, such a specialization of a vector needs special
handling for references and iterators.
As a result, a vector<bool> does not meet all requirements of other vectors. For example, a
vector<bool>::reference is not a true lvalue and vector<bool>::iterator is not a random access iterator.
Therefore, template code might work for vectors of any type except bool.
In addition, vector<bool> might perform worse than normal implementations,
because element operations have to be transformed into bit operations. However, how vector<bool> is implemented is
implementation specific. Thus, the performance (speed and memory) might differ.
Note that class vector<bool> is more than a specialization of vector<> for bool. It also
provides some special bit operations. You can handle bits or flags in a more convenient way.
vector<bool> has a dynamic size, so you can consider it a bitfield with dynamic size. Thus,
you can add and remove bits.


*/


/*
Deque

Similar to vector, manages its elements with a dynamic array, provides random access
with a deque, the dynamic array is open at both ends. so there are O(1) insertions at the front and back
To provide this ability, the deque is typically implemented as a bunch of individual blocks, with the
first block growing in one direction and the last block growing in the opposite direction.
Deque can also be implemented as an vector of pointers to vectors, bad for cache!

• Inserting and removing elements is fast at both the beginning and the end (for vectors, it is fast
only at the end). These operations are done in amortized constant time.
• The internal structure has one more indirection to access the elements, so with deques, element
access and iterator movement are usually a bit slower.
• Iterators must be smart pointers of a special type rather than ordinary pointers because they must
jump between different blocks.
• In systems that have size limitations for blocks of memory (for example, some PC systems),
a deque might contain more elements because it uses more than one block of memory. Thus,
max_size() might be larger for deques.
• Deques provide no support to control the capacity and the moment of reallocation. In particular,
any insertion or deletion of elements other than at the beginning or end invalidates all pointers,
references, and iterators that refer to elements of the deque. However, reallocation may perform
better than for vectors because according to their typical internal structure, deques don’t have to
copy all elements on reallocation.
• Blocks of memory might get freed when they are no longer used, so the memory size of a deque
might shrink (however, whether and how this happens is implementation specific).
The following features of vectors apply also to deques:
• Inserting and deleting elements in the middle is relatively slow because all elements up to either
end may be moved to make room or to fill a gap.
• Iterators are random-access iterators.
In summary, you should prefer a deque if the following are true:
• You insert and remove elements at both ends (this is the classic case for a queue).
• You don’t refer to elements of the container.
• It is important that the container frees memory when it is no longer used (however, the standard
does not guarantee that this happens)

Interface for a deque is largely the same as for a vector

1. No member functions for element access (except at()) check whether an index or an iterator is
valid.
2. An insertion or deletion of elements might cause a reallocation. Thus, any insertion or deletion
invalidates all pointers, references, and iterators that refer to other elements of the deque. The
exception is when elements are inserted at the front or the back. In this case, references and
pointers to elements stay valid, but iterators don’t.

*/

std::deque<int> dq(5, 1);  // deque with 5 elements


/*
 List

list manages its elements as a doubly linked list
elements of the list may have any type T
The internal structure of a list is totally different from that of an array, a vector, or a deque. The list
object itself provides two pointers, the so-called anchors, which refer to the first and last elements.
Each element has pointers to the previous and next elements (or back to the anchor). To insert a new
element, you just manipulate the corresponding pointers

Thus, a list differs in several major ways from arrays, vectors, and deques:
• A list does not provide random access. For example, to access the fifth element, you must
navigate the first four elements, following the chain of links. Thus, accessing an arbitrary element
using a list is slow. However, you can navigate through the list from both end. So accessing both
the first and the last elements is fast.
• Inserting and removing elements is fast at each position (provided you are there), and not only at
one or both ends. You can always insert and delete an element in constant time, because no other
elements have to be moved. Internally, only some pointer values are manipulated.
• Inserting and deleting elements does not invalidate pointers, references, and iterators to other
elements.
• A list supports exception handling in such a way that almost every operation succeeds or is a
no-op. Thus, you can’t get into an intermediate state in which only half of the operation is
complete.
The member functions provided for lists reflect these differences from arrays, vectors, and deques
as follows:
• Lists provide front(), push_front(), and pop_front(), as well as back(), push_back(),
and pop_back().
• Lists provide neither a subscript operator nor at(), because no random access is provided.
• Lists don’t provide operations for capacity or reallocation, because neither is needed. Each
element has its own memory that stays valid until the element is deleted.
• Lists provide many special member functions for moving and removing elements. These member
functions are faster versions of general algorithms that have the same names. They are faster
because they only redirect pointers rather than copy and move the values

to access all elements of a list, we must use range based for loops, specific operations or iterators
because it does not have random access, a list provides only front() and back() for accesing elements directly

As usual, these operations do not check whether the container is empty. If the container is empty,
calling these operations results in undefined behavior. Thus, the caller must ensure that the container
contains at least one element

td::list<Elem> coll; // empty!
std::cout << coll.front(); // RUNTIME ERROR ⇒ undefined behavior
if (!coll.empty()) {
std::cout << coll.back(); // OK
}

To access all elements of a list, you must use iterators
list iterators are only bidirectional, not random access, so we can use ony a subset of the STL's algorithms

As usual when using the STL, you must ensure that the arguments are valid. Iterators must refer
to valid positions, and the beginning of a range must have a position that is not behind the end.
Inserting and removing is faster if, when working with multiple elements, you use a single call
for all elements rather than multiple calls.
For removing elements, lists provide special implementations of the remove() algorithms.
These member functions are faster than the remove() algorithms because they manipulate only internal pointers rather than the elements.
So, unlike with vectors or deques, you should call remove() as a member function and not as an algorithm

Lists have the best support of exception safety of the standard containers in the STL. Almost all list
operations will either succeed or have no effect. The only operations that don’t give this guarantee
in the face of exceptions are assignment operations and the member function sort() (they give
the usual “basic guarantee” that they will not leak resources or violate container invariants in the
face of exceptions). merge(), remove(), remove_if(), and unique() give guarantees under the
condition that comparing the elements (using operator == or the predicate) doesn’t throw. Thus,
to use a term from database programming, you could say that lists are transaction safe, provided
that you don’t call assignment operations or sort() and that you ensure that comparing elements
doesn’t throw.


*/

std::list<int> list(5);  // list with 5 elements


// Forward list
/*
maintains elements as a singly linked list
may have nay type <T>
forward list is a list restricted such that it is not able to iterate backward

it uses less memory and slightly better runtime behaviour

only forward iterators

provide no pointer to the last element

• A forward list does not provide random access. For example, to access the fifth element, you
must navigate the first four elements, following the chain of links. Thus, using a forward list to
access an arbitrary element is slow.
• Inserting and removing elements is fast at each position, if you are there. You can always insert
and delete an element in constant time, because no other elements have to be moved. Internally,
only some pointer values are manipulated.
• Inserting and deleting elements does not invalidate iterators, references, and pointers to other
elements.
• A forward list supports exception handling in such a way that almost every operation succeeds
or is a no-op. Thus, you can’t get into an intermediate state in which only half of the operation is
complete.
• Forward lists provide many special member functions for moving and removing elements. These
member functions are faster versions of general algorithms, because they only redirect pointers
rather than copy and move the values. However, when element positions are involved, you have
to pass the preceding position, and the member function has the suffix _after in its name.




*/

std::forward_list<int> forlist;

// distance() is a call with linear complexity with forward lists since they have size member
// forward lists work by inserting elements before or after the element you pass to the function, since they can only point forwards



// remember that maps and sets insert copies of elements just like with all stl containers

// set and multiset containers sort their elements automatically according to a certian sorting criterion
// multisets allow suplicates whereas sets do not
// elements in the set or multiset may have any type T that is comparable according to the sorting criterion
// elements are considered to be duplicates if the sorting criteria decides they are equivalent
/*
sets and multisets are implemented as balanced binary trees, as red-black trees, which are good for changing both teh number of elemebts and searching for elements
They guarantee at most two internal relinks on insertions
The major advantage of automatic sorting is that a binary tree performs well when elements with
a certain value are searched. In fact, search functions have logarithmic complexity. For example, to
search for an element in a set or a multiset of 1,000 elements, a tree search performed by a member
function needs, on average, one-fiftieth of the comparisons of a linear search (which is performed by
a search algorithm that iterates over all elements).

to modify the value of an element, you must remove the element having the old value and
insert a new element that has the new value. The interface reflects this behavior:
• Sets and multisets don’t provide operations for direct element access.
• Indirect access via iterators has the constraint that, from the iterator’s point of view, the element
value is constant.

sorting criterion is less by default

Note that the sorting criterion is also used to check for equivalence of two elements in the same
container (i.e., to find duplicates). Thus, when the default sorting criterion is used, the check for
equivalence of two elements looks like this:
if (! (elem1<elem2 || elem2<elem1))

This has three advantages:
1. You need to pass only one argument as the sorting criterion.
2. You don’t have to provide operator == for the element type.
3. You can have contrary definitions between equivalence and equality (however, this might be a
source of confusion).
Checking for equivalence in this way takes a bit more time because two comparisons might be
necessary to evaluate the previous expression. Note, however, that if the result of the first comparison
yields true, the second comparison is not evaluated.

Note also that if two containers are compared by operator ==, the elements in both containers are
compared using their operator ==, which means that operator == has to be provided for the element
type

the return type for the insert function for a set returns two values in a pair
1. The member second of the pair structure returns whether the insertion was successful.
2. The member first of the pair structure returns the position of the newly inserted element or the position of the still existing element. (returns an iterator)
In all other cases, the functions return the position of the new element or of the existing element if
the set already contains an element with the same value
*/


/*
Maps and multimaps are containers that manage key/value pairs as elements. These containers sort
their elements automatically, according to a certain sorting criterion that is used for the key. 

The elements of a map or a multimap may have any types
Key and T that meet the following two requirements:
1. Both key and value must be copyable or movable.
2. The key must be comparable with the sorting criterion.

The elements are sorted according
to their keys, so the value doesn’t matter for the order of the elements. The sorting criterion is also
used to check for equivalence; that is, two elements are equal if neither key is less than the other

if a special sprting criterion is not passed, the default less is used

In fact, sets, multisets, maps, and multimaps
typically use the same internal data type. So, you could consider sets and multisets as special maps
and multimaps, respectively, for which the value and the key of the elements are the same objects.
Thus, maps and multimaps have all the abilities and operations of sets and multisets. Some minor
differences exist, however. First, their elements are key/value pairs. In addition, maps can be used
as associative arrays

Maps and multimaps sort their elements automatically, according to the element’s keys, and so have
good performance when searching for elements that have a certain key. Searching for elements that
have a certain value promotes bad performance. Automatic sorting imposes an important constraint
on maps and multimaps: You may not change the key of an element directly, because doing so might
compromise the correct order. To modify the key of an element, you must remove the element that
has the old key and insert a new element that has the new key and the old value. The values can be modified however

The find() member function searches for the first element that has the appropriate key and returns
its iterator position. If no such element is found, find() returns end() of the container. You can’t
use the find() member function to search for an element that has a certain value. Instead, you have
to use a general algorithm, such as the find_if() algorithm, or program an explicit loop.

as with all associative containers, iterators are biderectional and insert operations return a pair like sets

a few ways to insert into a map:

the most convenient way to insert elements is to pass them as an initializer list,
where the first entry is the key and the second entry is the value:
std::map<std::string,float> coll;
...
coll.insert({"otto",22.3})

or Use pair<>. Another way is to use pair<> directly. For example:
std::map<std::string,float> coll;
...
// use implicit conversion:
coll.insert(std::pair<std::string,float>("otto",22.3));
// use no implicit conversion:
coll.insert(std::pair<const std::string,float>("otto",22.3));
In the first insert() statement, the type is not quite right, so it is converted into the real element
type. For this to happen, the insert() member function is defined as a member template.

or Use make_pair(). Probably the most convenient way before C++11 wasto use make_pair(),
which produces a pair object that contains the two values passed as arguments (see Section 5.1.1,
page 65):
std::map<std::string,float> coll;
...
coll.insert(std::make_pair("otto",22.3));

maps provide [] and at() as another convient way to insert and set elements
at() yields the value of the element with the passed key and throws an exception object of type
out_of_range if no such element is present.
For operator [ ], the index also is the key that is used to identify the element. This means that
for operator [ ], the index may have any type rather than only an integral type. Such an interface is
the interface of a so-called associative array.

• The disadvantage is that you might insert new elements by accident or mistake. For example, the
following statement does something you probably hadn’t intended or expected:
std::cout << coll["ottto"];
It inserts a new element with key "ottto" and prints its value, which is 0 by default. However,
it should have generated an error message telling you that you wrote "otto" incorrectly.
Note, too, that this way of inserting elements is slower than the usual way for maps, which is using the insert({key,value}).
The reason is that the new value is first initialized by the
default value of its type, which is then overwritten by the correct value

*/

/*
Unordered Containers
these contain all elements we insert in an arbitrary order, no sorting criteria unlike ordered associative containers and no semantics to put elements into specific positions unlike sequential containers
As with associative containers, the individual classes differ as follows:
• Unordered sets and multisets store single values of a specific type, whereas in unordered maps
and multimaps, the elements are key/value pairs, where the key is used to store and find a specific
element, including its associated value.
• Unordered sets and maps allow no duplicates, whereas unordered multisets and multimaps do.

The elements of an unordered set or multiset may have any type T that is comparable.
For unordered maps and multimaps, the first template parameter is the type of the element’s key,
and the second template parameter is the type of the element’s associated value. The elements of
an unordered map or an unordered multimap may have any types Key and T that meet the following
two requirements:
1. Both key and value must be copyable or movable.
2. The key must be comparable with the equivalence criterion.
Note that the element type (value_type) is a pair<const Key,T>.
The optionalsecond/third template parameter definesthe hash function. If a special hash function
is not passed, the default hash function hash<> is used, which is provided as a function object in
<functional> for all integral types, all floating-point types, pointers, strings, and some special
types.14 For all other value types, you must pass your own hash function

All standardized unordered container classes are implemented as hash tables, which nonetheless
still have a variety of implementation options. As usual, the C++ standard library does not specify all these implementation details to allow a variety of possible implementation options, but a
few of the specified abilities of unordered containers are based on the following assumptions :

• The hash tables use the “chaining” approach, whereby a hash code is associated with a linked
list. (This technique, also called “open hashing” or “closed addressing,” should not be confused
with “open addressing” or “closed hashing.”)
• Whether these linked lists are singly or doubly linked is open to the implementers. For this
reason, the standard guarantees only that the iterators are “at least” forward iterators.
• Various implementation strategies are possible for rehashing:
– With the traditional approach, a complete reorganization of the internal data happens from
time to time as a result of a single insert or erase operation.
– With incremental hashing, a resizing of the number of bucket or slots is performed gradually,
which is especially useful in real-time environments, where the price of enlarging a hash table
all at once can be too high.
Unordered containers allow both strategies and give no guarantee that conflicts with either of
them

For each element to store, which is a
key/value pair, the hash function maps the value of the key to a bucket (slot) in the hash table. Each
bucket manages a singly linked list containing all the elements for which the hash function yields
the same value

The major advantage of using a hash table internally is its incredible running-time behavior.
Assuming that the hashing strategy is well chosen and well implemented, you can guarantee amor14 error_code, thread::id, bitset<>, and vector<bool>
tized constant time for insertions, deletions, and element search (“amortized” because the occasional
rehashing happens that occurs can be a large operation with a linear complexity).
The expected behavior of nearly all the operations on unordered containers, including copy construction and assignment, element insertion and lookup, and equivalence comparison, depends on
the quality of the hash function. If the hash function generates equal values for different elements,

7.9 Unordered Containers 359
which also happens if an unordered container that allows duplicates is populated with equivalent
values or keys, any hash table operation results in poor runtime performance. This is a fault not so
much of the data structure itself but rather of its use by unenlightened clients.
Unordered containers also have some disadvantages over ordinary associative containers:
• Unordered containers don’t provide operators <, >, <=, and >= to order multiple instances of
these containers. However, == and != are provided (since C++11).
• lower_bound() and upper_bound() are not provided.
• Because the iterators are guaranteed only to be forward iterators, reverse iterators, including
rbegin(), rend(), crbegin(), and crend(), are not supported, and you can’t use algorithms
that require bidirectional iterators, or at least this is not portable.
Because the (key) value of an element specifies its position — in this case, its bucket entry — you
are not allowed to modify the (key) value of an element directly. Therefore, much as with associative
containers, to modify the value of an element, you must remove the element that has the old value
and insert a new element that has the new value. The interface reflects this behavior:
• Unordered containers don’t provide operations for direct element access.
• Indirect access via iterators has the constraint that, from the iterator’s point of view, the element’s
(key) value is constant.
As a programmer, you can specify parameters that influence the behavior of the hash table:
• You can specify the minimum number of buckets.
• You can (and sometimes have to) provide your own hash function.
• You can (and sometimes have to) provide your own equivalence criterion: a predicate that is used
to find the right element among all entries in the bucket lists.
• You can specify a maximum load factor, which leads to automatic rehashing when it is exceeded.
• You can force rehashing.
But you can’t influence the following behavior:
• The growth factor, which is the factor automatic rehashing uses to grow or shrink the list of
buckets
• The minimum load factor, which is used to force rehashing when the number of elements in the
container shrinks
Note that rehashing is possible only after a call to insert(), rehash(), reserve(), or clear().
This is a consequence of the guarantee that erase() never invalidates iterators, references, and
pointers to the elements. Thus, if you delete hundreds of elements, the bucket size will not change.
But if you insert one element afterward, the bucket size might shrink.
Also note that in containers that support equivalent keys — unordered multisets and multimaps
— elements with equivalent keys are adjacent to each other when iterating over the elements of the
container. Rehashing and other operations that internally change the order of elements preserve the
relative order of elements with equivalent keys

at() yields the value of the element with the passed key and throws an exception object of type
out_of_range if no such element is present.
For operator [ ], the index also is the key used to identify the element. This means that for
operator [ ], the index may have any type rather than only an integral type. Such an interface is the
interface of a so-called associative array.
For operator [ ], the type of the index is not the only difference from ordinary C-style arrays.
In addition, you can’t have a wrong index. If you use a key as the index for which no element yet
exists, a new element gets inserted into the map automatically. The value of the new element is
initialized by the default constructor of its type. Thus, to use this feature, you can’t use a value type
that has no default constructor. Note that the fundamental data types provide a default constructor
that initializes their values to zero

*/

/*

The C++ standard library provides different container types with different abilities. The question
now is: When do you use which container type? Table 7.57 provides an overview. However, it
contains general statements that might not fit in reality. For example, if you manage only a few
elements, you can ignore the complexity because short element processing with linear complexity is
better than long element processing with logarithmic complexity (in practice, “few” might become
very large here).
As a supplement to the table, the following rules of thumb might help:
• By default, you should use a vector. It has the simplest internal data structure and provides
random access. Thus, data access is convenient and flexible, and data processing is often fast
enough.
• If you insert and/or remove elements often at the beginning and the end of a sequence, you should
use a deque. You should also use a deque if it is important that the amount of internal memory
used by the container shrinks when elements are removed. Also, because a vector usually uses
one block of memory for its elements, a deque might be able to contain more elements because
it uses several blocks.
• If you insert, remove, and move elements often in the middle of a container, consider using a
list. Lists provide special member functions to move elements from one container to another
in constant time. Note, however, that because a list provides no random access, you might
suffer significant performance penalties on access to elements inside the list if you have only the
beginning of the list.
Like all node-based containers, a list doesn’t invalidate iterators that refer to elements, as
long as those elements are part of the container. Vectors invalidate all their iterators, pointers,
and references whenever they exceed their capacity and part of their iterators, pointers, and
references on insertions and deletions. Deques invalidate iterators, pointers, and references when
they change their size, respectively.
• If you need a container that handles exceptions so that each operation either succeeds or has no
effect, you should use either a list (without calling assignment operations and sort() and, if
comparing the elements may throw, without calling merge(), remove(), remove_if(), and
unique(); see Section 7.5.3, page 296) or an associative/unordered container (without calling
the multiple-element insert operations and, if copying/assigning the comparison criterion may
throw, without calling swap() or erase()). See Section 6.12.2, page 248, for a general discussion of exception handling in the STL.
• If you often need to search for elements according to a certain criterion, use an unordered set
or multiset that hashes according to this criterion. However, hash containers have no ordering,
so if you need to rely on element order, you should use a set or a multiset that sorts elements
according to the search criterion.
• To process key/value pairs, use an unordered (multi)map or, if the element order matters, a
(multi)map.
• If you need an associative array, use an unordered map or, if the element order matters, a map.
• If you need a dictionary, use an unordered multimap or, if the element order matters, a multimap.


A problem that is not easy to solve is how to sort objects according to two different sorting criteria.
For example, you might have to keep elements in an order provided by the user while providing
search capabilities according to another criterion. As in databases, you need fast access about two
or more different criteria. In this case, you could probably use two sets or two maps that share the
same objects with different sorting criteria. However, having objects in two collections is a special
issue, covered in Section 7.11, page 388.

The automatic sorting of associative containers does not mean that these containers perform
better when sorting is needed. This is because an associative container sorts each time a new element
gets inserted. An often faster way is to use a sequence container and to sort all elements after they
are all inserted, by using one of the several sort algorithms









*/




int main()
{
	arr[1] = 10;  // random access, change the element
	for (auto a : arr)
	{
		std::cout << a << "\n";
	}

	std::cout << vec.capacity() << std::endl;

	for (int i = 0; i < 12; ++i)
	{
		vec.push_back(i);
		std::cout << vec.capacity();
	}
	std::cout << vec.size() << std::endl;

	//std::cout << vec.capacity() << std::endl;
	vec.shrink_to_fit();
	std::cout << vec.size() << std::endl;

	std::vector<int> vec2(5, 1);  // 5 elements, all 1

	//std::cout << vec2[15];   runtime error

	dq.push_front(1);  // push this to front of deque
	dq.push_back(2);

	std::cout << dq.size() << std::endl;  // 7

	list.push_back(1);
	list.push_back(2);
	list.push_front(2);

	list.remove(2); // remove member function is faster for lists, remove everything with value 2

	forlist.emplace_front(1);
	forlist.insert_after(forlist.before_begin(), 5);  // insert 5 at the front

	for (auto i : forlist)
	{
		std::cout << i << "\n";
	}

}
