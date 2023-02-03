#include <iostream>
using namespace std;

//consider that the destination cell is in the bottom right corner, its co-ordinates are [m-1][n-1], where m is num of rows and n is num of columns
// the values stored in the ans array is the minimum value required to get to each cell from the bottom right destination cell
 //this works because the minimum in the bottom right cell is just the value at that cell, and the cells bove and to its left can find their minimum because the only cell they can be compared to is the bottom right
  //remember that the next cell that is evalueted must be one of the right, diagonal or down, but for the cells on the border next to the bottom right cell, everything is out of bounds for them apart form that cell
  //our answer will ultimately be the value stored in ans[0][0]


  //now remember that Dynamic programming amounts to breaking down an optimization problem into simpler sub-problems, and storing the solution to each sub-problem so that each sub-problem is only solved once.
  //storing solutions — a technique known as memoization — matters in dynamic programming.
  //Memoization means no re-computation, which makes for a more efficient algorithm.
  // Thus, memoization ensures that dynamic programming is efficient, but it is choosing the right sub-problem that guarantees that a dynamic program goes through all possibilities in order to find the best one.

int minCostPath_DP(int ** edges, int m, int n){
      int ** ans = new int * [m]; // create a pointer to an array of pointers
      for(int i = 0; i<m;i++){  //n is number of columns so below code creates m number of rows to point to an array that is n columns long
          ans[i] = new int [n]; //   so each of the pointers in edges points to a new array of rows
          //now lets fill in the row array
          for (int j = 0;j<n;j++){
              ans[i][j] = -1; //this is how we can refer to the matrix using the pointer array to arrays  , first initialise to 0
              //the matrix has now been created
          }
      }

      ans[m-1][n-1] = edges[m-1][n-1]; // fill in the answer cell

      //remember m in no of rows and n is num of columns

     //for rows
      for (int j = n-2; j >= 0; j--){ // because n-3 is 0 when n is 3
          ans[m-1][j] = edges[m-1][j] + ans[m-1][j+1]; // so the value to the left of the corner value gets the corner value added onto its own, this is for last row
      }
      //for columns
      for (int i = m-2; i >= 0; i--){
          ans[i][n-1] = edges[i][n-1] + ans[i+1][n-1];   // so add the value above the bottom right corner to the vaue on the bottom right corner and store it
      }

      //so we've got the bottom row and right column, but now we need the other values

      for (int i = m-2; i>=0;i--){
          for (int j = n-2;j>=0;j--){ //so start from centre square
              ans[i][j] = edges[i][j] + min(ans[i][j+1],min(ans[i+1][j],ans[i+1][j+1]));
          }

      }

      return ans[0][0];  // then return the answer
}

int main(){

     int m,n; //m is rows and n is columns
    cout << "Enter your m and n: " << endl;
    cin >> m;
    cin >> n;
    //lets create the 2d array using the heap

    int ** edges = new int * [m]; // create a pointer to an array of pointers
      for(int i = 0; i<m;i++){  //n is number of columns so below code creates m number of rows to point to an array that is n columns long
          edges[i] = new int [n]; //   so each of the pointers in edges points to a new array of rows
          //now lets fill in the row array
          for (int j = 0;j<n;j++){
              edges[i][j] = 0; //this is how we can refer to the matrix using the pointer array to arrays  , first initialise to 0
              //the matrix has now been created
          }
      }  //now we insert the values
      for (int i = 0; i < m; i++){
            for(int j = 0; j<n;j++){
                int ans;
                cin >> ans;
                edges[i][j] = ans;
            }
      }
              cout << minCostPath_DP(edges,m,n);

}