# include <iostream>
# include <vector>

// c++11 introduced emplacement, this is another way to add elements to containers
// member functions like push_back and insert() require an existing object
// the container copies the existing object into the new element, if there is no existing object, we need to create a temporary object
// with emplacement, the container creates the object in the new element, instead of copying it, this avoids a copy constructor call

class refrigerator{
        int size;
    public:
        refrigerator(int size) : size(size){
        }
        void print(){
            std::cout << size;
        }
};

int main(){

refrigerator samsung(150); // create a refrigerator object

std::vector<refrigerator> vec; // vector of fridge objects

vec.insert(begin(vec),samsung); // adds an element and copy samsung into it
// samsung is not used again, we want to avoid passing in objects this way, wasteful

// alternatively, we can pass in a constructor call for the new element
vec.insert(end(vec),150);   // this creates a temporary object which is destroyed when the insert call is returned

// this is better but there's still a copy operation which we want to avoid

// c++11 has emplace(), we pass the constructor arguments as part of the emplace call
// the new object is created directly in the container element

vec.emplace(begin(vec),150); // add an element and create an object in it, avoids any copying

for (auto el : vec){
    el.print();
}

// emplace is used instead of insert()
// emplace_back() is used instead of push_back() for containers that support push_back()
// there is also emplace_front() for containers that support push_front()

// emplace() for container adapters instead of push()

//  emplace works differenty with containers that have unique keys
// for std::set and std::map, emplace() created a temporary object, it then checks if there is an element woth the same key
// c++17 provides an improved version of emplace() for maps
// try_emplace() checks for duplciates before creating the new element object
// if there already is an element with the same key, nothing happens

// emplacement is the only way to insert objects which cannot be copied or moved
// emplacement will cause a temporary object to be created if the container does not allow duplciates (set or map), the implementation uses assignment rather than copying or if a type conversion is required
// compilers can often optimize away the copy in insert()
// move semantics can avoid copying temporary objects

}