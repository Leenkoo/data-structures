#include <iostream>
#include <exception>

using namespace std;

template <class T>
class Vector
{
	T* values;
	size_t usedSize = 0;
	size_t allocated;

	void reAllocate(size_t newSize)
	{
		values = (T*)std::realloc(values, newSize * sizeof(T));
	}

	void reAllocate()
	{
		allocated = allocated == 0 ? 1 : (2 * allocated);
		reAllocate(allocated);
	}

public:
	Vector(const size_t alloc = 0): allocated(alloc), usedSize(alloc)
	{
		values = static_cast<T*>(std::malloc(allocated*sizeof(T)));
		if (values == nullptr)
			cout << "okay, this is epic" << endl;
	}

	size_t size() const
	{
		return usedSize;
	}

	void reserve(const size_t newSize)
	{
		reAllocate(newSize);
	}
	size_t capacity() const
	{
		return allocated;
	}

	T& get(const size_t position) const
	{
		if (position >= usedSize)
			throw std::out_of_range("position index out of range");
		return values[position];
	}

	void insert(const size_t position, const T& value)
	{
		if (position > size())
			throw std::out_of_range("position index out of range");
		if (size() == capacity())
		{
			reAllocate();
		}
		
		for (size_t i = size() - 1; i >= position && size() != 0; --i)
		{
			cout << "i " << i << " position " << position << endl;
			values[i+1] = values[i];
		}

		values[position] = value;
		++usedSize;
	}

	T& operator[](const size_t position) const
	{
		return values[position];
	}

	class iterator
	{
		T* value;
	public:

		iterator(T* value): value(value) {}
		
		bool operator==(const iterator& other) const
		{
			return this == other.value;
		}

		bool operator!=(const iterator& other) const
		{
			return !(*this == other);
		}

		iterator& operator++()
		{
			++value;
			return *this;
		}
		
		T& operator*()
		{
			return *value;
		}
	};

	iterator begin()
	{
		return iterator(&values[0]);
	}
	

	iterator end()
	{
		return iterator(&values[size()]);
	}
};

int main()
{
	Vector<int> vector(0);
	int n = 10;
	
	for (int i = 0; i < n; ++i)
	{
		vector.insert(i,i);
	}

	for (auto it : vector)
	{
		cout << it << endl;
	}
	return 0;
}
