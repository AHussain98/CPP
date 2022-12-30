#include <iostream>
using namespace std;

//a queue is a data structure similar to a a stack, but it is FIFO, first in first out
//we need pointers pointing to the front and the rear of the queue
//the enqueue fucntion will insert an element into the queue, the index pointed to by queue will increase by 1
//the dequeue function will take out the element being pointed to by front, and front will move along by one to the next index
//we need a size function to tell us the size of the queue and a front fucntion to tell us whats at the front


//lets begin by building a queue data structure using an array
template<typename T>
class arrayQueue{
    public: 
    T * data; //data pointer used to point to the stack array
    int front; //based on index, so always integers
    int rear;
    int size; //how much of the array is filled currently
    int capacity; //how big the queue is
    
    arrayQueue(){ //constructor to initalise
        data = new T[5]; //data pointer points to an array of ints declared on the stack
        front = -1; //for the inital part, front is not pointed to any element as the array is empty, when the first value is entered, front must become 0 
        rear = -1;
        size = 0;
        capacity = 5;
    }
    
    bool isEmpty(){
        return size == 0; //if size is zero, this returns true
    }
    
    int sizeOf(){
        return size;
    }
    
    void enqueue( T input){
        if( size == capacity){
            cout << "queue is full, doubling capacity" << endl; //we can set up the queue to resize itself as we did  with the stack previously
           T * newData = new T[2*capacity]; //delcare a pointer to a new array that is double the size, only in the event that the current data arrauy is full and we try to enqueue 
           int index = 0; //we'll use this in the newData loop
            for(int i = front; i < capacity; i++) { //start from front as front may not be pointing to data[0], so we need to start fron whatever index front is
               newData[index] = data[i];
               index++; 
            }
            
            //so the above loop has taken care of inputting values between front and the end of the data array
            //but we need another loop to input values between data[0] and the front index
               for(int i = 0; i<front; i++){
               newData[index] = data[i];
               index++;   
            }
            
            delete [] data; //delete the array that data pointer was pointing to
            data = newData; //repoint data to the new larger array
            
            //now we need to repoint front and rear
            front = 0;
            rear = index -1; //this is because index will finish as 1 more than the last data entry after the two loops above have completed (index will point to 6, we need the rear value to point to index 5
            //so rear will need to be pointed to the index before index 
            
        } //we are just coming in and inserting into the queue, we are not traversing the array, so the time complexity is of an order of 1
        
        if (size == 0){ //there are no elements inside our queue
        front = 0; //data now entered so front can move to 0 index
        }
        rear = (rear + 1)%capacity;  //rear starts as -1 so now becomes 0, but say for example that we've dequeed the first two queue values but not the last 3 (front is at index 2 and rear is at index 4), that means the first two array cells are empty and not being used, which is inefficient
        //so we can work out a way of making use of these so the spaces aren't wasted, this cn be done by making the rear value reach back around so it points to the first empty cell in the array
        //we can do this by using the modulo operator, remember that 1%5 = 1 and 2%5 = 2 etc... (when using the modulo operator, if the LHS is less than the RHS, the LHS is returned)
        //so we can get the rear value to return to the empty index 0 by using the modulo and capacity, see above
        //this will only take effect once we've reached the end of the array because otherwise the LHS is less than the RHS and the LHS will be returned, which is the normal condition anyway
        data[rear] = input; //data inserted into queue
        size++; //element has been inserted
        
    }
    
    T dequeue(){  //will return T
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return 0;
        }
        int temp = data[front];
        front = (front + 1)%capacity; //front only moves when you dequeue, but in the case that front is indexed at the last index in the array, and a dequeue happens, front will need to return to the front of the array at the 0 index
        //therefore we include this modulo, which will allow this to happen in that scenario, same as with the rear in the enqueue finction
        size --; //queue gets smaller
       
        if(size == 0){  //incase you dequeue the last value
            front = -1;
            rear = -1;
        }
         return temp;
    }
    
    T queueFront(){
        if(isEmpty()){
            cout << "queue is empty" << endl;
            return 0;  
        }
        return data[front];
    }
};

int main(){
    
    arrayQueue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.enqueue(5);
    q1.enqueue(6);
    
    cout << q1.sizeOf() << endl;
    cout << q1.isEmpty() << endl;
    
}