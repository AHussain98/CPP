# include <iostream>
# include <string>
// normally, a non member function can only access a class's public members
// the class can declare a non-member function to be a "friend"
// this allows the function access to all the class's members, even the private ones

class Test{
    int i {42};
    std::string s {"Hello"}; //a couple of private members
    public:
        friend void print(const Test&); //just put the function in here, we don't need to define it in the class because its not a class member
        // friend definition must be public
        friend class Example;
};

void print(const Test& test){    // define the function outside the class, but we can still access the provate member variable
    std::cout << test.i << '\n';
}

// you can also declare another class to be a friend of a class, this means they get the same unlimited access

class Example{

    public:
        void print(const auto& test){
            std::cout << test.s;
        }
};

// some c++ programmers dislike friend because it reduces encapsulation
// we can create a member function in our class that can perform the same functionality that the friend class does

int main(){

Test test;

print(test);
Example ex;
ex.print(test); //accessed via the friend class

}