#include <iostream>
# include <string>

int main(){




    std::string str {"Zello"};
    std::string str2 {"HZZZZZZZZZZZZ!"}; // the comparison is made on the first char that is different

    std::cout << std::max(str,str2);
}