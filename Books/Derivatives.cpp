# include <iostream>
# include <vector>
# include <cmath>
# include <string>

// Derivatives are contracts that have a price based on the properties of an underlying asset.
// All derivatives that are traded in the market can be analyzed using a random walk model
// In a random walk model, the prices of securities are studied under the assumption that their changes are random
// The random walk model for derivative pricing results in a set of equations that determine the behaviour of proces as time passes
// These equations can be solved to determine the fair price, this is the price that neither the buyers or sellers have any advantage
// fair pricing models allow no arbitrage

// A credit default swap (CDS) is a derivative that allows investors to bet on the solvency 
// of a particular institution.In this case, the underlying asset is defined as the value of a
// business minus the liabilities it currently has.Solvency is then defined as the situation in
// which the value of the business is superior to its liabilities

// A collateralized debt obligation (CDO) is a financial derivative product based on the 
// cash flow of a collection of loans.The collateralization process makes it possible to split
// the cash flows among different investors based on the characteristics of individual loan
// originations.

// Equations used to model the future price of derivatives are generally based on Black Scholes
// which describe the properties of procing models when considering these parameters:
// price of the underlying asset
// strike price
// current interest rate
// volatility of the price of the underlying asset
// time to expiry

// when working with options, the BS equation results in a formula that returns the price of a call or put option, which depends on the desired strike
// more exact formulas can be used depending on exercise type, Euro or US

// numerical methods and simulation methods have been devised to calculate prices and to solve the black scholes model 

// another technique used to determine the price of derivatives is the binomial tree.
// binomial tree is a technique to organise the computation necessary to determine derivative prices in a step by step fashion
// the root of the tree is the original price, at each node there are two possible directions for the new price, which can be calculated via equations
// the complete tree can be used to answer questions about the fair price of the derivative at particular strike prices and time periods
// the complete algorithm for binomial trees has 3 main steps:
// forward phase, starting at time zero with an initial price, total time is divided into discrete steps and at each step a new set of nodes is created. these nodes represent the underlying price going up and down. This phase ends when maturity date is reached
// payoff phase, the profit (payoff) of each node is calculated, the calculation starts from the maturity date 
// the backward phase, the computation of the payoff continues moving backwards in time, using values calculated in each previous phase as the start point. ends when initial node is reached

// simulation models are also called monte-carlo models, and are another approach to solving problems involving differential equations
// simulation models suggest that equations for derivatives pricing generally dont have a closed mathemtaical solution and its best to run a simulation of proce evolution
// simulation runs according to random distribution 
// To find the price of a derivative security, the basic step is to develop a random walk 
// model for the security.As discussed previously, derivatives are based on the idea that
// underlying prices are always moving in an unpredictable, random way. A Monte Carlo
// algorithm will use this property to simulate the movements of the underlying asset for a
// large number of times.The random fluctuations are determined with a random number
// generator, according to the parameters that have been previously observed for the asset,
// such as volatility, current interest rate, and observed price of the underlying instrument.
// If the simulation is properly performed, a Monte Carlo algorithm will converge to a
// particular value of derivative price, according to the assumptions of the Black - Scholes
// model.The interpretation of these simulated runs can then be used to determine the
// price of a particular contract

// a random walk is a process that simulates stochastic movement
//  Random walks are important in the analysis of price movements: if we 
// assume that such movements are random(as we can assume at least for relatively small
// timeframes), then a random walk can be used to model the change in prices for several
// classes of financial assets.For example, the price of a set of stocks can be analyzed as a
// random walk, from which we can derive the probability of its change in the near future.

// class that generates a random walk and stores the data in an std::vector
// class uses a vector to hold the elements of the random walk so they can later be plotted

class RandomWalkGenerator {
public:
	RandomWalkGenerator(int size, double start, double step); // size is time to expiry, start is start value, step is number of steps
	RandomWalkGenerator(const RandomWalkGenerator& v); // copy constructor
	~RandomWalkGenerator();
	RandomWalkGenerator& operator= (const RandomWalkGenerator& v);

	std::vector<double> generateWalk();  // returns a vector with values of the random wlk

	double computeRandomStep(double currentPrice);  // returns a single step of the random walk
private:
	int m_numSteps; 
	double m_stepSize; // size of each step in percentage points
	double m_initialPrice;  // starting price

};

RandomWalkGenerator::RandomWalkGenerator(int size, double start, double step) : m_numSteps(size), m_stepSize(step), m_initialPrice(start)
{

}

RandomWalkGenerator::RandomWalkGenerator(const RandomWalkGenerator& v) : m_numSteps(v.m_numSteps), m_initialPrice(v.m_initialPrice), m_stepSize(v.m_stepSize)
{
	
}

RandomWalkGenerator::~RandomWalkGenerator()
{

}

RandomWalkGenerator& RandomWalkGenerator::operator=(const RandomWalkGenerator& v)
{
	if (this != &v)
	{
		m_initialPrice = v.m_initialPrice;
		m_numSteps = v.m_numSteps;
		m_stepSize = v.m_stepSize;
	}

	return *this;
}

// return a single step of the random walk

double RandomWalkGenerator::computeRandomStep(double currentPrice)
{
	constexpr int num_directions = 3;
	int r = rand() % num_directions;  // 1 in 3 chance of the price going up, staying same or goinf down
	double val = currentPrice;
	if (r == 0)
	{
		val += (m_stepSize * val); // price up
	}
	else if (r == 1)
	{
		val -= (m_stepSize * val);  // price down
	}
	return val;
}

// generates numbers within the constraints set by the constructor
std::vector<double> RandomWalkGenerator::generateWalk()
{
	std::vector<double> walk;
	double prev = m_initialPrice;

	for (int i = 0; i < m_numSteps; ++i)
	{
		double val = computeRandomStep(prev);
		walk.push_back(val);
		prev = val;
	}
	return walk;
}

// this random walk simulates how a monteCarlo simulation can operate

// moving averages calculation
// given a particular equity investment, determine the simple moving average and the exponential moving average for a sequence of closing prices
/* The moving average can be calculated using a simple average formula that is 
repeated for each new period. Given prices p1, p2, ..., pN, the general formula for a 
particular time period is given by
MA = (1/N) (p1 + p2 + ... + pN) */

// to calculate the moving average of a stock, we create a class that stores a sequence of prices in a vector
// exponential moving average can also be calculated
/*The main step of the EMA calculation is the addition of new values that are weighted 
by the multiplier. The default multiplier r for EMA computation is given by
P = 2/(N + 1)
This multiplier gives greater weight to new values, thus making the EMA more 
responsive to price changes than the simple moving average.*/

class MACalculator
{
public:
	MACalculator(int period);
	MACalculator(const MACalculator& v);
	MACalculator& operator= (const MACalculator& v);
	~MACalculator();

	void addPriceQuote(double close);
	std::vector<double> calculateMA();
	std::vector<double> calculateEMA();
private:
	int m_numPeriods; // number of periods used in the calculation
	std::vector<double> prices;
};

MACalculator::MACalculator(int period) : m_numPeriods(period)
{

}

MACalculator::MACalculator(const MACalculator& v) : m_numPeriods(v.m_numPeriods)
{

}

MACalculator::~MACalculator()
{

}

MACalculator& MACalculator::operator= (const MACalculator& v)
{
	if (this != &v)
	{
		m_numPeriods = v.m_numPeriods;
		prices = v.prices;
	}
	return *this;
}

std::vector<double> MACalculator::calculateMA()
{
	std::vector<double> ma;
	double sum = 0;
	for (int i = 0; i < prices.size(); ++i)
	{
		sum += prices[i];
		if (i >= m_numPeriods)  // caluclate moving average for new prices after the limit has been hit
		{
			ma.push_back(sum / m_numPeriods);
			sum -= prices[i - m_numPeriods];  // update sum so the first item over the sequence is removed
		}
	}
	return ma;
}

std::vector<double> MACalculator::calculateEMA()
{
	std::vector<double> ema;
	double sum = 0;
	double multiplier = 2.0 / (m_numPeriods + 1);
	for (int i = 0; i < prices.size(); ++i)
	{
		sum += prices[i];
		if (i == m_numPeriods)
		{
			ema.push_back(sum / m_numPeriods);
			sum -= prices[i - m_numPeriods];
		}
		else if (i > m_numPeriods)
		{
			double val = (1 - multiplier) * ema.back() + multiplier * prices[i];
			ema.push_back(val);
		}
	}

	return ema;
}

void MACalculator::addPriceQuote(double close)
{
	prices.push_back(close);
}

// Calculating volatility of a particular equity instrument
// volatility can be calculated useing max val - min val, or by finding the average of a range of values over a time period
// or by using the statistical definition of standard deviation

class VolatilityCalculator
{
public:
	VolatilityCalculator();
	~VolatilityCalculator();
	VolatilityCalculator(const VolatilityCalculator& v);
	VolatilityCalculator& operator= (const VolatilityCalculator& v);

	void addPrice(double Price);
	double rangeVolatility();
	double stdDev();
	double mean();
	double avgDailyRange();

private:
	std::vector<double> m_prices;
};

VolatilityCalculator::VolatilityCalculator()
{
}
VolatilityCalculator::~VolatilityCalculator()
{
}
VolatilityCalculator::VolatilityCalculator(const VolatilityCalculator& v)
	: m_prices(v.m_prices)
{
}
VolatilityCalculator& VolatilityCalculator::operator =(const
	VolatilityCalculator& v)
{
	if (&v != this)
	{
		m_prices = v.m_prices;
	}
	return *this;
}

void VolatilityCalculator::addPrice(double price)
{
	m_prices.push_back(price);
}

double VolatilityCalculator::rangeVolatility()
{
	if (m_prices.size() < 1)
	{
		return 0;
	}

	double min = m_prices[0];
	double max = min;
	for (int i = 1; i < m_prices.size(); ++i)
	{
		if (m_prices[i] < min)
		{
			min = m_prices[i];
		}
		if (m_prices[i] > max)
		{
			max = m_prices[i];
		}
	}

	return max - min;
}

double VolatilityCalculator::avgDailyRange()
{
	unsigned long n = m_prices.size();
	if (n < 2)
	{
		return 0;
	}
	double previous = m_prices[0];
	double sum = 0;
	for (int i = 1; i < m_prices.size(); ++i)
	{
		double range = std::abs(m_prices[i] - previous);
		sum += range;
	}
	return sum / n - 1;
}

double VolatilityCalculator::mean()
{
	double sum = 0;
	for (int i = 0; i < m_prices.size(); ++i)
	{
		sum += m_prices[i];
	}
	return sum / m_prices.size();
}

double VolatilityCalculator::stdDev()
{
	double m = mean();
	double sum = 0;
	for (int i = 0; i < m_prices.size(); ++i)
	{
		double val = m_prices[i] - m;
		sum += val * val;
	}
	return std::sqrt(sum / (m_prices.size() - 1));
}

// Instrument correlation
// given a sequence of closing prices for the last N periods, calculate the correlation between two equity instruments
// two equities that are highly correlated (e.g. coke and pepsi) can use this property to accurately model thier prices

// lets create two classes, a time series class for calculating values specific to a single time series, such as the average or standard deviation
// the second class is the correlation calculator, which collects the data desired for the time series and computes the correlation

class TimeSeries
{
public:
	TimeSeries();
	TimeSeries(const TimeSeries&);
	~TimeSeries();
	TimeSeries& operator= (const TimeSeries& v);

	void addValue(double val);
	double stdDev();
	double mean();
	size_t size();
	double elem(int i);

private:
	std::vector<double> m_values;
};

TimeSeries::TimeSeries() : m_values()
{

}

TimeSeries::~TimeSeries()
{

}

TimeSeries::TimeSeries(const TimeSeries& v) : m_values(v.m_values)
{

}

TimeSeries& TimeSeries::operator= (const TimeSeries& v)
{
	if (this != &v)
	{
		m_values = v.m_values;
	}
	return *this;
}

void TimeSeries::addValue(double val)
{
	m_values.push_back(val);
}

double TimeSeries::mean()
{
	double sum = 0;
	for (int i = 0; i < m_values.size(); ++i)
	{
		sum += m_values[i];
	}
	return sum / m_values.size();
}

double TimeSeries::stdDev()
{
	double m = mean();
	double sum = 0;
	for (int i = 0; i < m_values.size(); ++i)
	{
		double val = m_values[i] - m;
		sum += val * val;
	}
	return std::sqrt(sum / (m_values.size() - 1));
}

size_t TimeSeries::size()
{
	return m_values.size();
}

double TimeSeries::elem(int pos)
{
	return m_values[pos];
}

class CorrelationCalculator
{
public:
	CorrelationCalculator(TimeSeries& a, TimeSeries& b);
	~CorrelationCalculator();
	CorrelationCalculator(const CorrelationCalculator& v);
	CorrelationCalculator& operator= (const CorrelationCalculator& v);

	double correlation();

private:
	TimeSeries& m_tsA;
	TimeSeries& m_tsB;  // TimeSeries objects are members of the CorrelationCalculator
};

CorrelationCalculator::CorrelationCalculator(TimeSeries& a, TimeSeries& b) : m_tsA(a), m_tsB(b)
{

}

CorrelationCalculator::~CorrelationCalculator()
{
}

CorrelationCalculator::CorrelationCalculator(const CorrelationCalculator& c)
	: m_tsA(c.m_tsA),
	m_tsB(c.m_tsB)
{
}

CorrelationCalculator& CorrelationCalculator::operator=(const
	CorrelationCalculator& c)
{
	if (this != &c)
	{
		m_tsA = c.m_tsA;
		m_tsB = c.m_tsB;
	}
	return *this;
}

double CorrelationCalculator::correlation()
{
	double sum = 0;
	double meanA = m_tsA.mean();
	double meanB = m_tsB.mean();

	if (m_tsA.size() != m_tsB.size())
	{
		// there are a different number of observations so fail
		return -1;
	}

	for (int i = 0; i < m_tsA.size(); ++i)
	{
		auto val = (m_tsA.elem(i) - meanA) * (m_tsB.elem(i) - meanB);
		sum += val;
	}

	double stDevA = m_tsA.stdDev();
	double stDevB = m_tsB.stdDev();
	sum /= (stDevA * stDevB);
	return sum / (m_tsB.size() - 1);
}



int main() {

	// 100 steps starting at $30
	RandomWalkGenerator rw(100, 30, 0.01);
	std::vector<double> walk = rw.generateWalk();
		
		for (int i = 0; i < walk.size(); ++i)
		{
			std::cout << ", " << i << ", " << walk[i] << std::endl;
		}
	std::cout << std::endl;
	return 0;
}

