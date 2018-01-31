#include<iostream>
#include<queue>
using namespace std;

template<class T>
struct Node
{
	T data;
	Node<T> *left, *right;

	Node(int data)
	{
		this->data = data;
		left = NULL;
		right = NULL;
	}
};

template<class T>
class Tree
{
	Node<T>* root;
	queue<Node<T>*> q;

public:
	Tree()
	{
		root = NULL;
	}

	void addNode(Node<T> *newNode)
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
	void createTree()
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
	void delTree(Node<T> *_root)
	{
		if (_root)
		{
			delTree(_root->left);
			delTree(_root->right);
			delete _root;
			_root = nullptr;
		}
	}
	void printHelpBFS(Node<T>* _root)
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
	void printBFS()
	{
		printHelpBFS(this->root);
	}
	void printHelpDFS(Node<T>* _root)
	{
		if (_root)
		{
			cout << _root->data << " ";
			printHelpDFS(_root->left);
			printHelpDFS(_root->right);
		}
	}
	void printDFS()
	{
		printHelpDFS(this->root);
	}
};

int main()
{
	Tree<int> t;
	t.createTree();

	t.printDFS();
}