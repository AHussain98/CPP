# include <iostream>
# include <vector>
# include <map>
# include <utility>
# include <algorithm>
# include <functional>
//# include "boost/date_time/gregorian/gregorian.hpp"
# include "boost/ratio/ratio.hpp"
//using namespace boost::gregorian;
# include <string>
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

// encapsulation means hiding data, which becomes the member varoables of the target class
// consider a credit default swap
enum CDSUnderlying {
	CDSUnderlyingBond,
	CDSUnderlyingCash
};

class CDSContract {
public:
	CDSContract();
	CDSContract(const CDSContract& p);
	~CDSContract();
	CDSContract& operator= (const CDSContract& p);
	std::string counterpart() { return m_counterpart; }
	void setCounterpart(const std::string& s); //{ m_counterpart = s; }  // any changes happening to m_counterpart and m_payoff will only occur through an operation on CDSContract
	double payoff() { return m_payoff; }
	void setPayoff(double payoff) { m_payoff = payoff; }
	virtual double computeCurrentValue(const Date& d);

private:
	std::string m_counterpart;
	CDSUnderlying m_underlying;
	double m_payoff;
	int m_term;
	double m_spreadCost;

	const static double kStandardPayoff; // made static because its the same for all members of the class
};

void CDSContract::setCounterpart(const std::string& s)
{
	m_counterpart = s;
	setPayoff(kStandardPayoff);
}

class LoanOnlyCDSContract : public CDSContract
{
public:
	void changeLoanSource(const std::string& s);
	virtual double computeCurrentValue(const Date& d);
private:
	std::string m_loanSource;
};

// Whenever the counterpart for the contract changes, the class reacts by resetting the 
// payoff to a standard value(defined by the constant kStandardPayoff).That would not
// be possible if the m_counterpart data member were not properly encapsulated into the CDSContract class

/* Inheritance requires that the new class be used in a context similar to the 
original class. Therefore, inheritance shouldn’t be used to create classes that have 
just a superficial similarity to the original class. In particular, a class that inherits 
from a base class could be used in the same code as the original class. If this is 
not true for the new class you need, it is better to create a separate class with a 
specialized interface.*/

// you can pass a derived class to a function that expects an object of the base class

/* 
The first step in using polymorphism via virtual functions is to understand how they
differ from regular member functions. When a virtual function is called, the compiler
has to determine the type of call and translate it into binary code that will perform the
call to the correct implementation. This is done in C++ using the so-called virtual table
mechanism.
A virtual table is a vector of functions that is created for each class that uses at least
one virtual function. The virtual table stores the addresses of virtual functions that have
been declared for that particular type */

/* Although creating class hierarchies is a useful technique for code maintenance and 
sharing, inheritance may not be the best strategy for code organization in some cases. It 
is important to be able to identify the situations in which other approaches would work 
better. Here are some potential disadvantages of using inheritance:
• Increased coupling between classes: Once you decide to use 
inheritance, there is a big interdependence between classes. A small 
change in the base class can affect all descendent classes. If there is 
a situation where the base class can vary frequently in functionality 
and responsibilities, then inheritance may not be the best solution.
• Physical dependencies at compilation time: In C++, inheritance also 
creates a compile-time dependency between classes. To generate 
correct code, the C++ compiler needs to access the definition of each 
base class. This may result in increased compilation time, which is 
sometimes undesirable, especially in large software projects.
• Increased information coupling: Class hierarchies may also require 
developers to learn the multiple implementations of different classes 
at different levels. This is necessary especially when classes are not 
well designed and information about their operations is not clear.*/

/* Composition is an alternative to inheritance, where you can use the behavior of an 
object without the dependency caused by direct class/subclass relationship.
To use object composition, you need to store the object that has the desired behavior 
as a member variable for the containing object. This is the basic strategy, which can be 
implemented in at least three ways in C++:
• Storing a pointer to an object: In this case, only a pointer to the 
object is stored as part of the class. This option allows an object to be 
created inside the class or passed as a parameter from a user of the 
class and then stored in a member variable.

• Storing a reference to an object: This option allows the class to receive 
a reference to an existing object, but doesn’t allow the object to be 
created after the constructor is executed. A reference in C++ cannot 
be reassigned, which leads to a requirement that the stored object 
needs to be valid the whole time the container object exists.
• Storing the object directly as a member variable: In this case, the 
containing class assumes complete responsibility for storing the 
required object. Here, it is also necessary for the compiler to know 
the exact size and type of the object stored as a member variable, 
which reduces the flexibility of this method.
With object composition, a class can use the functionality provided by another class 
without the use of inheritance*/

// Design patterns for options processing
// Factory: Instead of asking clients to perform the initialization steps, factory methods provide a simple interface that can be called to create the objectand return a reference.
// Singleton: a class that can have at most one active instance
// Observer: allows objects to receive notifications for important events occurring in the system. This pattern also reduces the coupling between objects in the system, since the generator of notification events doesn’t need to know the details of the observers
// Visitor: The visitor pattern allows a member function of an object to be called in response to another dynamic invocation implemented in a separate class.


// Factories are used to indirectly create objects of a particular class
/* , using the factory method design pattern, it is possible to avoid the use of the 
new keyword to create an object, along with the parameters required by the constructor.
The factory design pattern allows an object to be created through a member function 
of the desired class, so that the client doesn’t need to create the object directly. */
// Factory methods in c++ are implemented as static member functions

/* A 
situation where the use of a factory method is desirable is when you need to load data 
objects. The data source used can vary from a local file to a URL, and the parsing of 
that data is not an important part of the overall algorithm. In that case, abstracting the 
creation of the data source can be an important application of the factory method */

// When using factory methods, it is frequently useful to hide the real implementation of the constructor.This can be done through careful use of the private modifier.

class DataSource {
private:
	DataSource(const std::string& name);  // private constructors
	DataSource(const DataSource& p);
	DataSource& operator= (const DataSource& p);
public:
	~DataSource();  // must be public so clients can use delete
	static DataSource* createInstance();  // static function, public, used to generate an instance
	void readData();
private:
	std::string m_dataName;
};


DataSource::DataSource(const std::string& name) : m_dataName(name)
{

}

DataSource::DataSource(const DataSource& p) : m_dataName(p.m_dataName)
{

}

DataSource& DataSource::operator= (const DataSource& p)
{
	if (this != &p)
	{
		m_dataName = p.m_dataName;
	}
	return *this;
}

DataSource::~DataSource()
{
}

DataSource * DataSource::createInstance()
{
	std::string sourceName;
	// Complex method used here to find sourceName and other construction 
		DataSource* ds = new DataSource(sourceName);
	return ds;
}

void DataSource::readData()
{
	// Read data here...
}

// Not member function!
void useDataSource()
{
	// DataSource *source = new DataSource(""); // this will not work!
	DataSource* source = DataSource::createInstance();
	source->readData();
	// Do something else with data
	delete source;
}

// singleton pattern, a single object is used to represent the whole class, so there is a central location where services managed by that class can be redirected
// clearing house can be represented as a singleton
/*  A clearing house is an institution that provides clearing services for
trades on options and derivatives.The clearing house makes sure that every trade has
collateral so that counterpart risk is reduced, among other attributions.For example, if a
trader sells options in a particular instrument, the clearing house will make sure that the
trader has enough margin to satisfy the requirements of that particular trade.
While a clearing house provides important services in the trading industry, most
applications need to connect to a single clearing house.Thus, creating a single object to
represent the clearing house is an obvious implementation technique for this situation.  */

class clearingHouse {
private:
	clearingHouse();  // constructors, destructor, assignment operator all made private
	clearingHouse(const clearingHouse& p);
	clearingHouse& operator=(const clearingHouse& p);
	~clearingHouse();

public:
	static clearingHouse& getClearingHouse();
	void clearTrade(const Trade& t);

private:
	static clearingHouse* s_clearingHouse;  // the private member is a pointer to the only instance
};

clearingHouse* clearingHouse::s_clearingHouse = nullptr;  // set this to null initially

clearingHouse::clearingHouse() // private constructor, cannot be used by clients
{
}
clearingHouse::~clearingHouse() // this is private and cannot be used by clients
{
}

clearingHouse& clearingHouse::getClearingHouse()
{
	if (!s_clearingHouse)
	{
		s_clearingHouse = new clearingHouse();
	}
	return *s_clearingHouse;
}
void clearingHouse::clearTrade(const Trade& t)
{
	// Trade is processed here
}
void useClearingHouse()
{
	Trade trade;
	clearingHouse& ch = clearingHouse::getClearingHouse();
	ch.clearTrade(trade);
}

// observer design pattern
// observer design pattern is a powerful strategy to manage event updates by giving clients the ability to listen to events and updates to a particular object and react accordingly
// observing objects can have pointers to them stored in the object that is creating events
// the notify function can be called after the event function activates, and each observer object can call thier notify() function

// visitor pattern
//






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