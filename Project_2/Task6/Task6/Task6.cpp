// trii.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Participant
{
	string name;
	int coefficient;
};

vector<Participant> readParticipants(ifstream& file)
{
	file.open("participants.txt");

	if (!file)
	{
		cerr << "File couldn't be opened!" << endl;
		exit(1);
	}

	vector<Participant> allParticipants;
	while (!file.eof())
	{
		Participant p;
		getline(file, p.name, ' ');
		string sCoefficient;
		getline(file, sCoefficient); // !!! now p.coefficient is string
									 // std::stoi was introduced in C++11. Make sure your compiler settings are correct and/or your compiler supports C++11
		p.coefficient = stoi(sCoefficient); // convert string coeff to int
											// store the participant
		allParticipants.push_back(p);
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
	//myFile.open("participants.txt");
	vector<Participant> result = readParticipants(file);
	for (int i = 0; i < result.size(); i++)
		cout << "Name: " << result[i].name << "\n Coefficient: " << result[i].coefficient << endl;
	return 0;
}