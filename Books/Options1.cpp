# include <iostream>
# include <vector>

// create a class for a generic option to calculate the value of the option at expiration
// constructors are called often and sometimes unintentionally so make them as lightweight as possible
// Avoid designing classes with complex constructors. Constructors are 
// frequently called for the creation of temporary objectsand used when passing
// parameters by value, for example.Complex constructors can cause your code to run slowerand make classes harder to maintain.

enum class OptionType {  // Optiontype best represented as an enum
	OptionType_Call,
	OptionType_Put
};

class GenericOption {
public:
	GenericOption(double strike, OptionType type, double cost);
	GenericOption(const GenericOption& p);
	~GenericOption();
	GenericOption& operator= (const GenericOption& p);

	double valueAtExpiration(double underlyingAtExpiration);
	double profitAtExpiration(double underlyingAtExpiration);

private:
	double m_strike;
	double m_cost;
	OptionType m_type;
};

GenericOption::GenericOption(double strike, OptionType type, double cost) : m_strike(strike), m_type(type), m_cost(cost)
{

}

GenericOption::GenericOption(const GenericOption& p) : m_strike(p.m_strike), m_cost(p.m_cost), m_type(p.m_type)
{

}

GenericOption::~GenericOption()
{

}

GenericOption& GenericOption::operator= (const GenericOption& p)
{
	if (this != &p)
	{
		m_type = p.m_type;
		m_cost = p.m_cost;
		m_strike = p.m_strike;
	}

	return *this;
}

// now compute the value of the option at expiration date

double GenericOption::valueAtExpiration(double underlyingAtExpiration)
{
	double value = 0.0;
	if (m_type == OptionType::OptionType_Call)
	{
		if (m_strike < underlyingAtExpiration)
		{
			value = underlyingAtExpiration - m_strike;
		}
	}

	else  // it's a put type
	{
		if (m_strike > underlyingAtExpiration)
		{
			value = m_strike - underlyingAtExpiration;
		}
	}

	return value;
}


int main() {
	GenericOption option(100.0, OptionType::OptionType_Put, 1.1);
	double price1 = 120.0;
	double value = option.valueAtExpiration(price1);

	std::cout << "for 120 put for expiry at " << price1 << " is " << value;
}