//a set is an unordered collection of unique elements
// in a set, there are no duplicates, you can either find the element or you cannot
//finding the elemnt is a constant time operation therefore, as you dont need to search the whole set
//

#include <iostream>
#include <set>
using namespace std;

int main(){
     set<int> s1 = {1,10,1};  //set declared and initialised

     for(auto itr = s1.begin(); itr != s1.end(); itr++){ //we use a pointer to refer to each value in the set
         cout << *itr << endl; //show us the value that the pointer is pointing at
         //just 1 and 10 show up, duplicated will not work
         }

         //now we can look through the set to see if an element appears in it

         if (s1.find(9) == s1.end()){  //this means the itr pointer will point through to the end of the set, and it couldnt find the value, doesnt exist
              cout << "True" << endl;
         }

      string str = "This is a test";
      set<char> exists;

      for (int i = 0; i < str.length(); i++){
          char letter = str[i]; //define the variable we're inserting
          exists.insert(letter);
      }  // so we've now looped through the string and inserted every single element into the set

      for (auto itr = exists.begin(); itr != exists.end(); itr++){//pointer begins at start and the loop runs aslong as it doesnt get to the end
          cout << *itr << endl; //now print out the value at the itr pointer for each run
          //because its a set, only the unique values will be stored and therefore printed
      }

      // solving a problem: for the string test, check if all the elements in test exist in str

      string test = "This";
      set<char> findLetters;

      for(int i = 0; i<test.length();i++){
          char letter = test[i];
          findLetters.insert(letter); //so insert all the elemnts in the string test into the set findLetters
      }
      // now we want to check if these elements exist in the string str

      for(int i = 0; i < str.length();i++){
          char letter = str[i]; //letter becomes each char in str in turn
          findLetters.erase(letter); //so erase the letter if it exists in the set
          //if the findLetters set is empty at the end of this operation, all elemnts in test appear in str
      }

      if (findLetters.empty()){ //so if it is empty, it will match!
          cout << "They match!" << endl;
      }

}