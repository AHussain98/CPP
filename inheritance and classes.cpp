# include <iostream>

// programmers often work with entities which are related or represent similar concepts
// a class hierarchy can express these relationships, making it easier for related classes to reuse code
// an example is input streams, istream is a basic input stream from which specialised ifstreams and istringstream are derived
// the class at the top of the hierarchy represents the most general or most basic veriosn, this is known as teh base class (istream for example for input streams)
// classes below are known as derived classes or subclasses, they inherit form the base class, they are more specialized or enhanced versions of the base class
// ifstreama nd istringstream derive from istream
// relationship between classes at different levels in the hierarchy is called inheritance
// inheritance models an is-a type of relationship between classes
// istringstream is a kind of istream


class vehicle{
int max_speed;

public:
    vehicle(int max_speed) : max_speed(max_speed) { // constructor
    std::cout << "Vehicle constructor" << std::endl;
    }

    vehicle(){
        std::cout << " default vehicle constructor" << std::endl;
    }

};

class aeroplane : public vehicle {
    protected:
    int max_speed;
    int max_height;

 // derived class defined by putting a colon after the name
// derived class is able to call the non private member functions and data members of the base class
// derived class can also replace the base classes member functions with its own verisons
 public:

  //   aeroplane(int max_speed, int max_height) : vehicle(max_speed), max_height(max_height) { // derived class constructor calls the base class's constructor to initialise the base class part of the object, same initializer syntax as for a class member
  //   std::cout << "speed and height Aeroplane constructor" << std::endl;
  //   }

     aeroplane(int max_speed, int max_height) : max_speed(max_speed), max_height(max_height) { // derived class constructor calls the defualt constructor of the base class, as defined above
     std::cout << "speed and height Aeroplane constructor" << std::endl;
     }

     aeroplane(){  // this will be called in case we don't provide a specific base class constructor when calling the jet constructor
         std::cout << " default Aeroplane constructor" << std::endl;
     }


};

// a derived class object is stored in memory as a base class object followed by teh derived class part
// whena  derived class object is created, the base class's constructor is called first, then the derived class's constructor
// when it is destroyed, the derived classes destructor is called before the base classes

// we can even use a derived class as the base class of another derived class

class jet : public aeroplane {

    int max_speed;
    int max_height;

    public:

     //   jet(int max_speed) : max_speed(max_speed) { // default aeroplane constructor called here
     //       std::cout << "wheeee" << std::endl;
     //   }

       // jet() {  // default aeroplane constructor called here
       // std::cout << "default jet Wheeeee" << std::endl;
              //  }

        jet() : aeroplane(max_speed, max_height){ // specific aeroplane base class constructor called here
        std::cout << "specific jet wheeee" << std::endl;
        }

        jet(int max_height, int max_speed) : max_height(max_height), max_speed(max_speed) {   // default aeroplane constructor called
            std::cout << "jet defined its variables itself!" << std::endl;
        }

        void print() {
          //std::cout << "did it!";
           std::cout << max_speed << " " << max_height << std::endl;
        }
};

//   All that’s happening is that the Derived constructor is calling a specific Base constructor to initialize the Base portion of the object.
//   because max speed and height live in the base class, the base constructor is the only constructor that can initialise these values
// When constructing a derived class, the derived class constructor is responsible for determining which base class constructor is called. If no base class constructor is specified, the default base class constructor will be used.
// In that case, if no default base class constructor can be found (or created by default), the compiler will display an error. The classes are then constructed in order from most base to most derived.


int main(){

  //  aeroplane biplane(50,50); // calls both constructors

    jet sleek; // all 3 constructors called

   sleek.print();

   // jet test;
  //  test.print();

   // jet specific(200,200);
   // specific.print();

   jet test(200,200);
   test.print();
}