#include <iostream>
#include <cstring>
using namespace std;

class Car
{
protected:
	char* ID;
	int weight;

	void deleteCar()
	{
		delete[] ID;
	}

	void copyCar(Car const& other)
	{
		weight = other.weight;
		ID = new char[strlen(other.ID) + 1];
		//strcpy_s(ID, strlen(other.ID) + 1,  other.ID); - strcpy_s само дава грешки и го махнах :D
		strcpy(ID, other.ID);
	}

public:
	Car()
	{
		ID = new char[1];
		ID[0] = '\0';
		weight = 0;
	}

	Car(char* id, int _weight)
	{
		weight = _weight;
		ID = new char[strlen(id) + 1];
		//strcpy_s(ID, strlen(id) + 1, id);
		strcpy(ID, id);
	}

	Car(Car const& other)
	{
		copyCar(other);
	}

	Car& operator=(Car const& other)
	{
		if (this != &other)
		{
			deleteCar();
			copyCar(other);
		}
		return *this;
	}

	~Car()
	{
		deleteCar();
	}

	void setID(char* id)
	{
		delete[] ID;
		ID = new char[strlen(id) + 1];
		//strcpy_s(ID, strlen(id) + 1, id);
		strcpy(ID, id);
	}

	void setWeight(int _weight)
	{
		weight = _weight;
	}

	const char* getID() const
	{
		return ID;
	}

	int getWeight() const
	{
		return weight;
	}

	friend ostream& operator<<(ostream& os, Car const& car)
	{
		os << "Car ID: " << car.getID() << endl;
		os << "Weight: " << car.getWeight() << endl;
		return os;
	}

	friend istream& operator >> (istream& is, Car& car)
	{
		char temp[256];
		int _weight;

		is >> temp >> _weight;
		car.setWeight(_weight);
		car.setID(temp);
		//car.ID = new char[strlen(temp) + 1];
		//strcpy(ID,temp);

		return is;
	}


};

class Garage
{
private:
	Car* garage; // тъй като гаража е множество от коли, реших да преименувам cars :D
	int currentGarageWeight;
	int maxGarageWeight;
	int maxWeightCar;
	int capacity;
	int index; //Колко места от гаража са запълнени.

	void copy(Garage const& other)
	{
		maxGarageWeight = other.maxGarageWeight;
		capacity = other.capacity;
		maxWeightCar = other.maxWeightCar;
		index = other.index;
		currentGarageWeight = other.currentGarageWeight;
		garage = new Car[capacity];

		for (int i = 0; i <= index; i++)
		{
			garage[i] = other.garage[i];
		}
	}

public:
	Garage()
	{
		currentGarageWeight = 0;
		maxGarageWeight = 15000;
		maxWeightCar = 1500;
		capacity = 10;
		index = -1;
		garage = new Car[capacity];
	}

	Garage(int _maxGarageWeight, int _capacity, int _maxWeightCar)
	{
		maxGarageWeight = _maxGarageWeight;
		capacity = _capacity;
		maxWeightCar = _maxWeightCar;
		index = 0;
		currentGarageWeight = 0;
		garage = new Car[capacity];

	}

	Garage(Garage const& other)
	{
		/*
		maxWeight = other.maxWeight;
		cap = other.cap;
		maxWeightCar = other.maxWeightCar;
		index = other.index;
		garageWeight = other.getWeight();
		cars = new Car[other.cap];
		*/

		copy(other);
	}

	Garage& operator=(Garage const& other)
	{
		if (this != &other)
		{
			delete[] garage;
			/*
			maxWeight = other.maxWeight;
			cap = other.cap;
			maxWeightCar = other.maxWeightCar;
			index = other.index;
			garageWeight = other.getWeight();
			cars = new Car[other.cap];
			*/
			copy(other);

		}
		return *this;
	}

	~Garage()
	{
		delete[] garage;
	}

	void carIn(Car const& car) // слагам const& ... да има
	{
		char* a;
		a = new char[strlen(car.getID()) + 1];
		// strcpy_s(a, strlen(car.getID()) + 1, car.getID());
		strcpy(a, car.getID());

		if ((a[0] == 1 && a[1] == 3) ||
			((car.getWeight() + currentGarageWeight) > maxGarageWeight) ||
			car.getWeight() > maxWeightCar)
		{
			cout << "The garage is full!" << endl;
		}
		else
		{
			garage[index] = car;
			currentGarageWeight += car.getWeight();
			index++;
		}

		delete a;
	}

	void setGarageMaxWeight(int _max)
	{
		maxGarageWeight = _max;
	}
	void setGarageCapacity(int _cap)
	{
		capacity = _cap;
	}
	void setGarageMaxWeightCar(int _max)
	{
		maxWeightCar = _max;
	}

	int getGarageMaxWeight() const
	{
		return maxGarageWeight;
	}
	int getMaxWeightCar() const
	{
		return maxWeightCar;
	}
	int getCurrentGarageWeight() const
	{
		return currentGarageWeight;
	}
	int getCarsInGarage() const
	{
		return index;
	}
	int getGarageCapacity() const
	{
		return capacity;
	}

	void carOut()
	{
		currentGarageWeight -= garage[index].getWeight();
		index--;
	}

	friend ostream& operator<<(ostream& os, Garage const& gar)
	{
		os << "Current garage Weight: " << gar.getCurrentGarageWeight() << endl;
		os << "Cars in garage: " << gar.getCarsInGarage() << endl;
		os << "Garage capacity: " << gar.getGarageCapacity() << endl;
		os << "Free spaces: " << gar.getGarageCapacity() - gar.getCarsInGarage() << endl;
		return os;
	}

	friend istream& operator >> (istream& is, Garage& gar)
	{
		int _maxWeight, _cap, _maxWeightCar;
		is >> _maxWeight >> _cap >> _maxWeightCar;
		gar.setGarageMaxWeight(_maxWeight);
		gar.setGarageCapacity(_cap);
		gar.setGarageMaxWeightCar(_maxWeightCar);
		return is;
	}
};
int main()
{

	// test default constructor
	Garage garage;
	cout << garage << endl;

	Garage garagee(garage);
	cout << garagee << endl;

	Garage garageee = garage;
	cout << garageee << endl;

	// test parametrized Constructor
	Garage garage1(10000, 15, 1500);
	cout << garage1 << endl;

	// test copy constructor
	Garage garage2(garage1);
	cout << garage2 << endl;

	// test operator=
	garage = garage2;
	cout << garage << endl;

	// test carIn
	Car car2("123fff", 1000);
	cout << garage1 << endl;
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);
	garage1.carIn(car2);

	cout << garage1 << endl;

	garage1.carOut();
	garage1.carOut();
	garage1.carOut();
	garage1.carOut();

	cout << garage1 << endl;

	return 0;
}
