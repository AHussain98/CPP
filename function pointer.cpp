 # include <iostream>
// the execuatable code that is executed when a function is stored in memory has an address
// we can point to this address using a function pointer
// func_ptr is a pointer to the start of the function code
using pfunc = void (*)(int);
void func(int a){
    std::cout << a;
}

void func2(int b, pfunc func_ptr){
    (*func_ptr)(b);
}


 int main(){
  auto func_ptr = &func; // lhs here is actually void (*func_ptr)(int), the & is optional
  // we can then call the function via the pointer
 // (*func_ptr)(2);   // the * is optional

  // you can pass a function pointer to another function, and access the function in the other function through dereferencing

  func2(5,func_ptr);
 }