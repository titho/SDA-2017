#include<iostream>
#include<vector>

using namespace std;

template <typename T>
struct Node
{
	T key;
	struct Node *left, *right;
};

template <typename T>
Node<T> *newNode(T key)
{
	Node<T> *temp = new Node<T>;
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	return (temp);
}

template <typename T>
void createNode(vector<T>  &parent, int i, vector< Node<T>* >  &created, Node<T> **root)
{
	if (created[i] != NULL)
		return;

	created[i] = newNode(i);

	if (parent[i] == -1)
	{
		*root = created[i];
		return;
	}

	if (created[parent[i]] == NULL)
	{
		createNode(parent, parent[i], created, root);
	}

	Node<T> *p = created[parent[i]];

	if (p->left == NULL)
	{
		p->left = created[i];
	}
	else
		p->right = created[i];
}

template <typename T>
Node<T> *createTree(vector<T> &parent, int n)
{
	vector<Node<T>* > created;

	for (int i = 0; i<n; i++)
	{
		created.push_back(NULL);
	}

	Node<T> *root = NULL;

	for (int i = 0; i<n; i++)
		createNode(parent, i, created, &root);

	return root;
}

template<typename T>
void inorder(Node<T> *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		cout << root->key << " ";
		inorder(root->right);
	}
}

int main()
{
	vector<int> parent;
	parent.push_back(-1);
	parent.push_back(0);
	parent.push_back(0);
	parent.push_back(1);
	parent.push_back(1);
	parent.push_back(3);
	parent.push_back(5);

	int n = parent.size();
	Node<int> *root = createTree(parent, n);

	inorder(root);
}