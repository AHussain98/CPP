#include <iostream>
using namespace std;

//we can implement a queue as a linked list, making use of the head and tail pointers that already exist as part of the linked list to point to front and tail

template<typename T>
class Node{
    public:
        T data;  //data variable belonging to each object
        Node <T> * next;   //next pointer to a node object
        
        Node(T input){
            this->data = input;
            next = NULL; //make pointer null initially
        }
};

template<typename T>
class LLQueue{
    public:
          Node<T> * front; //create pointers for front and rear, both of type node
          Node<T> * rear;
          int size;
          
          LLQueue(){
              front = NULL;
              rear = NULL;
              size = 0;
          }
    


int sizeOf(){
    return size;
}

bool isEmpty(){
    return (size==0); //returns true if size is = 0
}

void enqueue(T input){  
        Node<T> * newNode = new Node<T>(input); // firstly create a node that has our input value
        if(front == NULL && rear == NULL){ //so if this is the first element
           front = newNode;
           rear = newNode;
        }
        else{
        rear->next = newNode;   //we only need to move rear, front can stay as it is
        rear = newNode; //so point the current last node's next value to the new node and then move rear so that its pointing to the new node
        }
        size++; //this is out of the logic statements above because size will need to be increased regardless
        
}

T dequeue(){
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return 0;
    }
    else{
    T temp = front->data; 
    Node<T> *t = front;   //since we're returning teh data of front, lets store its pointer somewhere
    front = front->next; //move front along to the next node
    delete t; //delete the previous front node
    size --;
    return temp;
    //so now the data value that was the previous front's is stored and returned, and fron moves along with the node being destroyed
}
}

T frontQueue(){
     if(isEmpty()){
        cout << "queue is empty" << endl;
        return 0;
    }
    else{
        return front->data;
    }
}
};

int main(){
    
    LLQueue<int> q1;
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    q1.enqueue(40);
    q1.enqueue(50);
  cout << q1.sizeOf() << endl;
  cout << q1.frontQueue() << endl;
  cout << q1.dequeue() << endl;
  cout << q1.sizeOf() << endl;
  cout << q1.frontQueue() << endl;
    

    
    
}