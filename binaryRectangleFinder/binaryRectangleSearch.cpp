/****************************************************************************************************
This project gets the width and heigth of a 2D matrix from the user, randomly generates a binary
matrix with those dimensions, and allows the user to search the matrix for rectangles whos corners
are 0 (the contents of the rectangle are irrelevant). The corners are then output into a file.
--------------------------------------------------------------------------------------------------
Explination of Logic:
--------------------------------------------------------------------------------------------------
Created by: Puugu
Created on: 19 April 2017
--------------------------------------------------------------------------------------------------
Last Edit: n/a
****************************************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//function predicates
int getUserMenuSelection();

int main() {

	//declare and initalize variables, etc.
	int menuSelection = 0;

	//display program welcome
	cout << "Welcome to Binary Rectangle Finder\n\n";
	menuSelection = getUserMenuSelection();

	cout << "Menu Selection was: " << menuSelection<< endl;

	system("pause");
	return 0;
}

int getUserMenuSelection() {
	//This function displays the menu to the user and gets the user's menu selection
	// Created by Puugu on 19 April 2017

	//declare and intialize variables, etc.
	int menuSelection = 0;

	//display menu options
	cout << "Main Menu: \n1. Create Matrix \n2. Find Rectangles \n3. Exit \n";
	cout << "Please enter your selection: ";
	cin >> menuSelection;
	cout << endl;
	//validate input
	while ((!cin) || (menuSelection<1) || (menuSelection>3)) {
		//clear error
		cin.clear();
		//flush input buffer
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//Tell user they have entered invalid data and prompt for re-entry
		cout << "ERROR: Your input was not valid. Please make a selection from the menu below: ";
		cout << "Main Menu: \n1. Create Matrix \n2. Find Rectangles \n3. Exit \n";
		cout << "Please enter your selection: ";
		cin >> menuSelection;
		cout << endl;
	}

	return menuSelection;
}