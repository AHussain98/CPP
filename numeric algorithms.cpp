# include <iostream>
# include <vector>
# include <algorithm>
# include <numeric>

// iota() populates an iterator range with values that successively increase by 1
// it takes te iterator range and a starting value, it then assigns this starting value to the first element in the range
// iota() then increments the value and assigns it to the next element

// the accumulate() function will return the sum of all the elements in an iterator range, the third argument is the inital value of the sum (usually should be 0)
int main(){

std::vector<int> vec(10); // created a vector with 10 elements
std::iota(begin(vec),end(vec),1); //we dont use the const functions because we are modifying the values
// so the vector values will now be 1,2,3,4 etc...

std::cout << std::accumulate(cbegin(vec),cend(vec),0) << std::endl;

// by default, the + operator is used to perform the addition, we can perform different operations by passing in a lambda as an additional fourth argument

auto sum = std::accumulate(cbegin(vec),cend(vec),0, [] (int sum, int n) {return (n % 2 == 1) ? sum + n: sum;}); // only add the odd elemnts onto the sum
                                                          // the order we pass in these arguments matters, based on the documentation of the aglorithm, the first lambda argument must be the summation
std::cout << sum;
// std::accumulate() cannot be parrallilised, this is because each addition operation must occur sequentially
// c++17 introduced the reduce() algorithm, this does the same thing as accumulate() but can perofrm the additions in any order, so is compatible with parallel processing
}
