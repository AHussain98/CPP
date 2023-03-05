# include <iostream>
# include <algorithm>
# include <vector>

// transform() will call a given function on every element in the range
// the result is copied into a destination

// we can use transform() to implement equal_strings(), which is our check for case insensitive string equality
// make a copy of the argument strings
// use transform() to convert the copies ti upper case
// call std::strings == operator to compare them

bool equal_strings(const std::string& str1, const std::string& str2){
    // copy the arguments
    std::string lhs {str1};
    std::string rhs {str2};

    transform(begin(lhs),end(lhs),back_inserter(lhs), [] (char c) { return std::toupper(c);
    });  // transform the string copy inplace

    transform(begin(rhs),end(rhs),back_inserter(rhs), ::toupper ); // can also use the toupper function call, the :: is showing its in teh global namespace

    // now return whether or not they're equal

    return lhs == rhs;
}

int main() {
std::vector<int> vec {1,2,3,4,5};
std::vector<int> vec2;

std::transform(begin(vec),end(vec),back_inserter(vec2), [] (int n) {return (n*2); });

for (auto i : vec2){
    std::cout << i << " "; // all elements have been doubled and stored in this other vector
}
std::cout << std::endl;

// usually when algorithms operate on a container, the destination is a different container
// however, the destination iterator is allowed to overlap the source
// this allows us to do an inplace transformation
// you'd just pass in begin(vec) for the third argument
// again, easily accomplished via loop aswell

for (auto& i : vec){
    i = i*2;
    std::cout << i << " ";
}
std::cout << std::endl;
// we can overload the transform() algo to take the results of an operation on two containers and transpose them into a third container

std::vector<int> vec3;

std::transform(begin(vec),end(vec),begin(vec2),back_inserter(vec3), [] (int n, int m) { return n+m;
});

for (auto i : vec3){
    std::cout << i << " "; // vec3 is the sum of the other two vectors
}

std::cout << std::endl;

std::string name {"Asad Hussain"};
std::string NAME {"ASAD HUSSAIN"};

std::cout << std::boolalpha << equal_strings(name,NAME);
}