#include <iostream>

using namespace std;

template <class T>
T pow(T number, const int power)
{
	if (power == 0)
		return 1;
	T original = 1;
	// you could do this in log(power) steps :)
	for (int i = 0; i < power; ++i)
		number *= original;
	return number;
}

template <class T, int D>
class Fixed
{
	T value;
	double realValue() const
	{
		return ((double)value / (double)pow(10, D));
	}
public:
	Fixed(const T numerator, const T denominator)
	{
		value = (numerator * pow(10,D)) / denominator;
	}

	Fixed(const T value)
	{
		this->value = value;
	}
	
	// addition operations
	template <int D2>
	auto operator+(const Fixed<T, D2>& second) const
	{
		T value;
		if (D == D2)
			value = this->value + second.value;
		else if (D < D2)
			value = this->value + second.value / pow(10, D2 - D);
		else
			value = this->value + second.value * pow(10, D - D2);
		return Fixed<T,D>(value);
	}

	auto operator+(const int integer) const
	{
		return Fixed<T,D>(this->value + (T)(integer * pow(10,D)));
	}

	auto operator+(float fl) const
	{
		int denominator = 0;
		while (fl - (int)fl != 0 || denominator < D)
		{
			fl *= 10;
			++denominator;
		}
		return *this + Fixed<T,D>((T)fl);
	}

	// subtraction operations
	template <int D2>
	auto operator-(const Fixed<T, D2>& second) const
	{
		T value;
		if (D == D2)
			value = this->value - second.value;
		else if (D < D2)
			value = this->value - second.value / pow(10, D2 - D);
		else
			value = this->value - second.value * pow(10, D - D2);
		return Fixed<T,D>(value);
	}

	auto operator-(const int integer) const
	{
		return Fixed<T,D>(this->value - (T)(integer * pow(10,D)));
	}

	auto operator-(float fl) const
	{
		int denominator = 0;
		while (fl - (int)fl != 0 || denominator < D)
		{
			fl *= 10;
			++denominator;
		}
		return *this - Fixed<T,D>((T)fl);
	}

	// multiplication operations
	template <int D2>
	auto operator*(const Fixed<T, D2>& second) const
	{
		T value;
		if (D == D2)
			value = this->value * second.value;
		else if (D < D2)
			value = this->value * second.value;
		else
			value = this->value * second.value;
		value /= pow(10,D2);
		return Fixed<T,D>(value);
	}

	auto operator*(const int integer) const
	{
		return Fixed<T,D>(this->value * (T)(integer));
	}

	auto operator*(float fl) const
	{
		int denominator = 0;
		while (fl-(int)fl != 0 || denominator < D)
		{
			fl *= 10;
			++denominator;
		}
		return *this * Fixed<T,D>((T)fl);
	}

	// division operations
	template <int D2>
	auto operator/(const Fixed<T, D2>& second) const
	{
		T denominator;
		if (D == D2)
			denominator = second.value;
		else if (D < D2)
			denominator = second.value / pow(10, D2 - D);
		else
			denominator = second.value * pow(10, D - D2);
		return Fixed<T,D>((int)this->value, (int)denominator);
	}

	auto operator/(const int integer) const
	{
		return Fixed<T,D>(this->value / (T)(integer));
	}

	auto operator/(float fl) const
	{
		int denominator = 0;
		while (fl-(int)fl != 0 || denominator < D)
		{
			fl *= 10;
			++denominator;
		}
		return *this / Fixed<T,D>((T)fl);
	}

	template<class T2, int D2>
	friend ostream& operator<<(ostream&, const Fixed<T2, D2>&);
	
	template<class T2, int D2>
	friend class Fixed;
};

template <class T, int D>
ostream& operator<<(ostream& out, const Fixed<T,D>& fixed)
{
	out << fixed.realValue();
	return out;
}

template <class T, int D>
auto operator+(const int integer, const Fixed<T,D> fixed)
{
	return fixed + integer;
}

template <class T, int D>
auto operator+(const float fl, const Fixed<T,D> fixed)
{
	return fixed + fl;
}

template <class T, int D>
auto operator-(int integer, const Fixed<T,D> fixed)
{
	for (int i = 0; i < D; ++i)
		integer *= 10;
	return Fixed<T,D>((T)integer) - fixed;
}

template <class T, int D>
auto operator-(float fl, const Fixed<T,D> fixed)
{
	int denominator = 0;
	while (fl - (int)fl != 0 || denominator < D)
	{
		fl *= 10;
		++denominator;
	}
	return Fixed<T,D>((T)fl) - fixed;
}

template <class T, int D>
auto operator*(const int integer, const Fixed<T,D> fixed)
{
	return fixed * integer;
}

template <class T, int D>
auto operator*(const float fl, const Fixed<T,D> fixed)
{
	return fixed * fl;
}

template <class T, int D>
auto operator/(int integer, const Fixed<T,D> fixed)
{
	for (int i = 0; i <D; ++i)
		integer *= 10;
	return Fixed<T,D>((T)integer) / fixed;
}

template <class T, int D>
auto operator/(float fl, const Fixed<T,D> fixed)
{
	int denominator = 0;
	while (fl-(int)fl != 0 || denominator < D)
	{
		fl *= 10;
		++denominator;
	}
	return Fixed<T,D>((T)fl) / fixed;
}

int main()
{
	Fixed<long, 5> pi(22, 7);
	Fixed<long, 1> e(19, 7);
	cout << "pi = " << pi << endl;
	cout << "e = " << e << endl;

	cout << "e + pi = " << e + pi << endl;
	cout << "pi + e = " << pi + e << endl;
	cout << "pi + 3 = " << pi + 3 << endl;
	cout << "3 + pi = " << 3 + pi << endl;
	cout << "pi + 2.33 = " << pi + (float)2.33 << endl;
	cout << "2.33 + pi = " << (float)2.33 + pi << endl << endl;

	cout << "e - pi = " << e - pi << endl;
	cout << "pi - e = " << pi - e << endl;
	cout << "pi - 3 = " << pi - 3 << endl;
	cout << "3 - pi = " << 3 - pi << endl;
	cout << "pi - 2.33 = " << pi - (float)2.33 << endl;
	cout << "2.33 - pi = " << (float)2.33 - pi << endl << endl;

	cout << "e * pi = " << e * pi << endl;
	cout << "pi * e = " << pi * e << endl;
	cout << "pi * 3 = " << pi * 3 << endl;
	cout << "3 * pi = " << 3 * pi << endl;
	cout << "pi * 2.33 = " << pi * (float)2.33 << endl;
	cout << "2.33 * pi = " << (float)2.33 * pi << endl << endl;

	cout << "e / pi = " << e / pi << endl;
	cout << "pi / e = " << pi / e << endl;
	cout << "pi / 3 = " << pi / 3 << endl;
	cout << "3 / pi = " << 3 / pi << endl;
	cout << "pi / 2.33 = " << pi / (float)2.33 << endl;
	cout << "2.33 / pi = " << (float)2.33 / pi << endl;

	return 0;
}
