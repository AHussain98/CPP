# include <iostream>

// a namespace is used to group together logically related symbols, typically done within libraries
// an example is the standard libraries std namespace, grouping together all the functions, types and variables defined by it
// we use namespace prefixes to avoid naming conflicts
//  if a name is not in any namespace, it is said to be in the global namespace, the compiler assumes this
// the global namespace has no name, if we specify that we are referring to it, we use :: on its own before its name, so a class Test in the global namespace would be instantiated via: ::Test test;
// namespaces can be split over different parts of the code, even over different files, just refer to it again
// when a symbol is defined in a namespace, it hides any symbol outside the namespace with the same name
// the using decleration brings a particular version of objects into the global namespace, this takes effect from the decleration to the end of the scope, not good practice as it contradicts the point of namespaces

namespace Asad{   // all objects defined in this namespace will have the Asad:: prefix applied implicitly by the compiler

    void print(){
        std::cout << "Yo!";
    }
}

int x = 10;   // x defined in the global namespace

namespace Asad{
    void printAgain(){
    std::cout << "Once more, Yo!";
    }

        int x = 15; // x defined in my namespace


    void func(){
     std::cout << ::x << "  "; //print out the global x ( main function is in the global namespace )
     std::cout << Asad::x; //now print mine
     }
}



int main(){

     Asad::print(); // if we want to use an object from the namespace outside of it, we have to use the prefix
     Asad::printAgain();
     std:: cout << '\n';
     Asad::func();

}