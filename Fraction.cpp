class Fraction{
	
	private:
		int numerator;
		int denominator; //private variables
		
	public:
		Fraction(int numerator, int denominator) { // constructor must be public
			this->numerator = numerator; // so the numerator and demoniator variables of the object instantiated from the class are made equal to the valeu of the parameters of the class constructor
			this->denominator = denominator;
		}
	int getNumerator() const{ //so we can use getters and setters to access the private variables 
		return numerator;
	}
	//calling the get functions as constant meakes it clear to the compiler that they won't change anything, so they can be safely called if the object is constant
	//pay attention to the placement of the const keyword, placed AFTER the function name
	int getDenominator() const{ // because these functions are in the same class, they are able to access the private variables
	return denominator;	
	} // const functions are only useable if they dont make any changes, the disply function could also be const
	//const objects can ONLY use const functions
	void setNumerator(int num) { // it's important we make these functions public 
		this->numerator = num;
	}
	
	void setDenominator(int deno) {
		this->denominator = deno;
	}
	
	void display() {
		cout << "Fraction is" << endl;
		cout << numerator << " / " << denominator << endl;
		}

   void add (Fraction f2) { // you give the add function a copy of f2, it doesn't actually operate on the values at the address of f2
 //internally, a copy of f2 using the copy constructor is used for the add function
 //to avoid this copying, just pass the f2 Fraction by reference, so it would be void add(Fraction &f2), and the changes you make to f2 in the function here would be reflected in the actual f2
 //so to avoid using a copy of f2, and to avoid risking making any changes while still using the actual address of f2, we can do void add(Fraction const &f2)  this will not allow the values of f2 to change
   //add is a function that takes an object as a parameter
    	// the name f2 doesnt actually amtter here, since we're just defining the functionality of the fucntion
	
	int lcm = this->denominator * f2.denominator; //you are allowed to access the denominator of f2 in the function, even though the variable itself is private so you can't access it directly
	// important to use this here because f1 and f2 have variables called numerator and denominator
	int x = lcm / this->denominator;
	int y = lcm / f2.denominator;
	int num = (x * this->numerator) + (y * f2.numerator); // combined numerator
	int deno = lcm;
	this->numerator = num; // change the values of the object that calls this function to the uodated values
	this->denominator = deno;
	//why does this change actually change the value in f1??? it hasnt been passed by reference???? (usage of the this statement above)
		 // for the above comment, because of the this keyword. In other words: each time you use a class member inside a member function, an implicit this-> is prepended to that member; so if member is a class member, then member is always equivalent to this->member inside a class member function.

    // now call the simplify function
	simplify(); //you can call this within another function and it knows to use f1's values because f1 called the original function	
	}
	

// now we need a simplify function to print the final simplified fraction

void simplify() {
int gcd; //greatest common denominator, at first, we don't know what this is
int min_value = min(this->numerator, this->denominator); // min function returns the minimum
	for (int i = 1; i <= min_value; i++) {
		if (this->numerator % i == 0 && this->denominator % i == 0) {
			gcd = i; // loop for finding the gcd, we can divide both numerator and operator by this to get our simplified fraction
		}
	}
this->numerator = this->numerator / gcd; //dont actually need the this keywords here as the values of f1 would be used automatically
this->denominator = this->denominator / gcd; // this is because the simplify fnunction doesn't include another function in the parameter, so the value of f1 is used by default

}

void multiply(Fraction const &f2) { // pass fraction by using const so it cant be changed and using the actual address so we don't create any copies
	
this->numerator = this->numerator * f2.numerator;
this->denominator = this->denominator * f2.denominator;
simplify(); // right now we're not returning anything, we're just making changes to f1
}

//operator overloading defined just for the Fraction class
 Fraction operator+(Fraction const &f2) { // return type is a fraction object
 // as soon as you try to overload something, the part before the operator is accessed using this, and the part after can go in the parameter
//this is why we only pass one thing in the parameter, even though we're adding two objects
	int lcm = this->denominator * f2.denominator; //you are allowed to access the denominator of f2 in the function, even though the variable itself is private so you can't access it directly
	// important to use this here because f1 and f2 have variables called numerator and denominator
	int x = lcm / this->denominator;
	int y = lcm / f2.denominator;
	int num = (x * this->numerator) + (y * f2.numerator); // combined numerator
	int deno = lcm;
Fraction fnew(num,deno); // create a new fraction in here
fnew.simplify();
return fnew;

}
//now define operator overloading for a multiplication 

Fraction operator*(Fraction const &f2) {
	int num = this->numerator * f2.numerator;
    int deno = this->denominator * f2.denominator;
    Fraction fnew(num,deno); //  create a new object and simplify it, as before
    fnew.simplify();
    return fnew;
}

// now lets overload the equality operator ==
bool operator==(Fraction const &f2) { // return a boolean, as we only need to know true or false
	return (this->numerator==f2.numerator && this->denominator==f2.denominator);
}
//and again for the precrement operator

//preincrement overloading
Fraction& operator++(){ //passed by reference
// return a new fraction object, we don't have to set this up to be recieved in the main code, so the changes to the object calling this function will be made regardless of wheteher we store them in a new object or not
//if youre not storing the return value in a fraction object, system instead uses the buffer and created memory addresses in there to complete each operation and store the return values at the buffer address
//we could get around this by passing by reference, no extra buffer memory is created, it only works on f1 itself, so doing ++(++f1) would work, otherwise you'd have to do Fraction f2 = ++(++f1) instead to see the double operated value
	this->numerator = this->numerator + this->denominator;
	this->simplify(); // so the change will be made to f1, as the this keyword makes the changes at the address of the object that calls the function
	return *this; // but by returning the value at the address of f1, we can assign tjose values to our new object
	//denominator is unchanged
}

//postincrement overloading, denoted by (int)
Fraction operator++(int){
	Fraction fnew(this->numerator,this->denominator); // create and store the old values in this object
	this->numerator = this->numerator + this->denominator; //  increase the incremented objects values
	this->simplify();
	fnew.simplify();
	return fnew;
}
//overload the += operator
void operator+=(Fraction f2){ //void as it shouldnt return anything, simply make the changes
	int lcm = this->denominator * f2.denominator; //you are allowed to access the denominator of f2 in the function, even though the variable itself is private so you can't access it directly
	int x = lcm / this->denominator;
	int y = lcm / f2.denominator;
	int num = (x * this->numerator) + (y * f2.numerator); // combined numerator
	int deno = lcm;
	this->numerator = num; // change the values of the object that calls this function to the updated values
	this->denominator = deno;
}

};





