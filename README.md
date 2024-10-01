# CSI Project

## Author
Kollin Brown (ksb91)

## Version
1.01 - April 24, 2024

## Project Overview
This project simulates a hospital room management system using a 2D array to represent hospital floors and rooms. The grid tracks room statuses, such as checkouts, transfers, nurse stations, and vacancies, and updates based on user input for new patient admissions.

### Key Symbols:
- **T**: Transfers
- **C**: Checkouts
- **W**: Nurse Work Stations
- **O**: Occupied Rooms
- **V**: Vacant Rooms
- **X**: Utility Rooms

### Files:
- **Beds1.txt**: Input file containing initial hospital room data.

## Program Features

### Functions:
1. **`printGrid()`**
   - **Precondition**: A hospital grid is provided.
   - **Postcondition**: The grid is printed to the console.

2. **`readGrid()`**
   - **Precondition**: A hospital grid exists.
   - **Postcondition**: Reads from the input file, converts data into characters, and stores them in the grid.

3. **`checkOuts()`**
   - **Precondition**: A hospital grid with room statuses is passed.
   - **Postcondition**: All "checkout" rooms are converted to "vacant."

4. **`transfers()`**
   - **Precondition**: A hospital grid and vacancy count are passed.
   - **Postcondition**: Dynamically allocates a pointer array to store vacant room addresses. Processes transfers by swapping room statuses.

5. **`newPatient()`**
   - **Precondition**: Number of patients, vacancy count, and pointer array of vacant rooms are passed.
   - **Postcondition**: Assigns new patients to available rooms.

6. **`newPatientInput()`**
   - **Precondition**: The number of vacant rooms is passed.
   - **Postcondition**: Returns validated user input for the number of new patients.
