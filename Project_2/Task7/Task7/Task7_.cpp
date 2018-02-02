#include<iostream>
#include<queue>
#include<time.h>

using namespace std;

template<class T>
struct Node
{
	T data;
	int win;
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
		if(this != &n)
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
	Node<T>* root;
	queue<Node<T>*> q;
	void printHelpBFS(Node<T>* _root);
	void printHelpDFS(Node<T>* _root);
	int name(int n, Node<T>*);
	int tournamentHelper(Node<T> *root);
public:
	Tree();
	void addNode(Node<T> *);
	void createTree();
	void delTree(Node<T> *_root);
	void printBFS();
	void printDFS();
	int tournament();
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
int Tree<T>::tournamentHelper(Node<T>* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL) {
		int k = rand() % (root->data * 2 + 1) + root->data*(-1);
		root->win = k;
		return k;
	}

	int firstNumber = tournamentHelper(root->left);

	int secondNumber = tournamentHelper(root->right);

	if (firstNumber>secondNumber)
		return firstNumber;
	return secondNumber;
}

template <class T>
int Tree<T>::name(int n, Node<T>* _root)
{
	if (_root)
	{
		queue<Node<T>*> q;
		q.push(_root);
		while (!q.empty())
		{
			Node<T> *helper = q.front();
			q.pop();
			if (helper->win == n)
			{
				return helper->data;
			}
			if (helper->left)
				q.push(helper->left);
			if (helper->right)
				q.push(helper->right);
		}
	}
}

template<class T>
int Tree<T>::tournament()
{
	srand(time(0));
	int n = tournamentHelper(root);
	return name(n, root);
}


int main()
{
	Tree<int> t;
	t.createTree();
	cout << t.tournament();
	cout << endl;
	system("pause");
	return 0;
}

