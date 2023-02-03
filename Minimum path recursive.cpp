#include <iostream>
using namespace std;

//imagine you start on the top left corner of a grid and want to get to the bottom right corner
//how to get there in the least amount of steps?
//so if you imagine us on a 2 dimensional array grid, starting point is (i,j), moving right is [i][j+1]
// i increases if you move down and they both increase if you move diagonally
// m is rows and n is columns, we have found our corner when i,j = n-1,m-1
// we'll create an array of pointers m, which points to row arrays n
//we access this array structure using a pointer, prt[0][0] gives us the first value on the first array row

int minCostHelper(int ** edges,int m,int n, int i, int j){
  //base case
  if(i==m-1 && j==n-1){ //this means you're at the bottom right cell, at our destination so just return the value there
  return edges[i][j]; //so this being reached will kick off the reverse chain
  }

  if(i >=m || j >=n) { //because i means row and j means column, if one of these tries retunring a value that goes beyond the scope of the grid
  return INT_MAX; // this means it'll never be one of the minimum options below
  }
     //now we can start calling the function for each case, and the minimum will be returned each time
    int x = minCostHelper(edges,m,n,i,j+1); //move to the right
    int y = minCostHelper(edges,m,n,i+1,j); //move downward
    int z = minCostHelper(edges,m,n,i+1,j+1); // move diagonallly
    int output = min(x,min(y,z)) + edges[i][j]; //so move to the smallest possible value and add the answer to the node you're currently standing on
    return output;
}


int minCostPath(int ** edges,int m, int n){

    return minCostHelper(edges,m,n,0,0); //give initial i and j values as 0,0 so we start in the topleft corner

}

//lets try a memoizational approach, as a lot of cells that are out of bounds are considered multiple times, we can cut down on this

int minCostHelper_memo(int ** edges,int m,int n, int i, int j, int ** ans){
  //base case
  if(i==m-1 && j==n-1){ //this means you're at the bottom right cell, at our destination so just return the value there
   ans[i][j] = edges[i][j]; //store the result in the ans 2d array
  return edges[i][j]; //so this being reached will kick off the reverse chain
  }

  if(i >=m || j >=n) { //because i means row and j means column, if one of these tries retunring a value that goes beyond the scope of the grid
  return INT_MAX; // this means it'll never be one of the minimum options below
  }

  //now we need to check if the smallest value already exists in our ans 2d array
  if(ans[i][j] != -1){
      //so if it exists in the array, lets use it rather than calling recursion
     return ans[i][j];
  }
     //now we can start calling the function for each case, and the minimum will be returned each time
    int x = minCostHelper_memo(edges,m,n,i,j+1,ans); //move to the right
    if(x < INT_MAX){
        ans[i][j+1] = x;  //so store the value in ans, remember this is working backwards from the destination
        //this works because the minimum in the bottom right cell is just the value at that cell, and the cells bove and to its left can find their minimum because the only cell they can be compared to is the bottom right
        //remember that the next cell that is evalueted must be one of the right, diagonal or down, but for the cells on the border next to the bottom right cell, everything is out of bounds for them apart form that cell
        //out answer will ultimately be the value stored in ans[0][0]
    }
    int y = minCostHelper_memo(edges,m,n,i+1,j,ans); //move downward
    if(y < INT_MAX){
        ans[i+1][j] = y; //store the value if its legitimate
    }
    int z = minCostHelper_memo(edges,m,n,i+1,j+1,ans); // move diagonallly
    if (z < INT_MAX){
        ans[i+1][j+1] = z;
    }
    int output = min(x,min(y,z)) + edges[i][j]; //so move to the smallest possible value and add the answer to the node you're currently standing on
    //then just before you return, store the answer in ans
    ans[i][j] = output;

    return output;
}

int minCostPath_memo(int ** edges,int m, int n){  //so create anotehr array called ans thats 2d
       int ** ans = new int * [m]; // create a pointer to an array of pointers
      for(int i = 0; i<m;i++){  //n is number of columns so below code creates m number of rows to point to an array that is n columns long
          ans[i] = new int [n]; //   so each of the pointers in edges points to a new array of rows
          //now lets fill in the row array
          for (int j = 0;j<n;j++){
              ans[i][j] = -1; //this is how we can refer to the matrix using the pointer array to arrays  , first initialise to 0
              //the matrix has now been created
          }
      }
      return minCostHelper_memo(edges,m,n,0,0,ans);
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

      int ans = minCostPath(edges,m,n); //run the function
      cout << ans << endl;
      cout << minCostPath_memo(edges,m,n); //run the memo version too, time complexity much reduces, its O(n)
}