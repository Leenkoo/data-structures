#include <iostream>
#include <vector>
#include <sstream>

struct Node
{
	char digit;
	Node* next;
	Node* prev;
	Node(char digit, Node* next, Node* prev)
		: digit(digit), next(next), prev(prev)
	{
	}
};

struct List
{
	Node* head = nullptr;
	Node* tail = nullptr;

	void addFront(char digit)
	{
		Node* newNode = new Node(digit, head, nullptr);
		if (head != nullptr)
			head->prev = newNode;
		head = newNode;
		if (tail == nullptr)
			tail = newNode;
	}

	void addBack(char digit)
	{
		Node* newNode = new Node(digit, nullptr, tail);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
			return;
		}
		tail->next = newNode;
		tail = newNode;
	}
};


struct Bignum;
std::ostream& operator<<(std::ostream& out, const Bignum& bn);

struct Bignum
{
	bool negative = 0;
	List number;

	Bignum() {}

	Bignum(const std::string& str)
	{
		for (const char c : str)
			number.addBack(c - '0');
		negative = (number.head->digit + '0' == '-');
		if (negative)
			number.head->digit = 0;
		clearZeros();
	}

	Bignum(int value)
	{
		if (value < 0)
		{
			negative = 1;
			value *= -1;
		}
		if (value == 0)
		{
			number.addFront(value);
			return;
		}
		while (value > 0)
		{
			number.addFront(value % 10);
			value /= 10;
		}
	}

	void removeHead()
	{
		Node* newHead = number.head;
		Node* temp = newHead;
		newHead = newHead->next;
		newHead->prev = nullptr;
		number.head = newHead;
		delete temp;
	}

	Bignum operator+(Bignum other)
	{
		int op = 0;
		if (this->negative)
			op += 2;
		if (other.negative)
			op += 1;

		Bignum result;
		switch (op)
		{
			case 0:
				break;
			case 1:
				other.negative = 0;
				result = *this - other;
				other.negative = 1;
				return result;
			case 2:
				this->negative = 0;
				result = other - *this;
				this->negative = 1;
				return result;
			case 3:
				result.negative = 1;
				break;
		}
		Node* it1 = this->number.tail;
		Node* it2 = other.number.tail;
		int carry = 0;
		while (it1 != nullptr || it2 != nullptr)
		{
			const int d1 = (it1 == nullptr) ? 0 : static_cast<int>(it1->digit);
			const int d2 = (it2 == nullptr) ? 0 : static_cast<int>(it2->digit);
			const int temp = d1 + d2 + carry;
			result.number.addFront(temp % 10);
			carry = temp / 10;

			it1 = (it1 == nullptr) ? nullptr : it1->prev;
			it2 = (it2 == nullptr) ? nullptr : it2->prev;
		}
		if (carry != 0)
			result.number.addFront(carry);
		return result;
	}

	Bignum operator+(int rhs)
	{
		return Bignum(rhs) + *this;
	}
	
	Bignum operator-(Bignum other)
	{
		int operation = 0;
		if (this->negative)
			operation += 2;
		if (other.negative)
			operation += 1;

		Bignum result;
		//std::cout << operation << std::endl;
		switch (operation){
			case 0:
			break;
			case 1:
				other.negative = 0;
				result = *this + other;
				other.negative = 1;
				return result;
			case 2:
				this->negative = 0;
				result = other + *this;
				this->negative = 1;
				result.negative = 1;
				return result;
			case 3:
				other.negative = 0;
				this->negative = 0;
				result = other - *this;
				other.negative = 1;
				this->negative = 1;
				return result;
		}

		if (other > *this)
		{
			//std::cout << "cowabunga" << std::endl;
			result = other - *this;
			result.negative = 1;
			return result;
		}

		Node* it1 = this->number.tail;
		Node* it2 = other.number.tail;
		int carry = 0;
		while (it1 != nullptr || it2 != nullptr)
		{
			const int d1 = (it1 == nullptr) ? 0 : static_cast<int>(it1->digit);
			const int d2 = (it2 == nullptr) ? 0 : static_cast<int>(it2->digit);
			int temp = d1 - d2 - carry;
			//std::cout << "t: " << temp << std::endl;
			carry = 0;
			while (temp < 0)
			{
				temp += 10;
				carry += 1; 
			}
			result.number.addFront(temp);
			it1 = (it1 == nullptr) ? nullptr : it1->prev;
			it2 = (it2 == nullptr) ? nullptr : it2->prev;
		}
		result.clearZeros();
		return result;
	}

	void clearZeros()
	{
		while (number.head != nullptr && number.head != number.tail && static_cast<int>(number.head->digit) == 0)
			removeHead();
	}

	Bignum operator*(Bignum other)
	{
		Bignum result(0);
		if ((this->negative && !other.negative) || (!this->negative && other.negative))
			result.negative = 1;
		Node* res = result.number.tail;
		int carry = 0;
		for (Node* it2 = other.number.tail; it2 != nullptr; it2 = it2->prev)
		{
			Node* it3 = res;
			for (Node* it1 = this->number.tail; it1 != nullptr; it1 = it1->prev)
			{
				int d1 = static_cast<int>(it1->digit);
				int d2 = static_cast<int>(it2->digit);
				int d3 = static_cast<int>(it3->digit);
				int temp = (d1 * d2) + d3 + carry;
				it3->digit = temp % 10;
				carry = temp / 10;
				if (it3->prev == nullptr)
					result.number.addFront(0);
				it3 = it3->prev;
				
			}
			it3->digit = carry;
			carry = 0;
			res = res->prev;
		}
		result.clearZeros();
		return result;
	}

	bool operator<(const Bignum other)
	{
		Node* it1 = this->number.head;
		Node* it2 = other.number.head;
		int n = 0;
		while(it1 != nullptr || it2 !=nullptr)
		{
			if (it1 == nullptr)
				return true;
			if (it2 == nullptr)
				return false;
			if (n == 0 && it1->digit != it2->digit)
				n = (it1->digit < it2->digit) ? 1 : -1;
			it1 = it1->next;
			it2 = it2->next;
		}
		return n == 1;
	}

	Bignum operator/(Bignum other)
	{
		if (other == Bignum(0))
		{
			std::cout << "REEEEEEEEEEEE!!" << std::endl;  

		}
		Bignum div;
		Node* it1 = this->number.head;
		while (div < other)
		{
			div.number.addBack(it1->digit);
			it1 = it1->next;
		}
		std::cout << "div: " << div << std::endl;
		Bignum result;
	
		while(div >= other)
		{
			//iskanje parametra
			for (int i = 1; i < 10; ++i)
			{
				Bignum temp = other*Bignum(i);
				if (div - temp < other)
				{
					div = div - temp;
					result.number.addBack(i);
					if (it1 != nullptr)
						div.number.addBack(it1->digit);
					 std::cout << "newDiv " << div << std::endl;
					break;
				}
			}
			if (it1 != nullptr)
			{
				it1 = it1->next;
			}
		}
		return result;
	}

	// boolean operations
	bool operator==(const Bignum other)
	{
		if (this->negative != other.negative)
			return false;
		for (Node* it1 = this->number.head, *it2 = other.number.head; it1 != nullptr || it2 != nullptr; it1 = it1->next, it2 = it2->next)
		{
			if (it1 == nullptr || it2 == nullptr)
				return false;
			if (it1->digit != it2->digit)
				return false;
		}
		return true;
	}

	bool operator!=(const Bignum other)
	{
		return !(*this == other);
	}
	bool operator<=(Bignum other)
	{
		return (*this == other) || (*this < other);
	}

	bool operator>(const Bignum other)
	{
		return !(*this <= other);
	}

	bool operator>=(const Bignum other)
	{
		return !(*this < other) || (*this == other);
	}

};

std::ostream& operator<<(std::ostream& out, const Bignum& bn)
{
	if (bn.negative)
		out << '-'; 
	Node* node = bn.number.head;
	while(node != nullptr)
	{
		out << static_cast<int>(node->digit);
		node = node->next;
	}
	return out;
}

struct TestBignum
{
	std::string a;
	std::string b;
	std::string expected;
};


struct TestInteger
{
	std::string a;
	int b;
	std::string expected;
};

int main()
{
/*
	std::vector<TestBignum> tests{
		{"", "", ""},
		{"0", "", "0"},
		{"0", "0", "0"},
		{"1", "0", "1"},
		{"1", "1", "2"},
		{"1", "10", "11"},
		{"589", "1", "590"},
		{"00", "00", "0"},
		{"999999999999", "1", "1000000000000"},
		{"5555555555", "5555555555", "11111111110"},
		{"001", "002", "3"},
		{"000045", "1001", "1046"},
	};

	std::cout << "testing Bignum + Bignum: " << std::endl;
	for (const auto& test_case : tests)
	{
		Bignum a(test_case.a);
		Bignum b(test_case.b);
		std::stringstream ss;
		ss << (a + b);
		std::string actual = ss.str();
		if (actual != test_case.expected)
			std::cout << "Test failed! " << test_case.a << " + " << test_case.b << " = " << (a + b) << std::endl << "Expected: " << test_case.expected << std::endl;
		else 
			std::cout << "ok" << std::endl;
	}

	std::cout << "testing Bignum + integer: " << std::endl;
	std::vector<TestInteger> tests2{
		{"10000000000", 1, "10000000001"},
		{"0", 1, "1"},ontrol reaches end of non-void functio
		{"0", 0, "0"},
		{"1", 0, "1"},
		{"1", 1, "2"},
		{"1", 10, "11"},
		{"589", 1, "590"},
		{"999", 999999, "1000998"},
		{"999999999999", 1, "1000000000000"},
		{"5555", 5555 , "11110"},
		{"9", 2, "11"},
		{"45", 1001, "1046"},
	};

	for (const auto& test_case : tests2)
	{
		Bignum a(test_case.a);
		int b(test_case.b);
		std::stringstream ss;
		ss << (a + b);
		std::string actual = ss.str();
		if (actual != test_case.expected)
			std::cout << "Test failed! " << test_case.a << " + " << test_case.b << " = " << (a + b) << std::endl << "Expected: " << test_case.expected << std::endl;
		else 
			std::cout << "ok" << std::endl;
	}
	std::cout << Bignum("8") * Bignum("7") << std::endl;
	std::cout << Bignum("00025") * Bignum("11") << std::endl;
	std::cout << Bignum("100") * Bignum("1000") << std::endl;
	std::cout << Bignum("78") * Bignum("99") << std::endl;
	std::cout << Bignum("1556729863428") * Bignum("33333023916427343") << std::endl;
	std::cout << Bignum("999") * Bignum("999") << std::endl;

	std::vector<TestBignum> tests3{
		{"", "", "0"},
		{"0", "", "0"},
		{"0", "0", "0"},
		{"1", "0", "0"},
		{"2", "1", "2"},
		{"8", "9", "72"},
		{"589", "1", "589"},
		{"89", "1", "89"},
		{"1556729863428", "33333023916427343", "51890513769062195354074911804"},
		{"5555555555", "5555555555", "30864197524691358025"},
		{"001", "002", "2"},
		{"100", "100", "10000"},
	};

	std::cout << "testing Bignum * Bignum: " << std::endl;
	for (const auto& test_case : tests3)
	{
		Bignum a(test_case.a);
		Bignum b(test_case.b);
		std::stringstream ss;
		ss << (a * b);
		std::string actual = ss.str();
		if (actual != test_case.expected)
			std::cout << "Test failed! " << test_case.a << " * " << test_case.b << " = " << (a * b) << std::endl << "Expected: " << test_case.expected << std::endl;
		else
			std::cout << "ok" << std::endl;
	}
*/
	std::cout << Bignum(85) / Bignum(5) << std::endl;
	std::cout << Bignum(12) / Bignum(4) << std::endl;
	std::cout << Bignum(30) / Bignum(3) << std::endl;
	std::cout << Bignum(100) / Bignum(10) << std::endl;
	return 0;
}
