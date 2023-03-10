#include <iostream>
using namespace std;

// In simple words, a linked list consists of nodes where each node contains a data field and a reference(link) to the next node in the list.
//this is different to an array, which is a contigous form of data retention where all data members are stored sequentially in memory
//linked lists can store data in different memory addresses
//The size of memory can be allocated or de-allocated at run time based on the operation insertion or deletion.
//The insertion and deletion of elements are simpler than arrays since no elements need to be shifted after insertion and deletion, Just the address needed to be updated.
//Linked List is a dynamic data structure, the size increases or decreases as per the requirement so this avoids the wastage of memory. 
//Various advanced data structures can be implemented using a linked list like a stack, queue, graph, hash maps, etc.

//start by creating a class for nodes:
class Node{
  public: 
        int data;  //data stored at the address
        Node * next; //pointer of type node that points to the next node
          
   Node(int data){ //constructor that takes data as input
          this->data = data;
          this->next = NULL; //set next pointer to be null for now, 
   } 
};

Node* takeInput(){ //return a Node type pointer, but this method takes O(n) time complexity to execute because you have to traverse the whole list to insert each time
      int data;
      Node * head = NULL; //should be null to start with, It is always a good practice to assign the pointer NULL to a pointer variable in case you do not have exact address to be assigned.
      cin >> data; //take in data for the first node of the linked list
      
      while(data != -1){  //assume that data being -1 means we want no more data
          Node *temp = new Node(data);   //create a pointer called temp that points to a new node object, with the data as the input, this line creates a node
          if(head == NULL){ //then this must be the first node, this line checks the head of that node is not null
          
          head = temp; // this means that head will now point to the same node that temp does
          }
          else{ //so head is not null
            Node *t1 = head; //so we have this new pointer which has the same value as head, so both t1 and head are pointing to n1
            while(t1->next != NULL){ //so if the node has an address for the next node in the list
                t1=t1->next;   //make pointer t1 point to the next node in the linked list
            }
            //to get to this point, a next value in the linked list must be = 0 for the above while loop to stop, this means we've reached the end of the list
            t1->next = temp;  //so if head is not null, traverse the linked list until you get to the end and point the next variable of the last node to the address of the new node
          }
          cin >> data; //so take in data and the loop reruns
      }
      
      return head; //return the head value as the result of this function, the head value is the first node of the linked list
}

void print(Node *head){
            while (head->next != NULL){
                 cout << head->data << endl;
                 head = head->next;
            }
            cout << head->data;  //still need to print the data of the last node
}                          

//lets create a function to find the length of the linked list
int length(Node * head){
    if (head == NULL){
         return 0;
    }
    int count = 0;
    while (head != NULL){
        count++;
        head = head->next; 
    }
    return count;
}

//we can improve on the takeInput function above by keeping track of the tail of the linked list via a pointer to it, and then only adding onto the list via this tail pointer

Node* takeInputImproved(){ //this method should only take O(1), should be constant time , returns a pointer of type node
      int data;
      Node * head = NULL;
      Node * tail = NULL; //add a null pointer for tail 
      cin >> data; 
      
      while(data != -1){  
          Node *temp = new Node(data);    //remember temp is used to store the address of the newest node
          if(head == NULL){ 
          
          head = temp;
          tail = temp; //tail must also point to the first element in the list
          }
          else{ //so head is not null, for rest of list:
                tail->next = temp;//tail is currently at the last node,  so we can use the tail pointer to change the value of the next field for the last node to be pointed to the new one
                tail = temp; //tail itself should then point to the new node
          }
          cin >> data; //so take in data and the loop reruns
      }
      
      return head; //return the head value as the result of this function, the head value is the first node of the linked list
}

//we also need a function that will allow us to insert new values at any point into the linked list 

Node * Insert(Node * head, int data, int pos){ //returns a pointer of type node, function needs the pointer to the head of the linked list, the data to insert and the position(array index) to insert into
          Node * newNode = new Node(data); //so here is our new node on the heap, with a stack pointer
         if (pos == 0){ //implies we want to add to the start of the list
              newNode->next = head; //so the new node points to the node stored at head, whoch was the tart of the original linked list
              head = newNode;  //head then moves to the newNode address
         }
         int count = 0;
         Node * temp = head; //stores the address of head , we can use this in the while loop, we dont use head because we dont ever want to change what head points to
         while(count < pos-1){
             temp = temp->next;
             count++;
         }
         newNode->next = temp->next; //now we've got temp pointing to the entry before our insertion, replace newNode's next with the next from that entry
         temp->next = newNode;  //we now make the preceding entry point to newNode
        
         return head;
}

//we can create a function that will allow us to delete a node form the linked list, this needs to work for a node at the start, middle or end of the list

Node * Delete(Node * head, int pos) { //will return a new pointer, need to pass it head pointer
       if (head == NULL){ //this means if linked list contains no elements
           return head;             
       }
       if(pos == 0){ //this means if we want to delete the first node
           head = head->next;
           return head;
       } 
       int count = 0;
       Node * temp = head;  //store the head value because we need it for later
       while(temp != NULL && count<pos-1){ //we're using pos to store the index position of the node we're deleting, but someone could try to delete a node that doesn't exits, so include that temp must not be NULL 
            temp = temp->next;
            count++; //stops when we're at the node before the one we're deleting
       }
       if (temp == NULL || temp->next == NULL){ //this means we're at the last node
            return head;
       }
       temp->next = temp->next->next; //so store the next value to be pointed to the one after we're deleting
       return head;    
}

//create a function to delete duplicates

Node * removeDuplicates(Node * head){ //pass it the address of the head
       if (head == NULL || head->next == NULL){ //if the linked list is empty or has only one element
            return head; //there cant be any duplicates if the linked list is empty or only has one element so just return head
       }
       //now take two pointers
       Node * t1 = head;
       Node * t2 = head->next;
       
       while(t2 != NULL){ //so before we reach the end of the linked list
         if(t1->data == t2->data){ //if we have a duplicate
            Node * temp = t2; //we're going to use this pointer to delete the duplicate, which is taking up unneccessary memory
            t2 = t2->next; 
            delete temp; //this deletes the heap Node object that temp was pointing to
         }
         else{ //if they're not the same
            t1->next = t2;
            t1 = t2;
            t2 = t1->next; //so they both move along by one, and the comparison in the loop is redone
             
         }
       }
       t1->next = t2; //at the end of the loop, t2 is NULL so we're pointing t1->next to NULL
       return head;
}

//create a function to find the node that a specific value is stored at

int findData(Node * head, int value){
    
    if(head == NULL) { //if the linked list is empty
       return -1;
    }
    int count = 0;
    Node * temp = head; //this is the pointer we'll use to work the loop
    
    while (temp != NULL){ //so before we reach end of linked list
       if (temp->data == value){
           return count;
       }
          count++;      //increase the count to the next index value
          temp = temp->next;  //move to the next node and rerun the loop
        
    }
    
    return -1; //this is what is returned if the value is not in the linked list
}

//find the midpoint of the linked list
//we'll do this by using two pointers, one fast and one slow, the fast pointer will move two nodes at a time, the slow one will only move one at a time
//when the fast pointer reaches NULL or a node with next as NULL, the node that the slow pointer is pointing to at that moment is the middle node

Node * midpoint(Node * head){ //return a pointer
    if(head == NULL || head->next == NULL){ //if there is no linked list, or only one element
        return head;
    }
    Node * slow = head;
    Node * fast = head->next;    //slow points at first element and fast points at second
    
    while(fast != NULL && fast->next != NULL){   //so fast is either at the last node or has just passed it, write the while condition this way around, because if fast is NULL, it cannot have a next, so writing that first may cause an error
        slow = slow->next;
        fast = fast->next->next; //fast moves by two, slow only by one
    }
    
    return slow; //we come out of the loop when the above condition is broken, so slow is now pointing at the middle element ans should be returned
}

//finally, we can merge sorted linked lists

Node * merge(Node * list1, Node * list2){ //takes two pointers to linked lists and returns a pointer to a third, sorted one
  if (list1 == NULL){
      return list2;
  }
  if (list2 == NULL){  //so if either of them are empty, return the other
      return list1;
  }

  Node * newhead  = NULL; //new pointer, this is for the sorted linked list but null for now
  Node * tail = NULL; //using this because we don't want to keep traversing the linked list
  
  Node * temp1 = list1; //pointer to the first list passed in
  Node * temp2 = list2; //pointer to the second list passed in
  
  if (temp1->data < temp2->data) {
      newhead = temp1;
      tail = newhead;
      temp1 = temp1->next; 
      
  }
  
  else{ //if the head of list2 is smaller
  newhead = temp2;
  tail = newhead;
  temp2 = temp2->next;
      
  }
  
  //so we've now set the head of the sorted combined linked list and moved the temp pointer to the next node
  
  while(temp1 != NULL && temp2 != NULL){ //so before you get to the end of both lists
      if (temp1->data < temp2->data){
            tail->next = temp1; //tail is still at the newhead, so here its pointing thenewhead's next as the second smallest value
            tail = temp1; //tail then moves over to the second smallest value
            temp1 = temp1->next;   //temp1 moves to the next value along in the first linkedlist
      }
      else{ tail->next = temp2;
             tail = temp2; //in this case, tail moves to the second array
             temp2 = temp2->next;
          
      }
      
  }
  
  //we come out of the above loop if one of the temp pointers is null, so if one of the linked lists finishes
  
  if(temp1 != NULL){
      tail->next = temp1;
  }
  //only one of these statements will get executed, and the rest of that linked list will just carry on as normal
  if(temp2 != NULL){
      tail->next = temp2;
  }
  
  return newhead;
}





int main(){
   //now lets create some nodes
   
   Node n1(10);
   Node n2(20);
   Node n3(30);
   
   //now we can point these to the next node in the list
   
   n1.next = &n2;
   n2.next = &n3;
   
   //value within an object can be accessed using the . operator
   //pointer to an object can access the values within the object using the -> operator
    
    //create a node type pointer called head, point it to address of n1, this is used to kick off our linked list
    
  //  Node * head = &n1;
    //so head is pointing to node n1, which points to n2, which points to n3
    //address stored in n3 should be made null, as this is last node
    //we can create a function to create a linked list and do the above steps for us
    
  //  Node * head = takeInput(); //node type pointer returned by the takeInput function can be stored in this head pointer
   // print(head);
   // cout << endl;
    //cout << length(head);
    
    //lets try running the new version of takeInput
    
    Node * head1 = takeInputImproved();   //improved time complexity to standard
 //   print(head1);  //works!
    
    cout << endl;
    
   // Node * updateLinkedList = Insert(head1,99,2);    //works!!
   // print(head1);
   // Delete(head1,3);  //try deleting the entry at 3rd index
   // cout << endl;
   // print(head1);
    
  //  Node * update = removeDuplicates(head1);
   // print(update);
    
    cout << endl;
    
  int ans = findData(head1, 3); //give the index that has the data value 3
  
    cout << ans << endl;
    
    Node * mid = midpoint(head1);
    cout << mid->data << endl;
    
    
    //create a couple of linked lists to try merging them
    
    Node * list1 = takeInputImproved();
    Node * list2 = takeInputImproved();
    
    Node * newhead = merge(list1,list2);
    print(newhead);
    
}