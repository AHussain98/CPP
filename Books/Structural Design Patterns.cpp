# include <iostream>
# include <string>
# include <vector>

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

// Composite
//  Essentially, we try to give single objects and groups of objects an identical interface.
// take for example, a simple object we want to render graphically and an object composed of a group of objects that we also want to render, the composite pattern will make it so that we can do both with the same interface
// 

struct GraphicObject {
	virtual void draw() = 0;  // interface, pure virtual class, cannot be instantiated
};

struct Circle : public GraphicObject { // simple single object
	void draw() override {
		std::cout << "draw a circle!" << std::endl;
	}
};

// now lets try creating a composite object that is composed of multiple different objects
struct Group : public GraphicObject {
	std::string name;
	std::vector<GraphicObject *> objects; // lets store a vector of pointers to objects within the group object
	
	Group(const std::string& name) : name(name){} // constructor
 
	void draw() override {
		std::cout << "Group name: " << name << std::endl;
		for (auto obj : objects) {
			obj->draw();
		}

	}

};

/* Both a scalar Circle and any Group are drawable insofar as they both implement the draw() function. Group keeps a vector of pointers to 
other graphic objects (those can be Groups too!) and uses that vector for rendering itself.*/

/* The Composite design pattern allows us to provide identical interfaces for individual objects and collections of objects. This can be done either 
through the explicit use of interface members or, alternatively, through duck typing—for example, range-based for loops don’t require you to 
inherit anything, and work on the basis of the typing having suitablelooking begin()/end() members.

Finally, I must admit that all of these jumps through hoops are necessary only if you want to have a single member function. If you are 
OK with calling a global function or if you are happy with having more than one connect_to() implementation, the base class SomeNeurons is unnecessar*/


// Decorator
// The Decorator pattern allows us to enhance existing types without either modifying the original types(Open - Closed Principle) or causing an explosion of the number of derived types.
// The decorator pattern uses composition to enhance objects
//  Dynamic composition allows you to compose something at runtime, typically by passing around references.It allows maximum flexibility, since the composition can happen at runtime in response to, for example, the user’s input.
// Static composition implies that the object and its enhancements are composed at compile time via the use of templates.This means the exact set of enhancements on an object needs to be known at the moment of compilation, since it cannot be modified later.

// suppose we have a shape class
struct Form {
	virtual std::string str() = 0; // abstract class
};
struct Square : public Form {
	std::string str() override { return "Square"; }
};
// so lets create a dynamic decorator called colouredForm
struct ColouredForm : public Form {
	Form& shape;
	std::string colour;

	ColouredForm(Form& shape, const std::string& colour) : shape(shape), colour(colour) {

	}
	std::string str() override { return  shape.str() + " has the colour " + colour; }
};

	// this decorator works as a wrapper around the Shape class, extending its functionality without modifying it
	// dynamic because it uses a Form object thats instantiated at runtime, and will not work without it

	// lets also create a Transparent Form object and see how we could go about combining these
	struct TransparentForm : public Form {
		Form& form;
		int transparency;
		TransparentForm(Form& form, const int transparency) : form{ form }, transparency{ transparency } {}
		
		std::string str() override { return  form.str() + " has the transparency " + std::to_string(transparency); }
};


/*  suppose you don’t really care whether you can compose objects at runtime or not, but you really do care about being able to access all 
the fields and member functions of a decorated object. We can construct such a decorator via mixin inheritance*/

	// the idea is that the class inherits from its own template argument

template <typename T> 
struct static_ColouredShape : T {  // class inherits from its template parameter
	
	static_assert(std::is_base_of<Form, T>::value, "Template argument must be a Form");
	// assert that the template parameter is inheriting from Form
	
		std::string color;

		std::string str() const override
		 {
		
		 return T::str() + " has the color " + color;
		
		 }
};

/* A decorator gives a class additional functionality while adhering to the OCP.
Its crucial aspect is composability: several decorators can be applied to an object in any order. We’ve looked at the following types of decorators:

• Dynamic decorators can store references (or even store the entire values, if you want!) of the decorated objects 
and provide dynamic (runtime) composability, at the expense of not being able to access the underlying objects’ own members.

• Static decorators use mixin inheritance (inheriting from template parameter) to compose decorators at compile-time. This loses any sort of runtime flexibility 
(you cannot recompose objects) but gives you access to the underlying object’s members. These objects are also fully initializable through constructor forwarding.*/


// Facade is a structural design pattern that provides a simplified interface to a library,a framework or any other complex set of classes
/* The Facade provides convenient access to a particular part of the subsystem’s functionality. It knows where to direct the client’s request and how to operate all the moving parts.

An Additional Facade class can be created to prevent polluting a single facade with unrelated features that might make it yet another complex structure. Additional facades can be used by both clients and other facades.

The Complex Subsystem consists of dozens of various objects. To make them all do something meaningful, you have to dive deep into the subsystem’s implementation details, such as initializing objects in the correct order and supplying them with data in the proper format.

Subsystem classes aren’t aware of the facade’s existence. They operate within the system and work with each other directly.

The Client uses the facade instead of calling the subsystem objects directly.*/

// proxy pattern is similar to decorator, but its goal is to preserve the API being used while offering certain internal enhancements
// an example of this is a smart pointer, which wraps around a raw pointer and tries to emulate the interface you get with a normal pointer but also adds a reference count etc...
/*  Unlike the Decorator pattern, the Proxy doesn’t try to expand the functionality of an object 
by adding new members (unless it can’t be helped). All it tries to do is enhance the underlying behavior of existing members.

Plenty of different proxies exist:

• Property proxies are stand-in objects that can replace fields and perform additional operations during 
assignment and/or access.

• Virtual proxies provide virtual access to the underlying object, and can implement behaviors such as lazy 
object loading. You may feel like you’re working with a real object, but the underlying implementation may not have been created yet, and can, for example, be loaded 
on demand.

• Communication proxies allow us to change the physical location of the object (e.g., move it to the 
cloud) but allow us to use pretty much the same API. Of course, in this case the API is just a shim for a remote 
service such as a REST API.

• Logging proxies allow you to perform logging in addition to calling the underlying functions.
There are lots of other proxies out there, and chances are that the ones 
you build yourself will not fall into a preexisting category, but will instead 
perform some action specific to your domain
*/


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

	Adapter* adapter = new Adapter(adaptee); // create a pointer to a new adapter object, pass in the adaptee pointer
	clientCode(adapter);

	Group root("root");
	Circle c1;
	root.objects.push_back(&c1);
	root.draw();

	// static_ColouredShape<TransparentForm> square;  implement with a parameter pack and constructor forwarding



}