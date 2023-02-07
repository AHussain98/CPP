#include <iostream>
#include <algorithm>
using namespace std;


//Kruskals algorithm allows you to create a minimum spanning tree with smallest possible weight, with no cycles
//  Kruskals works by picking the edge with minimum weight, note the vertices connected by that edge, then repeat the cycle, avoiding cycles

class Edge{     //edge object, will have a source, end and a weight
    public:
        int source;
        int destination;
        int weight;
        printKruskals(){
            if (source < destination){
                cout << source << " " << destination << " " << weight;
            }
            else{
                 cout << destination << " " << source << " " << weight;
            }
            cout << endl;
        }
};

int findParent(int v, int * parent){
    if(parent[v] == v){
        return v;
    }
    int par = findParent(parent[v],parent);
    return par;
}

bool compare(Edge e1, Edge e2){   // used to sort the edges in ascending order
    return (e1.weight < e2.weight);
}

void kruskals(Edge * input, int v, int e){
   sort(input,input + e, compare); // sort algo in algorithm header file
   Edge * output = new Edge[v-1];
   int * parent = new int[v];
   for (int i = 0; i < v; i++){
       parent[i] = i;  //all the nodes are thier own parents initally


   }
   int count  = 0;
   int i = 0;
   while( count != (v-1)){ // v - 1 as there are only v -1 edges
    Edge currentEdge = input[i];
    int sourceParent = findParent(currentEdge.source,parent);
    int destinationParent = findParent(currentEdge.destination,parent);
    if (sourceParent != destinationParent){
        output[count] = currentEdge;         //if parents are different, its safe to add that edge
        count++;
            parent[sourceParent] = destinationParent;

    }
    parent[sourceParent] = destinationParent; //now make the parent of the source equal to the destination
    i++;

   }
   for (int k = 0; k < v-1 ; k++){

   output[k].printKruskals();
}
}

int main(){
     //we need the vertices and number of edges
     int n,e;
     cin >> n >> e;

     Edge * input = new Edge[e]; //create a pointer to an array of Edge objects
     for (int i = 0; i < n; i++){
         int s,d,w; // create variables for source, desitination and weight
         cin >> s >> d >> w;  //take them in
        // new edge objects are created for every index in the array
          input[i].source = s;
          input[i].destination = d;
          input[i].weight = w;


     }

     kruskals(input,n,e);

}