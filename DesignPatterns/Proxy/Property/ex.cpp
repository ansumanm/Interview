#include<iostream>

using namespace std;

template <typename T>
class Property {
	public:
	T value;

	Property(T val) {
		cout << "Constructor" << endl;
		// value = val;
		*this = val;
	}

	T operator=(T new_value) {
		cout << "Assignment" << endl;
		value = new_value;
		return value;
	}

	operator T() {
		cout << "Returning value ";
		return value;
	}
};

class Cube {
	public:
	Property<int> length{5};
	Property<int> breadth{5};
	Property<int> width{5};
};

int main() {
	Cube c;

	cout << c.length << " " << c.breadth << " " << c.width << endl;
	c.length = 10;
	cout << c.length << " " << c.breadth << " " << c.width << endl;

	return 0;
}
