# C Mini Preprocessor

## Project Overview

C Mini Preprocessor is a modular C programming project that performs basic preprocessing operations on C source files.

The program takes a C source file as command-line input, processes preprocessing directives and generates an output file with the `.i` extension.

## Features

- Removal of single-line comments (`//`).
- Removal of multi-line comments (`/* ... */`).
- Header file inclusion.
- Object-like macro definition and replacement.
- Recursive macro replacement.
- Identifier boundary validation.
- Modular implementation using multiple C source and header files.

## Technologies Used

- C Programming
- File Handling
- Pointers and Strings
- Structures
- Modular Programming
- Makefile

## Project Files

- `main.c` – Main program.
- `comment_removal.c` – Comment removal.
- `file_inclusion.c` – Header file inclusion.
- `macro_handler.c` – Macro handling and replacement.
- `mystring.c` – String-related operations.
- Header files – Function declarations and supporting definitions.
- `Makefile` – Compilation and build instructions.

## Compilation

Run the following command:

```bash
make
```

## Execution

```bash
./mypreprocessor input.c
```

The program generates the preprocessed output file with the `.i` extension.

## Limitations

This project implements basic preprocessing operations. It is not a complete implementation of the standard C preprocessor.

## Author

Vishnu P.U.

## Project Type

C Programming Mini Project
