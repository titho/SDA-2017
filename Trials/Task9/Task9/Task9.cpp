#include <iostream>
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
	int static const MAX_PLAYERS = 256;
	/*int p.coefficient;
	string name;*/
	Node<T> *left, *right;
	Participant p;
	//Node(T p.coefficient, string name)
	//{
	//	this->p.coefficient = p.coefficient;
	//	this->name = name;
	//	left = NULL;
	//	right = NULL;
	//}
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
};

template<class T>
class Tree
{
	int static const MAX_PLAYERS = 256;
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
	//bool inVector(vector<int> arr, const int element);
	//void fillTree(vector<T> leaves, Tree<T>& tree);
	// task 6
	//vector<Participant> readParticipants(ifstream& file);
	// task 7
	string tournamentArrayHelper(int n, Node<T>* arr1[MAX_PLAYERS], int arr2[MAX_PLAYERS]);
	int tournamentHelper(Node<T> *root, Node<T>* arr1[MAX_PLAYERS], int* arr2, int i);
	string tournament();
	// task 8
	//void findpath(string& _name, Node<T>*& root);
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
//task 5

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
string Tree<T>::tournamentArrayHelper(int n, Node<T>* arr1[MAX_PLAYERS], int arr2[MAX_PLAYERS])
{
	int k = sizeof(arr2) / sizeof(arr2[0]);
	cout << "Number of elements in the array: " << sizeof(arr2) / sizeof(arr2[0]) << endl;
	for (int i = 0; i < k; i++)
	{
		if (arr2[i] == n)
		{
			Node<T>* a;
			a = arr1[i];
			string str;
			str = a->p.name;
			return str;
		}
	}
}

template<class T>
int Tree<T>::tournamentHelper(Node<T>* root, Node<T>* arr1[MAX_PLAYERS], int * arr2, int i)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL) {
		//cout << "This one is " << root->p.coefficient << endl;
		arr1[i] = root;
		int k = rand() % (root->p.coefficient * 2 + 1) + root->p.coefficient*(-1);
		arr2[i] = k;

		return k;
	}
	//
	//if (root->left != NULL)
	//cout << "This one is ->left and " << root->left->p.coefficient << endl;
	int firstNumber = tournamentHelper(root->left, arr1, arr2, i++);

	//if(root->right != NULL)
	//cout << "This one is ->right and " << root->right->p.coefficient << endl;
	int secondNumber = tournamentHelper(root->right, arr1, arr2, i++);
	cout << firstNumber << " VS " << secondNumber << endl;

	if (firstNumber>secondNumber)
		return firstNumber;
	return secondNumber;
}

template<class T>
string Tree<T>::tournament()
{
	Node<T>* arr1[MAX_PLAYERS];
	int arr2[MAX_PLAYERS] = { 0 };
	int i = 0;
	int n = tournamentHelper(root, arr1, arr2, i);
	return tournamentArrayHelper(n, arr1, arr2);
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
	/*for (int i = 0; i < a.size(); i++)
	{
		cout << a[i].name << " " << a[i].coefficient << endl;
	}*/

	Tree<Participant> t;
	string str = a[6].name;
	//cout << "fillTree\n";
	t.tournament();
	fillTree(a, t);
	//findpath(str, t.getRoot());
	//cout << "BFS\n";
	//t.printBFS();

	system("pause");
}