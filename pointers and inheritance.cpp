# include <iostream>

//normally, a pointer must point to a variable of the same type
// however a pointer to a base class can point to any object in the same hierarcy
// however, the reverse is not true, we cannot have a pointer of child type pointing to a parent class, its only base class downwards

class shape{
    public:
    virtual void draw() const{ std::cout << "drawing generic shape" << std::endl; //  making the function virtual forces the program to decide to call the circle version of draw when we call it using a pointer to circle, as circle is its dynamic type
        }  // virtual means dynamic type gets executed

};

class circle : public shape{
    public:
        void draw() const { std::cout << "drawing a circle" << std::endl;    // fucntion we're overriding must have the same signature (arguments), none in this case
        }
        void area() const { std::cout << "Calculating area of a circle" << std::endl;
        }



};

class triangle : public shape{
    public:
        void draw() const{ std::cout << "oww pointy!" << std::endl;  // draw function will not modify any memver variables of teh class, because its const placement
        }
};     // remember that const applies to the thing left of it. If there is nothing on the left then it applies to the thing right of it.
//

void draw_shape(const shape& s){ // srgument is a reference to a shape
s.draw(); // calls draw member function of circle etc...
}  // so because draw was declared virtual in the shape base class, whatever child class we pass into this function, teh draw function for that class will be used

// remember that the draw() function must be const because we're passing it a const object, reminder:
/* const T& get_data() const { return data_; }
   ^^^^^
means it will return a const reference to T (here data_)

Class c;
T& t = c.get_data()             // Not allowed.
const T& tc = c.get_data()      // OK.
const T& get_data() const { return data_; }
                    ^^^^^
means the method will not modify any member variables of the class (unless the member is mutable). */

int main(){

circle circ;

shape * ptr = &circ; // this is valid, a base class pointer pointing to a derived class
// this works because the memory of a derived class contains an object of the base class in it
// however a base object may not necessarily be part of a derived object
// hence a circle to a shape makes no sense

ptr->draw();  // compiler sees that pshape is a pointer to the base class, so it uses the draw() function defined by shape
//ptr->area(); // doesnt work, compiler still thinks pshape is pointed to shape

// we can call any public member fucntion of shape on ptr, this will call shape's version of the function
// we cannot call any public member functions of circle, even though the object is really a circle
// this is because the compiler sees ptr as pointing to a shape object
// to do object oriented programming, we need to be able to use ptr as a pointer to a circle

circ.draw();   // this will work, not using a pointer rather, just accessing member directly

// to recap, ptr is declared as a pointer to shape, ptr is the address of a circle object, it is simultaenously both of these things
// in c++, variables have two different kinds of type, static and dynamic type
// the static type is the type used in the variable definition

//int x {5}; // static type int
//int * px = &x; // static type pointer to int
//circle circ2; //static type circle
//circle& pcirc = circ2; // static type reference to circle
//// shape * pshape = &cicle // static type pointer to shape
// shape& rshape = circle // static type reference to shape

//// the dynamic type is the type of the variable that is actually used in memory, for most objects, this will be the same as the static type
//int x {5}; // dynamic type int
//int * px = &x; // dynamic type pointer to int
//circle circ2; //dynamic type circle
//circle& pcirc = circ2; // dynamic type reference to circle

// however, it can be different for a pointer or reference to base class

// shape * ptr = &circle;   // dynamic type pointer to circle
// shape& rshape = circle; // dynamic type reference to circle

// c++ almost always uses static typing, type checking and function call resolution is done by the compiler, less runime overhead, better optimisation
// the dynamic type is only used for a pointer or reference to a base class, the compiler does not decided which member function to call, instead the member function is chosen at runtime using th eobject in memory

// to use the dynamic type, we need to declare the member function to be virtual in the base class
// now when we call it through a pointer or reference to teh base classs, the dynamic type of the object will be used

// virtual functions:
// normally when we call a member function of an object, the compiler will decide which function is called, this is done using the static type of the object
// this decision is made at compile time, this is known as static binding

// however there are some cases where the compiler does not make the decision
// instead, it generates some code which is used to make the decision
// the program will use this code to decide, at run time, which function to call
// it will use the dynamic type of the object, this is known as dynamic binding

// two conditions must apply for dynamic binding to occur:
// a member function is called through a pointer or reference to a base class
// the member function was declared virtual in the base class

//to make a member function virtual, we put the virtual keyword before its decleration in the base class
// the virtual member function will be inherited in all sub-classes, we do not need to write "virtual" again
// a child class which redefines a virtual function is said to override it

circle circ2;         // derived class object

shape& rshape = circ2;   // reference to base class, bound to a circle object
rshape.draw(); // use dynamic binding to call circle::draw(), this is doable because the draw member function in shape class is virtual

// virtual functions solve the problem with function call arguments
// we pass a reference or pointer to the base class
// the version for the dynamic type of the object will be called
triangle t;  // we can see this with the triangle here
draw_shape(t);

}