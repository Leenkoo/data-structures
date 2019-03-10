#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>
#include <array>

using namespace std;
using namespace std::chrono;

template <class V>
struct Node
{
	V data;
	Node<V>* next;

	Node(const V d, Node* n = nullptr)
		: data(d), next(n)
	{
	}
	~Node()
	{
		if (next != nullptr)
			delete next;
	}
};

template <class V>
struct List
{
	Node<V>* head = nullptr;
	Node<V>* tail = nullptr;
	size_t length = 0;

	~List()
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}

	void append(const V data)
	{
		Node<V>* t = new Node<V>(data);
		if (head == nullptr)
			head = t;
		if (tail != nullptr)
			tail->next = t;
		tail = t;
		++length;
	}

	void prepend(const V data)
	{
		Node<V>* t = new Node<V>(data, head);
		head = t;
		if (tail == nullptr)
			tail = t;
		++length;
	}

	bool contains(V t)
	{
		Node<V>* it = head;
		Node<V>* jt = nullptr;
		while (it != nullptr)
		{
			if (it->data == t)
			{
				if (jt == nullptr)
					return true;
				if (it == tail)
					tail = jt;
				jt->next = it->next;
				it->next = head;
				head = it;
				return true;
			}
			jt = it;
			it = it->next;
		}
		return false;
	}
	
};

template<class V, size_t D>
class HashSet
{
	array<List<V>, D> buckets;

	static size_t hash(const V value)
	{
		size_t h = 0;
		for (int i = 0; i < sizeof(V); ++i)
		{
			uint8_t byte = (value >> (8 * i)) & 0xFF;
			h += byte;
			h += (h << 10);
			h ^= (h >> 6);
		}
		h += (h << 3);
		h ^= (h >> 11);
		h += (h << 15);
		return h % D;
	}

public:
	void add(const V value)
	{
		size_t h = hash(value);
		List<V>& bucket = buckets[h];
		bucket.prepend(value);
	}

	bool contains(const V value)
	{
		size_t h = hash(value);
		List<V>& bucket = buckets[h];
		return bucket.contains(value);
	}
};

template <class T>
ostream& operator<<(ostream& out, const class Node<T>& node)
{
	out << node.data;
	return out;
}

ostream& operator<<(ostream& out, const class Node<bool>& node)
{
	out << (node.data ? 'T' : 'F');
	return out;
}

template <class T>
ostream& operator<<(ostream& out, const List<T>& list)
{
	for (auto it = list.head; it != nullptr; it = it->next)
	{
		out << *it;
		if (it->next != nullptr)
			out << "->";
	}
	return out;
}

struct Test
{
	int a;
	int b;
	int n;
};

int main()
{
	vector<Test> tests{
		{1, 100, 1000},
		{1, 100, 10000},
		{1, 100, 100000},
		{1, 1000, 1000},
		{1, 1000, 10000},
		{1, 1000, 100000},
		{1, 10000, 1000},
		{1, 10000, 10000},
		{1, 10000, 100000},
		{1, 100000, 1000},
		{1, 100000, 10000},
		{1, 100000, 100000},
		{1, 1000000, 1000},
		{1, 1000000, 10000},
		{1, 1000000, 100000},
	};
	
	random_device rd;
	mt19937 g(rd());

	for (const Test& test : tests)
	{
		HashSet<int, 7919> set;
		uniform_int_distribution<> dis(test.a, test.b);

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		for (int i = 0; i < test.n; ++i)
		{
			const int t = round(dis(g));
			if (!set.contains(t))
				set.add(t);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>( t2 - t1 ).count();
		cout << test.b << "," << test.n << "," << duration << endl;
	}
	return 0;
}
