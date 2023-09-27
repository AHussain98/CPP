#include <iostream>;

/* A statement is a basic unit in a C++ program.A statement always ends with a semicolon, and it’s the
semicolon that marks the end of a statement, not the end of the line.A statement defines something, such as
a computation, or an action that is to be performed.Everything a program does is specified by statements.
Statements are executed in sequence until there is a statement that causes the sequence to be altered. */

/*Input and output are performed using streams in C++. To output something, you write it to an output stream, 
and to input data, you read it from an input stream. A stream is an abstract representation of a source of data 
or a data sink. When your program executes, each stream is tied to a specific device that is the source of data 
in the case of an input stream and the destination for data in the case of an output stream.*/

// a return statement ends fucntion control and returns to the point it was called, program may or may not return a value

/*A namespace is a sort of family name that prefixes all the names declared within the namespace. The 
names in the Standard Library are all defined within a namespace that has the name std. cout and endl
are names from the Standard Library, so the full names are std::cout and std::endl. Those two colons 
together, ::, have a fancy title: the scope resolution operator. */
// main function must not be defined in a namespace, it must be global

// general convention is not to use names that start with an underscore

/*Creating an executable from your C++ source code is basically a three-step process. In the first step, the 
preprocessor processes all preprocessing directives. Traditionally, one of its key tasks was to copy the 
entire contents of all #included headers into your source files, yet this practice will be phased out with the 
introduction of modules in C++20. We discuss #include and other preprocessing directives in Appendix A. 
In the second step, your compiler processes each source file to produce an object file that contains the 
machine code equivalent of the preprocessed code. In the third step, the linker combines the binary files for 
a program into a file containing the complete executable program*/
// one object file is produced for every cpp file, the linker links these into an executable

// little endian -> most signifigant bits stored at the end
// big endian -> most significant bits stored at the front

/*First, the preprocessor prepares and modifies each source file according to instructions that you specify 
by preprocessing directives. It recursively analyzes, executes, and then removes all these directives from 
the source code. The output of the preprocessor is called a translation unit, and it consists purely of C++ 
declarations and statements.
Next, the compiler processes each translation unit independently to generate an object file. An object 
file contains the machine code for the definitions it encountered in the translation unit, as well as references 
to so-called external entities—entities that were used by, but not defined in, the translation unit. Examples 
of external entities include entities that are defined and exported by an imported module (see Chapter 11). 
Later in this appendix, you will encounter other examples of external entities as well.
The linker combines all object files of a program to produce the final executable. It establishes all 
necessary connections between all object files for all source files. If an object file contains references to an 
external entity that is not found in any of the other object files, no executable will result, and there will be 
one or more error messages from the linker.
The combined process of preprocessing source files, compiling translation units, and linking object files 
is referred to as translation*/

//  Never use a macro in C++ when a const variable (or variable template) will do. Using a #define directive has at least three major disadvantages : there’s no type checking support, it doesn’t respect scope, and the identifier name cannot be bound within a namespace
// the preprocessor just copies whatever the macro is, it treats it purely as text
//  use function templates rather than macros as they're type safe, respect scope and their names can be bound to a namespace

// macros are defined with #define and undefined with #undef
// there's also conditional macros, #ifdef for checking if an identifier is defined
// there are preprocessing constants that are tied to each translation unit, such as _DATE_ and _TIME_ which gives the date and time of last compilation

//  the macro in #include <cassert> assert() is for detecting programming errors, not for handling errors at runtime. It is for asserting facts that you, as a programmer, are 110 % convinced should never, ever occur.The logical expression of an assertion should thus never be based on something beyond your control(such as whether opening a file
//	succeeds).Your program should include code to handle anyand all error conditions that might be expected to occur occasionally—however unlikely their occurrence may be.A
// static_assert() is for checking conditions statically, at compile time, assets() via macro are for dynamic checking, at runtime

/*The concrete difference between specifying a filename between double quotes or between angled 
brackets lies in the locations in which the preprocessor will search for a file with that name. The precise 
locations the preprocessor uses for this are implementation-dependent and should be described in your 
compiler documentation. Usually, though, the idea is that you use angle brackets for headers of external 
libraries, and double quotes for files that are stored next to the current source file*/

/*In a given translation unit, no variable, function, class type, enumeration type, or template must ever be 
defined more than once. You can have more than one declaration for any such entity, but there must never 
be more than one definition that determines what it is and causes it to be created. If there’s more than one 
definition within the same translation unit, the code will not compile.
■ Note A declaration introduces a name into a scope. A definition not only introduces the name but also 
defines what it is. In other words, all definitions are declarations, but not all declarations are definitions.*/

/*Exceptions to this rule are inline functions and inline variables. In fact, for inline functions and 
inline variables that are not defined in a module file, a definition must appear once and only once in 
every translation unit that uses them. All definitions of a given inline function or variable within different 
translation units of a program have to be identical, though. One traditionally uses inline functions and 
variables to define variables or functions in header files, something which with regular functions and 
variables would almost certainly lead to ODR violations. W*/

/*8. If you want to access a variable that is defined outside the current translation unit, then you must 
declare the variable name using the extern keyword:
extern int power_range; // Declaration of an externally defined variable
This statement is a declaration that power_range is a name that is defined elsewhere. The type must 
correspond exactly to the type that appears in the definition. You can’t specify an initial value in an extern
declaration because it’s a declaration of the name, not a definition of a variable. Declaring a variable as 
extern implies that it is defined in another translation unit. This causes the compiler to mark the use of the 
externally defined variable. It is the linker that makes the connection between the name and the variable to 
which it refers.
we can add extern specifiers to function declerations aswell, this makes things clearer for the reader

A const variable, however, has internal linkage by default, which makes it unavailable in other
translation units. You can override this by using the extern keyword in the definition:
// Range.cpp
extern const int power_range {3}; // Definition of a global constant with external linkage
The extern keyword tells the compiler that the name should have external linkage, even though it is const.
When you want to access power_range in another source file, you must declare it as const and external:
extern const int power_range; // Declaration of an external global constant

 All names declared inside an unnamed namespace have internal linkage (even names defined with
an extern specifier…). If a function, global variable, class, enumeration, or template is not supposed to be
accessible from outside a particular translation unit, you should therefore always define it in an unnamed
namespace, especially in non-modular code (see also the next section). Using a static specifier for this
purpose is no longer recommended (and was only ever possible for function and variable definitions anyway).

Surround all your headers with an #include guard to eliminate the potential for violating the one
definition rule when that header is included twice into the same translation unit.
■ Tip Most compilers offer a #pragma preprocessing directive to achieve the same effect as the relatively
verbose #include guard pattern. Simply placing a line containing #pragma once at the beginning of a header
file generally suffices to prevent duplication of the header’s contents as well. While nearly all compilers support
this #pragma, it is not standard C++, so for this appendix we’ll continue to use #include guards in header files.

ODR can be violated by non const variables and functions. These can be inlined to prevent this.

 Note The inline keyword is merely a suggestion to the compiler to inline a function, nothing more. If
the compiler concludes that it would be more efficient not to inline a particular call, it will still ignore your
suggestion and generate a function call instead. Conversely, if it believes this to be more efficient, the compiler
will happily inline any non-inline function definition that is present in the same translation unit as well.
■ Caution Defining functions and variables in a header file comes at a cost, especially during development.
Each time you change a definition in a header file, all translation units in which that header is included will need
to be recompiled. If you change a definition in a source file, on the other hand, only that source file needs to be
recompiled. (In both cases, the program of course has to be linked again.) Because function definitions change
far more often than their prototypes, defining functions in source files rather than in header files generally
speeds up development tremendously.

Determining Linkage for a Name
The linkage for each name in a translation unit is determined after the contents of any header files have
been inserted into the source file that is the basis for the translation unit. The linkage possibilities have the
following meanings:
• Internal linkage: The entity that the name represents can only be accessed from
within the same translation unit. For example, the names of non-inline, nonexported, const-qualified variables defined at global or namespace scope have
internal linkage by default.
• External linkage: A name with external linkage can be accessed from other
translation units in addition to the one in which it is defined. In other words,
the entity that the name represents can be shared and accessed throughout the
entire program. In non-modular code, most names that are declared at global or
namespace scope have external linkage by default—including those of functions,
enumerations, classes, templates, and inline or non-const variables. Naturally, all
entities that are exported from a module have external linkage as well.
• Module linkage: An entity name with module linkage is accessible only in translation
units of the same named module. The name of any non-exported entity that is
declared at global or namespace scope within the purview of a module file (in
other words, anywhere after the module file’s optional global module fragment; see
Chapter 11) has module linkage by default.
• No linkage: When a name has no linkage, the entity it refers to can be accessed only
from within the scope that applies to the name. All names that are defined within a
block—local names, in other words—have no linkage.

The static keyword can be used in four different ways:

to create permanent storage for local variables in a function.
to specify internal linkage.
to declare member functions that act like non-member functions.
to create a single copy of a data member.

When a class is (intended as) an abstract class, a protected constructor is exactly right. In that situation you don't want objects to be instantiated from the class but only use it to inherit from.
There are other uses cases, like when a certain set of construction parameters should be limited to derived classes.

Non-public constructors are useful when there are construction requirements that cannot be guaranteed solely by the constructor. 
For instance, if an initialization method needs to be called right after the constructor, or if the object needs to register itself with some container/manager object, this must be done outside the constructor. By limiting access to the constructor and providing only a factory method, you can ensure that any instance a user receives will fulfill all of its guarantees. This is also commonly used to implement a Singleton, which is really just another guarantee the class makes (that there will only be a single instance).

The reason for making the constructor protected, rather than private, is the same as for making any other method or field protected instead of private: so that it can be inherited by children. Perhaps you want a public, non-virtual factory method in the base class, which returns references to instances of the derived classes; 
the derived classes obviously want access to the parent constructors, but you still don't want to be creating them outside of your factory.

*/






int main() {

	int answer{ 42 }; // integer called answer storing value of 42
	std::cout << "This is the answer: " << answer << std::endl;





	return 0; // main doesnt have to have this
}
