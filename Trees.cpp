#include <iostream>
#include <vector>
#include <queue> //for levelwise operation
using namespace std;
  //this is how we'll use the vector built in

//trees are another type of data structure
//a tree has nodes which link to a n number of nodes, trees start from a root node
//in a linked list, a node only has one address, to the next node
//however, in a tree, a node must have data, and then n addresses of other nodes it is the parent node of
//so nodes can point to any node that comes after it in the tree, but not any nodes further down than that
//leaf nodes are nodes without children

//vectors are dynamic arrays, we use these to create arrays without specifying the size. It handles the size at compile time
//we can use vectors to create children arrays for parent nodes, we can store the childrens addresses in the vectors

//lets start by creating the node class
template<typename T>  //we create the template here with type T, so in practice when we instantiate the class in the main fucntion below, we need to fill in what type we want it to be
class TreeNode{
    public:
    int data;
    vector<TreeNode<T>*> children;  // vector called children whose type is TreeNode pointers, TreeNode data is type T so theres a template within the template here
    TreeNode( T data){ //constructor
      this->data = data; //make the data value passed into the constructor become the data member of the object
        }
    };

    //the below are not fucntions of the TreeNode class, they are functions that will use the objects instantiated from the class
    //there's no need for node objects above to be able to do access any of the blow functions using the dot operator, we accomplish everything using pointers ->


    //lets create an input function

    TreeNode<int>* treeInput(){ //called input and returns a pointer to a TreeNode object
        cout << "Enter the root's data" << endl;
        int rootData;
        cin >> rootData;
        TreeNode<int> *root = new TreeNode<int>(rootData); //create a pointer to a new node object with the data vaue you've passed in
        cout << "enter the number of children for " << rootData << endl;
        int n;
        cin >> n;  //take in the number of children this root should have

        for(int i = 0; i<n;i++){  //so the child then repeats the process and asks for its data and how many children it should have
            TreeNode<int> *child = treeInput();  //the address returned by teh input function is then made the value of the child pointer
            //the function above will return the pointer to the childs address
            root->children.push_back(child); //give root the address of the child node in its vector
            } //so do this for the number of children we have

            //if n = 0, thats the base case, the recursive aspect stops and the root pointer is returned to the above node

        return root; //as soon as you get to a node that doesnt have any children, this line will run, and the chain stops, the root values get returned and we work our way back up the stack
    }

    //now lets create a print function

    void treePrint(TreeNode<int> * root){ //  the print function should take a root pointer as its input
        cout << root->data << " : ";
        for(int i = 0; i<root->children.size();i++){  //vectors have a size function
         cout << root->children[i]->data << " , ";  //we can use double arrow operator here as root is pointing to a node object, and the children vector of that object stores the pointers that point to their children
        }
        cout << endl;
        //so we've made root print all of its data, now we can make its children print all of thiers
        for(int i = 0; i<root->children.size();i++){
           treePrint(root->children[i]);
        }
 }

//however, we can actually create a levelwise input fucntion for a tree using a queue to store the addresses, we can come to inputting and printing the children that come further down the tree when we get to them, rather than branch by branch


      TreeNode<int> * levelwiseInput(){ //returns an address to the root node as before (so a TreeNode type pointer)
      int rootData;
      cout << "whats the roots data" << endl;
      cin >> rootData;
      TreeNode<int> * root =  new TreeNode<int>(rootData); //we've now created the root node via a root pointer
      //now create the queue
      queue<TreeNode<int> *> pendingNodes; //create the queue, this will store pointers to TreeNode objects
      pendingNodes.push(root); //push means enqueue, push the root pointer

      while(!pendingNodes.empty()){ //.empty() is a function for queues, this line means while the queue is not empty
      //inbuilt function pop is used to dequeue but it returns void so use the function front
      TreeNode<int> * front = pendingNodes.front();  //created a pointer and given it the address of the first pointer in the queue , front points to the first child address in the queue
      pendingNodes.pop(); //remove the first element in the queue, if we've only put in the root then the queue is empty
      //but we've saved the address that was popped using the pointer front

      cout << "enter the number of children for " << front->data << endl;
      int num;
      cin >> num;

      for(int i = 0; i<num;i++){  //this for loop runs for each child on the level
            int childData;
            cout << "enter the data for " << i+1 << " child" << endl;
            cin >> childData;

            TreeNode<int> * child = new TreeNode<int>(childData);
            front->children.push_back(child); //root address is stored in the front pointer, so update the children vector
            pendingNodes.push(child);   //so the queue gets filled with the pointer to the childrens address
              }
      }

       return root;   //as soon as the pendingNodes queue becomes empty, the pointer to the root node is returned

      }

      //now lets try printing levelwise
      void levelwisePrint(TreeNode<int> * root){
          queue<TreeNode<int>*>  pendingNodes;  //redefine the queue of pointers to TreeNode objects called pendingNodes
          pendingNodes.push(root); //so push the root node in the function argument into the queue

          while(!pendingNodes.empty()){ //so while pendingNodes is not empty
              TreeNode<int> * front = pendingNodes.front(); //make the front pointer point to whatever is at the front of the pendingNodes queue
              pendingNodes.pop(); //remove whatever was at the front of the queue, as the front pointer is storing this
              cout << front->data << " : ";   //print the data contained in front's data, now we have to print its children
              for(int i = 0; i <front->children.size(); i++){ //vectors have an inbuilt function called size, we can use this to help us work out how many children front has and how many times we run this loop
                  cout << front->children[i]->data << " , ";  //use a further arrow because children contains pointers to the children addresses, so we can access their data using the arrow on the pointer stored in front's children
                  pendingNodes.push(front->children[i]); //push the child into the pendingNodes queue so the loop can begin again
                  //front will then point to the next child node in the queue, and the for loop will print out its children
                  //we've already popped the parent node at this point, so the queue just gets filled up with its children
              }

                 cout << endl;
          }

      }

    //now lets find a way to work out how many nodes are in a tree

    int nodeCount(TreeNode<int> * root){ //returns an int and you must pass it a pointer to a TreeNode object
    int ans;//declare and initalise out of the loop so we can access and return it outside
    ans = 1; //this is for the root condition, a tree must always have a root, so the answer must be atleast 1
    for(int i = 0; i<root->children.size();i++){  //so for each node, for the number of children it has, update the answer variable with the number of children that node has and return it, recursively
    ans = ans + nodeCount(root->children[i]);  //the ans veriable will get returned here, with whatever value it has, and this gets passed up the chain
    //the final ans values of the root children as added together in the for loop and returned
    }
    return ans;  //basecase is met at last node

    }

    //we can also find the sum of the nodes

    int nodeSum(TreeNode<int> * root){
        int sum;
        sum = root->data;

        for(int i = 0; i<root->children.size();i++){
           sum = sum + nodeSum(root->children[i]); //assume recursion brings correct answer
        }
        return sum;

    }

    //finding the max value in the tree
    int maxValue(TreeNode<int> * root){
        int ans;
        ans = root->data;
        for(int i = 0; i < root->children.size(); i++){
            int smallAns = maxValue(root->children[i]);

            if (smallAns > ans){
                ans = smallAns;     //compare the returned ans value (stored as smallAns with the current ans value
            }

        }
        return ans;
    }

    //finding which nodes are leaf nodes
    //a leaf node is a node with no children

     int leafNodes(TreeNode<int> * root){
       if(root->children.size() == 0){ //if children is empty, then they are a leaf node
         return 1; //first node is a leaf
       }
       int ans = 0; //initalise the ans value with 0 to start off with, this runs for every recursive function call
       for(int i = 0; i<root->children.size();i++){
            ans = ans + leafNodes(root->children[i]);
       }
       return ans;


     }

     //finding height of a tree

    int heightTree(TreeNode<int> * root){
        int ans = 0; //set ans = 0 initially
      for(int i = 0; i < root->children.size(); i++){ //so this loop will not be called when you get to the bottom node, as the bottom node will have .size = 0
          int childMax = heightTree(root->children[i]);
          if(childMax > ans) { //this logic is used when comparing routes down the tree
              ans = childMax;
          }

      }
         //when you hit the bottom of the tree, 1 will be returned in the function above, this is passed along the recursive chain
        return ans + 1; //add one because the initial node counts as one
    }

    //we can also print at a specific depth k

    void printAtDepth(TreeNode<int> * root, int k){

        if(root == NULL){ //null is a keyword, here its used to check if the tree is empty
            return;
        }

        if(k == 0){
            cout << root->data << " ";
            return; // you've reached the required level so just return
        }

        for(int i = 0; i < root->children.size(); i++){    //so this runs for all children

        printAtDepth(root->children[i], k-1); }

       return;
    }

int main(){
    /*
        //so lets instantiate our first object of class tree
        TreeNode<int> *root = new TreeNode<int>(10);
        //create a pointer to TreeNode object on heap called root, then make this qual a new TreeNode object, both pointer and object should store type int data
        TreeNode<int> *c1 = new TreeNode<int>(20);
        TreeNode<int> *c2 = new TreeNode<int>(30);      //also creates children pointers to other nodes, these will become children of the node root points to
        TreeNode<int> *c3 = new TreeNode<int>(40);
        TreeNode<int> *c4 = new TreeNode<int>(50);

        //we can give root some children manually as below

        root->children.push_back(c1);        //access the children vector of root via the root pointer and therefore with the -> operator
        root->children.push_back(c2);        //stored the addresses of the children nodes in the children vector of root
        root->children.push_back(c3);    */

   /*

    TreeNode<int> *root = treeInput(); //the input function returns a pointer to the root node, so we must create a root pointer to store this value
    treePrint(root);
     */

     TreeNode<int> *root = levelwiseInput();
     levelwisePrint(root);
     cout << endl;
     cout << "amount of nodes is equal to: " << nodeCount(root) << endl;
     cout << "sum of nodes is equal to : " << nodeSum(root) << endl;
     cout << "maxmimum value of nodes is : " << maxValue(root) << endl;
     cout << "the number of leaf nodes is: " << leafNodes(root) << endl;
     cout << "the height of the tree is : " << heightTree(root) << endl;
     printAtDepth(root,2);

   //first node is generally considered to be depth 0, child node is depth 1, child node of that is depth 2
   //height is generally consideredto be 1 from first node, so child will be h2, etc...

}
