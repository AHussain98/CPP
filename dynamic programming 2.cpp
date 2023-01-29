#include <iostream>
using namespace std;
//programme to find the minimum steps to n = 1, if n can only be reducedby 1, or divided by 2 or 3
int minSteps(int n){
     if(n <= 1){
         return 0; //if you're at 1, you don't need to return anything
     }
     int subtract1 = minSteps(n-1);
     int x = INT_MAX; //we're comparing these wuth subtract 1 at the bottom
     int y = INT_MAX; //so just incase they can't recieve a value, we'll initalise them with the largest possible value they could be, to avoid them messing with the min function
     if(n%2 == 0){ //if divisible by 2
          x = minSteps(n/2);
     }
     if(n%3 == 0){  //if divisible by 3
          y = minSteps(n/3);
     }

     int ans = min(subtract1,min(x,y)) +1; //add one for every step
     return ans;   //then return the minimum amount
}

//lets try doing this with memoization

int minStepsHelper(int n, int * a){
     if(n <= 1){
         a[n] = 0;
         return 0; //if you're at 1, you just return 0
     }
     if (a[n] != -1){  //answe already stored in my answer array so dont do any recursive strpe, just return the answer
         return a[n];
     }
     int subtract1 = minStepsHelper(n-1,a);
     int x = INT_MAX; //we're comparing these wuth subtract 1 at the bottom
     int y = INT_MAX; //so just incase they can't recieve a value, we'll initalise them with the largest possible value they could be, to avoid them messing with the min function
     if(n%2 == 0){ //if divisible by 2
          x = minStepsHelper(n/2,a);
     }
     if(n%3 == 0){  //if divisible by 3
          y = minStepsHelper(n/3,a);
     }

     a[n] = min(subtract1,min(x,y)) +1; //add one for every step
     return a[n];   //then return the minimum amount
}

int minSteps_mem(int n){
   int * a = new int[n+1]; //create an array thats one larger than the amount we're running the algorithm for, this is because we want to include the n number itself
for (int i = 0; i<=n;i++){
    a[i] = -1; //initalise the values in the array
}
return minStepsHelper(n,a);
}

//lets try doing this with a dynamic programming approach
int minSteps_DP(int n){
    int * ans = new int[n+1]; //heap array because we don't know how large it needs to be yet
    //dynamic programming involves implementing the base case as an assumption
    ans[0] = 0;
    ans[1] = 0;
    //now we can start the loop
    for (int i = 2; i<=n;i++){
        int subtract1 = ans[i-1];
        int divideby2 = INT_MAX;
        int divideby3 = INT_MAX;
        if(i%2 == 0) {
            divideby2 = ans[i/2];
        }
        if(i%3 == 0){
            divideby3 = ans[i/3];
        }
        ans[i] = min(subtract1,min(divideby2,divideby3)) + 1;
    }
    return ans[n];
}

int main(){
    cout << "n: " << endl;
    int n;
    cin >> n;
    cout << endl;
    cout << minSteps_DP(n) << endl;
    cout << minSteps_mem(n);




}