#include <iostream>

using namespace std;

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
	}

	void prepend(const V data)
	{
		Node<V>* t = new Node<V>(data, head);
		head = t;
		if (tail == nullptr)
			tail = t;
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

int main()
{
	List<bool> list;
	for (int i = 0; i < 10; ++i)
		list.append(i % 2);
	cout << list << endl;
	return 0;
}
