template <typename> class BT_NODE;

template <typename T>
class BT_MANAGER {
	public:
		BT_MANAGER();
		~BT_MANAGER();

		static BT_NODE<T> *bt_new(const T& t) {
			return new BT_NODE<T>(t);
		}

		static void bt_insert(BT_NODE<T> *n, const T& t) {
			n->insert(t);
		}

		static void bt_traverse_preorder(BT_NODE<T> *n) {
			n->pre();
		}

		static void bt_traverse_postorder(BT_NODE<T> *n) {
			n->post();
		}

		static void bt_traverse_inorder(BT_NODE<T> *n) {
			n->in();
		}

		static void bt_traverse_level(BT_NODE<T> *n) {
			n->level();
		}

		static void bt_traverse_reverselevel(BT_NODE<T> *n) {
			n->reverse_level();
		}

		static void bt_traverse_spiral(BT_NODE<T> *n) {
			n->spiral();
		}
};
