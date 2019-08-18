#include<iostream>
#include "bst.h"

using namespace std;

int main() {
	BT_NODE<int> *root = BT_MANAGER<int>::bt_new(10);

	cout << root << endl;

	return 0;
}
