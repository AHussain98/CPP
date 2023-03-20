# include <iostream>
# include <memory>

// polymorphism is when we use a base class object to represent a derived class object, in c++ this requires using either a pointer or a reference
// we can use unique_ptr instead of calling new() explicitly

// std::unique_ptr<Base> pbase {std::make_unique<Derived>()};
// this allocated memory will be managed by unique_ptr
// pbase cannot be initialised, pbase cannot be aliased, overwritten or invalidated
// pointer arithmetic on pbase is not allowd, delete is used automatically on an exception and pbase cannot be accidentally used again after deletion

// programmers often call a function to create a new object
// the function decides the type of the new object and returns a pointer to it
// this is known as the factory pattern, useful when working with class heirarchies, can create a child class object and preturn it through pointer to base
// advantages of factory pattern:
// all the code to create objects in the heirarchy is in a single place
// flexibility - can use arguments to choose which child class type to create
// easy to extend if new child classes are added

// we can implement the factory pattern with a unique_ptr
// create an appropriate unique_ptr as a local variable, this will allocate memory and store a pointer to it
// return teh unique pointer from the function
// the unique pointer will be moved into the functions return space, then it will be moved into a variable in the caller
// the caller's unique_ptr will automatically release the memory when it goes out of scope

// there are two ways to create a unique_ptr object:
// you can call the move constrcutor with the return value from make_unique() which calls new() internally    (reccommended)
// or call the constructor with a traditional pointer as argument, the object will adopt this pointer
// the constructor could be given any pointer, not just the one which represents allocated memory
// we could use unique_ptr as a generic class for managing resources
// however, unique_ptr's destructor calls delete
// this will be disastrous if the pointer was not returned by new, so if we used  apointer to a stack object, for example
// however, unique_ptr does provide for this, we can can provide a "deleter"
// this is a callable object, it will be invoked by the destructor instead of delete
// the managed pointer is passed to the deleter, the deleter then releases the resrouce as appropriate.

// the deleter is part of the unique_ptr's type, we need to give the deleters type as an optional template parameter
// so we add the type of the deleter to the template parameters, and pass the deleter to the constructor of the unique_ptr object

// decltype is similar to auto, but it takes an exxpression, we can use it to get the type of lambdas





class shape{
    public:
        virtual void draw() const = 0;
        virtual ~shape() = default;
};

class circle : public shape {
     public:
         void draw() const { std::cout << "drawing a circle" << std::endl;
         }
};

class triangle : public shape {
    public:
          void draw() const { std::cout << "drawing a triangle" << std::endl; }

};

class square : public shape {
    public:
          void draw() const { std::cout << "drawing a square" << std::endl; }

};

// factory function using unique_ptr

std::unique_ptr<shape> create_shape(int sides){
    // the returned unique_ptr will be moved into the function's return space
    if (sides == 1){
        return std::make_unique<circle>();  // create 1 sided shape
    }
    else if (sides == 3){
        return std::make_unique<triangle>();  // create 3 sided shape
    }
    else if (sides == 4){
        return std::make_unique<square>(); // create 4 sided shape
    }
    else {
        std::cout << "cannot create a shape with " << sides << " sides" << std::endl;
         return nullptr;
    }
}

// factory function using standard pointer

shape* previous_create_shape(int sides){  // returns pointer to base class object
    // the returned pointer is copied into the return space
    if (sides == 1){
        return new circle;  // create 1 sided shape
    }
    else if (sides == 3){
        return new triangle;  // create 3 sided shape
    }
    else if (sides == 4){
        return new square; // create 4 sided shape
    }
    else {
        std::cout << "cannot create a shape with " << sides << " sides" << std::endl;
         return nullptr;
    }
}

int main(){
     // the returned unique_ptr will be moved into a variable
     auto pshape{create_shape(4)};
     pshape->draw();


     // donw the old way
     shape * prev_ptr = {previous_create_shape(1)};
     prev_ptr->draw();

     delete prev_ptr;
}