# include <iostream>

// a child class inherits all the non private member functions of its parent class
// a child class can re-implement the parents class member functions, to make the more appropriate for the child


// a public memebr of a class is accessible from any part of the code, it is part of the class's interface
// a child class will have access to all its parents public members
// a child class does not have access to its parents private members
// often we want to write member functions which are not part of the class's public interface, but are available to the child classes
// a parent class can make its members available to its children, but not to other code, this means encapsulation (implementation details hidden from the outside world) and is done via the protected access specifier

class vehicle {

      protected:
        void secret(){
            std::cout << "I love you iddy!" << std::endl;
        }
    public:
        void start(){
            std::cout << "start the engine" << std::endl;
        }

       void accelerate(){
            std::cout << "zoom!" << std::endl;
        }
};

class aeroplane : public vehicle {
    public:
        using vehicle::accelerate; // have to do this without parenthesis! // have to put this above the overloaded version
        void start() {
            vehicle::start(); // child class can also call the parents public functions in its own class
             vehicle::secret();  // protected, so can access it in here within the child class
            std::cout << "spin up the turbines!" << std::endl;
        }

       void accelerate(int height){  // overloaded inherited member function, we write a new member function with the same name but a different signature
            std::cout << "accelerate until we reach " << height << std::endl;
        }

        // void accelerate(){ vehicle::accelerate();} call parent version of accelerate(), bad practice
};

int main(){

    aeroplane plane;
    plane.start(); // can use the inherited public function, but we've edited it to suit an aeroplane

    //plane.secret(); // doing this doesnt work, can only be called from within the class, or its derived class because its protected
    plane.accelerate(100);

//    plane.accelerate();  // however now this does not work
    // if we overload an inherited function in the child class, it will hide all the other inherited member functions with that name
    // those functions cannot be called on the child class, as above doesnt work
    // this is inconsistent with OO design principles, the parent class represents the face of the hierarcy, child classess should extend the interface, not obscure it
    // we could get around this by going into teh child class and define the inherited function ourselves
    // so in the commented function in aeroplane, we could define these so that the parents version is called manually, but this is poor pratcice, as we should always avoid repeating code

    // from c++11, we can tell the child class to use the parents version, this will make all the hidden versions of the function avaailable in teh child class when we've overwritten it

   plane.accelerate();
}

