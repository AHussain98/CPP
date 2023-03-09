# include <iostream>
# include <string>
# include <map>

// the c++ library provides std::map in <map>
// this is an associative container
// each element consists of an std::pair, the first member is the "key" of the element and the second member is the "value" of the element
// each element must have a unique key, the values do not need to be unique
// the elements are stored in order, using the < operator of the key to sort the elements
// for efficiency, the std::map is implemented as a tree, usually a red-black tree

// the value member of the pair is used to store the data, the key is sued to locate the corresponding data
// we search for a particular key, then look up the data in the value member, the key acts like an index
// this is very similar to hashmaps or directorys in other languages
// the trees are sorted by key
// we can use insert() and erase() as we did with set
// we need to pass the new element to insert() as an std::pair, e.g. m.insert(make_pair(k,v))
// with c++11, we can use a list initialiser:  m.insert({k,v})
// insert() will fail if the map already has an element with the same key


// insert() returns an std::pair, similar to std::set
// the second member is a bool indicating success/failure
// the first member is an iterator to the new element on success, on failure it will be an iterator to teh element that has caused insert() to fail, this will occur if an existing element in the map has the same key


int main(){
std::map<std::string,int> scores;    // create an empty std::map
scores.insert(std::make_pair("Asad",24));    // assign some elements to it
scores.insert(std::make_pair("Fezzy",24));

auto ret = scores.insert({"Iddy",3}); // can also be done with an initialiser list, and the pair returned can be stored in a variable


for (auto i : scores){  // we can use i.first because we're actually using the pair elements themselves
    std::cout << i.first << " has a score of " << i.second << std::endl; // first because they're pairs to get the name, second to get the value
}

auto it = ret.first; // first member of the pair returned by insert is an iterator to the new element
// here, it has become an iterator to the new element

// ret is a pair, first is the new pair element, second is a bool

std::cout << "I love " << ret.first->first << " and he's " << it->second ;

std::cout << std::endl;

// maps support subscripting, unlike sets and lists
// however, this works differently from vectors and arrays
// if an element does not already exist, it is created
// if it does exist, this overwrites its value

std::cout << scores["Asad"] << std::endl; // fetches the value

scores["Asad"] = 25; //changes the value

scores["Misha"] = 11; // creates a new entry

for (auto i : scores){  // we can use i.first because we're actually using the pair elements themselves
    std::cout << i.first << " has a score of " << i.second << std::endl; // first because they're pairs to get the name, second to get the value
}

// we can still use find() and count()

auto me = scores.find("Asad"); // returns the pair with that key

if (me != scores.end()){ // if the key we've found exists
me->second = 100; // can then change the value
                        }
std::cout << scores["Asad"];

// we can modify the value of a map element but NOT THE KEY
// algorithms we use must follow this principle

// maps are very fast at accessing an arbitrary element
// insertion and deletion are usually very fast, can be slow if tree gets unbalanced
// maps are very useful for indexed data (contacts lists, emplyee records etc...)
// also useful for storing data that is in key value pairs
}