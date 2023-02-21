# include <iostream>

// constructors get called automatically when an object of a class is created
// when a class with uninitialed or undefined data members is created, there members are given random garbage values
// we can actually initialise data members in the class definition
// its best to do this, as we don't want any undefined behaviour

class internet{
    public:
        void connect(){ std::cout << "Connected to internet";
        }
        void login( const std::string& id, const std::string& pw){
            std::cout << "Logged on with username " << id;
            std::cout << " and password " << pw;
        }
};

class refrigerator{
    int temperature {2};
    bool door_open {true};
    bool power_on {true};
    internet Internet; // you can create an object of a class in the definition of another class
    // an internet object will automatically be created when a refrigerator object is instantiated, the internet object is a data member of the refreigerator object

    public:
        void print(){
            std::cout << "temperature = " << temperature << std::endl;
            std::cout << std::boolalpha;
            std::cout << "door_open = " << door_open << std::endl;
            std::cout << "power_on = " << power_on << std::endl;
        }

void init(const std::string& id, const std::string& pw){  //  const used here with & of data type so that we don't make any changes to the parameter we pass in, and don't make any copies (hence the &)
// create a function to initalise the members of the internet class belonging to the refrigerator
    Internet.connect();
    Internet.login(id,pw); // better than making each constructor do this, DRY!
}
     // default constructor
     refrigerator(){
         init("me","secret"); // pass in the default values to the init function
     }

     // constructor using default login
     refrigerator(int temperature) : temperature(temperature){
         init("me","secret");
     }
     //constructor using default temperature
     refrigerator(const std::string& id, const std::string& pw){
         init(id,pw);
     }
     // constructor with no defaults
     refrigerator(int temperature, const std::string& id, const std::string& pw): temperature(temperature){
         init(id,pw);
     }




};

int main(){

    refrigerator fridge;
    fridge.print(); // prints the default values

    refrigerator fridge2(15,"ahus","cuzzy");
    fridge2.print();
}