# include <iostream>
# include <cstdlib>
# include <vector>
# include <algorithm>
# include <numbers>
# include <cmath>

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

	d_2 = d_1 - vol_sqrt_time;
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

// function for calculation of implied volatility
double implied_volatility(blackScholes bsc, double opt_mkt_price, double x0, double x1, double tol, unsigned max_iter) 
{  // function first takes in a black scholes object, followed by opt_market_price which is obersved in the market
   // x0 and x1 are initial guesses
	double y0 = bsc(x0) - opt_mkt_price;
	double y1 = bsc(x1) - opt_mkt_price;

	double impl_vol = 0.0;
	unsigned count_iter;
	for (count_iter = 0; count_iter <= max_iter; ++count_iter) {  // secant method for working out implied volatility
		if (std::abs(x1 - x0) > tol) {
			impl_vol = x1 - (x1 - x0) * y1 / (y1 - y0);

			x0 = x1;
			x1 = impl_vol;
			y0 = y1;
			y1 = bsc(x1) - opt_mkt_price;  // can have this inside a lambda since we do the same for y1 and y2
		}
		else {
			break;
		}
	}
	if (count_iter < max_iter) {
		return impl_vol;
}
	else {
		return std::nan(" ");
	}

}

double GetOneGaussianBySummation();
double GetOneGaussianByBoxMuller();


// declare a simple implementation of a Monte Carlo call option pricer

double SimpleMonteCarlo(const PayOff& ThePayOff, double Expiry, double Strike, double Spot, double Vol, double r, unsigned long NumberOfPaths);

// classes are much easier to design and think about if you map them to a real world object
// e.g. a option class should only know about the information you'd find on an option's term sheet

// use a class to encapsulate the notion of the pay-off of a vanilla function

class PayOff 
{
public:
	enum class OptionType { Put, Call };  // Option can be a put or a call, if we ever want more than put or call, we can add them to the enum Class
	PayOff(double Strike_, OptionType TheOptionsType_);  // custom constructor
	double operator() (double Spot) const;  // PayOff is a functor, returns a double, given the vaue of spot, the functor returns the payoff
	// functor is const, it does not affect the PayOff object 
private:
	double Strike;  // make these private so we can control how external code can access them
	OptionType TheOptionsType;
};

// if we want the method to be useable by const objects, the method must be const, so const PayOff objects can use the const functor
// remember that objects can be declared const too

PayOff::PayOff(double Strike_, OptionType TheOptionsType_) : Strike(Strike_), TheOptionsType(TheOptionsType_) {

}

double PayOff::operator() (double spot) const {
	
	switch (TheOptionsType) 
	{
	case OptionType::Call:
		return std::max(spot - Strike, 0.0);

	case OptionType::Put:
		return std::max(Strike - spot, 0.0);

	default:
		throw("unknown option type found");
	}
}

// now implement the monte carlo using a payoff object which has the strike hidden in it

double SimpleMonteCarlo(const PayOff& ThePayOff, double Expiry, double Strike, double Spot, double Vol, double r, unsigned long NumberOfPaths) {
	double variance = Vol * Vol * Expiry;
	double rootVariance = std::sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double movedSpot = Spot * std::exp(r * Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; ++i) {
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot * exp(rootVariance * thisGaussian);
		double thisPayOff = ThePayOff(thisSpot);  // payoff passed by reference to const since we have no need to change it
		runningSum += thisPayOff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= std::exp(-r * Expiry);
	return mean;
}


int main() {
	std::cout << "hi";
}
