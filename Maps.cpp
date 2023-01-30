//  maps are a data structure that allow us to associate some kind of key with some kind of value
// maps are similar to arrays, but are better if we need to constantly access a partuclar value in the map, we can just use the key to access it instantly
// keys are used to lookup values in O(1) time , constant time
//c++ has two different types of map, map and unordered map
// map is a ordered map whereas unordered is not, map is a self balancing red black binary search tree
// unordered map uses a hashtable, uses a hashfunction to hash your key to work out how to work your value, this can be faster than the standard map
// unordered map is typically faster, there's rarely a reason to use a standard map, if you needed access to ordered elemnts in key value pairs, you could use an array of pairs


#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

struct CityRecord{
    std::string Name;
    int Population;
    double Latitude,Longitude;

};

int main(){

//  std::vector<CityRecord> Cities; //create a vector of city records, call it cities
//  Cities.emplace_back("Melbourne",5000000,2.4,9.8);
//  Cities.emplace_back("Paris",6000000,7.8,6.5);
//  Cities.emplace_back("London",14000000,5.5,2.1);

  //imagine we needed to search through this list of cities 1000 times looking for one
  //A vector needs to be searched cell by cell, which would be time consuming
  //map could be used instead
  //map takes in key and value parameters, we can check for the existance of a key in real time

  std::map<std::string, CityRecord> cityMap; //create the map cityMap which takes in a string for key and CityRecord for value
  cityMap["Melbourne"] = CityRecord {"Melbourne",5000000,2.4,9.8};
  cityMap["Paris"] = CityRecord {"Paris",6000000,7.8,6.5};
  cityMap["London"] = CityRecord {"London",14000000,5.5,2.1};

  //so now we've stored that information about each city in this map
  //now if we wnat to access data about a particular city?

  CityRecord & londonData = cityMap["London"];  //object of the same type is made equal to the map key, use & to avoid making copies
  cout << londonData.Population << endl;   //value data is now accessible

  //its important that whatever you use as the key is hashable(for unordered map) or can have the less than < operator applied to it for an ordinary map
  // custom data structures like structs or classes cant be hashed, pointers to these can however

  map<char,int> mp = { //create a map and initialse it at once
         {'T',7},
         {'G',6}
};
cout << mp['T'] << endl; // access the value much like an array
mp['u'] = 9; //insert into the map
mp.insert(pair<char,int>('S',17)); //another way of inserting, using the insert function
cout << mp['S'] << endl;


//pair is its own kind of data structure, we can create a pair seperately:
pair<char,int> p1('j',1); //pair created
cout << p1.first << endl; //returns the first value in the pair
//this is what the key value pairs in the map actually are under the surface, they're pairs

// if we're creating a data structure we're going to iterate through, vectors are a much better choice as theyre faster and more efficient
//however we can iterate through maps aswell:

for (auto itr = mp.begin(); itr != mp.end(); itr++){
        //itr is actually a pointer here, its map<char,int>::iterator but this is covered by auto
        cout << itr->first; //we can see the values are ordered because we used a standard map
        //(*itr).first would give the same result
}

cout << endl;

//lets try using a map to solve a problem, we have to count the number of times each letter occurs in a string
//using an array, we'd have to loop through the array multiple times, map avoids this

string test = "Hello world, my name is Asad, tttthhhhaaaaa";
map<char,int> freq;
for (int i = 0; i < test.length(); i++){
    char letter = test[i];
   //check if the letter exists in the map, if it does then increase the value of the key by one
   if(freq.find(letter) == freq.end()){  //find fucntion used to return the iterator in the map that points to the pair in the map that has this key
   //so if the find function == end, then it is returning the end iterator and the value therefore does not exist in the map
        freq[letter] = 0; //therefore value of that letter must be 0, lets initialse it and create the map entry
   }
   freq[letter]++;
   //so if the key does exist, increase the value of the value by 1
   cout << freq[letter] << ", " << letter << endl;
}

}























