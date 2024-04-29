/*
   COPYRIGHT (C) 2024 Kollin Brown. All rights reserved.
   CSI project
   Author.  Kollin Brown, ksb91.
   Version. 1.01 04.24.2024.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>


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
    char **VacArray;
    int VacTotal = 0;
    bool loopFlag = true;
    int admitted = 0;

    readGrid(hospitalFloors);
    printGrid(hospitalFloors);
    cout << "Grid Loaded" << endl;
    checkOuts(hospitalFloors);
    VacArray = transfers(hospitalFloors, VacTotal);
    printGrid(hospitalFloors);
    cout << "Checkouts and Transfers Completed" << endl;

    while (VacTotal != 0)
    {
        if (VacTotal == 0)
        {
            break;
        }
        admitted = newPatientInput(VacTotal);
        newPatient(admitted, VacTotal, VacArray);
        printGrid(hospitalFloors);
        cout << "New patient updates completed" << endl;
    }


    cout << "*** No more rooms are available today ***" << endl;

    VacArray = nullptr;
    delete [] VacArray;
    return 4;
}

void readGrid(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE])
{
    int input;
    ifstream inputFile;
    inputFile.open("Beds1.txt");

     if (!inputFile)
    {
        std::cerr << "Input file failed to load!\n";
        return;
    }

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
            if (hospitalFloors[i][j] == CHECKOUT)
            {
                hospitalFloors[i][j] = VACANT;
            }
        }
    }
}

char** transfers(char hospitalFloors[FLOOR_ARRAY_SIZE][ROOM_ARRAY_SIZE], int& VacantRooms)
{
    char** DblPtrArray = new char*[VacantRooms];

    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {

            if (hospitalFloors[i][j] == VACANT)
            {
                VacantRooms++;
                DblPtrArray[VacantRooms] = &hospitalFloors[i][j];
            }
        }
    }

    int indexPtr = VacantRooms;

    for (int i = 0; i < FLOOR_ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ROOM_ARRAY_SIZE; j++)
        {

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

    while (validate)
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
            exit(4);
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
    for (int arrCount = VacantRooms; arrCount >= 0; --arrCount)
    {
        if(admitted == 0)
        {
            break;
        }
        **(DblPtrArray + arrCount) = OCCUPIED;
        VacantRooms--;
        admitted--;
    }

}
