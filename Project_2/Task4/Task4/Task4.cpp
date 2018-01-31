#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T value;
	Node* left;
	Node* right;

	Node(T _value) {
		value = _value;
		left = nullptr;
		right = nullptr;
	}

	Node(T _value, Node<T>* _left, Node<T>* _right) {
		value = _value;
		left = _left;
		right = _right;
	}
	~Node() {
		delete left;
		delete right;
	}
};

template <typename T>
class BinTree
{
public:
	Node<T>* root;
public:
	BinTree() {
		root = nullptr;
	}

	~BinTree() {
		delete root;
	}

	bool insert(T x, string trace) {
		return insert_helper(x, trace, root);
	}

	unsigned height() {
		return height(root);
	}

	void get_leaves() {
		get_leaves(root);
	}

	int count_leaves() {
		return count_leaves_help(root, 0);
	}

	T max_leaf() {
		T maxLeaf = root->value;
		return max_leaf_help(root, maxLeaf);
	}

	bool find(T value) {
		return find_helper(value, root);
	}

	void findPath(T value) {
		find_path(value, root);
	}

	int count() {
		return count_help(root, 0);
	}

	int countEvens() {
		return count_evens(root, 0);
	}

private:

	//добавя елемент към дървото, публичната функция просто извиква тази, в стринг-а пазиш в кое поддърво искаш да добавиш елемента
	bool insert_helper(T x, string trace, Node<T>*& subRoot) {
		if (trace == "" && subRoot == nullptr) {
			subRoot = new Node<T>(x, nullptr, nullptr);
			return true;
		}
		if (trace != "" && subRoot == nullptr)
			return false;

		if (trace[0] == 'L') {
			trace.erase(trace.begin());
			insert_helper(x, trace, subRoot->left);
		}
		if (trace[0] == 'R') {
			trace.erase(trace.begin());
			insert_helper(x, trace, subRoot->right);
		}
	}

	T height(Node<T>* sub_root) {
		if (sub_root == nullptr)
			return 0;
		unsigned left = height(sub_root->left);
		unsigned right = height(sub_root->right);

		return 1 + (left > right ? left : right);
	}

	void get_leaves(Node<T>* sub_root) {
		if (sub_root == nullptr)
			return;

		if (sub_root->left == nullptr &&
			sub_root->right == nullptr) {

			cout << sub_root->value;
		}
		get_leaves(sub_root->left);
		get_leaves(sub_root->right);
		cout << " ";
	}

	int count_leaves_help(Node<T>* currentRoot, int counter) {
		if (currentRoot == nullptr)
			return 0;
		if (currentRoot->left == nullptr && currentRoot->right == nullptr)
			counter++;
		int countL = count_leaves_help(currentRoot->left, counter + 1);
		int countR = count_leaves_help(currentRoot->right, counter + 1);

		return (currentRoot->left == nullptr && currentRoot->right == nullptr ? 1 : 0) + countL + countR;
	}

	bool isLeaf(Node<T>* currentRoot) {
		if (currentRoot == nullptr)
			return false;
		if (currentRoot->left == nullptr && currentRoot->right == nullptr)
			return true;
	}

	// Изкарва най-голямото листо
	T max_leaf_help(Node<T>* currentRoot, T maxLeaf) {
		if (currentRoot == nullptr) {
			return maxLeaf;
		}
		if (isLeaf(currentRoot) == true) {
			if (maxLeaf <= currentRoot->value)
				maxLeaf = currentRoot->value;
		}
		else {
			unsigned maxL = max_leaf_help(currentRoot->left, maxLeaf);
			unsigned maxR = max_leaf_help(currentRoot->right, maxLeaf);

			maxLeaf = (maxL > maxR ? maxL : maxR);
		}
		return maxLeaf;
	}

	int count_help(Node<T>* currentRoot, int counter) {
		if (currentRoot == nullptr)
			return 0;

		int counterL = count_help(currentRoot->left, counter);
		int counterR = count_help(currentRoot->right, counter);

		return 1 + counterL + counterR;
	}


	int count_evens(Node<T>* currentRoot, int counter) {
		if (currentRoot == nullptr)
			return 0;

		int counterL = count_evens(currentRoot->left, counter);
		int counterR = count_evens(currentRoot->right, counter);

		return (currentRoot->value % 2 == 0 ? 1 : 0) + counterL + counterR;
	}

	//Well this one is obvious
	bool find_helper(T value, Node<T>* currentRoot) {
		if (currentRoot == nullptr)
			return false;
		if (currentRoot->value == value)
			return true;
		else
			return find_helper(value, currentRoot->left) ||
			find_helper(value, currentRoot->right);

		return false;
	}

	//Търси пътя до даден node
	void find_path(T value, Node<T>* currentRoot) {
		if (find_helper(value, currentRoot) == false) {
			cout << value << " is not found" << endl;
			return;
		}
		if (currentRoot->value == value) {
			cout << "Found " << value << endl;
		}
		else {

			if (find_helper(value, currentRoot->left) == true) {
				cout << "L->";
				find_path(value, currentRoot->left);
			}
			else if (find_helper(value, currentRoot->right) == true) {
				cout << "R->";
				find_path(value, currentRoot->right);
			}
		}
	}
};

int main()
{
	BinTree<int> empty;
	BinTree<int> tr;
	tr.insert(5, "");
	tr.insert(6, "L");
	tr.insert(8, "R");
	tr.insert(6, "RL");
	tr.insert(8, "RR");
	tr.insert(6, "LL");
	tr.insert(6, "LR");
	tr.insert(50, "LLR");
	tr.insert(25, "RLR");
	tr.insert(2, "RLL");
	tr.insert(2, "LRR");
	tr.insert(7, "LRL");
	tr.insert(19, "LLL");

	tr.get_leaves();
	system("pause");
	return 0;
}