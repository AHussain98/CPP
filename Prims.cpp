#include <iostream>
using namespace std;

//we've got a vector of weights, a vector of "visited" and a vector of parent nodes
// prims is also used to generate a minimum spanning tree, but by selecting from a root vertex and then selecting nodes from there

int findMinVertex( int * weight, int n, bool * visited){
    // so traverse the 2d array from 0 to n and return the minimum vertex
             int minVertex = -1;  // min vertex starts as -1 , 0 is returned in that case
     for (int i = 0; i < n ;i++){
         if (!visited[i] && (minVertex == -1 || weight[i] < weight[minVertex])){
             minVertex = i;
         }
     }
    return minVertex;   //minimum vertex returned based on weight
}



void prims( int ** edges, int n, int e){
// now create our three arrays (vectors)
int * parent = new int [n];
int * weight = new int [n];
bool * visited = new bool [n];

for (int i = 0; i < n; i++){
    weight[i] = INT_MAX; //fill weights in with maximum value initally, this is for comparison later
    visited[i] = false;

}
// make starting weight 0
weight[0] = 0;
parent[0] = -1;  //0's parent cant be 0 so fill in with -1

for (int i = 0; i < n; i++){
// now we need to find the minimum vertex
int minVertex = findMinVertex(weight,n,visited);
visited[minVertex] = true;
//now explore every possible adjacent vertex
for (int j = 0; j < n; j++){
    if(edges[minVertex][i] != 0 && !visited[j]){ //so if theres an edge there and its not been visited
    if(edges[minVertex][j] < weight[j]){
        weight[j] = edges[minVertex][j];
        parent[j] = minVertex; // edit the weight value and the parent
    }
    }
}

}  //now print the output

for (int i = 1; i < n; i++){  // dont need to print first cell so start from 1
    if (parent[i] < i){
        cout << parent[i] << " " << i << " " << weight[i];
    }
    else{  // just to print in ascending order
        cout << i << " " << parent[i] << " " << weight[i];
    }
}
}




//whatever we have as our starting vertex, make the wieght of that 0, and everything else has weight of infinity
int main(){
int n,e; // number of vertexes and edges
cin >> n >> e;
int ** edges = new int * [n];

for (int i = 0; i < n; i++){
     edges[i] = new int [n];  //an array of n x n vertices is created, to represent the edges between them
     for (int j = 0; j < n; j++){
         edges[i][j] = 0; //initalise with 0 values
     }
}
// now we need to take input
for (int i = 0; i < e; i++){
    int sv,ev,w; //take in start value, end value and weight
    cin >> sv >> ev >> w;
    edges[sv][ev] = w; // create an array with weight values for all sv/ev pairs
    edges[ev][sv] = w;
    //because this is an undirected graph, we can mirror the sv ev cells to reflect the opposite direction has the same weight
}
prims(edges,n,e);





}