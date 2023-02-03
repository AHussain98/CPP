#include <iostream>
using namespace std;

int knapsack_DP(int * weight, int * val, int n, int weight_bag){
    int ** ans = new int * [n + 1];  // 2d array has n number of rows and weight_max number of columns
    for (int i = 0; i <= n; i++){
        ans[i] = new int [weight_bag + 1];
        for (int j = 0; j <= weight_bag; j++){
            ans[i][j] = -1; //create and initalise the array
        }
    }

    //1st row will be all 0, max value is 0 if n is 0 (nothing left to pick)

    for (int i = 0; i <= weight_bag; i++){
        ans[0][i] = 0;
    }

    //first column must also be all 0, as there can be no more added as max_weight limit is reached
    for(int i = 0; i <= n; i++){
        ans[i][0] = 0;
    }

    for (int i = 1; i <= n; i++){    //now fill in all the values, row by row, starting with first row

        for ( int w = 1; w <= weight_bag; w++){
              if (weight[i-1] > w){  //weight is bigger than what we currently can carry
                  ans[i][w] = ans[i-1][w]; //so drop down by one, just reduce the value of n and carry on
              }
              else{
                  ans[i][w] = max(ans[i-1][w] , val[i-1] + ans[i-1][w - weight[i-1]]);
              }                //max of either not choosing the value(same value as the cell above, no change
                               // or we take it, so add the value of it to the value of the cell where weight_bag has decreased by the weight[w]


        }
    }

    return ans[n][weight_bag]; //answer in the bottom right

}


int knapsack(int * weight, int * val, int n, int weight_bag){
    if (n == 0 ||  weight_bag == 0){ //base case, if there are no items left, or there is no more capacity in ther bag, just return what we got
        return 0;   //no items or capacity so just return
    }

    if(weight[0] > weight_bag){
          knapsack(weight + 1,val + 1,n-1,weight_bag);  //weight is too large to fit in my bag
          //so rerun the knapsack fucntion for the next value in the weight array (can be done by adding 1) to pointer passed in
    }
    else {
         int x = val[0] + knapsack(weight+1,val+1,n-1,weight_bag - weight[0]); // if we choose it
         int y = knapsack(weight+1,val+1,n-1,weight_bag); // if we didn't choose it, max weight is unchanged
         return max(x,y);
    }

}


int main(){
    int weight[] = {6,1,2,4,5};
    int val[] = {20,5,4,8,6};

    int n = 5; // int n just tells how many items we have avaiable
    int weight_bag = 5;
    int ans = knapsack_DP(weight,val,n, weight_bag);
    cout << ans;



}