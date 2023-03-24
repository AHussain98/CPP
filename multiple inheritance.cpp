# include <iostream>

// in multiple inheritance, a derived class has more than one parent
// multiple inheritance is controversial, adds complexity, many programmers and OO designers dislike it, some languages do not support it
// in multiple inheritance, a derived class has more than one parent, this represents a class which is a combination of different entities

// a derived class object is stored in memory as the base class objects followed by the derived class part
// the base class objects are stored in the order they were listed
// the base class's constructor are called in the order they were listed, then the derived class's constructor is called
// the destructors are called in the reverse order of the constructors

// the derived class inherits all the memebrs of its parents, provided they were declared as public or protected
// if we call an inherited member function, its name must only be defined in one parent
// this can be avoided by declaring which version should be called by prefacing the decleration in the child class definition with the name of teh parent that you want to inehrit from
// so just add a forwarding function to the child class

// there can be an issue when both parent classes inherit from teh same base class (diamond problem)
//  e.g. imagine a sales manager class that inherits from a sales employee and manager class, which both inherit from an employee class
//  this means a sales manager object will contain a sales_employee object and a manager object, each of these objects contains a seperate emplyee object
// this is undesirable, the sales amanager represents a unique employee

class employee{
    public :
        void address(){ std::cout << "employee address: " << static_cast<void *>(this) << std::endl;}
};

class sales_employee : public virtual employee{
};

class manager : public virtual employee{
};

class sales_manager : public sales_employee, public manager{
};

int main(){

sales_manager sm;
std::cout << "cast to sales_employee \n";
sales_employee* se{static_cast<sales_employee *>(&sm)}; // create a pointer to a sales employee object by casting the sales manager object
std::cout << "cast to manager \n";
manager* m{static_cast<manager*> (&sm)}; // so the same for the manager object within sm
se->address();
m->address();
// this shows that they're at different addresses within the same object

// this can be solved by making sales_emplyee and manager use virtual inheritance from employee
// this makes employee a virtual base of salesemplyee and manager
// the sales emplyee and manager parts of a sales manager object will now share a single employee object
// sales manager is deifnes as usual

//so sales_employee class declaration should become class sales_employee : public virtual employee {
// and same for manager class declaration
// if we do that, the addresses will print out the same
// so then sales_employee and manager both contain the same employee object

}