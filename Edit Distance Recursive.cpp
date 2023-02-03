#include <iostream>
#include <string>
using namespace std;

//return the minimum number of edits so that two strings become the same
//this can be done through insertion, deletion or substitution

int editDistance(string s, string t){
    if(s.size() == 0 || t.size() == 0){
        if(s.size() == 0){
            return t.size(); //if one string is empty, the minimum number of steps to
            //get the first string to that level will be to insert the same number as the size of the full string, so return the size of the other string
        }
        else{ return s.size(); //if t is not empty, return the size of s
        }
    }
    if(s[0] == t[0]){ //so the first values are the same, we can then continue with the rest of the string
    return editDistance(s.substr(1),t.substr(1));
    }
    else{
        int a = 1 + editDistance(s.substr(1),t); // a deletion, so delete one from s and keep t as it is, add 1 for the operation count
        int b = 1 + editDistance(s,t.substr(1)); // an insertion, s is not affected but t is, add 1 for the operation
        int c = 1 + editDistance(s.substr(1),t.substr(1)); //a substitution, s and t is affected

      return min(a,min(b,c)); //return whichever is smallest
    }
}

    //we can use memoisation on this by storing the minimum number of edits needed in an array when s[0] and t[0] are a particular value, using a 2d array
int editDistance_memo(string s, string t, int ** ans){
    int m = s.size();
    int n = t.size();
      if(s.size() == 0 || t.size() == 0){
        if(s.size() == 0){
            ans[m][n] = t.size(); //m is 0 in this case, but whatever size t is, that value must be inputted into the array
            return t.size(); //if one string is empty, the minimum number of steps to
            //get the first string to that level will be to insert the same number as the size of the full string, so return the size of the other string
        }
        else{ return s.size(); //if t is not empty, return the size of s
        ans[m][n] = s.size(); //same as above case
        }
    if (ans[m][n] != -1){
        return ans[m][n]; //so if the value in the answer array already exists for this size of s and t, return it and don't call recursion
    }

    }
    int value; // declare outside of the below if and else blocks so we can call it at the end;

    if(s[0] == t[0]){ //so the first values are the same, we can then continue with the rest of the string
    value = editDistance_memo(s.substr(1),t.substr(1),ans);
    }
    else{
        int a = 1 + editDistance_memo(s.substr(1),t,ans); // a deletion, so delete one from s and keep t as it is, add 1 for the operation count
        int b = 1 + editDistance_memo(s,t.substr(1),ans); // an insertion, s is not affected but t is, add 1 for the operation
        int c = 1 + editDistance_memo(s.substr(1),t.substr(1),ans); //a substitution, s and t is affected

      value = min(a,min(b,c)); //return whichever is smallest
    }
    ans[m][n] = value; //so now before the min is returned and the function ends, store the value in the array
    return value;

}



int editDistance_memo(string s, string t){ //declare the 2d array using the array of pointers method
    int m = s.size();
    int n = t.size();
    int ** ans = new int * [m+1];  //remember we are working backwards in the 2d array, so s[1] is the last char of s, and we make it m+1 because we need to account for the case where the string is empty
    for (int i = 0; i<=m;i++){
        ans[i] = new int [n+1];
        for (int j = 0; j <= n; j++){
            ans[i][j] = -1; //initialise the 2d array with -1 values
        }
    }
    return editDistance_memo(s,t,ans); //function overloading, returns the above function

}

//now lets try a dynamic programming approach, bottom right cell is the destination cell as before

int editDistance_DP(string s, string t){
         int m = s.size();
    int n = t.size();
    int ** ans = new int * [m+1];  //remember we are working backwards in the 2d array, so s[1] is the last char of s, and we make it m+1 because we need to account for the case where the string is empty
    for (int i = 0; i<=m;i++){
        ans[i] = new int [n+1];
        for (int j = 0; j <= n; j++){
            ans[i][j] = -1; //initialise the 2d array with -1 values
        }
    }
    //for first row
    for (int j = 0; j <= n; j++){
        ans[0][j] = j;
    }
    //for first column
    for(int i = 0; i <=m;i++){
        ans[i][0] = i; //so the value when one of the strings is 0 is just the size of the other
    }
    //now lets go about filling in values row by row, we just reinterpret the three recursive calls we made earlier
    for (int i = 1; i<=m; i++){
        for(int j=1; j<=n;j++){

            if (s[m-i] == t[n-j]){ // imagine s is abc and t is just c, but was originally dac, we need to work out how to compare s[0] with t[2], we can do this by taking away i and j (thier indexes on the ans array) from m and n (their actual sizes)
                    //so comparing from the ends of the strings, if i,j is 1 and m,n is 3, s[2] is compared with t[2], the answer is stored in ans[1][1], because there's only one char in each string for that comparison
            //this is why the answer is in ans[m][n], because thats the value when they've both been fully compared
                ans[i][j] = ans[i-1][j-1]; // no change needed, this becomes the same as for the previous chars in the strings
            }
            else{
                int a = 1 + ans[i-1][j];  //delete
                int b = 1 + ans[i-1][j-1]; //substitute
                int c = 1 + ans[i][i-1];   //insert

                ans[i][j] = min(a,min(a,b));

            }
        }
    }

    return ans[m][n];



}

int main(){
     string s,t;
     cin >> s >> t;
     cout << editDistance_DP(s,t)<< endl;
     cout << editDistance_memo(s,t) ;




}