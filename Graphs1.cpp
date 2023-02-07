#include <iostream>
using namespace std;
// a graph is made of edges and vertices(nodes). Edges connect vertices
// trees are a type of graph, except they don't contain any cycles and there's only ever one specific path between one node and another
//graphs have cycles and generally many routes to connect nodes
// two vertices that are directly connected via an edge are 'adjacent' vertices
//  a connected graph is a graph where there are paths between every vertex, they can all reach each other via edges
// a disconnected graph is where there are vertices that cannot be reached from other vertices (there are no edges between them)
// graphs can also have connected components, where they have connected subgraphs that are not connected with each other
// minimum number of edges required to create a connected graph is n-1 vertices
// degree of a vertex is the number of direct edges it has
// a complete graph is where every vertex is connected to each other via edges
// we can implement a graph with n vertices by creating a nxn adjacency matrix and then storing the connections each vertex has as a boolean, so the vertex represented by the row has a 1 or 0 for each vertex connection is has on the column

//Depth First Search -> print the nodes in order, following down the vertices from one to the next, follow the loop of the graph, printing whatevers connected and smallest
//Breadth First Search -> print the first node and all its children, then the next node and all its children etc..., print by level, in order of whats smallest

void printHelper( int ** arr, int n, int sv, bool * check){ // sv for start value
     cout << sv;
     check[sv] = true; //so turn that start value to 1 as its been printed

     for (int i = 0; i < n; i++){
         if (arr[sv][i] && !check[i]){ //so if there is an edge between your starting vertex and i (your end vertex), and this end vertex hasnt been visited before

             printHelper(arr,n,i,check); //so run through for the enrtire first row, for loop ends when theres a new column
         }
     }

}


void printDFS(int ** arr, int n){
      //we can create an array of nodes we've visited, to avoid printing them again
      //make them boolean and initialised with 0 values, when the vertex is printed, change to 1, therefore before printing a vertex, check it is false first in the array
      bool * check = new bool [n]; //delcare a heap array of size n, remember to store boolean values
      for (int i = 0; i < n; i++){
          check[i] = false; //initalise with boolean false values
      }

      //we need to consider the fact that we could have a disconnected graph, so we need to run the printing function for every vertex that hasn't been checked
      for (int i = 0; i < n; i++){
          if (!check[i]){   // check is false, so run for vertices that havent been printed yet
              printHelper(arr,n,i,check); // i is 0 to start with, but when i gets to a value that is still false in check, that graph will now be printed
          }
      }

}


int main(){
     //code for DFS
     int n, e;  // take in n number of nodes and e number of edges
     cin >> n >> e;

     int ** arr = new int * [n]; // so n number of rows
     for (int i = 0; i < n; i++){
         arr[i] = new int[n]; // and n number of columns, so we now have a space for every nodes connection with itself and others
         for (int j = 0; j<n; j++){
             arr[i][j] = 0;  //initalise the matric with 0 values
         }
     }

     for (int i = 0; i < e; i++){

          int sv,ev; //take starting vertex and ending vertex
          cin >> sv >> ev;
          arr[sv][ev] = 1;
          arr[ev][sv] = 1; //fill in the corresponding spots in the matrix as true
     }

     printDFS(arr,n); // now call the function
}