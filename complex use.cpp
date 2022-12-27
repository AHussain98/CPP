#include <iostream>
using namespace std;
#include "Complex.cpp"

int main() {
	Complex c1(4,5);
	c1.display();
	Complex c2(6,7);
//	c1.add(c2);
	c1.display();
	c1.multiply(c2);
	c1.display();
}
