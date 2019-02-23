#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* next;
	Node(const T d, Node<T>* n = nullptr)
	{
		data = d;
		next = n;
	}

	~Node()
	{
		if (next != nullptr)
			delete next;
	}
};


template <class T>
class Stack
{

	Node<T>* head = nullptr;

public:
	~Stack()
	{
		if (head != nullptr)
			delete head;
	}

	void push(const T data)
	{
		Node<T>* node = new Node<T>(data, head);
		head = node;
	}

	T top() const
	{
		if (head == nullptr)
			throw runtime_error("To top or not to top; that is the question.");
		return head->data;
	}

	void pop()
	{
		if (head == nullptr)
			return;
		Node<T>* prev = head;
		head = head->next;
		prev->next = nullptr;
		delete prev;
	}

	bool empty() const
	{
		return head == nullptr;
	}
/*
	Node<T>* itStart() const
	{
		return head;
	}
*/
template <class U>
friend ostream& operator<<(ostream&, const Stack<T>&);


};

template <class T>
ostream& operator<<(ostream& out, const Node<T>& node)
{
	out << node.data;
	return out;
}

template <class T>
ostream& operator<<(ostream& out, const Stack<T>& stack)
{
	for (auto it = stack.head; it != nullptr; it = it->next)
	{
		out << *it;
		if (it->next != nullptr)
			out << "->";
	}
	return out;
}

Stack<int>& operator<<(Stack<int>& stack, const int i)
{
	stack.push(i);
	return stack;
}

Stack<int>& operator>>(Stack<int>& stack, int& i)
{
	i = stack.top();
	stack.pop();
	return stack;
}


int main()
{
 Stack<int> stack;
 stack << 1 << 2 << 3;

 int a, b, c;
 stack >> a >> b >> c;
 cout << a << " " << b << " " << c << endl;

 int d;
 stack >> d;
 return 0;
}
