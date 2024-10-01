/*
   COPYRIGHT (C) 2024 Kollin Brown. All rights reserved.
   CSI project
   Author.  Kollin Brown, ksb91.
   Version. 1.01 04.24.2024.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits> //for ignoring and clearing input


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
Precondition: Function is passed a constant character array for hospital grid
Postcondition: Returns nothing - prints out hospital grid to standard output
*/
void printGrid(const char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE]);

/*
Precondition: Function is passed an existing character array - in this case, it is the hospital grid
Postcondition: Returns nothing - has read data from the input file, converted to chars, and stored in hospital array
*/
void readGrid(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE]);


/*
Precondition: Function is passed the hospital floors array to be adjusted
Postcondition: Returns nothing - checks all of elements of the array for "checkout" and replaces them with "vacant"
*/
void checkOuts(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE]);

/*
Precondition: Function is passed the hospital floors array after processing checkouts and the initial amount of vacant rooms (0)
Postcondition: Returns a dynamically allocated array of pointers, with each index of the array storying the memory address of a vacant room.
               Also, "transfers" have been processed by effectively switching memory locations with a different vacant room
*/
char** transfers(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE], int &);

/*
Precondition: Function is passed the new patients, amount of vacant rooms, and pointer array of vacant rooms
Postcondition: Returns nothing - uses dynamic pointer array to fill all the vacant rooms based on how many patients are provided from standard input
*/
void newPatient(int, int &, char **);

/*
Precondition: Function is passed the amount of vacant rooms
Postcondition: Returns the user input (amount of new patients), which has been validated
*/
int newPatientInput(int);


int main()
{   //initial variable declarations/initializations to be used throughout program
    char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE];
    char **VacArray;
    int VacTotal = 0;
    int admitted = 0;

    //function calls for reading input file and printing out grid
    readGrid(hospitalFloors);
    printGrid(hospitalFloors);
    cout << "Grid Loaded" << endl << endl;

    //calling checkout and transfer functions to updated hospital floor array
    checkOuts(hospitalFloors);
    VacArray = transfers(hospitalFloors, VacTotal);
    printGrid(hospitalFloors);
    cout << "Checkouts and Transfers Completed" << endl << endl;

    //takes user input to determine how many new patients, and where they should go
    while (VacTotal != 0)
    {
        admitted = newPatientInput(VacTotal);

        if (admitted == -1)
        {
            break;
        }
        else
        {
            newPatient(admitted, VacTotal, VacArray);
            printGrid(hospitalFloors);
            cout << "New patient updates completed" << endl << endl;
        }
    }


    cout << "*** No more rooms are available today ***" << endl;

    //memory de-allocation
    delete [] VacArray;
    VacArray = nullptr;
    return 4;
}

void readGrid(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE])
{
    int input;
    ifstream inputFile;
    inputFile.open("Beds1.txt");

     if (!inputFile) //verify input file can be read
    {
        std::cerr << "Input file failed to load!\n";
        return;
    }

    //converts integers from input file and stores them as characters in hospital array
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
    inputFile.close();
}


void printGrid(const char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE])
{
    cout << "---------------" << endl;

    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {
                cout << hospitalFloors[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---------------" << endl;
}

void checkOuts(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE])
{
    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {
            if (hospitalFloors[i][j] == CHECKOUT) //for converting all checkouts to vacants
            {
                hospitalFloors[i][j] = VACANT;
            }
        }
    }
}

char** transfers(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE], int& VacantRooms)
{
    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {

            if (hospitalFloors[i][j] == VACANT) //counts total amount of vacant rooms
            {
                VacantRooms++;
            }
        }
    }

    char** DblPtrArray = new char*[VacantRooms]; //declares pointer array of pointers to hold memory addresses of hospital rooms
    int vacIndex = 0;

    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {

            //for each instance of vacant, stores its memory address in the dynamic array at a specific index
            if (hospitalFloors[i][j] == VACANT)
            {
                DblPtrArray[vacIndex] = &hospitalFloors[i][j];
                vacIndex++;
            }
        }
    }

    int indexPtr = VacantRooms - 1;

    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {
            /*  Does the actual transferring - finds each instance of transfer
                Accesses last slot of dynamic array to put the patient in, and sets to occupied.
                Sets the current room as vacant
                Stores the newly vacant room in the dynamic array
            */
            if (hospitalFloors[i][j] == TRANSFER)
            {
                **(DblPtrArray + indexPtr) = OCCUPIED;
                hospitalFloors[i][j] = VACANT;
                *(DblPtrArray + indexPtr) = &hospitalFloors[i][j];
                indexPtr--;
            }
        }
    }
    return DblPtrArray;
}

int newPatientInput(int VacantRooms)
{
    int userInput;
    bool validate = true;

    while (validate) // repeats until user enters good data and returns the amount of new patients
    {
        cout << "Please enter the number of new patients, from one up to " << VacantRooms << ". (Quit with -1): ";
        cin >> userInput;

        if (userInput <= VacantRooms && userInput >= 1)
        {
            validate = false;
        }
        else if (userInput == -1)
        {
            cout << "Goodbye" << endl;
            return -1;
        }
        else
        {
            cout << "Entry not in range. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
    return userInput;
}

void newPatient(int admitted, int& VacantRooms, char** DblPtrArray)
{
    for (int indexPtr = VacantRooms - 1; indexPtr >= 0; indexPtr--)
    {
        if(admitted == 0) //loops based on how many new patients there are. Starts at the very back of the dynamic array with storing new patients and counts down
        {
            break;
        }
        **(DblPtrArray + indexPtr) = OCCUPIED;
        VacantRooms--;
        admitted--;
    }

}
