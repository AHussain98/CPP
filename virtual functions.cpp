# include <iostream>

// a child class can define a member function with the same name as a virtual member function in the parent class
// override : same signature (arguments) as the parent, circle and triangle override the virtual draw() member function
// overload : different signature (arguments) from parent (regarded as a different function), prevents dynamic binding, may hide the parents member function, have to put in a using directive to use parents version
// it is easy to overload by mistake

// c++11 intorduced the override keyword
// we can add this to the definition of a member function in a child class
// void draw() const override; // child class overrides shape::draw()
// the compiler will check whether this member function overrides a virtual member function in the parent class
// the compiler will give an error if the function does not override
// use this as a check, for fucntions we want to override


class shape{
    public :
        virtual void draw() const {std::cout << "drawing generic shape" << std::endl;
        }
};

class circle final : public shape {
    public:
        void draw() const override {std::cout << "drawing a circle" << std::endl; // override here will check we're doing this correctly
        }
};

//class newcircle : public circle {      cannot derive! circle is final
//};


int main(){

circle circ;
circ.draw();

// its recommended to use the override keyword everytime we're using an overrided inherited virtual function

// c++11 also introduced the "final" keyword, a final class cannot be derived from. a final member cannot be overridden in a child class
// libraries often use final, the library can provide a class hierarchy, or use one internally, users of the library cannot extend this class hierarchy
}