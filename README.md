# Company Employee Directory 

**Author:** Michael Gibson Jr., Bishesh Poudel, Cassidy Hancock  

**Course:** CSC 307/H002  

**Semester:** Fall/2026 

 

--- 

 

## 1. Prerequisites & Environment 

Before running this project, ensure your system meets the following requirements: 

* **Operating System:** Windows 11, macOS, Linux

* **Compiler:** C++11 or newer compatible compiler with the C/C++ extension installed in Visual Studio Code

* **Build System:** None (Direct command-line compilation via g++) 

 

### Required Libraries 

The app uses standard C++ only and requires no extra libraries. 

 

--- 

 

## 2. Installation & Setup 

Provide step-by-step instructions on how to install dependencies. 

1. Extract zipped folder, "Data_Whizzes_Employee_Directory_App_final_deliverables.zip"

2. Launch VS Code and open extracted folder 


 
--- 

 

## 3. Build Instructions 

**Using Command Line:** 
Compile code in command line as follows:

```bash
g++ -std=c++11 main.cpp -o employee_directory
```

then run using: 

Windows:

```bash
./employee_directory.exe (or employee_directory.exe in Command Prompt)
```

macOS/Linux:

```bash
./employee_directory
```
 

**Using IDE:** 

* You can compile the source code using the integrated terminal in VS Code.

Windows/Linux 
Ctrl + ~ or Ctrl + \

macOS
Ctrl + ~

 

--- 

 

## 4. Execution Guide 

* **Executable Name:** `employee_directory` (or `employee_directory.exe` on Windows) 

* **Entry Point:** No command-line arguments are required. 

* **Assets:** No assets included.

* Interactive Menu: The program launches an interactive text menu with the following options:

    1. Add Employee

    2. Find Employee

    3. Update Employee

    4. Delete Employee

    5. List All Employees (sorted by ID)

    6. Save to CSV

    7. Load from CSV

    8. Exit (prompts to save if changes are unsaved)

  Type a number to execute corresponding action. 
  

 

--- 

 

## 5. Troubleshooting / Known Issues

* Employee IDs are positive integers and thus cannot be changed through Update. The program rejects duplicate IDs, nonnumeric menu choices and empty employee fields.

* Data Storage: The program saves to and loads from `employees.csv` in the folder where the program is run. Each row contains: 
`employeeID,name,department,title,email`

* Use menu option 7 to load existing data. The loading does not happen automatically on startup. Loading adds records to the current directory and skips duplicate IDs and badly formatted rows. Option 6 saves the entire current directory and replaces the contents of `employees.csv`. Names and other fields containing commas or quotes are handled through CSV quoting.