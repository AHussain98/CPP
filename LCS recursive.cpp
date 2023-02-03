#include <iostream>
#include <string>
//Your implementation's iostream header includes string. This is not something which you can or should rely on.
// If you want to use std::string, you should always #include <string>, otherwise your program might not run on different implementations, or even in later versions of your current one.
using namespace std;

//return the length of the most common subsequence between two strings
// A subsequence is a sequence that can be derived from another sequence of elements without changing the order of the remaining elements.
//In other words, it's a generalised subarray/substring where the rule of contiguity does not apply.
//So, a subsequence can be derived from another sequence by deleting some or none of the elements in between but always maintaining the relative order of elements in the original sequence.

//C++ doesn't allow non-constant values for the size of an array. That's just the way it was designed.

int lcs(string s, string t){
    if(s.size() == 0 || t.size() == 0){
        return 0;
    }

    if(s[0] == t[0]){ //so if the first chars match, add one to the returned value and rerun for the remainder of the strings
        return 1 + lcs(s.substr(1),t.substr(1)); // substr is a string function that reduces a sting from the front by the int you pass it
    }

    else{ //if they don't have the same first letters, we have three cases:

    int a = lcs(s,t.substr(1)); // pass the whole of s but reduce t by one
    int b = lcs(s.substr(1),t); // pass the whole of t but reduce s by 1
    int c = lcs(s.substr(1),t.substr(1)); //pass the sunstring of them both
    return max(a,max(b,c)); //return the largest of these




    }

}

//we can do this using memoisation by making a 2d array of size s and t, and then storeing th evalues of each possible subsequence

int lcs_memo(string s, string t, int ** arr){

    int m = s.size(); //so the value of m and n will change depending on which recursive call is used
    int n = t.size();

    if(s.size() == 0 || t.size() == 0){
        arr[m][n] = 0;
        return 0;
    }

    if (arr[m][n] != -1){ //so if we have the value already stored, just return it and don't make any recursive calls
        return arr[m][n];  //so in the reduced size m or n value, we place the answer
    }

    int ans;

    if(s[0] == t[0]){ //so if the first chars match, add one to the returned value and rerun for the remainder of the strings
        ans = 1 + lcs_memo(s.substr(1),t.substr(1),arr); // substr is a string function that reduces a sting from the front by the int you pass it
    }

    else{ //if they don't have the same first letters, we have three cases:

    int a = lcs_memo(s,t.substr(1),arr); // pass the whole of s but reduce t by one
    int b = lcs_memo(s.substr(1),t,arr); // pass the whole of t but reduce s by 1
    int c = lcs_memo(s.substr(1),t.substr(1),arr); //pass the sunstring of them both
      ans = max(a,max(b,c)); //return the largest of these

    }
    arr[m][n] = ans;
    return ans;

}

/*
When you declare a variable as here

int a[10][10];
you are telling the C++ compiler that you want 100 consecutive integers allocated in the program's memory at runtime.
The compiler will then provide for your program to have that much memory available and all is well with the world.

If however you tell the compiler

int x = 9001;
int y = 5;
int a[x][y];
the compiler has no way of knowing how much memory you are actually going to need at run time without doing a lot of very complex analysis to track down every last place where the values of x and y changed [if any].
 Rather than support such variable size arrays, C++ and C strongly suggest if not outright demand that you use new to manually allocate the space you want.
 This is why we have to declare 2d arrays as an array of pointers
*/

// Using string::size: The method string::size returns the length of the string, in terms of bytes.
// Using string::length: The method string::length returns the length of the string, in terms of bytes. Both string::size and string::length are synonyms and return the exact same value.

int lcs_helper(string s, string t){  //we create the array in here then pass it over to the memo function because we don't want to create multiple arrays and waste memory

    int m = s.size();
    int n = t.size();
    int ** arr = new int * [m+1]; //create a pointer to an array of pointers, make it one larger than the size of the string because theres three characters, but arrays are indexed from 0 and we need the indexes to match, as we're including the empty string as a choice

    for (int i = 0; i <= m; i++){
        arr[i] = new int [n+1];
        for (int j = 0; j <= n; j++){
            arr[i][j] = -1; //initialise the array with -1 values
        }
    }


    return lcs_memo(s,t,arr);
}

//now lets try a dynamic programming approach

int lcs_DP(string s, string t){
    int m = s.size();   // number of rows is size of s plus 1
    int n = t.size();   //number of columns is size of n plus 1

    //so we can fill the top row and left column because they're when s or t are empty, so the answer will always be 0

      int ** arr = new int * [m+1]; //create a pointer to an array of pointers, make it one larger than the size of the string because theres three characters, but arrays are indexed from 0 and we need the indexes to match, as we're including the empty string as a choice

    for (int i = 0; i <= m; i++){
        arr[i] = new int [n+1];
        for (int j = 0; j <= n; j++){
            arr[i][j] = -1; //initialise the array with -1 values
        }
    }

    //so we've created the answer array and initialsed it, now lets fill in the 0's
    //for 1st row:

    for (int j = 0; j<=n; j++){
        arr[0][j] = 0; //so on the first row, j moves along the columns and 0 is inserted, along the top row
    }

    //now for 1st column:
    for (int i = 0; i<= m; i++){
        arr[i][0] = 0; //remember m is number of rows
    }

    for (int i = 1; i <= m; i++){ //start from 1 because we know the 0 index values are 0, as s[3] and t[3] cant possibly be part of the substring as theyre both empty
        for (int j = 1; j<=n;j++){   //so for the whole first row:
            if(s[m-i] == t[n-j]){ //so work backwards from the end of the string
              arr[i][j] = 1 + arr[i-1][j-1];
            }
            else{
                int a = arr[i][j-1];

                int b = arr[i-1][j];

                int c = arr[i-1][j-1];

                arr[i][j] = max(a,max(b,c));
            }
        }
    }

 return arr[m][n]; //answer stored in bottom right corner

}


int main(){

string s,t;
cin >>s>>t;
cout << lcs_helper(s,t) << endl;
cout << lcs_DP(s,t);




}