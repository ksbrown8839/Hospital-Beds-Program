/*
   COPYRIGHT (C) 2024 Kollin Brown. All rights reserved.
   CSI project
   Author.  Kollin Brown, ksb91.
   Version. 1.01 04.24.2024.
*/

#include <iostream>
#include <iomanip>
#include <fstream>


using std::cout;
using std::endl;
using std::cin;
using std::ifstream;

const int FLOOR_ARRAY_SIZE = 5;
const int ROOM_ARRAY_SIZE = 8;

//	Transfers are represented by a ‘T’.
//	The Check outs are represented by a ‘C’.
//	Nurse work stations are represented by a ‘W’.
//	Occupied rooms are represented by an asterisk ‘O’.
//	A vacant room is represented by a blank ‘V’.
//	The utility rooms are represented by an ‘X’.

const char VACANT = 'V';
const char CHECKOUT = 'C';
const char OCCUPIED = 'O';
const char NURSE_STATION = 'W';
const char TRANSFER = 'T';
const char UTILITY = 'X';
const char INVALID = '@';

// These functions will work in their current form. You must use them. You may add functions but
// don't remove them. Complete the pre and post condition comments.

//Function prototypes
/*
Pre and Post condition comments go here ... Prints the grid to the screen
*/
void printGrid(const char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE]);

/*
Pre and Post condition comments go here ... Reads in the initial grid from Beds.txt file
*/
void readGrid(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE]);


/*
Pre and Post condition comments go here ... Perform the checkouts
*/
void checkOuts(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE]);

/*
Pre and Post condition comments go here ...Perform the transfers and build the dynamic array of pointers.
this function also will compute the available number of rooms
*/
char** transfers(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE], int &);

/*
Pre and Post condition comments go here ...Perform the new patient adds passing the new patient input from
the nurse station and passing the dynamic array of vacancies count for updating
*/
void newPatient(int, int &, char **);

/*
 Pre and Post condition comments go here ... function for the input from the nurse's station. It returns
 the nurse station choice, passes the current vacancies.
*/
int newPatientInput(int);


int main()
{
    char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE];

    readGrid(hospitalFloors);
    printGrid(hospitalFloors);



    return 0;
}

void readGrid(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE])
{
    int input;
    ifstream inputFile;
    inputFile.open("Beds1.txt");

    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {
            inputFile >> input;

            switch (input)
            {
                case 0:
                    hospitalFloors[i][j] = VACANT;
                    break;
                case 1:
                    hospitalFloors[i][j] = CHECKOUT;
                    break;
                case 2:
                    hospitalFloors[i][j] = OCCUPIED;
                    break;
                case 3:
                    hospitalFloors[i][j] = NURSE_STATION;
                    break;
                case 4:
                    hospitalFloors[i][j] = TRANSFER;
                    break;
                case 5:
                    hospitalFloors[i][j] = UTILITY;
                    break;
                default:
                    hospitalFloors[i][j] = INVALID;
            }
        }
    }
}


void printGrid(const char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE])
{
    cout << "---------------" << endl;

    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j <ROOM_ARRAY_SIZE; j++)
        {
                cout << hospitalFloors[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---------------" << endl << "Grid loaded" << endl;
}
