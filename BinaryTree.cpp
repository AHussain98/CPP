#include <iostream>
#include <queue>
using namespace std;

// binary tree means a node can have only 2 children at the max
//binary tree node can have either 0,1 or max 2 children
//so when creating a binary node class, you need only 3 elements, a data value and pointers to the left node and right node

template <typename T>
class BinaryTreeNode{
    public:
      T data; //data can be of any type
      BinaryTreeNode<T> * left;
      BinaryTreeNode<T> * right;

      //initalise using constructor

      BinaryTreeNode( T value) {
          this->data = value; //make the object's data equal the value of the data passed in
          left = NULL;
          right = NULL; //so initalise the pointers to its children class as null initially
      }
};

// create a class containg the height and diameter of a tree
class DH{
    public:
        int diameter;
        int height;
};


//lets create a function that allows our binary tree to take an input

BinaryTreeNode<int> * takeInputBinary(){ //this function returns a pointer to a node
        int rootData;
        cout << "enter the data of the root" << endl;
        cin >> rootData;
        if (rootData == -1){  //if NULL is returned, then that pointer will point to no value, e.g. the child doesnt exist
            return NULL;
        }

        BinaryTreeNode<int> * root = new BinaryTreeNode<int>(rootData); //first node created
        BinaryTreeNode<int> * lchild = takeInputBinary();
        BinaryTreeNode<int> * rchild = takeInputBinary();
        root->left = lchild; //point the left and right pointers to the roots that are returned by the recursive function
        root->right = rchild;

        return root;    //so ultimately, the address of the root node of the tree is returned, each child node address gets returned to its parent, but only once both children trees point to NULL, when -1 is given

}     //When we create the tree, we only actually manually create the first node, the rest is done by recursion

//print the binary tree

void printBinaryTree(BinaryTreeNode<int> * root){
    if(root == NULL){   //incase node pointer points to is empty
        return; //so the function juststops running for that particular leg of the tree
    }

    cout << root->data << " : ";
    if(root->left != NULL){ //this means it exists
       cout << root->left->data << ", ";
    }
    if(root->right != NULL){ //this means it exists
       cout << root->right->data << ", ";
    }

    cout << endl;

    printBinaryTree(root->left);
    printBinaryTree(root->right); //now call the function recursively for the children of root
    //when we hit the bottom of the tree, root == NULL, and then the return chain begins, as per the first line
}

//lets try to take input on a level by level basis now, using a queue as before

BinaryTreeNode<int> * takeInputBinaryTreeLevelWise(){   //return a pointer to the root node, as before
    int rootData;

    cout << "enter the data of the root: " << endl;
    cin >> rootData;
    if(rootData == -1){
        return NULL; //pointer will be set to null if next node doesnt exist
    }

    BinaryTreeNode<int> * root = new BinaryTreeNode<int>(rootData); //create the root node initally
    //at this point, the left and right child are pointed to NULL
    //now we need to put our children in the queue, the queue will be made up of pointers
    queue<BinaryTreeNode<int> * > pendingNodes; //create a queue of pointers to BinaryTree nodes, call the queue pendingNodes
    pendingNodes.push(root); //enqueue push
    //we use a queue because its FIFO, we want to push in the root, then its children, then pop the root
    while(pendingNodes.size() != 0){ // could also used !pendingNodes.empty() here
       BinaryTreeNode<int> * front = pendingNodes.front(); //make the front pointer equal to the first value in the queue
       pendingNodes.pop(); //clear the first value in the queue, front is still pointing to that node however
        //so this is levelwise because we're putting in the values for each nodes left and right child sequentially, while the nodes are on the same level
       cout << "Enter the left child of: " << front->data << endl;
       int leftChild;
       cin >> leftChild;
       if (leftChild != -1){ //so if we put in -1, the following logic is skipped, no child exists so no child node is pushed onto the queue
           BinaryTreeNode<int> * lchild = new BinaryTreeNode<int>(leftChild);
           front->left = lchild; //so the left node is created, and now we can set roots left to point to the left node
           pendingNodes.push(lchild); //add the left child onto the queue, we then repeat the process for it
       }
         //now do same for RHS
        cout << "Enter the right child of: " << front->data << endl;
       int rightChild;
       cin >> rightChild;
       if (rightChild != -1){
           BinaryTreeNode<int> * rchild = new BinaryTreeNode<int>(rightChild);
           front->right = rchild; //so the right node is created, and now we can set roots left to point to the left node
           pendingNodes.push(rchild); //add the right child onto the queue, we then repeat the process for it
       }



    }
    return root; //after the while loop has run, we can assume that the tree has been created, so just return the root node address
}

//now lets print level wise
void printBinaryTreeLevelWise( BinaryTreeNode<int> * root){
    // first lets check if the tree is empty
    if(root == NULL){
       return; //you dont need to print anyhting in this case
    }
    //create the queue to store the child pointers, call it pendingNodes
    queue<BinaryTreeNode<int> *> pendingNodes;
    pendingNodes.push(root);
    while(!pendingNodes.empty()){ //while pendingNodes is not empty, do whatever is inside my loop

    BinaryTreeNode<int> * front = pendingNodes.front();
    pendingNodes.pop();
    cout << front->data << " : ";
    if (front->left != NULL){
        cout << front->left->data << ", ";
        pendingNodes.push(front->left); //as soon as you've printed the data, push that child onto the queue, process will repeat for that child
    }
    if (front->right != NULL){
        cout << front->right->data;
        pendingNodes.push(front->right);
    }
    cout << endl; //so after each parent has printed its data, we need a new line
    }

}

//lets find the number of nodes in the tree, by passing in the root node

int NodesInBinaryTree(BinaryTreeNode<int> * root){
    //in the case the tree is empty
    if(root == NULL){
        return 0;   //so eventually 0 will be retuned when we reach a leaf node
    }
    int ans = 1;  //this is for the root, the ans must always be atlest 1
    int lchild = NodesInBinaryTree(root->left);   //assume recursion brings left sides count of nodes
    int rchild = NodesInBinaryTree(root->right);  //assume same for RHS
    return ans + lchild + rchild; //so for each node, we return the sum of thier ans (1) and their childrens (potentially 2 more 1's)
}

//lets try to find a particular data value within the binary tree

bool findNode(BinaryTreeNode<int> * root, int x){ //will return a boolean
        if (root == NULL){
            return false;
        }
        if (root->data == x){   //as soon as the value is found, true is returned
            return true; //so this checks the data of root to see if it matches x
        }
        //if its not equal, we then come onto this line
        bool leftchild = findNode(root->left,x); //run the same check for the left child of root
        bool rightchild = findNode(root->right,x); //if the data is the same, one of these variables will become true

        if(leftchild == true || rightchild == true){  //same as saying if(leftchild || rightchild), this also means if either of them are true
            return true;
        }
        else{
            return false;
        }  //so as soon as the value is found, it returns true for the node above it, and since once of the left or right child nodes is true, true gets passed all the way up to root, true is returned

}

//lets work put how to find the height of a binary tree
//remeber, if one node is present, the height is 1

int heightBinaryTree(BinaryTreeNode<int> * root){
    if (root == NULL){
        return 0; //there is no height here
    }

    int ans = 1; //since root is a node, we start here
    int lchildans = heightBinaryTree(root->left);
    int rchildans = heightBinaryTree(root->right);

    int maxSide = max(lchildans, rchildans);
    return ans + maxSide;
}

//there  are 3 different types of traversal in a binary tree: pre order, in order and post order
//pre order is print root, then print left, then print right
//in order is print left,root,right
//post order is left,right,root

void preOrderTraversal(BinaryTreeNode<int> * root){
    if(root == NULL){
        return; // if tree is empty, just return
    }
    cout << root->data << " ";
    preOrderTraversal(root->left);   //so the node on the left will be printed, and the left child of that node will have this function called
    preOrderTraversal(root->right);   //same with the right, but this only gets evaluated once the left side expression above completes
    //so first root is printer, then recursion prints the left part and the right part
}

void inOrderTraversal(BinaryTreeNode<int> * root){
    if(root == NULL){
        return;
    }
    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);

}

void postOrderTraversal(BinaryTreeNode<int> * root){
    if(root == NULL){
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->data << " ";
}

//diameter of binary tree? how to find the number of nodes between the two firthest apart nodes
//the two furthest apart points are either the combined heights of both of roots children, or the diameter of the left child or right child
int diameterBinaryTree(BinaryTreeNode<int> * root){
       if (root == NULL){
           return 0;
       }
       //option 1, 2 and 3
       int op1 = heightBinaryTree(root->left) + heightBinaryTree(root->right);
       int op2 = diameterBinaryTree(root->left);
       int op3 = diameterBinaryTree(root->right);

       return max(op1,max(op2,op3)); //max function can only be used with two inputs
}

//lets do the above better, by seeing if we can avoid travelling down the tree multiple times

DH diameterHeight(BinaryTreeNode<int> * root){  //return the class DH , so we can return height and diameter at the same time
if(root == NULL){
    DH fail;
    fail.diameter = 0;
     fail.height = 0;
     return fail;
}
 DH lchild = diameterHeight(root->left);
 DH rchild = diameterHeight(root->right); //so the DH class returned by teh function is stored as lchild and rchild

 int l_diameter = lchild.diameter;
 int l_height = lchild.height;
 int r_diameter = rchild.diameter;      //take in these values for each parent node, made up of their childrens data
 int r_height = rchild.height;

  int height = max(l_height,r_height) + 1; //+1 for the root node youre using to compare these
  int op1 = l_height + r_height;
  int op2 = l_diameter;
  int op3 = r_diameter;
  int diameter = max(op1,max(op2,op3)); //so this way, we only need to traverse the trees to find their heights once
   //diameter only gets a value once height has some value
  DH ans;
  ans.diameter = diameter;
  ans.height = height;

  return ans;
}

int main(){
//    BinaryTreeNode<int> * root = new BinaryTreeNode<int>(1); //defined the root node via a pointer called root, instantiated
//    BinaryTreeNode<int> * node1 = new BinaryTreeNode<int>(2);
//    BinaryTreeNode<int> * node2 = new BinaryTreeNode<int>(3);
//
//    root->left = node1;
//    root->right = node2; //give the root node binary tree children through the pointers arrow operator
//

 BinaryTreeNode<int> * root = takeInputBinaryTreeLevelWise();
 printBinaryTreeLevelWise(root);
 cout << endl;
 //cout << "Number of nodes is: " << NodesInBinaryTree(root);
// cout << endl;
 //bool ans = findNode(root, 5);
 //cout << ans; //returns 1 because its true
 //bool ans2 = findNode(root, 19);
 //cout << " " << ans2 << endl; //returns 0 because its false
// cout << "Height of binary tree is: " << heightBinaryTree(root);

preOrderTraversal(root);
cout << endl;
inOrderTraversal(root);
cout << endl;
postOrderTraversal(root);
cout << endl;

DH ansClass = diameterHeight(root);
cout << "diameter: " << ansClass.diameter << endl;
cout << "height: " << ansClass.height << endl;
}