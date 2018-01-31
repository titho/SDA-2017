#include <iostream>
#include <cstring>

using namespace std;

class Car
{
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
        ID = new char[strlen(id)+1];
        strcpy(ID,id);
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
        ID = new char[strlen(id)+1];
        strcpy(ID,id);
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

    friend ostream& operator<<(ostream& os,Car const& car)
    {
        os << "Car ID: " << car.getID() << endl;
        os << "Weight: " << car.getWeight() << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Car& car)
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
int main()
{
    // test default constructor
    Car car;
    cout << car << endl;

    Car carr(car);
    cout << carr << endl;

    Car carrr = car;
    cout << carrr << endl;
    
    // test parametrized Constructor
    Car car2("123fff", 598120);
    cout << car2 << endl;

    // test copy constructor
    Car car3(car2);
    cout << car3 << endl;

    // test operator=
    car = car2;
    cout << car << endl;

    // test operator>>
    Car car4;
    cin >> car4;
    cout << car4;
    return 0;
}
