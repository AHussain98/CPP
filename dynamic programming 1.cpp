#include <iostream>
using namespace std;

//we can say a program uses dynamic programming when:
//it uses optimal substructure and avoids overlapping subproblems
//lets take an example

int fibo(int n){
    if (n <= 1){
        return n;
    }

    int a = fibo(n-1);
    int b = fibo(n-2);
    return (a+b);

}

//currently, the time complexity is 2^n, as the recursive call occurs for two elements per fucntion call, one for n-1 and another for n-2
//overlapping subproblems means making the same funcition calls we dont need to, e.g. fibo for 5 will call the fibo chain for 3 and 4, which have repeated valuesbut both functions will be fully called and the chains followed through
//optimal substructure is a program that breaks into smaller structures to solve problems more efficiently
//so what if we were able to store fibo results for n values we have aready called?
//lets try implementing this using an array to reduce our time complexity, implementing this array takes our time complexity down to O(n), as we've reduced the number of calls we need to make by saving results
//this approach is called memoization, memorize the value, store it and repeat it when we need to

int fiboHelper(int n, int * ans){
       if (ans[n] != -1){ //in this case, the array value already exists and we can return it without any recursion calls, first time round, this will be -1, the function will populate it
       return ans[n];
       }
       if (n <= 1){
         ans[n] = n;
         return ans[n];
    }

    int a = fiboHelper(n-1,ans); //we're passing them the pointer to the same array we passed into the function, so we know they're filling the correct one
    int b = fiboHelper(n-2,ans);
    int output = a+b; //so store the result rather than returning it at this point
    ans[n] = output; //so the corresponding ouput value is saved in the matching spot in the array
    return ans[n]; //return the final value dtored at that n value in the array
                 }

int fibo_mem(int n){   //creates the array and calls the function
      int * ans = new int[n+1]; //the ans pointer contains the address of the array that will store our values, make it one bigger than n because it needs to store the value of n aswell (remember indexing)
      for(int i = 0; i<=n;i++){
          ans[i] = -1; //initialise the array values with -1 initially
      }
      return fiboHelper(n,ans);   //better to seperate these functions out, as we only want to create the array once
}

//but we can solve the problem dynamically and reduce the time complexity further still. Dynamic programming uses no recursion whatsoever.
// for fibonacci, we only need the values of n = 0 and n = 1 for our base case, the rest we fill in via the recursive function call
// so lets try to fill in those other values without using recursion, only using the base caee

int fibo_dynamic(int n){
      int * ans = new int[n+1]; //create the array as before
      //we already know the base cases so implement them
      ans[0] = 0;
      ans[1] = 1;

      for (int i = 2; i <= n; i++){
          ans[i] = ans[i-1] + ans[i-2];  //just using the base case we can derive every possible answer
      }
      //this solution is O(n) because we run the loop an order of n times
      return ans[n];
      //simplicity is much preferable
}

int main(){
    int n;
    cout << "n :" << endl;
    cin >> n;
    cout << endl;
    cout << fibo_dynamic(n) << endl;
     int ans2 = fibo_mem(n);
     cout << ans2;
    int ans = fibo(n);        //difference is noticable when n is 45, for example


    cout << endl;
    cout << ans;
}

//the above is an example of efficent problem solving using memoization
/* In programming, memoization is an optimization technique that makes applications more efficient and hence faster. It does this by storing computation results in cache, and retrieving that same information from the cache the next time it's needed instead of computing it again.

In simpler words, it consists of storing in cache the output of a function, and making the function check if each required computation is in the cache before computing it.

A cache is simply a temporary data store that holds data so that future requests for that data can be served faster.

Memoization is a simple but powerful trick that can help speed up our code, especially when dealing with repetitive and heavy computing functions. */
