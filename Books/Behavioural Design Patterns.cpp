#include <iostream>
#include <string>
#include <vector>


// chain of responsibility
// you have several different elements of a system who can all process a message one after another.As a concept, it’s rather easy to implement, since all that’s implied is the use of a list of some kind.

struct Creature {
	std::string name;
	int attack, defence;
	Creature(std::string name, int attack, int defence) : name(name), attack(attack), defence(defence) {

	}

	std::string str() { return std::to_string(attack) + std::to_string(defence); }
};
// these defence and attack parameters may be modified in any order and several modifiers may be in place at once, we can store these in a list
// now lets have a class CreatureModifier

struct CreatureModifier {
	CreatureModifier* next{ nullptr }; // pointer to the next CreatureModifier

protected:
	Creature& creature; // alternative is a pointer to a creature object, or a shared pointer

public:
	explicit CreatureModifier(Creature& creature) : creature(creature){}

	void add(CreatureModifier* cm) {  // add a creature object to the chain
		if (next) { next->add(cm); }
		else { next = cm; }
	}

	virtual void handle() {  // this virtual function handles the next item in the chain if it exists
		if (next) { next->handle(); }
	}
};

/*  The class takes and stores a reference to the Creature it plans to modify.

• The class doesn’t really do much, but it’s not abstract: all its members have implementations.

• The next member points to an optional CreatureModifier following this one. The implication is, 
of course, that the modifier it points to is an inheritor of CreatureModifier.

• The function add() adds another creature modifier to the modifier chain. This is done recursively: if the 
current modifier is nullptr we set it to that, otherwise we traverse the entire chain and put it on the end.

• The function handle() simply handles the next item in the chain, if it exists; it has no behavior of its own. The fact 
that it’s virtual implies that it’s meant to be overridden */

class DoubleAttackModifier : public CreatureModifier {
public:
	explicit DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {} // pass in the creature object into the constructor of the CreatureModifier object, also into the constructor of the base class 
	
	void handle() override {
		creature.attack *= 2;
		CreatureModifier::handle();
		}
};

/*  So this modifier inherits from CreatureModifier, and in its handle() method does two things: 
doubles the attack value and calls handle() from the base class. That second part is critical: the only way in which a chain of modifiers can be 
applied is if every inheritor doesn’t forget to call the base at the end of its own handle() implementation */

class IncreaseDefenseModifier : public CreatureModifier {
public:
	explicit IncreaseDefenseModifier(Creature & creature) : CreatureModifier(creature) {}
	
		void handle() override  {
		if (creature.attack <= 2)
			creature.defence += 1;
		CreatureModifier::handle();
		}
};

// Here’s another curious point.Suppose you decide to cast a spell on a creature such that no bonus can be applied to it.Is it easy to do ?
// Quite easy, actually, because all you have to do is avoid calling the base handle() : this avoids executing the entire chain :
class NoBonusesModifier : public CreatureModifier {
public:
	explicit NoBonusesModifier(Creature & creature) : CreatureModifier(creature) {}
	
	 void handle() override {
		// nothing here!
			 }
};

// That’s it! Now, if you slot the NoBonusesModifier at the beginning of the chain, no further elements will be applied
// Chain of Responsibility is a very simple design pattern that lets components process a command (or a query) in turn.The simplest
// implementation of CoR is one where you simply make a pointer chainand, in theory, you could replace it with just an ordinary vector or , perhaps, a
// list if you wanted fast removal as well. A more sophisticated Broker Chain implementation that also leverages
// the Mediator and Observer patterns allows us to process queries on an event(signal), letting each subscriber perform modifications of the
// originally passed object (it’s a single reference that goes through the entire chain) before the final values are returned to the client.

// Command pattern
//The Command design pattern proposes that, instead of working with objects directly by manipulating them through their APIs, we send them
// commands : instructions on how to do something.A command is nothing more than a data class with its members describing what to doand how to do it.
  
struct BankAccount {
	int balance = 0;
	int overdraft_limit = -500;

	void deposit(int amount) {
		balance += amount;
		std::cout << "deposited " << amount << ", balance is now " << balance << std::endl;
}
	void withdraw(int amount) {
		if (balance - amount >= overdraft_limit) {
			balance -= amount;
			std::cout << "withdrew " << amount << ", balance is now " << balance << std::endl;
		}
	}
};
/* Now we can call the member functions directly, of course, but let us suppose that, for audit purposes, we need to make a record 
of every deposit and withdrawal made and we cannot do it right inside BankAccount because—guess what—we’ve already designed, 
implemented, and tested that class*/

// lets construct an interface for a command object
struct Command {
	virtual void call() const = 0;
};

struct BankAccountCommand : Command {
	BankAccount& account;
	enum Action{deposit, withdraw} action;
	int amount;

	BankAccountCommand(BankAccount& account, const Action action, const int amount) : account(account), action(action), amount(amount){}

	void call() const override {  // override the call() function
		switch (action) { // depending on the enum selected, call a switch statement
		
		case deposit:
			account.deposit(amount);
			break;

		case withdraw:
			account.withdraw(amount);
			break;
		}
	}
};

// the Command contains the account to act on, the action and the amount


// Iterator pattern
// An iterator is quite simply an object that can point to an element of a collection and also knows how to move to the next element in the collection
// As such, it is only required to implement the ++ operator and the != operator (so you can compare two iterators and check if they point to the same thing).That’s it.
// The function begin() exists as both a member function of vector and a global function.The global one is particularly useful for arrays(C - style) arrays, not std::array) because they cannot have member functions.
// So begin() returns an iterator that you can think of as a pointer in the case of a vector, it has similar mechanics.
// The iterator that we are given knows how to advance, that is, move to point to the next element. It’s important to realize that the ++ refers to the idea of moving forward, that is, it is not the same as a++ for pointers where you move forward in memory (i.e., increment a memory address) 
// Now, the counterpart to begin() is, of course, end(), but it doesn’t point to the last element—instead, it points to the element after the last one.

// traversing a binary tree
template <typename T> 
struct Node {
	T value;
	Node<T> * left = nullptr;
	Node<T> * right = nullptr;
	Node<T> * parent = nullptr;
	BinaryTree<T>* tree = nullptr;
};
// every node has a reference to its left and right branches, its parent and the entire tree
// a node can be constructed on its own or with a specification of its children

// lets create a pre-order iterator
template < typename U>
struct PreOrderIterator
{
	Node<U>* current;

	explicit PreOrderIterator(Node<U>* current) : current(current)
	{ }

	// other members here

	// We need to define operator != to compare with other iterators.Since our iterator acts as a pointer, this is trivial :
	 bool operator!=(const PreOrderIterator<U>&other)
		{
		 return current != other.current; }

	 //	We also need the* operator for dereferencing :
		 Node<U>&operator*() { return *current; }

	PreOrderIterator<U>& operator++()
	{
		if (current->right)
		{
			current = current->right;
			while (current->left)
				current = current->left;
		}
		else
		{
			Node<T>* p = current->parent;
			while (p && current == p->right)
			{
				current = p;
				p = p->parent;
			}
			current = p;
		}
		return *this;
	}
};

// Mediator
// A large proportion of the code we write has different components (classes) communicating with one another through direct references or
// pointers.However, there are situations when you don’t want objects to be necessarily aware of each other’s presence.Or, perhaps you do want them
// to be aware of one another, but you still don’t want them to communicate through pointers or references because, well, those can go stale and you
// don’t want to dereference a nullptr, do you ?
// So the Mediator is a mechanism for facilitating communication between the components. Naturally, the mediator itself needs to be
// accessible to every component taking part, which means it should either be a global static variable or , alternatively, just a reference that gets injected into every component.
/* The Mediator design pattern essentially proposes an introduction of an 
in-between component that everyone in a system has a reference to and 
can use to communicate with one another. Instead of direct memory 
addresses, communication can happen through identifiers (usernames, 
unique IDs, etc).
The simplest implementation of a mediator is a member list and a 
function that goes through the list and does what it’s intended to do—
whether on every element of the list or selectively.
A more sophisticated implementation of Mediator can use events to 
allow participants to subscribe (and unsubscribe) to things happening 
in the system. This way, messages sent from one component to another 
can be treated as events. In this set-up, it is also easy for participants to 
unsubscribe to certain events if they are no longer interested in them or if 
they are about to leave the system altogether.*/


// Observer
// Design pattern for notifying observing objects about a change made in another object

struct Person : Observable<Person> {
	int age;
	Person(int age) : age(age){}

	int get_age() const { return age; }
	void set_age(const int value) {
		if (this->age == age) return;
		this->age = age;
		notify(*this, "age");
	}
};

// how do we know when a person's age changes? we don't 
// we want to be informed on every write to a persons age

// person now needs a private list of all the observers interested in Person's changes
// Person should let the observers subscribe()/unsubscribe() to changes in Person
// Inform all observers when a change is made with notify()
// all this functionality can be moved into another class 

template <typename T>
struct Observable {
	void notify(T& source, const std::string& name) { // notify gets called by the Person's set_age function
		for (auto obs : observers) {
			obs->field_changed(source, name);
		}
	}
	void subscribe(Observer<T>*f) { observers.push_back(f); }
	void unsubscribe(Observer<T>*f) { ... }
 private:
	 std::vector<Observer<T>*> observers; // made private since we don't want anyone touching this

	};

// subscribe just pushes back a pointer to the object we want to add to the list of watchers


// lets create an Observer class

template<typename T>
struct Observer {
	virtual void field_changed(T& source, const std::string& field_name) = 0;
};
// source is a reference to the object whose field actually changed, field_name is the field name that changed

struct PersonObserver : Observer<Person> {
	void field_changed(Person& source, const std::string& field_name) override {
		std::cout << "Person's " << field_name << " has changed to " << source.get_age() << ".\n";
	}
};

/* Let’s recap the main design decisions when implementing Observer:
• Decide what information you want your observable to 
communicate. For example, if you are handling field/
property changes, you can include the name of the 
property. You can also specify old/new values, but 
passing the type could be problematic.
• Do you want your observers to been tire classes, or are 
you OK with just having a list of virtual functions?
• How do you want to handle observers unsubscribing?
– If you don’t plan to support unsubscription—
congratulations, you’ll save a lot of effort implementing 
the Observer, since there are no removal issues in 
reentrancy scenarios.
– If you plan to support an explicit unsubscribe() 
function, you probably don’t want to erase-remove 
right in the function, but instead mark your elements 
for removal and remove them later.
– If you don’t like the idea of dispatching on a (posibly 
null) raw pointer, consider using a weak_ptr instead.
• Is it likely that the functions of an Observer<T> will be 
invoked from several different threads? If they are, you 
need to protect your subscription list:
– You can put a scoped_lock on all relevant functions; or
– You can use a thread-safe collection such as the TBB/PPL 
concurrent_vector. You lose ordering guarantees.
• Are multiple subscriptions from the same source 
allowed? If they are, you cannot use an std::set.
There is, sadly, no ideal implementation of Observer that ticks all the boxes. 
Whichever implementation you go for, some compromises are expected*/

// State
// 
// Visitor
// Once you’ve got a hierarchy of types, unless you have access to the source code, it is impossible to add a function to each member of the hierarchy.
// This is a problem that requires some advance planning, and gives birth to the Visitor pattern
// Visitor is a behavioral design pattern that allows adding new behaviors to existing class hierarchy without altering any existing code

/**
 * The Visitor Interface declares a set of visiting methods that correspond to
 * component classes. The signature of a visiting method allows the visitor to
 * identify the exact class of the component that it's dealing with.
 */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
	virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
	virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};

/**
 * The Component interface declares an `accept` method that should take the base
 * visitor interface as an argument.
 */

class Component {
public:
	virtual ~Component() {}
	virtual void Accept(Visitor* visitor) const = 0;
};

/**
 * Each Concrete Component must implement the `Accept` method in such a way that
 * it calls the visitor's method corresponding to the component's class.
 */
class ConcreteComponentA : public Component {
	/**
	 * Note that we're calling `visitConcreteComponentA`, which matches the
	 * current class name. This way we let the visitor know the class of the
	 * component it works with.
	 */
public:
	void Accept(Visitor* visitor) const override {
		visitor->VisitConcreteComponentA(this);
	}
	/**
	 * Concrete Components may have special methods that don't exist in their base
	 * class or interface. The Visitor is still able to use these methods since
	 * it's aware of the component's concrete class.
	 */
	std::string ExclusiveMethodOfConcreteComponentA() const {
		return "A";
	}
};

class ConcreteComponentB : public Component {
	/**
	 * Same here: visitConcreteComponentB => ConcreteComponentB
	 */
public:
	void Accept(Visitor* visitor) const override {
		visitor->VisitConcreteComponentB(this);
	}
	std::string SpecialMethodOfConcreteComponentB() const {
		return "B";
	}
};

/**
 * Concrete Visitors implement several versions of the same algorithm, which can
 * work with all concrete component classes.
 *
 * You can experience the biggest benefit of the Visitor pattern when using it
 * with a complex object structure, such as a Composite tree. In this case, it
 * might be helpful to store some intermediate state of the algorithm while
 * executing visitor's methods over various objects of the structure.
 */
class ConcreteVisitor1 : public Visitor {
public:
	void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
		std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
	}

	void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
		std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
	}
};

class ConcreteVisitor2 : public Visitor {
public:
	void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
		std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
	}
	void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
		std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
	}
};
/**
 * The client code can run visitor operations over any set of elements without
 * figuring out their concrete classes. The accept operation directs a call to
 * the appropriate operation in the visitor object.
 */
void ClientCode(std::array<const Component*, 2> components, Visitor* visitor) {
	// ...
	for (const Component* comp : components) {
		comp->Accept(visitor);
	}
	// ...
}


int main() {
	Creature goblin{ "Goblin", 1, 1 };
	CreatureModifier root{ goblin };
	DoubleAttackModifier r1{ goblin };
	DoubleAttackModifier r1_2{ goblin };
	IncreaseDefenseModifier r2{ goblin };
	
	root.add(&r1);
	root.add(&r1_2);
	root.add(&r2);
	
	root.handle();
	
	std::cout << goblin.str() << std::endl;

	 Person p{ 20 };
	 PersonObserver cpo;
	 p.subscribe(&cpo);
	 p.set_age(21); // Person's age has changed to 21.
	 p.set_age(22); // Person's age has changed to 22.
}