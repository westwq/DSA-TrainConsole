// TrainConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Dictionary.h"
#include <string>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

void displayMenu();
void loadData();
list<string> loadFile(string);
void loadStations();
void loadRoutes();
void loadInterchanges();
void loadFares();

const string PATH = "data\\Simple\\";

Dictionary stations;

int main()
{
	loadData();

	while (true)
	{
		displayMenu();
		cout << "Enter option or Q/q to quit: ";
		char option;
		cin >> option;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//cin.ignore();

		switch (option)
		{
			case '1':
			case '2':
			case '3':
			case '4':
				cout << option << endl;
				break;
			case 'Q':
			case 'q':
				cout << "Goodbye!" << endl;
				goto endloop;
			default:
				cout << ">>>>>>>>>>>> Invalid input <<<<<<<<<<<<" << endl;
		};
	}

	endloop:
	system("PAUSE");
	return 0;
}

void loadData()
{
	loadStations();
}

void loadStations()
{
	list<string> contents = loadFile(PATH + "Stations.csv");

	for (std::list<string>::iterator it = contents.begin(); it != contents.end(); ++it) {
		string token[2];
		int i = 0;
		stringstream iss(*it);
		while (getline(iss, token[i++], ','));
		stations.add(token[0], token[1]);
	}
}

void loadRoutes()
{
	list<string> contents = loadFile(PATH + "Routes.csv");

	for (std::list<string>::iterator it = contents.begin(); it != contents.end(); ++it) {

	}
}

void loadInterchanges()
{
	list<string> contents = loadFile(PATH + "Stations.csv");
}

void loadFares()
{
	list<string> contents = loadFile(PATH + "Stations.csv");
}

list<string> loadFile(string file)
{
	ifstream infile;
	list<string> lines;
	string line;

	infile.open(file);
	while (getline(infile,line))
	{
		lines.push_back(line);
	}

	infile.close();

	return lines;
}

void displayMenu()
{
	cout << "======== MRT Console ========" << endl;
	cout << "(1) Display all stations of a line" << endl;
	cout << "(2) Display station information" << endl;
	cout << "(3) Add new station" << endl;
	cout << "(4) Search for a route" << endl;
	cout << "(5) Add new line" << endl;
	cout << "(6) Search for shortest route" << endl;
	cout << "(7) Search for 3 feasible routes" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
