# include <iostream>
# include <vector>
# include <map>
# include <utility>
# include <algorithm>
# include <functional>
//# include "boost/date_time/gregorian/gregorian.hpp"
# include "boost/ratio/ratio.hpp"
//using namespace boost::gregorian;
using namespace boost;


/*
 objects that are stored in a
std::vector need to be from classes that can be copied or moved, since elements in a
std::vector are stored by value. This means that a copy is created whenever there is the
need to move the object to a certain position, unless the class has a movable constr
*/

// Time Series Transformations
// Create a class that can perform common time-series transformations
// Time series data filtering is the task of identifying and removing values, both for short term and long term trends, in a sequence of data points

class TimeSeriesTransformations
{
public:
	TimeSeriesTransformations();
	TimeSeriesTransformations(const TimeSeriesTransformations& v);
	~TimeSeriesTransformations();
	TimeSeriesTransformations& operator= (const TimeSeriesTransformations& v);
	void reducePrices(double val);
	void increasePrices(double val);
	void removePricesLessThan(double val);
	void removePricesGreaterThan(double val);
	double getFirstPriceLessThan(double val);
	void addValue(double val);
	void addValues(const std::vector<double>& val);
private:
	std::vector<double> m_prices;
};

TimeSeriesTransformations::TimeSeriesTransformations() : m_prices()
{

}

TimeSeriesTransformations::TimeSeriesTransformations(const TimeSeriesTransformations& v) : m_prices(v.m_prices)
{

}

TimeSeriesTransformations::~TimeSeriesTransformations()
{

}

TimeSeriesTransformations& TimeSeriesTransformations::operator= (const TimeSeriesTransformations& v)
{
	if (this != &v)
	{
		m_prices = v.m_prices;
	}
	return *this;
}

void TimeSeriesTransformations::reducePrices(double val)
{
	std::vector<double> neg(m_prices.size());
	std::transform(m_prices.begin(), m_prices.end(), neg.begin(), std::bind2nd(std::minus<double>(), val));
	m_prices.swap(neg);
}

void TimeSeriesTransformations::increasePrices(double val)
{
	std::for_each(m_prices.begin(), m_prices.end(), std::bind1st(std::plus
		<double>(), val));
}
void TimeSeriesTransformations::removePricesLessThan(double val)
{
	std::remove_if(m_prices.begin(), m_prices.end(), std::bind2nd(std::less
		<double>(), val));
}

void TimeSeriesTransformations::removePricesGreaterThan(double val)
{
	std::remove_if(m_prices.begin(), m_prices.end(), std::bind2nd(std::
		greater<double>(), val));
}
double TimeSeriesTransformations::getFirstPriceLessThan(double val)
{
	auto res = std::find_if(m_prices.begin(), m_prices.end(),
		std::bind2nd(std::less<double>(), val));
	if (res != m_prices.end())
		return *res;
	return 0;
}
void TimeSeriesTransformations::addValue(double val)
{
	m_prices.push_back(val);
}
void TimeSeriesTransformations::addValues(const std::vector<double>& val)
{
	m_prices.insert(m_prices.end(), val.begin(), val.end());
}

// boost can be used to work efficiently with files

// class for handling dates
// Let’s see how to create a class that can be used to determine trading days for common securities, which are negotiated from Monday to Friday.
/*
class Date
{
public:
	enum class DayOfWeek
	{
		Sun,
		Mon,
		Tue,
		Wed,
		Thu,
		Fri,
		Sat
	};

	Date(int year, int month, int day);
	~Date();
	bool isLeapYear();
	Date& operator++();
	bool operator<(const Date& d);
	DayOfWeek getDayOfWeek();
	int daysInterval(const Date& v);
	bool isTradingDay();
	std::string toStringDate(Date::DayOfWeek day);

private:
	int m_year;
	int m_month;
	int m_day;
};

Date::Date(int year, int month, int day) : m_year(year), m_month(month), m_day(day)
{

}

Date::~Date()
{

}

bool Date::isLeapYear()
{
	if (m_year % 4 != 0) return false;
	if (m_year % 100 != 0) return true;
	if (m_year % 400 != 0) return false;
	return true;
}

Date& Date::operator++()
{
	std::vector<int> monthsWith31Days = { 1,3,5,7,8,10,12 };
	if (m_day == 31)
	{
		m_day = 1;
		m_month++;
	}
	else if (m_day == 30 &&
		std::find(monthsWith31Days.begin(),
			monthsWith31Days.end(), m_month) == monthsWith31Days.end())
	{
		m_day = 1;
		m_month++;
	}
	else if (m_day == 29 && m_month == 2)
	{
		m_day = 1;
		m_month++;
	}
	else if (m_day == 28 && m_month == 2 && !isLeapYear())
	{
		m_day = 1;
		m_month++;
	}
	else
	{
		m_day++;
	}
	if (m_month > 12)
	{
		m_month = 1;
		m_year++;
	}
	return *this;
}

int Date::daysInterval(const Date& d)
{
	Date bdate1(m_year, m_month, m_day);
	Date bdate2(d.m_year, d.m_month, d.m_day);

	// boost::gregorian::date_duration duration = bdate1 - bdate2; // not working
//	return (int)duration.days();
	return 0;
}

bool Date::operator<(const Date& d)
{
	if (m_year < d.m_year) return true;
	if (m_year == d.m_year && m_month < d.m_month) return true;
	if (m_year == d.m_year && m_month == d.m_month && m_day < d.m_day) return true;
	return false;
}

Date::DayOfWeek Date::getDayOfWeek()
{
	int day = 1;
	Date d(1900, 1, 1);
	for (; d < *this; ++d)
	{
		if (day == 7) day = 1;
		else day++;
	}
	return (DayOfWeek)day;
}

bool Date::isTradingDay()
{
	DayOfWeek dayOfWeek = getDayOfWeek();
	if (dayOfWeek == DayOfWeek::Sun || dayOfWeek == DayOfWeek::Sat)
	{
		return false;
	}
	return true;
}

std::string Date::toStringDate(Date::DayOfWeek day)
{
	switch (day)  // switch works with ints, chars and enums
	{
	case DayOfWeek::Sun: return "Sunday";
	case DayOfWeek::Mon: return "Monday";
	case DayOfWeek::Tue: return "Tuesday";
	case DayOfWeek::Wed: return "Wednesday";
	case DayOfWeek::Thu: return "Thursday";
	case DayOfWeek::Fri: return "Friday";
	case DayOfWeek::Sat: return "Saturday";
	}
	throw std::runtime_error("unknown day of week");
}

*/
// Designing Numerical Classes
// implement a class that represents a matrix with common associated operations

class Matrix
{
public:
	typedef std::vector<double> Row;
	Matrix(int size, int size2);
	Matrix(int size);
	Matrix(const Matrix& s);
	~Matrix();
	Matrix& operator= (const Matrix& s);

	void transpose();
	double trace();
	void add(const Matrix& v);
	void subtract(const Matrix& v);
	void multiply(const Matrix& v);

	Row& operator[] (int pos);

private:
	std::vector<Row> m_rows;
};

// free operators
Matrix operator+ (const Matrix& s1, const Matrix& s2);
Matrix operator- (const Matrix& s1, const Matrix& s2);
Matrix operator* (const Matrix& s1, const Matrix& s2);

Matrix::Matrix(int size)
{
	for (unsigned i = 0; i < size; ++i)
	{
		std::vector<double> row(size, 0);
		m_rows.push_back(row);
	}
}

Matrix::Matrix(const Matrix& s)
	: m_rows(s.m_rows)
{
}
Matrix::~Matrix()
{
}
Matrix& Matrix::operator=(const Matrix& s)
{
	if (this != &s)
	{
		m_rows = s.m_rows;
	}
	return *this;
}

Matrix::Row& Matrix::operator[](int pos)
{
	return m_rows[pos];
}

void Matrix::transpose()
{
	std::vector<Row> rows;
	for (unsigned i = 0; i < m_rows[0].size(); ++i)
	{
		std::vector<double> row;
			for (unsigned j = 0; j < m_rows.size(); ++j)
			{
				row[j] = m_rows[j][i];
			}
		rows.push_back(row);
	}
	m_rows.swap(rows);
}

double Matrix::trace()
{
	if (m_rows.size() != m_rows[0].size())
	{
		return 0;
	}
	double total = 0;
	for (unsigned i = 0; i < m_rows.size(); ++i)
	{
		total += m_rows[i][i];
	}
	return total;
}

void Matrix::add(const Matrix& s)
{
	if (m_rows.size() != s.m_rows.size() ||
		m_rows[0].size() != s.m_rows[0].size())
	{
		throw new std::runtime_error("invalid matrix dimensions");
	}
	for (unsigned i = 0; i < m_rows.size(); ++i)
	{
		for (unsigned j = 0; j < m_rows[0].size(); ++j)
		{
			m_rows[i][j] += s.m_rows[i][j];
		}
	}
}

void Matrix::subtract(const Matrix& s)
{
	if (m_rows.size() != s.m_rows.size() ||
		m_rows[0].size() != s.m_rows[0].size())
	{
		throw new std::runtime_error("invalid matrix dimensions");
	}
	for (unsigned i = 0; i < m_rows.size(); ++i)
	{
		for (unsigned j = 0; j < m_rows[0].size(); ++j)
		{
			m_rows[i][j] += s.m_rows[i][j];
		}
	}
}

void Matrix::multiply(const Matrix& s)
{
	if (m_rows[0].size() != s.m_rows.size())
	{
		throw new std::runtime_error("invalid matrix dimensions");
	}
	std::vector<Row> rows;
	for (unsigned i = 0; i < m_rows.size(); ++i)
	{
		std::vector<double> row;
		for (unsigned j = 0; j < s.m_rows.size(); ++j)
		{
			double Mij = 0;
			for (unsigned k = 0; k < m_rows[0].size(); ++k)
			{
				Mij += m_rows[i][k] * s.m_rows[k][j];
			}
				row.push_back(Mij);
		}
		rows.push_back(row);
	}
	m_rows.swap(rows);
}

Matrix operator+(const Matrix& s1, const Matrix& s2)
{
	Matrix s(s1);
	s.subtract(s2);
	return s;
}
Matrix operator-(const Matrix& s1, const Matrix& s2)
{
	Matrix s(s1);
	s.subtract(s2);
	return s;
}
Matrix operator*(const Matrix& s1, const Matrix& s2)
{
	Matrix s(s1);
	s.multiply(s2);
	return s;
}

// Using templates to calculate factorials
/* Template-based computation can be seen as a useful strategy to reduce the 
runtime overhead of numeric algorithms. After all, if you’re able to perform some of the 
calculations at compilation time, less time will be necessary to perform the complete 
computation each time you execute the compiled code 

Since functions can return any value at runtime, a traditional function cannot
serve as the basis for compile-time calculations. Instead, you need a way to store values
inside the class as a constant, which can then become readily available to the compiler.
One of the ways to achieve this in C++ is with an enumeration. For example, consider
enum {
 result = 1
};
This fragment defines a constant, integral value that can be later referenced in the
program. If a constant expression is used (instead of a number) in the right-hand side
of the declaration, the result value can be later employed in the program to access the
desired value.*/

// in c++, we can declare templates that take as parameters an int value, or long or char and these can be used to perform compile time clculations

/* In C++ templates, it is not 
possible to write loops, such as for or while, as part of a constant expression. All 
C++ loops are executed at runtime, which makes them unusable for compile-time 
operations. Thankfully, templates provide a specialization mechanism that can be used 
to implement recursion, a technique that can be used to achieve the same effects as 
looping.
For example, if a template uses a single integer parameter, you can specialize that 
parameter with a base case alongside a generic version that handles the common case. 
Together, these cases are enough to simulate a loop that starts with the generic case and 
terminates the computation once the special case is reached. */

template<long N>  // templated type
class Factorial
{
public:
	enum {result = Factorial<N-1>::result * N};
};

template<>
class Factorial<0>  // specialised case, this is the base case that ends the simulated loop
{
public:
	enum {result = 1};
};

template <int N, int P>
class ChoiceNumber {
public:
	enum {result = Factorial<N>::result / (Factorial<P>::result * Factorial<N-P>::result)};
};

void showFactorial()
{
	std::cout << " Some factorial values: " << std::endl;
	std::cout << "fact(5)= " << Factorial<5>::result;
	std::cout << "fact(7)= " << Factorial<7>::result;
	std::cout << "fact(9)= " << Factorial<9>::result;
}

/*
C++ now has the ability to calculate expressions at compilation time using the
constexpr keyword. When using the constexpr keyword, you’re instructing the compiler
to directly perform a calculation during compilation time. This is much simpler than
creating a recursive template class as you have seen in the previous section.
So, for example, if you need to create a factorial function, the following definition
would be enough:
constexpr int factorial(const int n)
{
 return n <= 1 ? 1 : (n * factorial(n - 1));
}
The definition of this function uses constexpr, which means that its value should
be calculated at compilation time, if possible (i.e., if the arguments are constant values
known to the compiler). The remaining of the syntax is similar to what you would write
for a standard function, using a recursive call to compute the value of factorial, based on
the result for a smaller integer number. You can also call this function in the same way
that you call a normal function  */


// The Calmar ratio is a measure of investment returns as compared to possible annual losses
// it is used to compare investments with different risk profiles
// Calmar ratio is the average annual rate of return for a given period divided by the maximum drawdown (loss) during the same period
// if you consider the same rate of return, investments with higher calmer ratio have lower risk during the considered period

// use boost to generate ratios, contain compile time optimisations
typedef boost::ratio<1, 1>::type CalmarRatioType; // standard ratio
typedef boost::ratio<1, 100>::type CalmarRatioBPS;  // percentage points
typedef boost::ratio<1, 1>::type CalmarRatioPerc; // percentage

template <class Ratio>  // we can pass in the ratio type to generate a class that returns information abour the particular ratio
class CalmarRatio {
public:
	CalmarRatio(double calmar, double ret) : m_calmar(calmar), m_ret(ret)
	{

	}
	virtual ~CalmarRatio() {}
	double getReturn()
	{
		return m_return;
	}
	double getDrawDown()  // default behaviour
	{
		return m_return / m_calmar * m_ratio.den;
	}
private:
	Ratio m_ratio;
	double m_calmar;
	double m_return;
};

template<>
double CalmarRatio<CalmarRatioBPS>::getDrawDown()  // specialised behaviour
{
	return m_return / m_calmar * m_ratio.den * 100;
}

boost::ratio<1, 2> one_half;
boost::ratio<1, 3> one_third;

void createCalmarRatio()
{
	CalmarRatio<CalmarRatioPerc> ratio(0.15, 11);
}

void printRatios()
{
	std::cout << "one_third numerator: " << one_third.num
		<< " denominator: " << one_third.den;
}

int main() 
{
	TimeSeriesTransformations ts;
	std::vector<double> vals = { 7, 6.4, 2.16, 5, 3, 7 };
	ts.addValues(vals);
	ts.addValue(6.5);
	ts.reducePrices(0.5);
	std::cout << " price is " << ts.getFirstPriceLessThan(6.0) << std::endl;
	/*
	Date myDate(2015, 1, 3);
	auto dayOfWeek = myDate.getDayOfWeek();
	std::cout << " day of week is "
		<< myDate.toStringDate(dayOfWeek) << std::endl;
	Date secondDate(2014, 12, 5);
	++secondDate; // test increment operator
	++secondDate;
	int interval = myDate.daysInterval(secondDate);
	std::cout << " interval is " << interval << " days" << std::endl;
	*/
	std::cout << "factorial(6) = " << Factorial<6>::result;
	std::cout << "\n choiceNumber(5,6) = "  << ChoiceNumber<6, 2>::result;
	showFactorial();

	CalmarRatio<CalmarRatioPerc> ratio(0.110, 3.12);
	std::cout << "return: " << ratio.getReturn()
		<< " drawdown: " << ratio.getDrawDown() << std::endl;
	CalmarRatio<CalmarRatioBPS> bpsRatio(480, 2.15);
	std::cout << "return: " << bpsRatio.getReturn()
		<< " drawdown: " << bpsRatio.getDrawDown() << std::endl;

	return 0;
}