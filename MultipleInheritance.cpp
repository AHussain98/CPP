#include<iostream>
using namespace std;


class Student{
    public:
        string name;
        int rollno;
        
      void print(){
            cout << "Student "<< endl;
        }
    
};

class Teacher{
    public:
        string name;
        int age;
        
        void print(){
            cout << "Teacher" << endl;
        }
    
};

class TA: public Teacher, public Student{      // TA class inherits from both Teacher and Student classes 
        string name;
};

int main(){
    
     TA t;
     // there are two print functions in the classes TA inherits from, to call a specific, one, preface it with the class it comes from with scope resolution operator
     t.Student::print();
     t.name = "Asad";
    
    
    
    return 0;
}