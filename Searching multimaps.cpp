# include <iostream>
# include <map>
# include <string>
# include <algorithm>

// we can use find() and count() to find elements in a multiset or multimap which have the same key
// it would be useful if we could get an iterator range for these elements
// std::multimap and std::multiset have member functions which do this
// there are also generic versions in <algorithm>, these are useful for working with sequential containers

// .upper_bound(k) returns an iterator to the first element whose key is greater than k
// .lower_bound(k) returns an iterator to the first element whose key is greater than or equal to k
int main(){

std::multimap<std::string,int> map;
map.insert({"Asad",25});
map.insert({"Farah",33});
map.insert({"Iddy",3});

auto upper = map.upper_bound("Asad"); // returns first element that is greater than Asad
auto lower = map.lower_bound("Iddy"); // returns an iterator to Iddy

// equal_range() is equivalent to calling lower_bounc() followed by upper_bounc(), it returns an std::pair
// the first member of the pair is the return value from lower_bounc()
// the second is the return value from upper_bound()

auto keys = map.equal_range("Iddy");

for (auto it = keys.first; it != keys.second; ++it){
    std::cout << (*it).first << " ";
}
std::cout << std::endl;

// we an us ethe returned iterator range with generic algorithms
// can call find_if with a lambda expression

auto start = keys.first;
auto end = keys.second;

auto result = std::find_if(start,end, [] (std::pair<std::string,int> p) { return (p.second == 3);});

if (result != end){
    std::cout << "we found someone who is 3!";}

}