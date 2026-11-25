# Company Employee Directory

**Author:** Data Whizzes team  
**Course:** CSC 307 – Data Structures and Algorithm Analysis  
**Semester:** Fall 2026

A command-line C++ application that uses an AVL tree to manage employee records.

## 1. Prerequisites & Environment

- **Operating system:** Windows, macOS, or Linux
- **Compiler:** A C++11-compatible compiler, such as GCC/G++ (not included with Windows by default)
- **Build system:** None required since it compiles from a terminal
- **External libraries:** None as the project only uses the C++ standard library

## 2. Installation & Setup

### Windows (installing G++)

1. Download and install **MSYS2** from https://www.msys2.org/.
2. Open **MSYS2 UCRT64** from the Start menu (not to be confused with the plain MSYS2 shell).
3. Install the compiler by entering:

   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```

   If it prompts you to proceed, type `Y`.
4. In the MSYS2 UCRT64 terminal, verify that the compiler is available:

   ```bash
   g++ --version
   ```

5. To use `g++` from Windows PowerShell, Command Prompt, or VS Code's Windows terminal, add `C:\msys64\ucrt64\bin` to your Windows **Path** environment variable, and then reopen the terminal. This assumes that you installed MSYS2 in the default location.

If you already have a working C++ compiler, you do not need to install another one.

### macOS / Linux

Install a C++ compiler using your operating system's normal development tools or package manager and then verify it with `g++ --version`. On macOS, `clang++` can be used instead of `g++` in the compilation command.

## 3. Build Instructions

Open a terminal in the folder containing `main.cpp`.

**Windows (PowerShell, after G++ is installed and on Path):**

```powershell
g++ -std=c++11 main.cpp -o employee_directory.exe
.\employee_directory.exe
```

**Windows (MSYS2 UCRT64 terminal):**

```bash
g++ -std=c++11 main.cpp -o employee_directory.exe
./employee_directory.exe
```

**Linux:**

```bash
g++ -std=c++11 main.cpp -o employee_directory
./employee_directory
```

**macOS (with Apple Clang):**

```bash
clang++ -std=c++11 main.cpp -o employee_directory
./employee_directory
```

## 4. Execution Guide

The numbered menu provides the following commands:

1. Add Employee
2. Find Employee
3. Update Employee
4. Delete Employee
5. List All Employees (sorted by ID)
6. Save to CSV
7. Load from CSV
8. Exit (prompts to save if changes are unsaved)

Employee IDs are positive integers and cannot be changed through Update. The program rejects duplicate IDs, nonnumeric menu choices, and empty required fields.

### CSV File

The program saves to and loads from `employees.csv` in the **working directory where the program is run**. Every single record contains:

```text
employeeID,name,department,title,email
```

Choose option 6 to save all current records (by overwriting the CSV file), or option 7 to load records. Loading does not happen automatically at startup. Loading adds valid records to the current directory and skips duplicate IDs and malformed rows. Fields containing commas or quotation marks are handled using CSV quoting.

## 5. Troubleshooting / Known Issues

- **`g++` is not recognized / command not found:** Install GCC/G++ as described above. On Windows, use the MSYS2 UCRT64 terminal or check the Windows Path entry and reopen the terminal.
- **`employees.csv` cannot be opened:** Check that the file exists in the directory from which the program was launched, and that the directory/file has appropriate permissions.
- **The CSV is empty when you start the app:** The loading is manual. Choose menu option 7 to load saved records.
- **Loading reports skipped rows:** Malformed records and duplicate employee IDs are ignored.
- **Known minor behavior:** Loading a CSV may trigger a save prompt upon exit even if no new employee records were added.
