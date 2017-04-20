/****************************************************************************************************
This project gets the width and heigth of a 2D matrix from the user, randomly generates a binary
matrix with those dimensions, and allows the user to search the matrix for rectangles whos corners
are 0 (the contents of the rectangle are irrelevant). The corners are then output into a file.
--------------------------------------------------------------------------------------------------
Explination of Logic:
First, search row by column to find upper left zero. When found, pass to function to find bottom left
zero - simply have to move down the column, giving fewer values to check. Next check for top right 
zero - only have to move to end of row. Finally, use bottom left and upper right zeros to find
location of  lower right corner, and check to ensure is zero - this prevents having to search 
through the 2d matrix.
While this approach is not the most efficient process, it meets all the requirements in the document
provided at the start of the assignment. I'm following the philosophy of "if it works, ship it
and move on to the next thing."
--------------------------------------------------------------------------------------------------
Created by: Puugu
Created on: 19 April 2017
--------------------------------------------------------------------------------------------------
Last Edit: n/a
****************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

//function predicates
int getMainMenuSelection();
int getRectangleWidth();
int getRectangleHeight();
string generateRectangleFile(int width, int height);
bool findRectangles(string fileName);
bool verifyFileExists(string fileName);
void findLowerLeft(int *binMatrix, int upperLeft[2], int rectWidth, int rectHeight, ofstream& cornersFile);
void findUpperRight(int *binMatrix, int upperLeft[2], int lowerLeft[2], int rectWidth, int rectHeight, ofstream& cornersFile);
bool findLowerRight(int *binMatrix, int lowerLeft[2], int upperRight[2], int rectWidth, int rectHeight);
void addCorners(int upperLeft[2], int lowerLeft[2], int upperRight[2], ofstream& cornersFile);

int main() {

	//declare and initalize variables, etc.
	int menuSelection = 0;
	int rectangleWidth = 0;
	int rectangleHeight = 0;
	string fileName = "fileNeverCreated";
	bool rectanglesSearched = false;

	//display program welcome
	cout << "Welcome to Binary Rectangle Finder\n\n";
	do {
		menuSelection = getMainMenuSelection();

		//process menu selection
		switch (menuSelection) {
		case 1:
			cout << "Create Matrix has been selected.\n";
			// call function to get width of rectangle
			rectangleWidth = getRectangleWidth();
			// call function to get heigth of rectange
			rectangleHeight = getRectangleHeight();
			// call function to generate rectangle output file
			fileName = generateRectangleFile(rectangleWidth, rectangleHeight);
			break;
		case 2:
			//call function to find rectangles
			rectanglesSearched = findRectangles(fileName);
			//check to see if file was available to be searched
			if (rectanglesSearched == false) {
				cout << "ERROR: File <" << fileName <<"> could not be found.\n";
			}
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

int getMainMenuSelection() {
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

string generateRectangleFile(int width, int height) {
	//This function creates the binary rectangle and outputs as a file
	//Created by Puugu on 19 April 2017

	//declare and intialize variables, etc.
	int binVal = 0;
	string fileName = "binRect.txt";
	ofstream binaryRectangleFile(fileName);

	//first line of output file will have the width and height
	binaryRectangleFile << width <<" "<< height << endl;

	//generate values for output file
	for (int i = 0; i < height-1; i++) {
		for (int j = 0; j < width-1; j++) {
			binVal = rand() % 2;
			binaryRectangleFile << binVal << " ";
		}
		binaryRectangleFile << rand() % 2;
		binaryRectangleFile << endl;
	}
	for (int j = 0; j < width - 1; j++) {
		binVal = rand() % 2;
		binaryRectangleFile << binVal << " ";
	}
	binaryRectangleFile << rand() % 2;

	//close file and exit function
	binaryRectangleFile.close();
	return fileName;
}

bool findRectangles(string fileName) {
	//This function searches the binary matrix for rectangles with corners that are 0s
	//Created by Puugu on 19 April 2017

	//check to see if matrix has been created
	if (verifyFileExists(fileName) == false) {
		//either file name is inaccurate or matrix has not been created
		//will be unable to search matrix for rectangles
		return false;
	}

	//declare and intialize variables
	ifstream binRectFile(fileName);
	int rectWidth = 0;
	int rectHeight = 0;
	ofstream cornersFile("corners.txt");
	int upperLeft[2];

	//get width and height
	binRectFile >> rectWidth;
	binRectFile >> rectHeight;

	//create array for values
	int *binMatrix = new int[rectWidth*rectHeight];

	//get values
	for (int i = 0; i < (rectWidth*rectHeight); i++) {
		binRectFile >> binMatrix[i];
	}

	//close input file
	binRectFile.close();

	//search for top left corner of rectangle
	for (int i = 1; i <= (rectWidth*rectHeight); i++) {
	//for (int i = 1; i <= (rectWidth); i++) {
		if (binMatrix[i - 1] == 0) {
			//find column
			upperLeft[1] = (i - 1) % 10;
			//find row
			upperLeft[0] = (i - upperLeft[1] - 1)/10;
			//cout << "Row: " << upperLeft[0] << " Column: " << upperRight[0] << endl;
			//call function to find lower left corner
			findLowerLeft(binMatrix, upperLeft, rectWidth, rectHeight, cornersFile);
		}
	}

	//close output file
	cornersFile.close();

	return true;
}

bool verifyFileExists(string fileName) {
	//This function verifies the binRect.txt file exists
	//Created by Puugu on 19 April 2017

	//check to see if file exists
	ifstream binaryRectangleFile(fileName);
	if (!binaryRectangleFile) {
		//file doesn't exits
		binaryRectangleFile.close();
		return false;
	}
	else {
		//file exists
		binaryRectangleFile.close();
		return true;
	}
}

void findLowerLeft(int *binMatrix, int upperLeft[2], int rectWidth, int rectHeight, ofstream& cornersFile) {
	//This function uses the upper left coordinate to check for a lower left coordinate
	//Created by Puugu on 19 April 2017

	//declare and initialize variables
	int lowerLeft[2];

	//search for lower left coordinate
	for (int i = upperLeft[0]+1; i < rectHeight; i++) {
		if (binMatrix[i*rectWidth + upperLeft[1]] == 0) {
			//find column
			lowerLeft[1] = upperLeft[1];
			//find row
			lowerLeft[0] = i;
			//call function to find upper right corner
			findUpperRight(binMatrix, upperLeft, lowerLeft, rectWidth, rectHeight, cornersFile);
		}
	}
	return;
}

void findUpperRight(int *binMatrix, int upperLeft[2], int lowerLeft[2], int rectWidth, int rectHeight, ofstream& cornersFile) {
	//This function uses the upper left coordinate to find the upper right coordinate
	//Created by Puugu on 19 April 2017

	//declare and initialize variables
	int upperRight[2];
	bool foundCorner = false;

	//search for upper right coordinate
	for (int i = upperLeft[1]; i < (rectWidth - upperLeft[1]); i++) {
		if (binMatrix[upperLeft[0] + i + 1] == 0) {
			//find row
			upperRight[0] = upperLeft[0];
			//find column
			upperRight[1] = i+1;
			//call function to find the lower right coordinate
			foundCorner = findLowerRight(binMatrix, lowerLeft, upperRight, rectWidth, rectHeight);

			if (foundCorner == true) {
				//four corners have been found, add to output file
				addCorners(upperLeft, lowerLeft, upperRight, cornersFile);
			}
		}
	}

	return;
}

bool findLowerRight(int *binMatrix, int lowerLeft[2], int upperRight[2], int rectWidth, int rectHeight) {
	//This function uses the lower left and upper right coordinates to find the lower right coordinate
	//Created by Puugu on 19 April 2017

	//check lower right corner
	if ((binMatrix[lowerLeft[0] * rectWidth+upperRight[1]]) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void addCorners(int upperLeft[2], int lowerLeft[2], int upperRight[2], ofstream& cornersFile) {
	//This function adds the corners of the rectangle to the output file
	//Created by Puugu on 19 April 2017

	//add rectangle to output file
	cornersFile << "(" << upperLeft[0] << "," << upperLeft[1] << "), ";
	cornersFile << "(" << lowerLeft[0] << "," << lowerLeft[1] << "), ";
	cornersFile << "(" << upperRight[0] << "," << upperRight[1] << "), ";
	cornersFile << "(" << lowerLeft[0] << "," << upperRight[1] << ")\n";

	//exit function
	return;
}