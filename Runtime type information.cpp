# include <iostream>

// runtime type information relates to the dynamic type of the object : typeid, type_info and dynamic_cast
// std::typeid() returns information about the dynamic type of its argument, defined in <typeinfo>
// std::type_info is a class defined in <typeinfo>, typeid() returns a type_info object, it contains information about the dynamic type of an object
// type_info::name() member function returns a c-style string, unique for each type, the ocntents of the string are compiler specific
// type_info also has a hash_code() member function, this returns a unique number for each dynamic type

// dynamic_cast converts pointer to base to a pointer to derived, also applies to references
// it allows us to check at runtime whether a base-to-derived conversion is possible, this only works if teh dynamic type of the base object is derived
// if it fails, it returns nullptr (for references, it throws std::bad_cast exception
// sowe cal also conevrt reference to base to reference to derived



int main(){



}