# include <iostream>
# include <vector>
# include <cmath>

// lets calculate a simple interest rate
// interest rates determine how much a financial institution will pay in exchange for holding a cash deposit over a period of time
// simple IR calculation V = P(1+R) V is future value after a single period, P is present value of the deposit

class IntRateCalculator {  // class that is responsible for the calculation
public:  // you should create classes that have thier own constructors, copy constructors, assignment operators and destructors, else the implementation is left to the compiler
	IntRateCalculator(double rate);
	IntRateCalculator(const IntRateCalculator& v);
	IntRateCalculator& operator= (const IntRateCalculator& v);
	~IntRateCalculator();
	double singlePeriod(double value);

private:
	double m_rate;  // storing current interest rate
};

// singlePeriod member function returns the future value of a deposit after a single period
// double used instead of float for extra precision

/* The code with all functions inlined is bigger. Therefore it occupies more cache space, and crucially it evicts more other code from cache. A cache miss is much more expensive than a jump, so it is by no means a guaranteed win to increase code size in order to reduce the number of jumps. Optimizing compilers use a better (and more complex) strategy than just, "inline everything possible".*/
// in high performance c++, its common to see all member functions inlined to achieve higher performance than regular function calls

inline double IntRateCalculator::singlePeriod(double value)  // inlined to suggest the member function be directly embedded in the code that calls it 
{  
	double f = value * (1 + this->m_rate);
	return f;
}

IntRateCalculator::IntRateCalculator(double rate) : m_rate(rate)
{

}

IntRateCalculator::~IntRateCalculator()
{

}

IntRateCalculator::IntRateCalculator(const IntRateCalculator& v) : m_rate(v.m_rate)
{

}
 
IntRateCalculator& IntRateCalculator::operator= (const IntRateCalculator& v)
{
	if (this != &v) {
		this->m_rate = v.m_rate;
	}
	return *this;
}


// Interest can be calculated as a discrete or continous compounding process.
// For discrete compounding, we assume interest is paid at only regular intervals
// Discrete compounded interest rate formula is V = P(1 + R)^N, N is number of periods
// Continous compounding means we assume the compounding doesnt happen in discrete steps 
// but that the payments are made overtime, this can be used to determine the upper bound of the desired future value of the item
// Calculation of continous interest rate compounding is V = Pe^RN, V is desired future value

class CompoundIntRateCalculator {
public:
	CompoundIntRateCalculator(double rate);
	CompoundIntRateCalculator(const CompoundIntRateCalculator& v);
	CompoundIntRateCalculator& operator= (const CompoundIntRateCalculator& v);
	~CompoundIntRateCalculator();

	double multiplePeriod(double value, int numPeriods);
	double continousCompounding(double value, int numPeriods);

private:
	double m_rate;
};

CompoundIntRateCalculator::CompoundIntRateCalculator(double rate) : m_rate(rate)
{

}

CompoundIntRateCalculator::~CompoundIntRateCalculator()
{

}

CompoundIntRateCalculator::CompoundIntRateCalculator(const CompoundIntRateCalculator& v) : m_rate(v.m_rate)
{

}

CompoundIntRateCalculator& CompoundIntRateCalculator::operator= (const CompoundIntRateCalculator& v)
{
	if (this != &v)
	{
		this->m_rate = v.m_rate;
	}

	return *this;
}

double CompoundIntRateCalculator::multiplePeriod(double value, int numPeriods)
{
	double f = value * std::pow(1 + m_rate, numPeriods);
	return f;
}

double CompoundIntRateCalculator::continousCompounding(double value, int numPeriods)
{
	double f = value * std::exp(m_rate * numPeriods);
	return f;
}

// Modelling cash flows


int main() {
	std::cout << "hi!" << std::endl;
	double rate = 0.5;
	double value = 30'000;

	IntRateCalculator calc_1(rate);
	std::cout << calc_1.singlePeriod(value) << std::endl;

	double compound_rate = 0.01;
	double compound_value = 20'000;
	int num_periods = 6;
	CompoundIntRateCalculator comp_1(compound_rate);
	std::cout << comp_1.multiplePeriod(compound_value, num_periods) << std::endl;
	std::cout << comp_1.continousCompounding(compound_value, num_periods) << std::endl;
}