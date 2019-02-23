#include <iostream>

using namespace std;

template <class T>
class Rational
{
	T numerator;
	T denominator;
public:
	Rational(T numerator, T denominator)
	{
		this->numerator = numerator;
		this->denominator = denominator;
	}

	// addition operations
	// Rational + Rational
	Rational<T> operator+(const Rational<T> other) const
	{
		T newNumerator = this->numerator * other.denominator +
						other.numerator * this->denominator;
		T newDenominator = this->denominator * other.denominator;
		Rational<T> newRational(newNumerator, newDenominator);
		return newRational;
	}
	
	// Rational + integer
	Rational<T> operator+(const int integer) const
	{
		T newNumerator = this->numerator + (T)integer * this->denominator;
		T newDenominator = this->denominator;
		Rational<T> newRational(newNumerator, newDenominator);
		return newRational;
	}
	
	// Rational + float
	Rational<T> operator+(const float fl) const
	{
		float flNumerator = fl;
		float flDenominator = 1;
		while ((flNumerator - (int)flNumerator) != 0)
		{
			flNumerator *= 10;
			flDenominator *= 10;
		}
		Rational<T> floatRational((T)flNumerator, (T)flDenominator);
		return *this + floatRational;
	}
	
	// subtraction operations
	// Rational - Rational
	Rational<T> operator-(const Rational<T> other) const
	{
		T newNumerator = this->numerator * other.denominator -
						other.numerator * this->denominator;
		T newDenominator = this->denominator * other.denominator;
		Rational<T> newRational(newNumerator, newDenominator);
		return newRational;
	}
	
	// Rational - integer
	Rational<T> operator-(const int integer) const
	{
		T newNumerator = this->numerator - (T)integer * this->denominator;
		T newDenominator = this->denominator;
		Rational<T> newRational(newNumerator, newDenominator);
		return newRational;
	}
	
	// Rational - float
	Rational<T> operator-( const float fl) const
	{
		float flNumerator = fl;
		float flDenominator = 1;
		while ((flNumerator - (int)flNumerator) != 0)
		{
			flNumerator *= 10;
			flDenominator *= 10;
		}
		Rational<T> floatRational((T)flNumerator, (T)flDenominator);
		return *this - floatRational;
	}
	
	// multiplication operations
	// Rational * Rational
	Rational<T> operator*(const Rational<T> other) const
	{
		T newNumerator = this->numerator * other.numerator;
		T newDenominator = this->denominator * other.denominator;
		Rational<T> newRational(newNumerator, newDenominator);
		return newRational;
	}
	
	// Rational * integer
	Rational<T> operator*(const int integer) const
	{
		T newNumerator = this->numerator * (T)integer;
		T newDenominator = this->denominator;
		Rational<T> newRational(newNumerator, newDenominator);
		return newRational;
	}
	
	// Rational * float
	Rational<T> operator*(const float fl) const
	{
		float flNumerator = fl;
		float flDenominator = 1;
		while ((flNumerator - (int)flNumerator) != 0)
		{
			flNumerator *= 10;
			flDenominator *= 10;
		}
		Rational<T> floatRational((T)flNumerator, (T)flDenominator);
		return *this * floatRational;
	}
	
	// division operations
	// Rational / Rational
	Rational<T> operator/(const Rational<T> other) const
	{
		T newNumerator = other.denominator;
		T newDenominator = other.numerator;
		Rational<T> newRational(newNumerator, newDenominator);
		return *this * newRational;
	}
	
	// Rational / integer
	Rational<T> operator/(const int integer) const
	{
		T newNumerator = this->numerator;
		T newDenominator = this->denominator * (T)integer;
		Rational<T> newRational(newNumerator, newDenominator);
		return newRational;
	}
	
	// Rational / float
	Rational<T> operator/(const float fl) const
	{
		float flNumerator = fl;
		float flDenominator = 1;
		while ((flNumerator - (int)flNumerator) != 0)
		{
			flNumerator *= 10;
			flDenominator *= 10;
		}
		Rational<T> floatRational((T)flNumerator, (T)flDenominator);
		return *this / floatRational;
	}
	
	template <class U>
	friend ostream& operator<<(ostream&, Rational<U>);
};

// output
template <class T>
ostream& operator<<(ostream& out, Rational<T> rational)
{
	out << ((float)rational.numerator/(float)rational.denominator);
	return out;
}

// rhs operator deklarations
// addition operations
template <class T>
Rational<T> operator+(const int integer, const Rational<T> rational)
{
	return rational + integer;
}

template <class T>
Rational<T> operator+(const float fl, const Rational<T> rational)
{
	return rational + fl;
}

// subtraction operations
template <class T>
Rational<T> operator-(const int integer, const Rational<T> rational)
{
	return rational - integer;
}

template <class T>
Rational<T> operator-(const float fl, const Rational<T> rational)
{
	return rational - fl;
}

// multiplication operations
template <class T>
Rational<T> operator*(const int integer, const Rational<T> rational)
{
	return rational * integer;
}

template <class T>
Rational<T> operator*(const float fl, const Rational<T> rational)
{
	return rational * fl;
}

// multiplication operations
template <class T>
Rational<T> operator/(const int integer, const Rational<T> rational)
{
	return rational / integer;
}

template <class T>
Rational<T> operator/(const float fl, const Rational<T> rational)
{
	return rational / fl;
}

int main()
{
	Rational<int> pi(22, 7);
	cout << "pi: " << pi << endl;
	Rational<int> e(19,7);
	cout << "e: " << e << endl;

	cout << endl;

	Rational<int> sum1 = pi + e;
	cout << "rational sum: " << sum1 << endl;
	Rational<int> sum2 = pi + 1;
	cout << "integer sum1: " << sum2 << endl;
	Rational<int> sum3 = 1 + pi;
	cout << "integer sum2: " << sum3 << endl;
	Rational<int> sum4 = pi + (float)1.22;
	cout << "float sum1: " << sum4 << endl;
	Rational<int> sum5 = (float)1.22 + pi;
	cout << "float sum2: " << sum5 << endl;

	cout << endl;

	Rational<int> diff1 = pi - e;
	cout << "rational diff: " << diff1 << endl;
	Rational<int> diff2 = pi - 1;
	cout << "integer diff1: " << diff2 << endl;
	Rational<int> diff3 = 1 - pi;
	cout << "integer diff2: " << diff3 << endl;
	Rational<int> diff4 = pi - (float)1.22;
	cout << "float diff1: " << diff4 << endl;
	Rational<int> diff5 = (float)1.22 - pi;
	cout << "float diff2: " << diff5 << endl;

	cout << endl;

	Rational<int> multi1 = pi * e;
	cout << "rational multi: " << multi1 << endl;
	Rational<int> multi2 = pi * 2;
	cout << "integer multi1: " << multi2 << endl;
	Rational<int> multi3 = 2 * pi;
	cout << "integer multi2: " << multi3 << endl;
	Rational<int> multi4 = pi * (float)3.22;
	cout << "float multi1: " << multi4 << endl;
	Rational<int> multi5 = (float)3.22 * pi;
	cout << "float multi2: " << multi5 << endl;

	cout << endl;

	Rational<int> division1 = pi / e;
	cout << "rational division: " << division1 << endl;
	Rational<int> division2 = pi / 2;
	cout << "integer division1: " << division2 << endl;
	Rational<int> division3 = 2 / pi;
	cout << "integer division2: " << division3 << endl;
	Rational<int> division4 = pi / (float)3.22;
	cout << "float division1: " << division4 << endl;
	Rational<int> division5 = (float)3.22 / pi;
	cout << "float division2: " << division5 << endl;

	cout << endl;

	Rational<int> test1 = pi * 3 + 1;
	cout << "test1: " << test1 << endl;
	Rational<int> test2 = 1 + pi * 3;
	cout << "test2: " << test2 << endl;

	return 0;
}
