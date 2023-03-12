# include <map>
# include <iostream>
# include <algorithm>
# include <string>

// the original STL provided two ways to insert an element into a map: the [] operator or the insert member function
// [] provides insert or assign functionality, if there is already an element in the map with the requested key, its value is overwritten, otherise a new element is inserted into the map
// operator [] performs an insertion is two stages, first it created the new element, the key is the argument and the value is default initialised, then it assigns the value
// this requires that the value's type has a default constructor, if the assignment throws an exception, the partially populated element is left in the map
// operator [] returns a value, this is a reference to the elements value member

// the insert() member function will only insert a new element, if the map already has an element with the same key, nothing happens, no overwriting
// the return value from insert() allows us to find out whether a new element was added
// the values type does not need to have a default constructor, if an exeption is thriwn during the operation, the insertion has no effect

int main(){

std::map<std::string,int> names;

names["Asad"] = 24;
names["Misha"]; // element with key misha and undefined value, partially populated element

auto result = names["test"] = 66; // now res = 66


// to insert or assign with insert(), we need to write some more code:

auto res = names.insert(std::make_pair("Alayna",5)); // remember insert returns a pair
auto iter = res.first; // iterator to the pair thats been inserted
if (res.second){
                      //  if the new element was inserted correctly, second is true
}
else{  // not inserted correctly, we need to assign the existing element
iter->second = 55; // assign to the value directly using a pointer, the key already exists
}

// c++17 introduced the structured binding, this is an easy way to access data structures
// in a single statement, we delcare local variables, bind them to members of a compound data structure (the types are deduced by the compiler)
// Compound data structures are formed by combining one or more data types.
// with auto in c++11, the compiler can deduce the type of a single variable, given a scalar initializer
// in c++17, this has been extended to work with multiple variables and a compound initialser, each veriable will be initialized from a member of a compund value, the compiler deduces each type

std::pair<int,double> p(1,3.12);
auto [i,d] = p; // we can declare and initalise multiple variables of different data types on the same line using a structured binding to initialse both i and d from the values in pair p
std::cout << i << " " << d << std::endl;

// these can be useful in maps because they can make them more readable

for (auto [name,age] : names){
    std:: cout << name << " is " << age << std::endl;
}

// remmber that insert() returns an pair comprised of an iterator to the pair inserted into the map, and a bool to indicate success of insertion
// checking the return value from insert() is easier using a structured binding

auto [iter2,success] = names.insert(std::make_pair("iddy",3));
if (success){
    std::cout << "inserted element!" << std::endl;
}
else{
    auto [name,age] = *iter2; // dereference iter because its a pointer to the element we've tried to insert
    std::cout << name << " was not inserted as it already exists" << std::endl;
}

// c++17 provides insert_or_assign()
// this takes two arguments, the new elements key and its value
// the returned value is an std::pair
// the first member is an iterator to teh element, its a new element on isertion and the existing element on assignent
// the second member is a bool, true on insertion, false on assignment

auto [iter3, state] = names.insert_or_assign("Asad",25);  // not working here bc this compiler is old
if (state){
    std::cout << "inserted new element!" << std::endl;
}
else{
    auto [name,age] = *iter3; // dereference iter because its a pointer to the element we've tried to insert
    std::cout << name << " was overwritten as it lready exists, new value is " << age << std::endl;
}

// using insert_or_assign() , the values type does not need to have a default constructor, if an exe[tion is thrown during the operation, the insertion has no effect
// try this again with visual sudio
}




