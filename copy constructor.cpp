# include <iostream>
# include <string>

// the copy constructor is a specialised verison of the constructor, it takes only one argument which is an object of the same class
// it uses this existign object to initalise the new object, the argument should be passed by reference
// the copy constructor is automatically called when we initalise a new object from an existing object of the ame class

// Test test1(x,y), Test test2{const Test& test1}, passed by reference, copy constructor
// Test test3 = test2; the default copy constructor, i think?

// copy constructor is called implicitly when we pass an argument by value and when we return a local variable by value
  // a new object gets created on the functions stack which is a copy of the argument/return value in the above cases
  // however the compiler may perform optimisations that reduce the amount of copying

// we only need to create our own copy constructor when the class is using some resource such as allocated memory
// in this case, we define a copy constructor to pass by const reference, so we don't end up sharing the resource
// otherwise the default copy constructor will be enough

// the assignment operator = is a member function, invoked when we assign two objects of the same class
// so if x and y are two objects of the same class, x = y is the same as x.operator=(y)
// after this statement has been executed, the members of x have the same value as y
// assignment operator takes its argument by const reference and returns the new value of x
// the reason we can return a value is that we can do multiple assignments, x = y = z is valid, for example
// this is processed from right to left, so y takes on the value of z, then this y value becomes the value of x
// the assignment operator returns by reference, not by const reference
// operator = is a member function, it is passed a hidden "this" pointer to the object it was called on, we can get the modified object by dereferencing the "this" pointer after performing the assignment

// if we do not define special member functions, the compiler will synthesize them for us, these include constrctor, copy constructor, assignment operator, destructor

/* The copy constructor must accept an argument of the same class type and create a duplicate in an
appropriate manner. This poses an immediate problem that you must overcome; you can see it clearly if you
try to define the copy constructor for the Box class like this:
Box::Box(Box box) // Wrong!!
 : m_length{box.m_length}, m_width{box.m_width}, m_height{box.m_height}
{}
Each member variable of the new object is initialized with the value of the object that is the argument.
No code is needed in the body of the copy constructor in this instance. This looks okay, but consider what
happens when the constructor is called. The argument is passed by value, but because the argument is a Box
object, the compiler arranges to call the copy constructor for the Box class to make a copy of the argument.
Of course, the argument to this call of the copy constructor is passed by value, so another call to the copy
constructor is required, and so on. In short, you’ve created a situation where an unlimited number of
recursive calls to the copy constructor will occur. Your compiler won’t allow this code to compile.
To avoid the problem, the parameter for the copy constructor must be a reference. More specifically, it
should be a reference-to-const parameter. For the Box class, this looks like this:
Box::Box(const Box& box)
 : m_length{box.m_length}, m_width{box.m_width}, m_height{box.m_height}
{}
Now that the argument is no longer passed by value, recursive calls of the copy constructor are avoided.
The compiler initializes the parameter box with the object that is passed to it. The parameter should be
reference-to-const because a copy constructor is only in the business of creating duplicates; it should not
modify the original. A reference-to-const parameter allows const and non-const objects to be copied. If the
parameter was a reference-to-non-const, the constructor would not accept a const object as the argument,
thus disallowing copying of const objects. You can conclude from this that the parameter type for a copy
Chapter 12 ■ Defining Your Own Data Types
416
constructor is always a reference to a const object of the same class type. In other words, the form of the
copy constructor is the same for any class:
MyClass::MyClass(const MyClass& object)
 : // Initialization list to duplicate all member variables
{
 // Possibly some additional code to duplicate the object...
}
Of course, the copy constructor may also delegate to other, non-copy constructors as well. Here’s an
example:
Box::Box(const Box& box) : Box{box.m_length, box.m_width, box.m_height}
{}  */


class String{
    std::string s; // private data member

    public:
        // Constructors

        String(){ // default constructor, s is left undefined
        s = "";
        };

        String( const std::string someString){
            s = someString;

        }

        String( const String& arg){ // standard copy constructor
            s = arg.s;
        }
       //Like a default copy constructor, the default copy assignment operator simply copies all the member
//      variables of a class one by one (in the order they are declared in the class definition). You can override this
//default behavior by supplying a user-defined assignment operator

        // assignment operator
        String& operator =(const String& arg){
            s = arg.s;
            return *this;
        }

        void print(){
            std::cout << s;
        }
};

int main(){

        String w{"world"}; //call standard constructor
        String bang{w}; //copy constructor
        String bang2;


        w.print();
        std::cout << '\n';
        bang.print();
        std::cout << '\n';
        bang2 = w;
        bang2.print();




}