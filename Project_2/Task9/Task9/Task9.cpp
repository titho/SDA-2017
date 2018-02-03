#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <time.h>

using namespace std;

struct Participant
{
	string name;
	int coefficient;
};

template<class T>
struct Node
{
	int a;
	Node<T> *left, *right;
	int win;
	Participant p;
	Node(Participant a)
	{
		p.coefficient = a.coefficient;
		p.name = a.name;
		left = NULL;
		right = NULL;
	}
	Node()
	{
		left = NULL;
		right = NULL;
	}
	Node(const Node<T>& n)
	{
		this->p.coefficient = n.p.coefficient;
		this->p.name = n.p.name;
		left = n->left;
		right = n->right;
	}
	Node& operator=(const Node<T>& n)
	{
		if (this != &n)
		{
			delete left;
			delete right;
			left = new Node<T>;
			right = new Node<T>;
			this->p.coefficient = n.p.coefficient;
				this->p.name = n.p.name;
			left = n->left;
			right = n->right;
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

public:
	Tree();
	void addNode(Node<T> *);
	void createTree();
	void delTree(Node<T> *_root);
	void printBFS();
	void printDFS();
	Node<T>* getRoot() const;
	// task 5
	// task 6
	// task 7
	int tournamentHelper(Node<T>* root); //finds the winner and returns his "winning number"
	string tournament();
	string name(int n, Node<T>* _root); //finds the winners' name by his "winning number"
										// task 8
};

template <class T>
Tree<T>::Tree()
{
	root = NULL;
}

template <class T>
Node<T>* Tree<T>::getRoot() const
{
	return root;
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
			cout << helper->p.name << " " << helper->p.coefficient << endl;
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
		cout << _root->p.name << " " << _root->p.coefficient;
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
//task 5 --------------------

bool inVector(vector<int> arr, const int element)
{
	vector<int>::iterator it = find(arr.begin(), arr.end(), element);
	if (it != arr.end())
		return true;

	return false;
}

template<class T>
void fillTree(vector<T> leaves, Tree<T>& tree)
{
	int size = leaves.size();
	vector<int> usedPositions;
	for (int i = 0; i < size; i++)
		usedPositions.push_back(-1);

	int i = 0;
	srand(time(NULL));
	while (i < leaves.size())
	{
		int position = rand() % leaves.size();
		if (!inVector(usedPositions, position))
		{
			usedPositions[i] = position;
			i++;
			Node<T>* nd = new Node<T>(leaves[position]);
			tree.addNode(nd);
		}
	}
}
//------------- Task 6 ----------

vector<Participant> readParticipants(ifstream& file)
{
	file.open("p.txt");

	if (!file)
	{
		cerr << "File couldn't be opened!" << endl;
		exit(1);
	}

	vector<Participant> allParticipants;
	while (!file.eof())
	{
		Participant a;

		while (file.peek() != ' ' && file.peek() != '\t')
		{
			char c;
			file >> c;
			a.name += c;
		}

		while (file.peek() == ' ' || file.peek() == '\t')
		{
			file.get();
		}

		string sCoefficient;
		getline(file, sCoefficient); // !!! now p.coefficient is string



		stringstream ss(sCoefficient);
		ss >> a.coefficient;
		allParticipants.push_back(a);
	}

	file.close();

	// get the size of the vector
	int n = allParticipants.size();
	// get random number
	srand(time(NULL));
	int random = rand() % n;
	// get random participants and add them to the result vector
	vector<Participant> randomParticipants;
	int index;
	for (int i = 0; i < random; i++)
	{
		index = rand() % n;
		randomParticipants.push_back(allParticipants[i]);
	}

	return randomParticipants;

}
//--------- Task 7

template<class T>
int Tree<T>::tournamentHelper(Node<T>* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL) {
		int k = rand() % (root->p.coefficient * 2 + 1) + root->p.coefficient*(-1);
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
string Tree<T>::name(int n, Node<T>* _root)
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
				return helper->p.name;
			}
			if (helper->left)
				q.push(helper->left);
			if (helper->right)
				q.push(helper->right);
		}
	}
}

template<class T>
string Tree<T>::tournament()
{
	int n = tournamentHelper(root);
	return name(n, root);
}
//--------------- Task 8
template <class T>
void findpath(string& _name, Node<T>* root)
{
	if (root == NULL)
	{
		return;
	}
	if (_name.empty())
	{
		return;
	}

	if (root->left == NULL && root->right == NULL)
		return;

	if (root->left->p.name == _name || root->right->p.name == _name)
	{
		cout << root->left->p.name << " VS " << root->right->p.name << endl;
		if (root->left->p.name == _name)
		{
			findpath(_name, root->left);
		}
		else
		{
			findpath(_name, root->right);
		}
	}

	else
	{
		findpath(_name, root->left);
		findpath(_name, root->right);
	}

}
int main()
{
	ifstream file;
	vector<Participant> a;
	a = readParticipants(file);

	Tree<Participant> t;

	fillTree(a, t);
	cout << t.tournament() << endl;

	system("pause");
	return 0;
}
