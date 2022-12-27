class Vehicle{
    
	protected:       //useable by this class and any derived classes
		int tyres;
		string colour;
        
    public:	
	  virtual void print() {   //made virtual as we'll be overwriting this
		     cout << "Colour is: " << colour << endl;
		    cout << "Tyres: " << tyres << endl;
        }
        
        void setInitials(int tyres, string colour){
              this->tyres = tyres;
              this->colour = colour;
        }
	
    virtual void price() = 0; //purely virtual function, the derived class also needs a price function now otherwise an error will occur
    //any class containing a purely virtual function can never be instantiated, so class vehicle can never be instantiated, only its derived classes
    //so we can never create a vehicle object
};     

//if the vehicle class had a constructor, when we called the car class, the car object would also call the vehicle constrcutor, as well as the car constructor, as the car class inherits from the vehicle class, its constrcutor is called upon the car class instantiation

class Car : public Vehicle{   // this means that everything that was public in Vehicle should also be public in the Car class, but the Vehicle members that were private/protected will remain private/protected, there's no change there
	public: 
    string make;
	int numGears;
    
	void print(){
		cout << "Car make is: " << make << endl;
        cout<< "Car colour is: " << colour << endl;
		cout << "Tyres: " << tyres << endl;
		cout << "Number of gears: " << numGears << endl;
        
	}
    
     Car(string make) {
        this->make = make;
    };
    
    Car() {
        cout << "default car constructor" << endl;
    }
    void price(){
        
    }
};

class Audi : public Car{
    public:
        string make = "Audi";
        Audi(int x, int y, string z){
            cout << "this is audi's constructor" << endl;
              this->numGears = x;
              this->tyres = y;
              this->colour = z;
       
        }

 void print(){
		cout << "Car make is: " << make << endl;
        cout<< "Car colour is: " << colour << endl;
		cout << "Tyres: " << tyres << endl;
		cout << "Number of gears: " << numGears << endl;
    }
    
    void price(){
        
    }
};


//       you can also create derived classes that have initalisation lists for the constrcutors of the classes they inherit from
                                         
                                         
                                         
//   single inheritance -> one class inherits form one base class
//   multi-level inheritance -> c inherits from b, who inherits from a, as above where audi inherits from car which inherits from vehicle
//   hierarchical inheritance -> multiple classes inherit from one base, e.g. vehcile class is base class for car, bike and truck classes
//   multiple inheritance -> multiple base classes that a child class inherits from