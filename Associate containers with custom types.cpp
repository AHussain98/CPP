# include <iostream>
# include <map>
# include <string>

// custom types are not builtins or library objects, these can be custom classes, for example
// custom types can be used with all the associative containers, map, set , multimap and multiset, ordered and unordered versions
// we can use custom types as either the key or value or both

// we are going to create a container to represent a library of books
// we want to be able to searhc the container to find the books written bu an author (key-value)
// an author can write more than one book (duplicate keys)
// the container will be a multumai, key is a string, value is an object of a class


class Book{
std::string title;
std::string publisher;

public:
    Book(std::string title, std::string publisher) : title(title), publisher(publisher){

    }

    friend std::ostream& operator << (std::ostream& os, const Book& bk){     // return an output stream object, needs to be a friend so it can access private memebrs
        os << "(" << bk.title << "," << bk.publisher << ")";  // we're going to overload the output operator so when we pass it a book object it will print the title and publisher
        return os;
    }

};

std::multimap<std::string, Book> library;  // string here will be author

int main(){

    Book b1("Trading engineer interview guide", "Brexit");
    library.insert({"kwasi", b1});   // insert a pair

    for (auto i : library){
        std::cout << i.first << "," << i.second;
    }

    // ordered associative containers use the < operator of their keys to sort their elements
    // the compiler will give an error if this is not defined
    // we need to define a < operator for our class
    // to ensure our books are sorted correctly, the < operator needs to compare the authors first, then the titles

    // unordered associative containers use the hash value of their keys to organise elements
    // need to specialise std::hash<T>
    // need to define operator == for our class

    // identity -> the objects occupy teh same memory but are referred to differently, corresponds to single copy of a book
    // equality -> the objects occupy different memory but have the same values, corresponds to two different copies of teh same book
    // equivalence -> important values are teh same, but unimportant values are not, e.g. hardback vs paperback, will sort as if they are equal


}