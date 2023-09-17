# include <iostream>

// Curiously recurring template pattern ->  an inheritor passes itself as a template argument to its base class e.g. struct Foo : SomeBase<Foo>
// one reason is to be able to access a typed this pointer inside a base class implementation. 
// CRTP is a technique to implement compile - time polymorphism.Here's a very simple example. In the below example, ProcessFoo() is working with Base class interface and Base::Foo invokes the derived object's foo() method, which is what you aim to do with virtual methods.

/*In C++, a class can be defined to inherit from its own template argument, 
for example:
1 template <typename T> struct Mixin : T
2 {
3 ...
4 }
This approach is called mixin inheritance and allows hierarchical 
composition of types. For example, you can allow Foo<Bar<Baz>> x; to 
declare a variable of a type that implements the traits of all three classes, 
without having to actually construct a brand new FooBarBaz type. */


template<typename T> // CRTP
struct Base {
	void foo() {
		(static_cast<T*>(this))->foo(); // static cast the this pointer, to change the type of pointer to the class passed in the template
	} // so this will call the version of foo that belongs to the class in the template
};

struct Derived : public Base<Derived> { // inherit from base and pass derived into base
	void foo() {
		std::cout << "This is from Derived" << std::endl;
	}
};

template <typename V>
void processFoo(Base<V> * b) {  // pass in a reference to the templated type of the base class, now any such type like derived and anotherderived can use this functionality
	b->foo(); // call the foo function
}


struct AnotherDerived : public Base<AnotherDerived> {
	void foo() {
		std::cout << "This is from AnotherDerived" << std::endl;
	}
};

// a property is a typically private field and a combination of a getter and setter
// cpp has a non standard decleration specifier called property which can be used to set these and works with most compilers

class Person {
	int age;
public:
	int get_age() { return age; }
	void set_age(int val) { age = val; }
	__declspec(property(get = get_age, put = set_age)) int age;  // this is the getter and setter property
};

/*enum classes - enumerator names are local to the enum and their values do not implicitly convert to other types (like another enum or int)

Plain enums - where enumerator names are in the same scope as the enum and their values implicitly convert to integers and other types*/

/*SOLID is an acronym which stands for the following design principles (and 
their abbreviations):
• Single Responsibility Principle (SRP)
• Open-Closed Principle (OCP)
• Liskov Substitution Principle (LSP)
• Interface Segregation Principle (ISP)
• Dependency Inversion Principle (DIP)*/

// Single Responsibility: each class has only one responsibility, and therefore has only one reason to change. An extreme example of an antipattern that violates the SRP is called a God Object.A God Object is a huge class that tries to handle as many concerns as possible, becoming a monolithic monstrosity that is very difficult to work with.
// OCP states that you shouldn’t need to go back to code you’ve already written and tested and change it. This is what is meant by “open for extension, closed for modification.”
// The Liskov Substitution Principle, named after Barbara Liskov, states that if an interface takes an object of type Parent, it should equally take an object of type Child without anything breaking
// the ISP suggests is that you split up interfaces so that implementors can pickand choose depending on their needs.Since printing and scanning are different operations (for example, a Scannercannot print), we define separate interfaces for these
/* Dependency Inversion is the strategy of depending upon interfaces or abstract functions and classes rather than upon concrete functions and classes.

Simply put, when components of our system have dependencies, we don’t want directly inject a component’s dependency into another. Instead, we should use a level of abstraction between them.

Let’s imagine we are building a model of a car. The car has different parts like a steering wheel, brake peddles, engine, etc.

We build the model. Now we are testing a prototype. We find out that whenever we change or update the engine, also the steering wheel needs a fix. What is wrong with this model?
We have created a dependency between the high level steering wheel and teh low level engine.
This can be solved by implementing an interface between them.

dependency injection is a programming technique in which an object or function receives other objects or functions that it requires, as opposed to creating them internally. Dependency injection aims to separate the concerns of constructing objects and using them, leading to loosely coupled programs

Cohesion refers to what the class (or module) can do. Low cohesion would mean that the class does a great variety of actions - it is broad, unfocused on what it should do. High cohesion means that the class is focused on what it should be doing, i.e. only methods relating to the intention of the class.

Example of Low Cohesion:

-------------------
| Staff           |
-------------------
| checkEmail()    |
| sendEmail()     |
| emailValidate() |
| PrintLetter()   |
-------------------
Example of High Cohesion:

----------------------------
| Staff                   |
----------------------------
| -salary                 |
| -emailAddr              |
----------------------------
| setSalary(newSalary)    |
| getSalary()             |
| setEmailAddr(newEmail)  |
| getEmailAddr()          |
----------------------------
As for coupling, it refers to how related or dependent two classes/modules are toward each other. For low coupled classes, changing something major in one class should not affect the other. High coupling would make it difficult to change and maintain your code; since classes are closely knit together, making a change could require an entire system revamp.

Good software design has high cohesion and low coupling.  These problems are solved by adhereing to the SOLID principles

*/


int main() {
	Derived d1;
	d1.foo(); // foo called normally from d1
	processFoo(&d1); // call processFoo with the address of d1
	AnotherDerived d2;
	processFoo(&d2); // call processFoo with address of d2

	Person p;
	// p.age = 25;  // calls p.set_age()
	// p.get;  

}