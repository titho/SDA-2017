#include <iostream>

using namespace std;

const int MAX = 100;

template<class T>
class Queue
{
	int head;
	int tail;
	int itemCount; // *
	T * array;

	void copyQueue(const Queue<T>& other) // *
	{
		head = other.head;
		tail = other.tail;
		itemCount = other.itemCount;
		array = new T[MAX];
		for (int i = 0; i <= itemCount; i++)
			array[i] = other.array[i];
	}

	void removeQueue()
	{
		delete[] array;
	}
public:
	Queue<T>() //default constructor
	{
		head = 0;
		tail = -1; // *
		itemCount = 0;
		array = new T[MAX];
	}

	Queue<T>(const Queue<T>& other) //copy constructor
	{
		copyQueue(other);
	}

	Queue<T>& operator=(const Queue<T>& other) //copy assignment operator
	{
		if (this != &other)
		{
			removeQueue();
			copyQueue(other);
		}
		return *this;
	}

	~Queue<T>() //destructor
	{
		removeQueue();
	}

	bool isEmpty() const
	{
		return itemCount == 0; // *
	}

	bool isFull() const
	{
		return itemCount == MAX; // *
	}

	int size() const
	{
		return itemCount; // *
	}

	T front() const
	{
		if (!isEmpty())
			return array[head];
		else
			cout << "The queue is empty!";
	}

	T back() const
	{
		if (!isEmpty())
			return array[tail];
		else
			cout << "The queue is empty!";
	}

	void pop()
	{
		if (!isEmpty())
		{
			head++;
			itemCount--;
		}
		else
			cout << "The queue is empty!";
	}

	void push(T element)
	{
		if (!isFull())
		{
			array[++tail] = element; // *
			itemCount++; // *
		}
		else
			cout << "The queue is full!";
	}

	void swap(int first, int second)
	{
		if (first != second && first >= 0 && second >= 0)
		{
			T temp = array[first];
			array[first] = array[second];
			array[second] = temp;
		}
	}
	void swapQueue(Queue<T>& other)
	{
		Queue temp = *this;
		*this = other;
		other = temp;
		temp.removeQueue();
	}

	friend ostream& operator<<(ostream& os, const Queue<T>& q)
	{
		for (int i = 0; i <= q.itemCount; i++)
		{
			cout << q.array[i] << " ";
		}
		return os;
	}

};

int main()
{
	Queue<int> q1;
	for (int i = 0; i < 10; i++)
	{
		q1.push(i); // ?
	}
	cout << q1 << endl;
	for (int i = 0; i < 5; i++)
	{
		q1.pop();
	}
	cout << q1 << endl;

	// test copy constructor
	Queue<int> q2(q1), q3;
	cout << q2 << endl;

	// test operator=
	q3 = q1;
	cout << q3 << endl;

	q1.swap(1, 2);
	cout << q1 << endl;
	// !!! q1.push(94);
	q1.swapQueue(q2);
	cout << "Q1 " << q1 << " Q2: " << q2 << endl;


	Queue<char> c1;
	for (char i = 'a'; i <= 'z'; i++)
	{
		c1.push(i);
	}
	cout << c1 << endl;

	Queue<char> c2(c1), c3;
	cout << c1 << endl;
	cout << c3 << endl;
	return 0;
}