#include <iostream>
using namespace std;

//dijkstras algorithm returns the minimum distance needed to travel to a node from the starting node

int findMinVertex( int * weight, int n, bool * visited){
    // so traverse the 2d array from 0 to n and return the minimum vertex
             int minVertex = -1;  // min vertex starts as -1 , 0 is returned in that case
     for (int i = 0; i < n ;i++){
         if (!visited[i] && (minVertex == -1 || weight[i] < weight[minVertex])){
             minVertex = i; //return the vertex with the smallest distance
             //so initalliy every other cell is infinity apart from 0 which contains 0
         }
     }
    return minVertex;   //minimum vertex returned based on weight
}


void dijkstras( int ** edges, int n, int e ){
    // we need a distance array and a visited array
    int * distance = new int [n];
    bool * visited = new bool [n];
    //lets initialise them
    for (int i = 0; i < n; i++){
        distance[i] = INT_MAX;
        visited [i] = false;
    }
    distance[0] = 0; //initalise the first value of the distance array
    for (int i = 0; i < n; i++){ // we could even make it run for n-1 times, as it doenst matter once the last node is reached
        int minVertex = findMinVertex(distance, n, visited);
        //now update visited
        visited[minVertex] = true; // we're now going to run for this minVertex value, so we can make it true to avoid a repeat
        for (int j = 0; j < n; j++){
            if(edges[minVertex][j] != 0 && !visited[j]){ // min vertex value stays teh same, so we run through the smallest distances for nodes 0,1,2,3 etc..., all with each other
                int Total_dist = distance[minVertex] + edge[minVertex][j]; //total distance is current distance added to the edge of j
              if(Total_dist < distance[j]){   //so distance from 0 to rest of nodes it connects to gets updated
                  distance[j] = Total_dist;   //so distance of 0 will always end up being 0, then we just add to it for subsequent minVertex values
              }  // so update the distance of that node index with the smallest value we can find
              //then it runs again for the next node (next minVertex)

            }
        }
    }

    for (int i = 0; i < n; i++){
        cout << i << " " << distance[i] << endl;
    }
}


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
dijkstras(edges,n,e);

//delete the heap memory after we've called the function
for ( int i = 0; i < n; i++){
    delete[] edges[i]; // so delete every array ponited to within i
}
delete[] edges; //now delete the edges array itself

}