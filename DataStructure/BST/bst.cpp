#include <iostream>
#include <queue>
#include <stack>
#include "bst.h"

template <typename T>
class BT_NODE {
	protected:
		class BT_NODE *left;
		class BT_NODE *right;

		T data;
	public:
		BT_NODE(const T& data): left(nullptr), right(nullptr), data(data) {}
		virtual ~BT_NODE() {} 

		void insert(const T& t) {
			if (t == data) return;

			if (t < data) {
				if (left) {
					left->insert(t);
				} else {
					left = new BT_NODE(t);
				}
			} else {
				if (right) {
					right->insert(t);
				} else {
					right = new BT_NODE(t);
				}
			}
		}

		void pre() {
			std::cout << this << " ";
			
			if (this->left) {
				this->left->pre();
			}

			if (this->right) {
				this->right->pre();
			}
		}

		void post() {
			if (this->left) {
				this->left->post();
			}

			if (this->right) {
				this->right->post();
			}

			std::cout << this << " ";
		}

		void in() {
			if (this->left) {
				this->left->in();
			}

			std::cout << this << " ";

			if (this->right) {
				this->right->in();
			}
		}

		void level() {
			std::queue<BT_NODE<T>*> q;

			q.push(this);

			while (!q.empty()) {
				BT_NODE<T>* tmp = q.front();

				q.pop();

				if (tmp->left) {
					q.push(tmp->left);
				}

				if (tmp->right) {
					q.push(tmp->right);
				}

				std::cout << tmp << " ";
			}
		}

		void reverse_level() {
			std::queue<BT_NODE<T>*> q;
			std::stack<BT_NODE<T>*> s;

			q.push(this);

			while (!q.empty()) {
				BT_NODE<T>* tmp = q.front();

				q.pop();

				if (tmp->right) {
					q.push(tmp->right);
				}

				if (tmp->left) {
					q.push(tmp->left);
				}

				s.push(tmp);
			}

			while (!s.empty()) {
				BT_NODE<T>* tmp = s.top();
				s.pop();
				std::cout << tmp << " ";
			}
		}

		void spiral() {
			std::stack<BT_NODE<T>*> r_to_l;
			std::stack<BT_NODE<T>*> l_to_r;

			r_to_l.push(this);

			while (!r_to_l.empty() || !l_to_r.empty()) {
				while(!r_to_l.empty()) {
					BT_NODE<T>* tmp = r_to_l.top();
					r_to_l.pop();

					if (tmp->left) {
						l_to_r.push(tmp->left);
					}

					if (tmp->right) {
						l_to_r.push(tmp->right);
					}

					std::cout << tmp << " ";
				}

				while(!l_to_r.empty()) {
					BT_NODE<T>* tmp = l_to_r.top();
					l_to_r.pop();

					if (tmp->right) {
						r_to_l.push(tmp->right);
					}

					if (tmp->left) {
						r_to_l.push(tmp->left);
					}

					std::cout << tmp << " ";
				}
			}
		}

		friend std::ostream& operator<<(std::ostream& os, const BT_NODE* bt_node) {
			os << bt_node->data;
			return os;
		}

};

using namespace std;

int main() {
	BT_NODE<int> *root = BT_MANAGER<int>::bt_new(10);
	BT_MANAGER<int>::bt_insert(root, 5);
	BT_MANAGER<int>::bt_insert(root, 3);
	BT_MANAGER<int>::bt_insert(root, 7);
	BT_MANAGER<int>::bt_insert(root, 6);
	BT_MANAGER<int>::bt_insert(root, 8);

	BT_MANAGER<int>::bt_insert(root, 15);
	BT_MANAGER<int>::bt_insert(root, 13);
	BT_MANAGER<int>::bt_insert(root, 14);
	BT_MANAGER<int>::bt_insert(root, 12);
	BT_MANAGER<int>::bt_insert(root, 17);
	BT_MANAGER<int>::bt_insert(root, 16);
	BT_MANAGER<int>::bt_insert(root, 18);

	cout << "root: " << root << endl;

	cout << " Preorder traversal " << endl;
	BT_MANAGER<int>::bt_traverse_preorder(root);
	cout << endl <<  " Preorder traversal END " << endl;

	cout << " Postorder traversal " << endl;
	BT_MANAGER<int>::bt_traverse_postorder(root);
	cout << endl <<  " Postorder traversal END " << endl;

	cout << " Inorder traversal " << endl;
	BT_MANAGER<int>::bt_traverse_inorder(root);
	cout << endl <<  "Inorder traversal END " << endl;

	cout << " Level order traversal " << endl;
	BT_MANAGER<int>::bt_traverse_level(root);
	cout << endl <<  "Level order traversal END " << endl;

	cout << " Reverse Level order traversal " << endl;
	BT_MANAGER<int>::bt_traverse_reverselevel(root);
	cout << endl <<  "Reverse Level order traversal END " << endl;

	cout << " Spiral traversal " << endl;
	BT_MANAGER<int>::bt_traverse_spiral(root);
	cout << endl << " Spiral traversal END " << endl;

	return 0;
}
