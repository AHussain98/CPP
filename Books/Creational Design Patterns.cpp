# include <iostream>
# include <string>
# include <vector>
# include <memory>

using namespace std;

// a couple of ways to create objects:
// stack and heap allocation
/* unique pointer (unique_ptr) can take a heapallocated pointer and manage it so that it’s cleaned up automatically when there is no longer a reference to it. A unique pointer really is unique: you cannot make copies of it, and you cannot pass it into another function without losing control of the original.
   A shared pointer (shared_ptr) takes a heap-allocated pointer and manages it, but allows the sharing of this pointer around in code. The owned pointer is only cleaned up when there are no components holding on to the pointer.
   A weak pointer (weak_ptr) is a smart but nonowning pointer, holding a weak reference to an object managed by a shared_ptr. You need to convert it to a shared_ptrin order to be able to actually access the referenced object. One of its uses is to break circular references of shared_ptrs.*/


// the builder pattern is concerned with the creation of compilacated objects that cannot be built up in a single line constructor call
// the builder pattern simply tried to outsource the piecewise construction of an object into a seperate class
// class constructors can be made private to force the use of a static function or friend function to create an instance of the class
// you can also have named constructors in cpp

// see below builder example
struct HtmlBuilder;

struct HtmlElement {
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;

	friend class HtmlBuilder; // make builder a friend class so it can access thr private constructors

	static unique_ptr<HtmlBuilder> build(const std::string& root_name) { return make_unique<HtmlBuilder>(root_name); }
	// static method so called without instantiating the class, and it returns a unique pointer 

private:  // make these protected so they're access controlled, we can create the Html object via the build method above
	HtmlElement() {}; // standard constructor
	HtmlElement(const std::string& name, const std::string& text) : name(name), text(text) {}; // when string references are passed in
};

// rather than having to build up HtmlElements every time we want to print a new one, we can create a builder class to build up HtmlElements

struct HtmlBuilder {
	HtmlElement root; // member root

	HtmlBuilder(std::string root_name) { root.name = root_name; }  // constructor

	HtmlBuilder * add_child(std::string child_name, std::string child_text) {  // return a pointer to the HtmlBuilder object
		HtmlElement e{ child_name, child_text }; // create the HtmlElement
		root.elements.emplace_back(e);
		return this; // return a pointer to this object so we can chain the add_child function
	}
	void print() {
		for (auto w : root.elements) {
			std::cout << w.name << " : " << w.text << std::endl;
		}
	}
};
// This is a dedicated component for building up an HTML element. The add_child() method is the method that’s intended to be used to add additional children to the current element, each child being a name - text pair.

/*The goal of the Builder pattern is to define a component dedicated entirely to piecewise construction of a complicated object or set of objects. We 
have observed the following key characteristics of a Builder:

• Builders can have a fluent interface that is usable for complicated construction using a single invocation chain.
To support this, builder functions should return this or *this.
• To force the user of the API to use a Builder, we can make the target object’s constructors inaccessible and 
then define a static create() function that returns the builder.
• A builder can be coerced to the object itself by defining the appropriate operator.
• A single builder interface can expose multiple subbuilders. Through clever use of inheritance and fluent interfaces, one can jump from one builder to 
another with ease.

The use of the Builder pattern makes sense when the construction of the object is a nontrivial process. 
Simple objects that are unambiguously constructed from a limited number of sensibly named constructor parameters should probably use a constructor (or dependency injection) without 
necessitating a Builder as such.*/




// Factory and Abstract Factory patterns: 
// The trouble with the constructor is that its name always matches the type. This means we cannot communicate any extra information in it, unlike in an ordinary function.
// We can try making the constructor protected and then exposing some static functions for creating new points

struct point {
	float x;
	float y;
private:
	point (const float x, const float y) : x(x), y(y){}  // protected constuctor
public:
//	static point newCartesian(float x, float y) { return { x,y }; }
//  static point newPolar(float r, float theta) { return { r * cos(theta), r * sin(theta) }; }

	friend class pointFactory;  // pointFactory can now access points constructor

// so the constrcutor is protected and we have exposed some static functions 
// each of the static functions is called a factory method, it cerated a point and returns it, the advantages being that both of the names of the methods as well as the arguments clearly communicate the co-ordinates required
};


// just like with builder, we can take all the point creating functions out of point and into a seperate class, a so-called factory
// lets do this by redefining the above class so the factory class is a friend of it

// note:
//• The constructor of Point is private because we don’t want anyone calling it directly.This isn’t a strict requirement, but making it public creates a bit of an
// ambiguity, as it presents the user two different ways of constructing the object.
//• Point declares PointFactory as a friend class.This is done deliberately so that the private constructorof Point is available to the factor—without this, the factory wouldn’t be able to instantiate the object!The
// implication here is that both of these types are being created at the same time, rather than the factory being created much later.

struct pointFactory { // a dedicated class specifically for creating point instances

	static point newCartesian(float x, float y) { return { x,y }; }
    static point newPolar(float r, float theta) { return { r * cos(theta), r * sin(theta) }; }
};

// we can also include pointFactory as an internal class within point. this is an internal factory and can be convenient when a factory only works with a single type

// abstract factory is a pattern for creating families of objects
// this just means a class that creates other classes that can make objects
// when we use teh term factory, we mean a class that knows how to create objects or a function that creates an object when called

/* A factory method is a class member that acts as a way of creating object. It typically replaces a constructor.
• A factory is typically a separate class that knows how to construct objects, though if you pass a function (as in std::function or similar) that constructs objects, this argument is also called a factory.
• An abstract factory is, as its name suggests, an abstract class that can be inherited by concrete classes that offer a family of types. 
A factory has several critical advantages over a constructor call, namely:
• A factory can say no, meaning that instead of actually returning an object it can return, for example, a nullptr.
• Naming is better and unconstrained, unlike constructor name.
• A single factory can make objects of many different types.
• A factory can exhibit polymorphic behavior, instantiating a class and returning it through its base class’ reference or pointer.
• A factory can implement caching and other storage optimizations; it is also a natural choice for approaches such as pooling or the Singleton pattern
Factory is different from Builder in that, with a Factory, you typically create an object in one go, whereas with Builder, you construct the object piecewise by providing information in parts.*/

// Prototype

int main() {
	// HtmlBuilder builder{ "ul" };
	auto builder = HtmlElement::build("ul");  // create the unique pointer to the builder object using the static function in HtmlElement
	builder->add_child("li", "hello")->add_child("li", "world");  // chained due to returning this
	builder->print();

	// create a new point
	// auto p = point::newCartesian(10, 5);
	auto my_point = pointFactory::newCartesian(3, 4); // create the point via factory class
}