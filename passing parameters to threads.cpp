#include <iostream>
#include <string>
#include <thread>
#include <chrono> // use this for time
//#include "common.h"

// a thread class object has a default constructor (useless), a move constructor and an initialization constructor which we can use for passing arguments to teh thread object

void func_1(int x, int y) {
	std::cout << "X + Y = " << x + y << '\n';
}

void func_2(int &x) {
	while (true) {
		std::cout << x << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void run() {
	int p = 8;
	int q = 9;
	std::thread thread1(func_1, p, q); // pass p and q variables to the function by adding them as csv arguments
	thread1.join();
}

void run_again() {
	int x = 9;
	std::cout << "the value of x is " << x << '\n';
	std::thread thread2(func_2, std::ref(x)); // thread automatically begins once the object has been created, this kicks off immediately
	//wrap the variable we want to pass in std::ref() to ensure it gets passed by reference
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	x = 15; // value of bound object changes
	std::cout << "the value of x is now " << x << '\n';
	thread2.join(); // when you join(), this just means stop teh calling thread (main in this case) until the thread2 is done
}

int main() {
	run_again(); // this is run by the main thread


}