# include <iostream>
# include <string>

//  Structural patterns are all about setting up the structure of your application so as to improve SOLID conformance as well as general usability and refactorability of your code
//  Inheritance: an object automatically acquires the nonprivate fieldsand functions of its base class or classes.To allow instantiation, the object must implement every pure virtual member from its parents; if it does not, it is abstractand cannot be created (but you can inherit from it)
//  Composition: generally implies that the child cannot exist without the parent.Think of an object having members of owner<T> type: when the object gets destroyed, they get destroyed with it
//  Aggregation: an object can contain another object, but that object can also exist independently.Think of an object having members of type T* or shared_ptr<T>.

// Adapter pattern: we are given an interface, but we want a different one, and building an adapter over the interface is what gets us to where we want to be
// maybe sure that you have at least two classes with incompatible interfaces
// adapter is a special object that converts the interface of one object so that it can be understood by another. This prevents us from having to go back and change other code to retrofit, in line with SOLID open closed principle

/* Adapters can not only convert data into various formats but can also help objects with different interfaces collaborate. Here’s how it works:

The adapter gets an interface, compatible with one of the existing objects.
Using this interface, the existing object can safely call the adapter’s methods.
Upon receiving a call, the adapter passes the request to the second object, but in a format and order that the second object expects.*/

// the target defines the domain specific interface used by the client code
struct Target {
	virtual std::string Request() {
		return "Target: the default targets behaviour";
	}
};

// the adaptee contains some useful behaviour but its interface is incompatible with existing client code
// the adaptee needs some adaptation before the client code can use it
struct Adaptee{
	std::string specificRequest() const {
		return ".eetpadA eht fo roivaheb laicepS";
	}
};

// adapter makes the adeptee's interface compatible with the targets interface

struct Adapter : public Target {
private: 
	Adaptee* adaptee_; // pointer to adaptee object as a private member

public:
	Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}; // constructor is passed in a pointer to an adaptee function
    
	std::string Request() override  {
		std::string to_reverse = this->adaptee_->specificRequest(); // store the string to reverse by calling the adaptee's fucntion via the member pointer of Adapter
		std::reverse(to_reverse.begin(), to_reverse.end());
		return "Adapter: (Translated) " + to_reverse;
	}
};

// client code supports all classes that implement the target interface
void clientCode(Target* tar) {
	std::cout << tar->Request();
}

// binary compatibility -> Binary-code compatibility (binary compatible or object-code-compatible) is a property of a computer system, meaning that it can run the same executable code, typically machine code for a general-purpose computer Central processing unit (CPU), that another computer system can run.

// "Pointer to implementation" or "pImpl" is a C++ programming technique that removes implementation details of a class from its object representation by placing them in a separate class, accessed through an opaque pointer
// this can speed up compile times as instead of changing the header file and then having every client recompile it, we can just change the implementation in a source file and only that source file needs recompiling

// pimpl is a specific illustration of the bridge design pattern
// Bridge is a structural design pattern that lets you split a large class or a set of closely related classes into two separate hierarchies—abstraction and implementation—which can be developed independently of each other.
// Bridge allows us to seperate the abstraction from the implementation, this is a design mechanism that encapsulates an implementation class inside of an interface class

// for example, take our rendering struct
struct Renderer {
	virtual void render_circle(float x, float y, float radius) = 0;
};

struct Shape {
protected:
	Renderer& renderer; // reference to a renderer object, this is the bridge we build
	Shape(Renderer& renderer) : renderer(renderer) {}

public:
	virtual void draw(){}
	virtual void resize(float factor){}

};
// we can now create an implementation of the shape class, supplying the information required
// The Bridge is a rather simple concept, serving as a connector or glue, connecting two pieces together.The use of abstraction(interfaces) allows
// components to interact with one another without really being aware of the concrete implementations.
// That said, the participants of the Bridge pattern do need to be aware of each other’s existence.



int main() {
	std::cout << "Client : I can work just fine with Target objects \n";
	Target* tar = new Target;
	clientCode(tar);

	std::cout << "\n";
	Adaptee* adaptee = new Adaptee;
	std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
	std::cout << "Adaptee: " << adaptee->specificRequest();

	std::cout << "\n";
	std::cout << "Client: but I can work with it via adapter \n";

	Adapter * adapter = new Adapter(adaptee); // create a pointer to a new adapter object, pass in the adaptee pointer
	clientCode(adapter);

}