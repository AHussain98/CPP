#include <iostream>
using namespace std;

//templates are very useful for generalising programmes so they work with different data types

int find_max(int x, int y){
    if(x > y){
        return x;
    }
    else {
        return y;
    }
    
}

//so the above function will only work for int datatypes
//but we can make another function that will work with all datatypes using a template

template<typename T> //T is the datatype that we've declared as a standin
T find_biggest(T x, T y){ //so T takes the place of int
     if(x > y){
        return x;
    }
    else {
        return y;
    }
} 


//lets try putting the above into a class 

template<typename U, typename V> //you can declare two templates
class Pair{
    U x;
    V y; //so class data members X and Y and of data type U and Y 
   
   public: 
    setX(U x){
        this->x = x;
    }
    setY(V y){
        this->y = y;
    }
    U getX(){
        return x;
    }
    V getY(){
        return y;
    }
};



int main(){
 
// cout << find_max(5,7) << endl; 
 
 cout << find_biggest('a','b') << endl; //the fucntion works with chars now
 cout << find_biggest(13,5) << endl;  
 cout << find_biggest("asad","hussain") << endl;
 
 cout << endl;  

//now lets create pair objects

Pair<int,char> test;   //declared an object of Pair class and declared U as int and V as char
 test.setX(45);
 test.setY('n');
 cout << test.getX() << endl;   //works!
 cout << test.getY() << endl;

//we can even create a Pair class and pass that in as the U data type in the template
Pair<Pair<int,int>,int> p2; //U value in the template is another pair object
p2.setY(6); //so y value of p2 is 6, but we need to create an object and pass that in as p2's x value

Pair<int,int> p3; //created a class 
p3.setX(10);
p3.setY(20); //initialise it with values

p2.setX(p3);
cout << p2.getX().getX();   //we can then access the value of p3's x using p2

}