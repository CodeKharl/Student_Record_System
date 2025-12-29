# Student Record System (C)

A simple C program that records student information.  
The program supports adding, finding, and dropping students, with data stored persistently on disk.

---

## Features

- Add a student record
- Find a student by ID
- Drop (delete) a student record
- Persistent storage using `.data` files

---

## Project Structure

The project uses a structured build layout created during compilation:

.
├── bin/ # Final executable
├── build/ # Object files (.o)
├── data/ # Student data files (.data)
├── src/ # Source code
├── Makefile
└── README.md

- **bin/** contains the executable after a successful build
- **build/** contains intermediate object files
- **data/** contains files used to store student records

All directories are created automatically during the build process.

---

## Build Requirements

- GCC (or compatible C compiler)
- Make
- Bear (or another tool capable of generating `compile_commands.json`)

---

## Build Instructions

### Standard build

make

After building, the executable can be found in:

bin/

Build with compile_commands.json

To enable code checking, static analysis, or IDE support (e.g., clangd), use Bear:

bear -- make

This generates a compile_commands.json file in the project root.
Running the Program

./bin/SRS

The program will display a menu allowing you to:

    Add a student

    Find a student

    Drop a student

    Exit

Data Storage

    Student records are stored in the data/ directory

    Data is kept in .data files so records persist between runs

Cleaning the Project

make clean

This removes:

    Executable files

    Object files

    Stored .data files

Notes

    This project is intended for learning and demonstration purposes

    The data format and storage method can be easily extended or replaced

    Bear or similar tools are recommended for code analysis and editor integration
