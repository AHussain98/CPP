# include <iostream>
# include <list>
# include <random>
# include <array>
# include <algorithm>
# include <unordered_map>

// associative containers store their elements in an order which depends on teh key, std::set, std::map etc... use a tree
// unsorted associative containers use a hash table

// hash table is an array of buckets
// these buckets could be a linked list or a vector or some other sequential container
// see below implementation


int main(){

std::mt19937 mt;
std::uniform_int_distribution<int> dist(1,100); //random distribution of ints between 1 and 100

// the hash table is an array of 10 linked lists
std::array<std::list<int>,10> buckets;

// generate 100 random numbers with values between 1 and 100
// if between 1 and 10, put into bucket [0], if between 11 and 20, put into bucket[1] etc...
for (int i = 0; i < 100; ++i){
    int num = dist(mt);  // generate the random numbers
    int idx = (num-1)/10;  // hash function to compute the hash values, the hash function is the steps you'll apply to every valeu to work out which bucket it should be in
    buckets[idx].push_back(num); // use the has value as the index into the array
}

// print out the contents of the buckets
for (int i = 0; i < 10; ++i){
    auto bucket = buckets[i];
    std::cout << "Bucket " << i << ": ";
    for (auto n : bucket){
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

// if we want to find an element in our hashmap, we have to use the find() algorithm

// find "43" in the hashmap

int target {43};
int idx = (target-1)/10; // apply the hash function, so we know the index of the array where we'll find this value is 4
std::cout << "Looking for " << target << " in bucket " << idx << std::endl;
auto it = std::find(cbegin(buckets[idx]), cend(buckets[idx]), target);

if (it != cend(buckets[idx])){
    std::cout << "Found "<< target << " in bucket " << idx;
}

// in an unordered container, the buckets are linked lists of pointers to the containers elements
// the index of the array is calculated fromthe element
// a hash function generated a number based on the key
// this is known as the hash of the key, this is usually a very fast operation
// the hash of the key is used as the index


// element search : calculate the hash number of the key, use that number to identify the bucket to search, search the bucket for the element with teh required key, using the == operator of the keys type unlike the < operator that the ordeered containers use

// for maximum efficiency, each element should have its own bucket ( no need for linked lists) , ecah key produces a different hash value, this requires the hash funcion to perform perfect hashing
// in practice, different keys sometimes give the same hash number
// in a multi map or multiset, several elements can have the same key
// the more elements there are in a bucket, the longer it will take to perform an operation involving that bucket

std::cout << std::endl;

std::unordered_map<std::string,int> map;  // unordered map, no duplicates
map.insert({"Asad", 24});
map.insert({"Misha", 10});

// we can have duplicates if we use unordered_multimap

}