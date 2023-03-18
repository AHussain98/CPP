# include <iostream>

// typically base classes model abstract conecpts like vehicle, derived classes model concrete entities such as aeroplane
//  the base class i sthe interface to the class hierarchy
// its the public virtual member functions that provide all the functionality that is common to the hierarchu, any shaoe object can be drawn, modeled etc...
// the derived classes override these fucntions, they implement this interface in a concrete way specific to each child class, a cricle object draws a circle shape etc...
// often, the base class's virtual member functions cannot do anything useful, (how do we draw a generic shape?) each derived class will implement teh functionality as appropriate
// these member functions can be left epty or we can use c++ syntax to indicate they are not implemented here but in specific derived classes
// this helps express the idea of a base class as an interface to the class hierarcy
// we can do this by making the base class's virtual functions "pure virtual", this is done by pytting =0 instead of the function body


class shape{
    public:
        virtual void draw() = 0; // draw() is a pure virtual function


};

class triangle : public shape{
    public:
        void draw() override {
            std::cout << "draw a triangle!" << std::endl;
        }
};

class shape_ordinary{
    public:
         virtual void draw_shape() const {    // standard virtual function, made const because we don't want it to modify the calling object
            std::cout << "shape::draw_shape()" << std::endl;
        }

};

class circle : public shape_ordinary{
    public:
        void draw_shape() const override { // where you place const matters, it always applies to whats on teh left of it unless theres nothing there, then it applie to teh right, so if override and const are switched then this wont complie
            std::cout << "draw a circle!" << std::endl;  // override the virtual function
        }

};

// this means that the shape class does not implement draw()
// it makes it clear that the virtual function is not part of the implementation of the base class
// a class with a pure virtual member function cannot be instantiated
// the class shape is now known as an abstract base class, also called an interface
// if we derive from an abstract base class, we must override all its pure virtual functions, otherwise our derived class will also be an abstract base class

// remmember in c++ if you don't pass something by reference or by address(pointer), the copy constructor will be called
// if we have a function that takes a base class object by value and we pas a derived class object to it
// it calls the copy constructor of the base class, the derived part of the argument has been sliced off
// this is known as object slicing

// function taking base class by value
void draw_shape_global(shape_ordinary s){
    s.draw_shape();  // will always call shape_ordianry's draw()
}

int main(){

// shape s1; //can't do this, can't instantiate an abstract base class!

 //  triangle t1; // we can create this because we've overwritten the pure virtual function, if we didn't, the triangle class would become an abstract base class that we couldnt instantiate
//   t1.draw();

 circle c1;
 draw_shape_global(c1); // pass derived class by reference
 // this calles the draw() member function of the shape class because the copy constructor is called, teh dynamic type of teh object is also shape
 // we can fix this by changing the function so we pass by reference instead, no copy constructor is called, so function args should be (const shape& s)
 // this way, the derived part of the object is not sliced off and the correct fucntion is called
 // an abstract base class cannot be passed by value, because we cannot declare a parameter of abstract type
 // it can only be passed by reference or address, in the function body, dynamic binding will be used to call the correct function
}

// member function implementation:
// member functions are not stored in the object, they are implemented as global functions, when they are called, a ponter to the object is passed as an extra argument called "this" which is a pointer to the object the member function was clled on
// virtual member function implementation:
// when the compiler encounters a class which has a virtual member function, it creates and populates a data structure
// this is teh class's virtual member function table, also known as vtable
// when the compiler sees a call to a virtual member function, it generates some extra code which is executed at runtime, it checks the dynamic type of the object and uses teh vtable to call teh correct version of the function
// when a virtual member function is called, the compiler replaces the name of the function by teh corresponding index in the vtable
// the runtime code will determine the objects dynamic type, locate the vtable for that dynamic type, look up the element in the vtable and dereference the function pointer and call it
// there is some overhead to using virtual member functions, calling a virtual member fucntion takes longer than for a non virtual one and takes extra memory, each class that has a virtual member fucntion needs a vtable an a pointer is needed for each virtual member fucntion in teh class
// only use virtual member functions when teh extra flexibility is required

// in programming, polymorphism means that different types have the same interface, the same behaviour
// STL containers are an exmaple of polymorphism, vector<int> is different from vector<string> but they have the same interface
// This is known as parametric polymorphism, because the element is a parameter of the vector

// the classes in an inheritance hierarchy have the same interface, shape, triangle and circle all have a draw() member fcuntion
// this is known as subtype polymorphism
// an object of a type can be replaced by an object of its subtype, liskov substitution principle, fundamental concept in oop

// polymorphism is a very useful programming technique
// when we have related types, we can write one set of code which handles all of them and avoids duplaicated code
// we can add new types without having to write extra code to handle them, saves the programmer time
// however it still respects the individual properties of a particular type

// in c++, subtype polymorphism is implemented using pointers or references to the base class and calling virtual functions on them
// this allows us to use the same code to handle different classes, but still keep type safety

// subtype polymorphism : run-time overhead, may require memory management, no control over child classes, can result in large, unmaintainable inheritance heirarchies
// parametric polymorphism : compile time binding, no run-time overhead, no memory allocation, more control over which types are instantiated

// inheritance is often overused, many problems are better solved by composition
// the trend in c++ is away from subtype polymorphsim towards parametric polymorphism
// only use inheritance if you need a is-a relationship