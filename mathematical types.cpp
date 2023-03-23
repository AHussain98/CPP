# include <iostream>
# include <complex>
// c++ has complex numbers in std::complex, these are implemented as a templated type


int main(){

std::complex<double> cn{3.0,4.0};
std::cout << cn << std::endl;
// ++cn doesnt work,
// you'd have to do cn += 1.0

//c++14 provides the literal suffix i, this returns a std::complex object with real part 0 (by default)

//auto s = 3.0 + 2i; // complex object s generated

//std::cout << s;

//pow() used to get power of somehtin by madgnitued of its econd argument
//abs() for absolute value

}