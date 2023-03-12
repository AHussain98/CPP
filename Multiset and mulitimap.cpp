# include <iostream>
# include <set>
# include <map>
# include <string>

// multiset and multimap are very similar to set and map, except duplicate keys are allowed
// however multimap does not support subscripting

int main(){

std::multiset<int> set {1,2,3,4,5,1}; // 1 appears twice but compilation still occurs

set.insert(2);
set.insert(3);
set.insert(4); // insertion of duplicate keys is fine when using a multiset

for (auto i : set) {
    std::cout << i << " ";  // they still print in order, as set uses a self balancing tree
}
std::cout << std::endl;


std::multimap<std::string,int> map;   // create an empty multimap
map.insert(std::make_pair("Asad",24));
map.insert(std::make_pair("Iddy",3));
map.insert(std::make_pair("Asad",25)); // duplicate key is allowed

for (auto [name,age] : map){
    std:: cout << name << " is " << age << std::endl;
}

// careful, map.erase("Asad") will erase every element with Asad as the key
// insert() will always siccees for a multimap and multiset
// we can erase a single element by passing an iterator to it

// a map can only have one matching element, a multimap coulf have mutiple matching elements
// we need to be able to manage these multiple matches
// because the multimap is sorted in the order of its keys, all the matching elements will be next to each other
// these form a range of elements
// theres can be represented by an iterator range
// one way to solve this problem is to use find() and count()

auto me = map.find("Asad"); // this returns an iterator to the first element with key Asad, or end() if not found
int num = map.count("Asad"); // number of elements with the key "Asad"
// given these two values, we can loop over all the elements in the range


if (me != map.end()){ // so if the element we're trying to find exists
for (int i = 0 ; i < num; ++i){
    std::cout << "key = " << me->first << " and value is " << me->second << std::endl;
    if (me->second == 25){
      break; // this breaks the loop when we've found the value we're after
    }
    ++me; // move the iterator along
}
}

map.erase(me); // erase the offending element using the iterator to it

for (auto [name,age] : map){
    std:: cout << name << " is " << age << std::endl;
} // now we no longer have the element
}