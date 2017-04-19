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
int getRectangleWidth();
int getRectangleHeight();
void generateRectangleFile(int width, int height);

int main() {

	//declare and initalize variables, etc.
	int menuSelection = 0;
	int rectangleWidth = 0;
	int rectangleHeight = 0;

	//display program welcome
	cout << "Welcome to Binary Rectangle Finder\n\n";
	do {
		menuSelection = getUserMenuSelection();

		//process menu selection
		switch (menuSelection) {
		case 1:
			cout << "Create Matrix has been selected.\n";
			// call function to get width of rectangle
			rectangleWidth = getRectangleWidth();
			// call function to get heigth of rectange
			rectangleHeight = getRectangleHeight();
			// call function to generate rectangle output file
			generateRectangleFile(rectangleWidth, rectangleHeight);
			break;
		case 2:
			cout << "Searching for rectangles. This code is not yet implemented.\n";
			break;
		case 3:
			cout << "Thank you for using Binary Rectangle Finder. Program will now close.\n";
			break;
		default:
			cout << "Menu Selection Error Occurred. Program will now terminate.\n";
			menuSelection = 3;
		}
	} while (menuSelection != 3);

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

	//return menu selection
	return menuSelection;
}

int getRectangleWidth() {
	//This function gets the width for the binary rectange from the user
	//Created by Puugu on 19 April 2017

	//declare and intialize variables, etc.
	int rectWidth = 0;

	//Prompt user for rectangle width
	//Assignment specified width must be between 10 and 80, inclusive
	cout << "The width of the rectangle must be between 10 and 80, inclusive.\n";
	cout << "Please enter the desired width of the binary rectangle: ";
	cin >> rectWidth;
	cout << endl;
	//validate input
	while ((!cin) || (rectWidth<10) || (rectWidth>80)) {
		//clear error
		cin.clear();
		//flush input buffer
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//Tell user they have entered invalid data and prompt for re-entry
		cout << "ERROR: Your input was not valid. Please enter a width between 10 and 80, inclusive: ";
		cin >> rectWidth;
		cout << endl;
	}

	//return rectangle width
	return rectWidth;
}

int getRectangleHeight() {
	//This function gets the height for the binary rectange from the user
	//Created by Puugu on 19 April 2017

	//declare and intialize variables, etc.
	int rectHeigth = 0;

	//Prompt user for rectangle height
	//Assignment specified height must be between 10 and 50, inclusive
	cout << "The height of the rectangle must be between 10 and 50, inclusive.\n";
	cout << "Please enter the desired height of the binary rectangle: ";
	cin >> rectHeigth;
	cout << endl;
	//validate input
	while ((!cin) || (rectHeigth<10) || (rectHeigth>50)) {
		//clear error
		cin.clear();
		//flush input buffer
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//Tell user they have entered invalid data and prompt for re-entry
		cout << "ERROR: Your input was not valid. Please enter a height between 10 and 50, inclusive: ";
		cin >> rectHeigth;
		cout << endl;
	}

	//return rectangle height
	return rectHeigth;
}

void generateRectangleFile(int width, int height) {
	//This function creates the binary rectangle and outputs as a file
	//Created by Puugu on 19 April 2017

	//declare and intialize variables, etc.
	int binVal = 0;
	ofstream binaryRectangleFile("binRect.txt");

	//first line of output file will have the width and height
	binaryRectangleFile << width <<" "<< height << endl;

	//generate values for output file
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			binVal = rand() % 2;
			binaryRectangleFile << binVal << " ";
		}
		binaryRectangleFile << endl;
	}

	//close file and exit function
	binaryRectangleFile.close();
	return;
}