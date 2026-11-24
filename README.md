# Company Employee Directory
CSC 307 - Data Whizzes

A command-line C++ employee directory using an AVL tree.

## Build and run

Open a terminal in the project folder and compile with a C++11 or newer compiler:

```bash
g++ -std=c++11 main.cpp -o employee_directory
```

On Windows:

```bash
employee_directory.exe
```

On macOS/Linux:

```bash
./employee_directory
```

## Menu

1. Add Employee
2. Find Employee
3. Update Employee
4. Delete Employee
5. List All Employees (sorted by ID)
6. Save to CSV
7. Load from CSV
8. Exit (the program prompts to save if changes are unsaved)

Employee IDs are positive integers and thus cannot be changed through Update. The program rejects duplicate IDs, nonnumeric menu choices and empty employee fields.

## CSV file

The program saves to and loads from `employees.csv` in the folder where the program is run. Each row contains:

`employeeID,name,department,title,email`

Use menu option 7 to load existing data. The loading does not happen automatically on startup. Loading adds records to the current directory and skips duplicate IDs and badly formatted rows. Option 6 saves the entire current directory and replaces the contents of `employees.csv`. Names and other fields containing commas or quotes are handled through CSV quoting.

The app uses standard C++ only and requires no extra libraries.
