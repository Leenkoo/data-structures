#include <iostream>
#include <array>
#include <stdexcept>

using namespace std;


template <class K, class V>
struct Node
{
	K key;
	V value;
	Node<K,V>* next;

	Node(const K k, Node* n = nullptr)
		: key(k), next(n)
	{
	}
	~Node()
	{
		if (next != nullptr)
			delete next;
	}
};

template <class K, class V>
struct List
{
	Node<K,V>* head = nullptr;
	Node<K,V>* tail = nullptr;
	size_t length = 0;

	~List()
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}

	void append(const K key, const V value)
	{
		Node<K,V>* t = new Node<K,V>(key, value);
		if (head == nullptr)
			head = t;
		if (tail != nullptr)
			tail->next = t;
		tail = t;
		++length;
	}

	Node<K,V>* prepend(const K key)
	{
		Node<K,V>* t = new Node<K,V>(key, head);
		head = t;
		if (tail == nullptr)
			tail = t;
		++length;
		return t;
	}

	Node<K,V>* find(const K k)
	{
		Node<K,V>* it = head;
		Node<K,V>* jt = nullptr;
		while (it != nullptr)
		{
			if (it->key == k)
			{
				if (jt == nullptr)
					return it;
				if (it == tail)
					tail = jt;
				jt->next = it->next;
				it->next = head;
				head = it;
				return it;
			}
			jt = it;
			it = it->next;
		}
		return nullptr;
	}
	
	V getValue(const K k)
	{
		Node<K,V>* it = head;
		while (it != nullptr)
		{
			if (it->key == k)
				return it->value;
		}
		throw std::invalid_argument("key not in List");
	}
};

template<class K, class V, size_t D>
class HashMap
{
	array<List<K,V>, D> buckets;

	static size_t hash(const K key)
	{
		size_t h = 0;
		for (int i = 0; i < sizeof(V); ++i)
		{
			uint8_t byte = (key >> (8 * i)) & 0xFF;
			h += byte;
			h += (h << 10);
			h ^= (h >> 6);
		}
		h += (h << 3);
		h ^= (h >> 11);
		h += (h << 15);
		return h % D;
	}
	

	List<K,V>& getBucket(const K key)
	{
		size_t h = hash(key);
		return buckets[h];
	}
public:

	Node<K,V>* add (const K key)
	{
		List<K,V>& bucket = getBucket(key);
		Node<K,V>* node = bucket.find(key);
		if (node == nullptr)
			node = bucket.prepend(key);
		return node;
	}

	void add(const K key, const V value)
	{
		Node<K,V>* node = add(key);
		node->value = value;
	}

	bool contains(const K key)
	{
		List<K,V>& bucket = getBucket(key);
		return !(bucket.find(key) == nullptr);
	}
	
	V get(const K key)
	{
		List<K,V>& bucket = getBucket(key);
		Node<K,V>* node = bucket.find(key);
		if (node == nullptr)
			throw std::invalid_argument("key does not yet exist or is not hashed correctly");
		return node->value;
	}

	V& operator[](const K key)
	{
		List<K,V>& bucket = getBucket(key);
		Node<K,V>* node = bucket.find(key);
		if (node == nullptr)
			node = add(key);
		return node->value;
	}
};

template <class T, class P>
ostream& operator<<(ostream& out, const class Node<T,P>& node)
{
	out << node.value;
	return out;
}

template<class P>
ostream& operator<<(ostream& out, const class Node<P, bool>& node)
{
	out << (node.value ? 'T' : 'F');
	return out;
}

template <class P, class T>
ostream& operator<<(ostream& out, const List<P,T>& list)
{
	for (auto it = list.head; it != nullptr; it = it->next)
	{
		out << *it;
		if (it->next != nullptr)
			out << "->";
	}
	return out;
}

int main()
{
	HashMap<int,int,8> map;
	map.add(1, 100);
	map.add(1, 200);
	map[1] = 300;
	map[2] = 150;
	cout << map[2] << endl;
	cout << map.get(1) << endl;

	return 0;
}
