# Matrix
Mathematical operations in matrices.
# Matrix Operations Project

This project provides a set of mathematical operations for matrices, including complex matrix operations. The implemented operations include addition, subtraction, multiplication, logical AND, logical OR, NOT, and transpose of matrices. The code is written in C and makes use of complex numbers provided by the `<complex.h>` library.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Files](#files)
- [Usage](#usage)
- [Operations](#operations)
- [Error Handling](#error-handling)
- [Memory Management](#memory-management)
- [License](#license)

## Overview

This project implements various matrix operations on matrices of complex numbers. The operations include addition, subtraction, multiplication, logical AND, logical OR, NOT, and transpose. The operations are performed on matrices that are read from input and the results are printed to standard output.

The system also includes memory management for dynamic matrix allocation and free operations to ensure proper memory usage. The program handles matrix input, performs specified operations, and handles errors related to invalid inputs or operations.

The project has several implementations depending on the specific method used for inter-process communication and synchronization:

1. **Matrix Operations with Complex Numbers**: Performs basic matrix operations in C.
2. **Matrix Operations using Shared Memory and Semaphores**: Implements matrix operations with inter-process communication.
3. **Multithreaded Matrix Operations**: Uses multithreading to perform matrix operations in parallel.

## Features

### Matrix Parsing
- Reads matrices from a string input in the format `(rows,cols:val1,val2,...)`.
- Supports both real and complex numbers.

### Matrix Memory Management
- Functions to allocate and free memory for matrices.

### Matrix Operations
- **Addition**: Adds two matrices.
- **Subtraction**: Subtracts one matrix from another.
- **Multiplication**: Multiplies two matrices.
- **Logical AND**: Performs a logical AND operation element-wise on two matrices.
- **Logical OR**: Performs a logical OR operation element-wise on two matrices.
- **Logical NOT**: Performs a logical NOT operation element-wise on a matrix.
- **Transpose**: Transposes a matrix.

### Matrix Printing
- Prints matrices in a readable format.

## Files

### 1. `main.c`
- Contains the main logic for reading from standard input, performing matrix operations, and printing the results.

### 2. `matrix_operations.c`
- Contains functions for matrix parsing, matrix operations (addition, subtraction, multiplication, transpose, logical AND, logical OR), and matrix printing.

### 3. `semaphore.c`
- Contains functions for semaphore operations used for inter-process synchronization (for shared memory implementation).

### 4. `matrix_operations_multithreaded.c` (if applicable)
- Implements multithreading for matrix operations to perform tasks in parallel.

### 5. `matrix_operations_shared_memory.c` (if applicable)
- Implements matrix operations using shared memory and semaphores for inter-process communication.

## Usage

The program reads matrices and operations from standard input. The matrices should be provided in the format `(rows,cols:val1,val2,...)`. Operations can be one of `ADD`, `SUB`, `MUL`, `AND`, `OR`, `NOT`, or `TRANSPOSE`. The input sequence should end with the keyword `END`.

### Compile the Code

```bash
gcc -o matrix_operations main.c matrix_operations.c semaphore.c -lpthread
Run the Program
bash
Copy code
./matrix_operations
Operations
ADD: Adds two matrices of the same dimensions.
SUB: Subtracts the second matrix from the first matrix of the same dimensions.
MUL: Multiplies two matrices (the number of columns in the first matrix must equal the number of rows in the second matrix).
AND: Performs a logical AND operation on two binary matrices.
OR: Performs a logical OR operation on two binary matrices.
NOT: Performs a logical NOT operation on a binary matrix.
TRANSPOSE: Transposes a matrix.
Example Input:
plaintext
Copy code
(2,2:1,2,3,4)
(2,2:5,6,7,8)
ADD
END
Example Output:
plaintext
Copy code
Result:
6 8
10 12
Error Handling
Invalid Dimensions: If the input matrices are not of the same dimensions for applicable operations, an error message is displayed.
Non-Binary Values for Logical Operations: For logical operations (AND, OR, NOT), if any element in the matrices is not binary (0 or 1), an error message is displayed.
Unknown Operations: If an unknown operation is provided, an error message is displayed.
Memory Management
The program uses dynamic memory allocation for matrix storage.
Allocated memory for matrices is freed after each operation to avoid memory leaks.
