# include <iostream>

// handle-body pattern
// typically in c++, we put the class definition in a header file and the member fucntion definitions in a source file
// public, private and protected specifiers are used to control access to the implementation

// however, some implementation details are still visible to clients:
// names of private data members, prototypes of private/protected member functions, definitions of inline member functions
// all clients which use the class must include the header file, any implementation changes to the header will force a recompile of all clients

// we don't want to change and recompile any more code than is absolutely necessary, the handle-body pattern addresses this
// we split the class into two parts:
// the handle is an outer class that provides the interface to clients
// the body is an inner class that provides the implementation
// when a client creates a handle object, the handle creates a body objct
// when a client calls a member function on the handle object, the call is forwarded to the body

// similar to adapter design pattern

// handle.h defines the handle class, public member functions only
// body.h defines the body class, the full class definition
// clients #include body.h
// if the implementation details change, this ony affects body.h
// clients do not need to be recompiled

// static linking -> all the binary code is compiled into one binary executable, client, body and halde are all compiled as one
// dynamic linking -> body.cpp is compiled into a shared libary which is loaded at runtime, not compiled together with client.cpp and handle.cpp, so the program binary will read the shared library at runtime, so any changes will just be to that shared library, not to the executable

// there are a number of ways of implementing the handle-body pattern.
// in the pimpl (pointer to implementation) idiom, the handle has a private member which is a pointer to a body object, this is also known as the compiler firewall methpd
// in pimpl, handle.h decleares the body class but does not define it, clients only know its name
 // handle class is implemented using RAII, the body object is allocated in the constructor, body object is released in teh destructor. we also need to consider the effects of copy and move operations
// we can use unique_ptr with the pimpl idiom, however this will not compile unless ~handle() is declared, needed to make handle a complete type
// if we declare a destructor, the compiler will not synthesize move operators, we need to provide these if we want them
// the compiler will not synthesize copy operators, the unique_ptr member cannot be copied

// advantages of body-handle:
// clients do not need to include body.h
// clients do not need to be modified if body.h changes
// clients do not need to be recompiled if body.h changes
// users do not need a new program executable if body.h changes (if we use dynamic linking)
// useful if implementation needs to be kept secret from clients

//disadvantages:
// requires an extra memory allocation for the body object
// member functions calls require a pointer dereference (slightly slower than not dereferencing)
// loading a shared library increases the programs start-up time
// adds complexity to the codebase

// pimpl is often used in large projects to reduce compilation time and simplify product updates
// pimpl could be used to write standard container classes, std::string could have a body that stores the data and manipulates it, and a handle that provides the std::string interface


int main(){




}