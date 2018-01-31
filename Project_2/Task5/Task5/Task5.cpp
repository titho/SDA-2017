#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

template <class T>
class CompleteBinTree
{
private:
	T* values;
	int current;
	int capacity;

	void resize();
	void clean();
	void copy(CompleteBinTree<T> const&);
public:
	CompleteBinTree();
	~CompleteBinTree();
	CompleteBinTree(CompleteBinTree<T> const&);
	CompleteBinTree& operator=(CompleteBinTree<T> const&);

	void addElement(T const& x);
	int leftChildIndex(int index) const;
	int rightChildIndex(int index) const;
	bool empty() const;
	void create();
	void print() const;
	void printBFS();
	void printDFS(); // TO DO
};

template <class T>
CompleteBinTree<T>::CompleteBinTree()
{
	capacity = 16;
	current = 0;
	values = new T[capacity];
}

template <class T>
CompleteBinTree<T>::~CompleteBinTree()
{
	clean();
}

template <class T>
CompleteBinTree<T>::CompleteBinTree(CompleteBinTree<T> const& other)
{
	copy(other);
}

template <class T>
CompleteBinTree<T>& CompleteBinTree<T>::operator=(CompleteBinTree<T> const& other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

template <class T>
void CompleteBinTree<T>::resize()
{
	T* helper = new T[capacity];
	for (int i = 1; i <= current; i++)
		helper[i] = values[i];

	clean();

	capacity *= 2;
	values = new T[capacity];
	for (int i = 1; i <= current; i++)
		values[i] = helper[i];
	delete[] helper;
}

template <class T>
void CompleteBinTree<T>::copy(CompleteBinTree<T> const& other)
{
	capacity = other.capacity;
	current = other.current;
	values = new T[capacity];
	for (int i = 1; i <= current; i++)
		values[i] = other.values[i];
}

template <class T>
void CompleteBinTree<T>::clean()
{
	delete[] values;
}

template <class T>
void CompleteBinTree<T>::addElement(T const& x)
{
	if (current == capacity - 1)
		resize();
	values[current++] = x;
}

template <class T>
int CompleteBinTree<T>::leftChildIndex(int index) const
{
	if (2 * index <= current)
		return 2 * index;
	return -1;
}

template <class T>
int CompleteBinTree<T>::rightChildIndex(int index) const
{
	if (2 * index + 1 <= current)
		return 2 * index + 1;
	return -1;
}

template <class T>
bool CompleteBinTree<T>::empty() const
{
	return current == 0;
}

template <class T>
void CompleteBinTree<T>::create()
{
	char c;
	do
	{
		int x;
		cout << "Enter element: ";
		cin >> x;
		addElement(x);
		cout << "Next element y/n? ";
		cin >> c;
	} while (c == 'y');
}

template <class T>
void CompleteBinTree<T>::printBFS()
{
	for (int i = 0; i < current; i++)
		cout << values[i] << " ";
	cout << endl;
}


bool inVector(vector<int> arr, const int element)
{
	vector<int>::iterator it = find(arr.begin(), arr.end(), element);
	if (it != arr.end())
		return true;

	return false;
}

template<class T>
void myerase(vector<T>& vec, int index)
{
	for (unsigned i = index + 1; i < vec.size() - 1; i++)
		vec[i - 1] = vec[i];
	vec.pop_back();
}

template<class T>
void fillTree(vector<T> leaves, CompleteBinTree<T>& tree)
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
			tree.addElement(leaves[position]);
		}
	}
}

int main()
{
	vector<int> vec;

	for (int i = 0; i < 10; i++)
		vec.push_back(i);

	CompleteBinTree<int> tree;
	fillTree(vec, tree);

	tree.printBFS();
	return 0;
}