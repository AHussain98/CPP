# include <iostream>
# include <string>
# include <algorithm>
# include <numeric>
# include <vector>

// there are some other algorithms in numeric that are useful

// partial_sum() writes the "running total" of the elements into another container
// given a source container {a,b,c..., the target container will have elements {a, a+b, a+b+c...
int main(){

std::vector<int> nums {1,2,3,4,5};
std::vector<int> sum;

std::partial_sum(cbegin(nums),cend(nums),back_inserter(sum));   // by default, + operator used

for (auto i : sum){
    std::cout << i << " ";
}

std::cout << std::endl;

// adjacent_difference() writes the difference between successive elements into another ocntainer
// so this is the inverse of partial sum, source container {a,b,c... has terget container {a,b-a,c-b...
// by default, the - operator is used

std::vector<int> vec3;
std::adjacent_difference(cbegin(sum),cend(sum),back_inserter(vec3)); // returns us to normal

for (auto i : vec3){
    std::cout << i << " ";
}

// inner_product() returns the scalar sum of each corresponding element of two vectors multiplying
// given source containers {a1,a2,a3,... and {b1,b2,b3....
// target container will be a1*b1 + a2*b2.....
// we have to provide an inital value for the sum

std::cout << std::endl;

std::cout << std::inner_product(cbegin(sum),cend(sum),cbegin(vec3),0);  // plus and * operators used by default
// inner_product() is equivalent to transform() followed by accumulate()
// a transform step which multiples elements from each range together and stores the results in another range
// an accumulate step which adds up the results in that range

std::cout << std::endl;

// we can write this as two seperate algorithm calls

std::vector<int> test1 {1,2,3,4,5};
std::vector<int> test2 {6,7,8,9,10};
std::vector<int> test3;
std::transform(cbegin(test1),cend(test1),cbegin(test2),back_inserter(test3), std::multiplies<int>()); // call the standard libraries fucntion object multiply for ints
int result = std::accumulate(cbegin(test3),cend(test3),0,std::plus<int>()); //same with plus for accumulate
std::cout << result << std::endl;


// we can overload the inner_product() algorithm by providing different binary functions instead of the default + and * operators
// we can replace the * operator with a transform operation
// we can replace the + operator with an accumulate operation

// transform + accumulate is a common pattern in parallel programming
// you can break a large calculation down into smaller parts that can be performed independently of each other, each sub calculation can be done on its own processor core
// we can combine the results of the sub calculations to give the final result

// std::accumulate() is not suitable for parallel processing, so as of c++17, we can ise std::transform_reduce()
// this is the same as iner_product(), but uses reduce() instead of accumulate(), std::reduce() is compatible with parallel processing

}