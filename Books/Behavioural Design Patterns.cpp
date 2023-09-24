#include <iostream>
#include <string>

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
// 
// Mediator
// 
// Observer
// 
// State
// 
// Visitor
// 

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
}