/*
 * Problem statement: Maintain a database of usernames
 *  so that they are optimized to save space.
 */

#include<iostream>
#include<map>

using namespace std;

typedef unsigned short key;

template <typename X, typename Y>
class mybimap {
	public:
		map<X, Y> X_to_Y;
		map<Y, X> Y_to_X;

		// Find X from Y
		std::pair<X, bool>
		find(const Y& y) {
			typename map<Y, X>::iterator it = Y_to_X.find(y);

			if (it == Y_to_X.end()) {
				return std::make_pair(X(), false);
			} else {
				return std::make_pair(it->second, true);
			}
		}

		void
		add(const std::pair<X, Y>& X_Y_pair) {
			X_to_Y.insert(X_Y_pair);
			Y_to_X.insert(std::make_pair(X_Y_pair.second, X_Y_pair.first));
		}

		// Find Y from X
		std::pair<Y, bool>
		find(const X& x) {
			typename map<X, Y>::iterator it = X_to_Y.find(x);

			if (it == X_to_Y.end()) {
				return std::make_pair(Y(), false);
			} else {
				return std::make_pair(it->second, true);
			}
		}
};

class User {
	protected:
		key first_name;
		key last_name;

		static mybimap<key, string> names;
		static key seed; // Initial value

		static key add(const string &s) {
			/* Check if the string exists */
			std::pair<key, bool> key_bool_pair;

			key_bool_pair = names.find(s);

			if (key_bool_pair.second == true) {
				// The string exists. return key.
				return key_bool_pair.first;
			} else {
				// Create a key and string pair.
				seed++;
				names.add(std::make_pair(seed, s));
				return seed;
			}
		}

		const string get_name_from_key(key k) const {
			std::pair<string, bool> str_bool_pair;

			str_bool_pair = names.find(k);

			if (str_bool_pair.second == true) {
				return str_bool_pair.first;
			} else {
				return string();
			}
		}

	public:
		// Constructor
		User(const string& fn, const string& ln):
			first_name(add(fn)), last_name(add(ln)) {}

		const string get_first_name() const {
			return get_name_from_key(first_name);
		}

		const string get_last_name() const {
			return get_name_from_key(last_name);
		}

		void print_keys() {
			cout << first_name << " " << last_name << endl;
		}

};

key User::seed = 0;
mybimap<key, string> User::names{};

ostream &operator<<(ostream &os, const User& user)
{
	os << user.get_first_name() << " " << user.get_last_name();
	return os;
}

int main() 
{
    User u1("Alia", "Bhat");
    User u2("Mahesh", "Bhat");
    User u3("Bhat", "Vikram");

    cout << u1.get_first_name() << " " << u1.get_last_name() << endl;
    u1.print_keys();

    cout << u2.get_first_name() << " " << u2.get_last_name() << endl;
    u2.print_keys();

    cout << u3.get_first_name() << " " << u3.get_last_name() << endl;
    u3.print_keys();

    // Operator overloading example.
    cout << u1 << endl;
    return 0;
}
