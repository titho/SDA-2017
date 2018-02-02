#include<iostream>
#include<queue>

using namespace std;

template<class T>
struct Node
{
	T data;
	Node<T> *left, *right;

	Node<T>()
	{

		left = NULL;
		right = NULL;
	}
	Node<T>(int data)
	{
		this->data = data;
		left = NULL;
		right = NULL;
	}
	Node<T>(const Node<T>& n)
	{
		this->data = n->data;
		left = n->data;
		right = n->data;
	}
	Node<T>& operator=(const Node<T>& n)
	{
		if (this != &n)
		{
			delete left;
			delete right;
			left = new Node<T>;
			right = new Node<T>;
			this->data = n->data;
			left = n->data;
			right = n->data;
		}
		return *this;
	}
};

template<class T>
class Tree
{
	int static const MAX_PLAYERS = 256;
	Node<T>* root;
	queue<Node<T>*> q;
	void printHelpBFS(Node<T>* _root);
	void printHelpDFS(Node<T>* _root);
	Node<T>* tournamentArrayHelper(int n, Node<T>* arr1[MAX_PLAYERS], T arr2[MAX_PLAYERS]);
	int tournamentHelper(Node<T> *root, Node<T>* arr1[MAX_PLAYERS], T* arr2, int i);
public:
	Tree();
	void addNode(Node<T> *);
	void createTree();
	void delTree(Node<T> *_root);
	void printBFS();
	void printDFS();
	Node<T>* tournament();
};


template <class T>
Tree<T>::Tree()
{
	root = NULL;
}


template<class T>
void Tree<T>::printHelpBFS(Node<T>* _root)
{
	if (_root)
	{
		queue<Node<T>*> q;
		q.push(_root);
		while (!q.empty())
		{
			Node<T> *helper = q.front();
			q.pop();
			cout << helper->data << " ";
			if (helper->left)
				q.push(helper->left);
			if (helper->right)
				q.push(helper->right);
		}
	}
}

template<class T>
void Tree<T>::printHelpDFS(Node<T>* _root)
{
	if (_root)
	{
		cout << _root->data << " ";
		printHelpDFS(_root->left);
		printHelpDFS(_root->right);
	}
}

template<class T>
string Tree<T>::tournamentArrayHelper(int n, Node<T>* arr1[MAX_PLAYERS], T arr2[MAX_PLAYERS])
{
	int k = sizeof(arr1) / sizeof(arr1[0]);
	for (int i = 0; i < k; i++)
	{
		if (arr2[i] == n)
		{
			return arr1[i];
		}
		return 0;
	}
}

template<class T>
int Tree<T>::tournamentHelper(Node<T>* root, Node<T>* arr1[MAX_PLAYERS], T * arr2, int i)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL) {
		cout << "This one is " << root->data << endl;
		arr1[i] = root;
		int k = rand() % (root->data * 2 + 1) + root->data*(-1);
		arr2[i] = k;

		return k;
	}
	//
	//if (root->left != NULL)
	//cout << "This one is ->left and " << root->left->data << endl;
	int firstNumber = tournamentHelper(root->left, arr1, arr2, i++);

	//if(root->right != NULL)
	//cout << "This one is ->right and " << root->right->data << endl;
	int secondNumber = tournamentHelper(root->right, arr1, arr2, i++);
	cout << firstNumber << " VS " << secondNumber << endl;

	if (firstNumber>secondNumber)
		return firstNumber;
	return secondNumber;
}


template<class T>
void Tree<T>::addNode(Node<T>* newNode)
{
	if (!root)
	{
		root = newNode;
		q.push(root);
		return;
	}

	Node<T> *n = q.front();
	if (n->left && n->right)
	{
		q.pop();
		n = q.front();
	}
	if (!n->left)
		n->left = newNode;
	else if (!n->right)
		n->right = newNode;

	q.push(newNode);
}

template<class T>
void Tree<T>::createTree()
{
	char c;
	do
	{
		int x;
		cout << "Element: "; cin >> x;
		addNode(new Node<T>(x));

		cout << "New element y/n? "; cin >> c;
	} while (c == 'y');
}

template<class T>
void Tree<T>::delTree(Node<T>* _root)
{
	if (_root)
	{
		delTree(_root->left);
		delTree(_root->right);
		delete _root;
		_root = nullptr;
	}
}

template<class T>
void Tree<T>::printBFS()
{
	printHelpBFS(this->root);
}

template<class T>
void Tree<T>::printDFS()
{
	printHelpDFS(this->root);
}

template<class T>
Node<T>* Tree<T>::tournament()
{
	Node<T>* arr1[MAX_PLAYERS];
	T arr2[MAX_PLAYERS] = { 0 };
	int i = 0;
	int n = tournamentHelper(root, arr1, arr2, i);
	return tournamentArrayHelper(n, arr1, arr2);
}

int main()
{
	Tree<int> t;
	t.createTree();
	t.printBFS();
	Node<int>* a = new Node<int>;
	a = t.tournament();
	cout << endl;
	cout << a->data << endl;
	system("pause");
	return 0;
}

