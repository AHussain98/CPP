#include <iostream>
# include <string>

class String{

    char * data; //array to store the characters
    int size; //number of elements in the array

    public:
        //constructor
        String(const std::string& s) : size(s.size()){
            data = new char[size]; // allocate the heap memory for the data

            for (int i = 0; i < size; i++){
                data[i] = s[i];  // populate the data
            }
        }
         /*; This is the difference between what is called a shallow copy and a deep copy. A shallow copy simply
copies all members of an object one by one, even if these members are pointers to dynamic memory. A deep
copy, on the other hand, copies all dynamic memory referred to by any of its pointer members as well. */

        // deep copy constructor

        String(const String& arg){
              size = arg.size;
              data = new char[size];
              for (int i = 0; i < size; i++){
                data[i] = arg.data[i];  // populate the data with the data from the argument, but a new version for the new object
                //now the new object isn't sharing any pointers with the object we're copying from
            }

            //Like a default copy constructor, the default copy assignment operator simply copies all the member
            //variables of a class one by one (in the order they are declared in the class definition). You can override this
            //default behavior by supplying a user-defined assignment operator

            // the assignment operator will cause the same issue as the shallow copy constructor, so we should overload that
           // we need to assign the target object with its own memory allocation, this must be large enough to hold the data
           // we also need to check for self assignmnet, to ensure the "this" and "arg" objects are not referring to the same object

           // assignment operator
           String& operator =(const String& arg){
               if (&arg != this){ // check for self assignment
               delete [] data; //release the original memory
               data = new char [arg.size]; //allocate the data member

               size = arg.size; //assign the size member

               for (int i = 0; i < size; i++){
                   data[i] = arg.data[i]; // populate the data
               }
               return *this;  // return the object that has been assigned to
               }
           }

        }

        //destructor

        ~String(){
            std::cout << "Calling destructor" << std::endl;
            delete [] data; //release the heap memory
        }
        int length(){
            return size;
        }

        // if a class needs to implement one of: a copy constructor, an assignment operator, or a destructor, then it probably needs to implement the other two aswell
        // e.g. class with pointer member allocated with 'new' in constructor and released by 'delete' in destructor
        // assignment operator is needed to create deep copy on assignmnet
        // this is called the rule of three
        // destructor needed with 'delete' alongside deep copy, as we need to delete the dynamic memory belonging to each object
        // else, if two object pointed to same dynamic memory, one calling destructor and deleteing would mean the destructor of the other has nothing to delete, leads to errors

};

int main(){

            String str("1");
            String str2("Two");
            String str3(str2);
            String str4 = str2;

            std::cout << str.length() << std::endl;
            std::cout << str2.length() << std::endl;
            std::cout << str3.length() << std::endl;
            std::cout << str4.length() << std::endl;


}