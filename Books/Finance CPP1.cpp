# include <iostream>
# include <cstdlib>
# include <vector>
# include <algorithm>
# include <numbers>

std::vector<int> v{ 1,2,3 };

std::size_t v_size = v.size();  // size_t means unsigned long int, enough bytes to represent the size of any type
// size_t is returned by the vectors .size() function

// prefer range based for loops with vectors

// enums are useful for switch statements


// lets try building a black scholes class
// we can apply an enum class to represent a call or put option
enum class PayoffType {
	Call = 1,
	Put = -1
};

class blackScholes {
public:
	blackScholes(double strike, double spot, double rate, double time_to_exp, PayoffType pot);  // define custom constructor
	// the constructor takes in each of the required arguments except for volatility which is used by the () operator to compute and return price, which allows us to reuse the class later when computing the implied volatility numerically
	double operator() (double vol);  // creates a functor, blackScholes() is now a function that can be called

private:
	void compute_norm_args(double vol);  // compute d1 and d2
	double strike_, spot_, rate_, time_to_exp_, sigma_;
	PayoffType pot_;
	double d_1{ 0.0 };  // d1 with default value
	double d_2{ 0.0 };  // d2 with default value
}; // d1 and d2 can be given default values since the constructor initialiser list is only responsible for data members that depend on input parameters


blackScholes::blackScholes(double strike, double spot, double rate, double time_to_exp, PayoffType pot) 
	: strike_{strike}, spot_{spot}, rate_{rate}, time_to_exp_{time_to_exp}, pot_{pot} {}
// good practice to initalise members at construction and in order they were declared

// private helper function, compute norm args:
void blackScholes::compute_norm_args(double vol) {
	
	double numer = log(spot_ - strike_) + rate_ * time_to_exp_ + 0.5 * time_to_exp_ * vol * vol;

	double vol_sqrt_time = vol * sqrt(time_to_exp_);

	d_1 = numer / vol_sqrt_time;

	d_2 = d1 - vol_sqrt_time;
}



// valueation of the option then begins with round bracket operator, taking volatility as input

double blackScholes::operator() (double vol) {
	int phi = static_cast<int> (pot_);  // phi depends on the payoff type

	double opt_price = 0.0;

	if (time_to_exp_ > 0.0) {
		compute_norm_args(vol);

		auto norm_cdf = [](double x) -> double { return (1.0 + std::erf(x / 1.41421356)) / 2.0; };  // lambda for cumulative distribution function

		double nd_1 = norm_cdf(phi * d_1); // +/-1 * d_1

		double nd_2 = norm_cdf(phi * d_2); 

		double disc_fctr = std::exp(-rate_ * time_to_exp_);  // discount factor

		 opt_price = phi * (spot_ * nd_1 - strike_ * nd_2);
	}

	else {
		 opt_price = std::max(phi * (spot_ - strike_), 0.0);  // only intrinsic value remains
	}

	return opt_price;
}

// using the payoff as an enum class and casting it allows us to avoid several extra lines in an if/else statement


int main() {
	std::cout << "hi";
}