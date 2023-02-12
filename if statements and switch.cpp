# include <iostream>
# include <vector>
# include <string>

int main(){

std::vector<int> vec {1,2,3,4,5};
// we can also define an initaliser in an if statement, saves us having to define it outside and waste memory
if (auto it = vec.begin(); it != vec.end()){  // checks if the vector is not empty
    std::cout << "Yay! Not empty!";
}
// this is something we can do just as a quick check to see a container isnt empty just before we use it
std::cout << '\n';


int ws_count {0}; //char c and whitespace count are initialised

std::string test {"How many whitespaces are there in here?"};

for(int i = 0; i < test.length(); i++){   // c++ allows us to fallthrough case statements, so they share the same break condition

    switch(const char c = test[i]; c){ // set c to to the value at an index of test, and make c the switch test object
        case ' ':
            [[fallthrough]]; //compiler attribute so that we don't get a warning for a fallthrough
        case '\t':
              ++ws_count; // so incase c is a whitespace or tab character, increase the whitespace count
              break;
        default:          // otherwise break the switch loop and rerun for the next index i
            break;
    }
}

std::cout << "The number of whitespaces is " << ws_count;

// c++ has attributes, which are instructions directly for the compiler, done in double square brackets [[ ]]

}