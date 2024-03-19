#include <iostream>
#include <string>
using namespace std;
//casting performs an explicit conversion
// this can mean converting an expression to a different type, const to non const, data in a buffer to untyped binary, pointer to base class object and pointer to derived
// casting should rarely be necessary if code is well written
// check this: key point, the casts do not change the object they are performned on directly at all, they only give you a different pointer to a related class type in the inheritance hierarchy.


#include <iostream>

class mammal{
    public:
  void speak(){std::cout << "mammal" << std::endl;  }
};

class human : public mammal{
    public:
    void speak() {std::cout << "human" << std::endl;}
}; 

int main() {
   
   mammal m1;
   mammal * mPtr = &m1;
   mPtr->speak();
   static_cast<human *>(mPtr);  // no effect
   auto hPtr = static_cast<human *>(mPtr);  // works
   hPtr->speak();
   mPtr->speak();  
   
   double val = 100.01;  
   auto dub = static_cast<int>(val);
   std::cout << dub << std::endl;  // 100
   static_cast<int>(val);  // no effect
   std::cout << val << std::endl;  // still 100.01
}

void print(char * x){
    cout << x;
}

int main(){

    // below is c style casting
    int c = 'A';
    cout << c << endl; // prints the numeric conversion
    cout << (char)c << endl; //prints the alphabetic char

    // we can also do static and const casting, which is more modern, shown below

    cout << static_cast<char>(c) << endl;

    // then const cast which is used to remove the const-ness from references and pointers that ultimately refer to something that is not const
    const char * i = "Asad";

    //print(i);  // not allowed as i is const
   print(const_cast<char *>(i)); // allowed as we've casted i to no longer be const here


//dynamic casting is used to convert a pointer to a base class object to a pointer to a derviced class object
}

// fooling around with casting
struct A {

    virtual void call() { std::cout << 'A' << std::endl; }
};

struct B : public A {

    virtual void call() { std::cout << 'B' << std::endl; }
};

struct C : public B {

    void call() { std::cout << 'C' << std::endl; }
};

struct D {
    void call() {std::cout << "D" << std::endl;}
};


int main()
{
    A a;
    B b;
    C c;

    A* ptr = &b;  // ptr pointing to the A region of b
    ptr->call();  // prints B
    ptr = static_cast<B*>(ptr);  // static cast is free, ptr pointing to B
    //ptr = &b;  // now pointing to the B region of B
    ptr->call();  // prints B
    
    C * ptr2 = &c;
    ptr2->call();  // prints C
    
    D d;
    auto ptr3 = static_cast<D*>(ptr2);  // fails, types are not related, static cast fails in this case
    
    ptr3->call();

    return 0;
}

// static downcasting cannot be done if the inheritance hierarcy is virtual, so if objects are inherited virtually

// the below is also valid
class Base {
};

class Derived : public Base {
};

int main() {
    Base* bptr = new Derived();

    Derived* dptr = static_cast<Derived*>(bptr);

    std::cout << dptr << std::endl;
}
// You are allowed to static_cast from Base* to Derived*, but this is a static cast so it will not perform any type-checking.
// It is still useful though, if you know through some other way that that pointer does actually point to a Dervied object. If the Base* didn't actually point to a Derived* then any dereferencing of the Derived* resulting from a static_cast would invoke undefined behaviour.

// static casting is free, dynamic casting is expensive
// static_cast can perform only those casts where memory layout between the classes is known at compile-time. 
// dynamic_cast can check information at run-time, which allows to more accurately check for cast correctness, as well as read run-time information regarding the memory layout.

// Virtual inheritance puts a run-time information into each object which specifies what is the memory layout between the Base and Derived. 
// Is one right after another or is there an additional gap? Because static_cast cannot access such information, the compiler will act conservatively and just give a compiler error.

/*
In more detail:

Consider a complex inheritance structure, where - due to multiple inheritance - there are multiple copies of Base. The most typical scenario is a diamond inheritance:

class Base {...};
class Left : public Base {...};
class Right : public Base {...};
class Bottom : public Left, public Right {...};
In this scenario Bottom consists of Left and Right, where each has its own copy of Base. The memory structure of all the above classes is known at compile time and static_cast can be used without a problem.

Let us now consider the similar structure but with virtual inheritance of Base:

class Base {...};
class Left : public virtual Base {...};
class Right : public virtual Base {...};
class Bottom : public Left, public Right {...};
Using the virtual inheritance ensures that when Bottom is created, it contains only one copy of Base that is shared between object parts Left and Right. The layout of Bottom object can be for example:

Base part
Left part
Right part
Bottom part
Now, consider that you cast Bottom to Right (that is a valid cast). You obtain a Right pointer to an object that is in two pieces: Base and Right have a memory gap in between, containing the (now-irrelevant) Left part. The information about this gap is stored at run-time in a hidden field of Right (typically referred to as vbase_offset). You can read the details for example here.

However, the gap would not exist if you would just create a standalone Right object.

So, if I give you just a pointer to Right you do not know at compile time if it is a standalone object, or a part of something bigger (e.g. Bottom). You need to check the run-time information to properly cast from Right to Base. That is why static_cast will fail and dynamic_cast will not.

Note on dynamic_cast:

While static_cast does not use run-time information about the object, dynamic_cast uses and requires it to exist! Thus, the latter cast can be used only on those classes which contain at least one virtual function (e.g. a virtual destructor)
*/


/*
static_cast can perform conversions between pointers to related classes, not only from the derived class to its base, but also from a base class to its derived. This ensures that at least the classes are compatible if the proper object is converted, but no safety check is performed during runtime to check if the object being converted is in fact a full object of the destination type. Therefore, it is up to the programmer to ensure that the conversion is safe. On the other side, the overhead of the type-safety checks of dynamic_cast is avoided.


class CBase {};
class CDerived: public CBase {};
CBase * a = new CBase;
CDerived * b = static_cast<CDerived*>(a);

This would be valid, although b would point to an incomplete object of the class and could lead to runtime errors if dereferenced.

static_cast can also be used to perform any other non-pointer conversion that could also be performed implicitly, like for example standard conversion between fundamental types:


double d=3.14159265;
int i = static_cast<int>(d);

Or any conversion between classes with explicit constructors or operator functions as described in "implicit conversions" above.  */

/*
dynamic_cast can be used only with pointers and references to objects. Its purpose is to ensure that the result of the type conversion is a valid complete object of the requested class.

Therefore, dynamic_cast is always successful when we cast a class to one of its base classes:


class CBase { };
class CDerived: public CBase { };

CBase b; CBase* pb;
CDerived d; CDerived* pd;

pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
pd = dynamic_cast<CDerived*>(&b);  // wrong: base-to-derived 

The second conversion in this piece of code would produce a compilation error since base-to-derived conversions are not allowed with dynamic_cast unless the base class is polymorphic.

When a class is polymorphic, dynamic_cast performs a special checking during runtime to ensure that the expression yields a valid complete object of the requested class:

// dynamic_cast
#include <iostream>
#include <exception>
using namespace std;

class CBase { virtual void dummy() {} };
class CDerived: public CBase { int a; };

int main () {
  try {
    CBase * pba = new CDerived;
    CBase * pbb = new CBase;
    CDerived * pd;

    pd = dynamic_cast<CDerived*>(pba);
    if (pd==0) cout << "Null pointer on first type-cast" << endl;

    pd = dynamic_cast<CDerived*>(pbb);
    if (pd==0) cout << "Null pointer on second type-cast" << endl;

  } catch (exception& e) {cout << "Exception: " << e.what();}
  return 0;
}
Null pointer on second type-cast is the result

Compatibility note: dynamic_cast requires the Run-Time Type Information (RTTI) to keep track of dynamic types. Some compilers support this feature as an option which is disabled by default. This must be enabled for runtime type checking using dynamic_cast to work properly.

The code tries to perform two dynamic casts from pointer objects of type CBase* (pba and pbb) to a pointer object of type CDerived*, but only the first one is successful. Notice their respective initializations:

CBase * pba = new CDerived;
CBase * pbb = new CBase;

Even though both are pointers of type CBase*, pba points to an object of type CDerived, while pbb points to an object of type CBase. Thus, when their respective type-castings are performed using dynamic_cast, pba is pointing to a full object of class CDerived, whereas pbb is pointing to an object of class CBase, which is an incomplete object of class CDerived.

When dynamic_cast cannot cast a pointer because it is not a complete object of the required class -as in the second conversion in the previous example- it returns a null pointer to indicate the failure. If dynamic_cast is used to convert to a reference type and the conversion is not possible, an exception of type bad_cast is thrown instead.

dynamic_cast can also cast null pointers even between pointers to unrelated classes, and can also cast pointers of any type to void pointers (void*).  */
/*
reinterpret_cast
reinterpret_cast converts any pointer type to any other pointer type, even of unrelated classes. The operation result is a simple binary copy of the value from one pointer to the other. All pointer conversions are allowed: neither the content pointed nor the pointer type itself is checked.

It can also cast pointers to or from integer types. The format in which this integer value represents a pointer is platform-specific. The only guarantee is that a pointer cast to an integer type large enough to fully contain it, is granted to be able to be cast back to a valid pointer.

The conversions that can be performed by reinterpret_cast but not by static_cast are low-level operations, whose interpretation results in code which is generally system-specific, and thus non-portable. For example:


class A {};
class B {};
A * a = new A;
B * b = reinterpret_cast<B*>(a);

This is valid C++ code, although it does not make much sense, since now we have a pointer that points to an object of an incompatible class, and thus dereferencing it is unsafe.

const_cast
This type of casting manipulates the constness of an object, either to be set or to be removed. For example, in order to pass a const argument to a function that expects a non-constant parameter:

// const_cast
#include <iostream>
using namespace std;

void print (char * str)
{
  cout << str << endl;
}

int main () {
  const char * c = "sample text";
  print ( const_cast<char *> (c) );
  return 0;
}  



static_cast
static_cast is the first cast you should attempt to use. It does things like implicit conversions between types (such as int to float, or pointer to void*), and it can also call explicit conversion functions (or implicit ones). In many cases, explicitly stating static_cast isn't necessary, but it's important to note that the T(something) syntax is equivalent to (T)something and should be avoided (more on that later). A T(something, something_else) is safe, however, and guaranteed to call the constructor.

static_cast can also cast through inheritance hierarchies. It is unnecessary when casting upwards (towards a base class), but when casting downwards it can be used as long as it doesn't cast through virtual inheritance. It does not do checking, however, and it is undefined behavior to static_cast down a hierarchy to a type that isn't actually the type of the object.

const_cast
const_cast can be used to remove or add const to a variable; no other C++ cast is capable of removing it (not even reinterpret_cast). It is important to note that modifying a formerly const value is only undefined if the original variable is const; if you use it to take the const off a reference to something that wasn't declared with const, it is safe. This can be useful when overloading member functions based on const, for instance. It can also be used to add const to an object, such as to call a member function overload.

const_cast also works similarly on volatile, though that's less common.

dynamic_cast
dynamic_cast is exclusively used for handling polymorphism. You can cast a pointer or reference to any polymorphic type to any other class type (a polymorphic type has at least one virtual function, declared or inherited). You can use it for more than just casting downwards – you can cast sideways or even up another chain. The dynamic_cast will seek out the desired object and return it if possible. If it can't, it will return nullptr in the case of a pointer, or throw std::bad_cast in the case of a reference.

dynamic_cast has some limitations, though. It doesn't work if there are multiple objects of the same type in the inheritance hierarchy (the so-called 'dreaded diamond') and you aren't using virtual inheritance. It also can only go through public inheritance - it will always fail to travel through protected or private inheritance. This is rarely an issue, however, as such forms of inheritance are rare.

reinterpret_cast
reinterpret_cast is the most dangerous cast, and should be used very sparingly. It turns one type directly into another — such as casting the value from one pointer to another, or storing a pointer in an int, or all sorts of other nasty things. Largely, the only guarantee you get with reinterpret_cast is that normally if you cast the result back to the original type, you will get the exact same value (but not if the intermediate type is smaller than the original type). There are a number of conversions that reinterpret_cast cannot do, too. It's often abused for particularly weird conversions and bit manipulations, like turning a raw data stream into actual data, or storing data in the low bits of a pointer to aligned data. For those cases, see std::bit_cast.*/
