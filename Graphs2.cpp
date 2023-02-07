#include <iostream>
#include <queue>
#include <vector>
using namespace std;
//spanning tree -> a connected graph with no cycles, with n vertices, you have n-1 numebr of edges
// minimum spanning tree is the one with the smallest weight of all edges combines, with no unconnected vertices 

// for breadth first search, we print the current vertex and then every vertex that is adjacent to the parent vertex
// so we'll again use the visited array concept
// we can do bfs using a queue, as soon as a vertex is inserted into the queue, put 1 in its visited array index
// when the queue is empty, the program can end

//without the using namespace std, we have to do std:: before using cin and cout, to verify that this functionality comes form the standard library

void printBFSHelper(int ** arr, int n, int sv, bool * visited){
queue<int> pendingVertices;
pendingVertices.push(sv); //push the starting vertex onto the queue
visited[sv] = true; //mark that index as true in the visited array

while( !pendingVertices.empty()){ //so while the queue is not empty
    int front = pendingVertices.front();
    pendingVertices.pop(); //pop the front value from the queue
    cout << front << endl; //so the first value in the queue has been printed
    for(int i = 0; i<n; i++){
        if(arr[front][i] == 1 && !visited[i]){  //so if there's a connection and this hasn't been visited already
          pendingVertices.push(i);
          visited[i] = true;
        //loading them in one at a time via a queue ensures they print in th eorder we want, level by level

        }
    }

}

}



void printBFS(int ** arr, int n){
    bool * visited = new bool [n];
    for (int i = 0;i<n;i++){
         visited[i] = false;
    }
   //we have the same issue as before, we need to print the disocnnected graph, we can accomplish this via the for loop:
   for(int i = 0; i<n; i++){
    if (!visited[i]){

    printBFSHelper(arr,n,i,visited);  // so if there;s any nodes we havent visited, rerun the funtion with them as the starting value
}  }}


//function to find a path between two vertices, so the vertices between them (if they are indeed connected)
//return a vector that contains all the values in the path
vector<int> * getPathHelper(int ** arr, int n, int sv, int ev, bool * visited){
   if (sv == ev){
     vector<int> * output = new vector<int>();  // dynamically declare a vector without a size or initalising it
     output->push_back(sv);   //  if starting value is same as ending value, just push that on
    return output;
   }

   visited[sv] = true;
   for (int i = 0; i<n; i++){
       if (arr[sv][i] && !visited[i]){ // so if a path exists and we've not visited the end node yet
           vector<int> * smallOutput = getPathHelper(arr,n,i,ev,visited); //recursive call for every start value
           if (smallOutput != NULL){ //if it doesnt return null, then there is a path
           smallOutput->push_back(sv);
           return smallOutput;
           }  // when i becomes ev, the first if block will activate and a vector with the end value will be retunred
           //each vertex then pushes itself on sequentially, and returns a pointer to that vector

       }
   }
return NULL;
}

vector<int> * getPath(int ** arr, int n, int sv, int ev){
    //with graph questions, we need a visited array so that we don't get caught in loops
    bool * visited = new bool [n];
    for (int i = 0; i<n; i++){
        visited[i] = false; //initalise the visited array as false initially
    }
    //now pass this into the getHelper function
    vector<int> * output = getPathHelper(arr,n,sv,ev,visited);
    return output;


}



int main(){
    //code for BFS
     int n, e;  // take in n number of nodes and e number of edges
     std::cin >> n >> e;

     int ** arr = new int * [n]; // so n number of rows
     for (int i = 0; i < n; i++){
         arr[i] = new int[n]; // and n number of columns, so we now have a space for every nodes connection with itself and others
         for (int j = 0; j<n; j++){
             arr[i][j] = 0;  //initalise the matric with 0 values
         }
     }

     for (int i = 0; i < e; i++){

          int sv,ev; //take starting vertex and ending vertex
          std::cin >> sv >> ev;
          arr[sv][ev] = 1;
          arr[ev][sv] = 1; //fill in the corresponding spots in the matrix as true
     }

     printBFS(arr,n); // now call the function

    vector<int> * ans = getPath(arr,n,0,3); //call the getpath function and store the result in the ans pointer to a vector
    cout << "PATH: ";
    for (int i = 0; i < ans->size(); i++){
        cout << ans->at(i) << " ";  //we have to use the at() function with a vector, instead of just [], or we could do (*ans)[], this is the dereference method
    }

}

