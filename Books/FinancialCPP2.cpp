# include <iostream>
# include <cstdlib>
# include <vector>
# include <algorithm>
# include <numbers>
# include <cmath>

class PayOff {  // does almost nothing
public:
	PayOff() {}
	virtual double operator() (double Spot) const = 0;  // pure virtual function, this class can never be instantiated
	virtual ~PayOff(){}  // any polymorphic class using virtual should always have a virtual destructor
	virtual PayOff* clone() const = 0;  // clone function, virtual copy constructor
};
// clone fucntion causes the object to create a copy of itself and return the copy
// return type of the clone function will be changed in the inherited classes, generally you can override the rule that virtual function return types must be teh same if you change the return type tfrom a pointer to base to a pointer to child, since the child pointer can always be converted to a base pointer

// we can say the call payoff is a type of payoff, this 'is a' relationship is represented via inheritance
class PayOffCall : public PayOff {
public:
		PayOffCall(double Strike_);
		virtual double operator() (double Spot) const;
		virtual ~PayOffCall() {}
		PayOffCall* clone() const;  // acceptable in this consition to change return type from pointer to base to pointer to child in child
private:
	double Strike;
}; 

// the compiler will accept a PayOffCall object wherever it expects a PayOff object
// private data in PayOff will not be reachable in PayOffCall
// private data is useful because we encapsulate what the base class does

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_){}

double PayOffCall::operator() (double Spot) const {
	return std::max(Spot - Strike, 0.0);
}

PayOffCall* PayOffCall::clone() const
{
	return new PayOffCall(*this);
}

class PayOffPut : public PayOff {
public:
	PayOffPut(double Strike_);
	virtual double operator() (double Spot) const;
	virtual ~PayOffPut() {}
	PayOff* clone() const;
private:
	double Strike;
};

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_) {}


double PayOffPut::operator() (double Spot) const {
	return std::max(Strike - Spot, 0.0);
}

PayOffPut* PayOffPut::clone() const
{
	return new PayOffPut(*this);
}
// the call to clone() is a call to the copy constructor of the object, as the this pointer always points to the object being called

// the operator() function is now virtual, this means its address is bound at runtime instead of compile time
// the compiler adds extra data to each child object which specifies which function should be used, virtual functions are fancy way of using function pointers

/* This virtual function table is a list of addresses to be
called for the virtual functions associated with the class. So if when running a
program, a virtual function is encountered, the table is looked up and execution
jumps into the function pointed to. Note that this operation takes a small amount of
time so efficiency fanatics dislike virtual functions as they cause a small decrease in
execution speed. Note also that the amount of memory per object has also increased
as the object now contains a lot of extra data */

// since we have a pure virtual function in PayOff, PayOff can now only be passed by reference, and not by value, since they cannot be instantiated

// we can pass in a reference to an inherited class where the compiler is expecting a reference to a base class
// similarly, if we have a pointer to a inherited object, we can always cast it into a base class object without issue

// if you have a custom destructor, you generally need an custom assignment operator and custom copy constructor aswell

// using new should be avoided in time critical pieces of code!


// Move onto Binomial Tree:
/* s. The point of view we adopt is that a tree is
a method of approximating the risk-neutral expectation. In particular, we assume
that we are pricing a derivative on a stock following geometric Brownian motion
with a constant volatility σ.

When we price on a binomial tree, we divide time into steps and across each step
we assume that the underlying Brownian motion can only move a fixed amount up
or down

However, the purpose of a tree is not to price a European option; there are lots of
better ways of doing that, including analytical solutions and numerical integration.
The reason trees were introduced was that they give an effective method for pricing
American options. The analysis for an American option is similar except that the
value at a point in the tree is the maximum of the exercise value at that point and
the discounted expected value at the next time. This corresponds to the optimal
strategy of exercise if and only if exercise gives more money than not exercising.

 The tree really has two aspects: the placement
of the nodes of the tree and the computing of the option value at each of the nodes.
Whilst we could further orthogonalize and define separate classes for each of these,
we write a single class to do the binomial tree which takes in an option as an
argument. An important point to note is that as the placement of the nodes does
not depend upon the option, we can save ourselves time if we want to price several
options by placing the nodes once and then pricing all the options on the same tree.
Given this fact, we design our tree class in such a way that the tree is built once,
and then any option can be valued on the tree via a separate method.
*/

// lets create an abstract base class to define an interface for the products we can value on trees

class TreeProduct {
public:
	TreeProduct(double FinalTime_);
	virtual double FinalPayOff(double Spot) const = 0;
	virtual double PreFinalValue(double Spot, double Time, double DiscountedFutureValue) const = 0;
	virtual ~TreeProduct(){}
	virtual TreeProduct* clone() const = 0;  // method used to return a copy of the object
	double GetFinalTime() const;  // will read up the only data member of the class

private:
	double FinalTime;  
};

TreeProduct::TreeProduct(double FinalTime_) {
}

double TreeProduct::GetFinalTime() const {
	return FinalTime;
}

// what we would like is a pay-off class that has polymorphic features while taking care of its own memory management
// this can be done with a templated wrapper class or using the bridge pattern
// bridge pattern implemented by taking the vanillaoption class and removing the Expiry member and the GetExpiry() function so we're left with a class that stores a pointer to an option pay-off and takes care of memory handling
/*
class PayOffBridge {
public:
	PayOffBridge(const PayOffBridge& original);  // copy constructed
	PayOffBridge(const PayOff& innerPayOff); 
	inline double operator() (double Spot) const;
	~PayOffBridge();
	PayOffBridge& operator= (const PayOffBridge& original);

private:
	PayOff* PayOffPtr;
};

inline double PayOffBridge::operator() (double Spot) const 
{
	return PayOffPtr->operator() (Spot);
}

PayOffBridge::PayOffBridge(const PayOffBridge& original)
{
	PayOffPtr = original.PayOffPtr->clone();
}

PayOffBridge::PayOffBridge(const PayOff& innerPayOff)
{
	PayOffPtr = innerPayOff.clone();
}

PayOffBridge::~PayOffBridge()
{
	delete PayOffPtr;
}

PayOffBridge& PayOffBridge::operator= (const PayOffBridge& original)
{
	if (this != original)
	{
		delete PayOffPtr;
		PayOffPtr = original.PayOffPtr.clone();
	}
	return *this;
}
*/

int main() {
	std::cout << "insert payoff" << std::endl;
	int n;
	std::cin >> n;
	std::cout << "insert strike" << std::endl;
	double strike;
	std::cin >> strike;

	PayOff* ptr;

	if (n == 0) {
		ptr = new PayOffCall(strike);
	}
	else {
		ptr = new PayOffPut(strike);
	}
	delete ptr;
	/*  At this
point we must be careful: we have a pointer to a base object, so which destructor
will it call? If the destructor is not virtual then it will call the base class destructor. If the object is of an inherited class this may cause problems as the object will
not be destroyed properly. For example, if the inherited class object had an array as
a data member then the memory allocated for that array will never be deallocated.
In our case, the base class is abstract and there cannot be any objects of its type.
This means that calling the base class destructor must be an error. For this reason,
we declare the destructor virtual. The compiler then uses the virtual function
table to correctly decide which destructor to call. In fact, many compilers issue
a warning if you declare a method pure virtual and do not declare the destructor
virtual */

}

// if we don't want to make a class copyable or assignable, we can declare the copy constructor and assignment operator private
// this means that only code within the class can call these methods, so they cannot be copied or assigned by any external code


// the inherited class implements the interface defined by the base class