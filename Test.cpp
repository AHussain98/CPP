#include <iostream>
using namespace std;

int main() {

struct boyo {
	int x;
	string y;
};

boyo boyo1;
boyo *b_point = &boyo1;

b_point->x = 100;
b_point->y = "this works!";

cout << b_point->x 
;

return 0;
 }



