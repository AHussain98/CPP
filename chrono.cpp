# include <iostream>
# include <chrono>

// chrono library used to handle date and time
using namespace std;
using namespace std::chrono;
using namespace std::literals;     // this allows us to use s and h suffixes

int main(){
auto start = steady_clock::now();
auto hour = 5h;  // 5 hour interval

std::cout << hour.count() << std::endl;

auto s1 = 10000s;
auto s2 = 200s;
auto sec = s1 + s2;
std::cout << sec.count() << std::endl; // we can add second objects, output them with count()


hours h = duration_cast<hours>(sec); // cast seconds into hours

std::cout << h.count() << std::endl;

//  best clock for measuring time intervalsis steady clock, it only goes forwards, one tick at a time, monotonic
// calling a clocks "now" function will return a time_point object, this represents a point in time
auto end = steady_clock::now();
auto elapsed = end - start;
auto elapsed_mil = duration_cast<milliseconds>(elapsed);
std::cout << elapsed_mil.count() << std::endl;
}