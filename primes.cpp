#include <iostream>
#include <limits>

using namespace std;

template <class T>
class Primes
{
private:
    T _from = 0;
    T _to = numeric_limits<T>::max();
    size_t _limit = numeric_limits<size_t>::max();
    
    static bool isPrime(T n)
    {
            if (n % 2 == 0)
                    return false;
            for (T i = 3; i * i <= n; i += 2)
                    if (n % i == 0)
                            return false;
            return true;
    }

    // Returns n if n is prime, or the next number that is prime
    static T nextPrime(T n)
    {
        if (n <= 2) return 2;
        if (n % 2 == 0)
            ++n;
        while (!isPrime(n))
            n += 2;
        return n;
    }
public:
    static Primes<T> from(const T startValue)
    {
        Primes<T> primes;
        primes._from = startValue;
        return primes;
    }

    Primes<T>& to(const T endValue)
    {
        _to = endValue;
        return *this;
    }
    
    Primes<T>& limit(const size_t number)
    {
        _limit = number;
        return *this;
    }

    class iterator
    {
    private:
        T value;
        size_t index;
    public:
        iterator(T val, size_t index): value(val), index(index) {}

        bool operator==(const iterator& other) const
        {
            return value == other.value || index == other.index;
        }
        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }
        iterator& operator++()
        {
            value = nextPrime(value + 1);
            ++index;
            return *this;
        }
        T operator*() const
        {
            return value;
        }
    };

    iterator begin()
    {
        return iterator(nextPrime(_from), 0);
    }

    iterator end()
    {
        if (_to == numeric_limits<T>::max())
            return iterator(_to, _limit);
        return iterator(nextPrime(_to), _limit);
    }
};

int main()
{
    using u64 = unsigned long long;
    for (const auto& prime : Primes<u64>::from(1000000000).to(1000001000).limit(3))
        cout << prime << endl;
}