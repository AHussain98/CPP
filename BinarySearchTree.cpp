// BST is same as BT except everything on LHS is less than node and everything on RHS is greater
//so for each root node, the left child should be less than the right child
//the children of root must also follow this rule
//in a BST, even the rchild of roots lchildren must still be smaller than root
// if even a small part of teh BST does not obey this rule, it is not a BST
#include <iostream>
#include <queue>
using namespace std;

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

//lets try to find the maximum value in the left hand side(smaller side) of the BST
int maximum(BinaryTreeNode<int> * root){
    if (root == NULL){
        return INT_MIN; //INT_MIN specifies that an integer variable cannot store any value below this limit.
    }

    int lchild_ans = maximum(root->left);
    int rchild_ans = maximum(root->right);

    return max(root->data,max(lchild_ans,rchild_ans)); //compare the lchild and rchild max values with root, the largest is whats returned
    //for every node, find the biggest value between its lchild, rchild and its root data

}

//find the minimum value in the RHS (larger side) of the BST
int minimum(BinaryTreeNode<int> * root){
    if(root == NULL) {
        return INT_MAX; //INT_MAX is a macro that specifies that an integer variable cannot store any value beyond this limit.
    }

    int lchild_ans = minimum(root->left);
    int rchild_ans = minimum(root->right);

    return min(root->data,min(lchild_ans,rchild_ans));
}



//lets create a function that searches a tree and checks if it is a BST

bool isBST(BinaryTreeNode<int> * root){
    if(root == NULL){
        return true; //a single node or no node at all still return true, as they still satisfy our BST requirement
    }
    int max = maximum(root->left);  //find the maximum on the side that should be all smaller than root
    int min = minimum(root->right); //find the minimum on the side that should be all larger than root

    if(max >= root->data){ //so you find the max on the smallest side and compare with each root nodes data value
        return false;
    }
    if (min <= root->data){  //same for min
        return false; //so if either of the key BST conditions are violated, return false
    }
    bool leftans = isBST(root->left);    //then run this recursively to check the left and right subtrees are BST's
    bool rightans = isBST(root->right);

    if(leftans && rightans == true){ //if the left subtree and right subtree are ordered correctly, return true
        return true;
    }
    else{
        return false;    //else it cannot be a BST, so return false
    }
}


bool searchBST(BinaryTreeNode<int> * root, int x){
    if (root == NULL){
        return false;
    }
    if(root->data == x){
         return true; //so we initially compare with the value at root, is this the value we're looking for?
    }
    else if (root->data > x){
      bool lchildans = searchBST(root->left,x);
      return lchildans;
    }
    else { bool rchildans = searchBST(root->right,x);
    return rchildans;
    }
}


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

int main(){
      BinaryTreeNode<int> * root = takeInputBinaryTreeLevelWise();
      printBinaryTreeLevelWise(root);

      cout << endl;
      cout << "Does the BT contain 5?" << endl;
      cout << searchBST(root,5) << endl;
      cout << "Is this tree a BST? " << isBST(root);


}