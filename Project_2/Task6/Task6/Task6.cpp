// zadacha6.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;

struct Participant
{
	string name;
	int coefficient;
};

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

int main()
{
	ifstream file;
	vector<Participant> result = readParticipants(file);
	for (int i = 0; i < result.size(); i++)
	{
		cout << "Name: " << result[i].name << endl;
		cout << "Coefficient: " << result[i].coefficient << endl;
	}

	return 0;
}