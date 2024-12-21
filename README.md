# Matrix
Mathematical operations in matrices.

# Matrix Operations Projects

This repository contains multiple projects that perform various matrix operations, including addition, subtraction, multiplication, logical operations, and more. Each project has a different focus, from basic matrix operations using complex numbers to inter-process communication via shared memory and semaphores, as well as multithreading.

## 1. Complex Matrix Operations

This project provides functions to perform various operations on matrices of complex numbers. The operations include addition, subtraction, multiplication, logical AND, logical OR, NOT, and transpose of matrices. The code is written in C and utilizes the `<complex.h>` library for handling complex numbers.

### Features

- **Matrix Parsing**: Reads matrices from input in the format `(rows,cols:val1,val2,...)`. Supports both real and complex numbers.
- **Matrix Memory Management**: Functions to allocate and free memory for matrices.
- **Matrix Operations**:
  - **Addition**: Adds two matrices.
  - **Subtraction**: Subtracts one matrix from another.
  - **Multiplication**: Multiplies two matrices.
  - **Logical AND**: Performs a logical AND element-wise on two matrices.
  - **Logical OR**: Performs a logical OR element-wise on two matrices.
  - **Logical NOT**: Performs a logical NOT element-wise on a matrix.
  - **Transpose**: Transposes a matrix.
- **Matrix Printing**: Prints matrices in a readable format.

### Usage

- **Input Format**: Matrices should be provided in the format `(rows,cols:val1,val2,...)`. Operations are specified by keywords such as `ADD`, `SUB`, `MUL`, `AND`, `OR`, `NOT`, `TRANSPOSE`, followed by the matrix data. Input ends with `END`.
- **Operations**:
  - `ADD`: Adds two matrices of the same dimensions.
  - `SUB`: Subtracts the second matrix from the first.
  - `MUL`: Multiplies two matrices.
  - `AND`: Logical AND (binary matrices only).
  - `OR`: Logical OR (binary matrices only).
  - `NOT`: Logical NOT (binary matrix only).
  - `TRANSPOSE`: Transposes a matrix.

- **Error Handling**: The program handles dimension mismatches, invalid logical values, and unknown operations by displaying appropriate error messages.

---

## 2. Matrix Operations with Shared Memory and Semaphores

This project implements matrix operations using shared memory and semaphores for inter-process communication. It continuously reads input from shared memory, processes matrix operations, and writes the result back.

### Files

- **main.c**: The main logic for reading from and writing to shared memory, processing matrix operations.
- **matrix_operations.c**: Contains functions for matrix parsing, operations (addition, subtraction, etc.), and printing.
- **semaphore.c**: Contains functions for semaphore operations.

### Prerequisites

- A Linux environment (for shared memory and semaphores).
- A C compiler (e.g., `gcc`).
- POSIX libraries (`sys/ipc.h`, `sys/shm.h`, `sys/sem.h`).

### Setup and Compilation

1. Clone the repository to your machine.
2. Navigate to the project directory.

### Supported Operations

- `ADD`, `SUB`, `MUL`, `AND`, `OR`, `NOT`, `TRANSPOSE` (same as above).

### Error Handling

- The program handles input errors such as mismatched matrix dimensions and invalid logical values. It prints `ERROR` or `ERR` accordingly.

### Memory Management

- The program dynamically allocates memory for matrices. Ensure that allocated memory is freed to avoid leaks.

---

## 3. Matrix Operations Using Multithreading

This program performs matrix operations using complex numbers, utilizing multithreading for parallel processing. The supported operations include addition, subtraction, multiplication, logical AND, and logical OR.

### Dependencies

- `stdio.h` for input/output
- `stdlib.h` for memory management
- `string.h` for string manipulation
- `complex.h` for complex number operations
- `pthread.h` for multithreading

### Program Structure

- **MatrixData**: A structure holding matrix dimensions, matrices, and the operation to perform.
- **Functions**:
  - `parseMatrix`: Parses matrix input.
  - `freeMatrix`: Frees allocated matrix memory.
  - `addMatrices`, `subtractMatrices`, `multiplyMatrices`: Matrix operations.
  - `andMatrices`, `orMatrices`: Logical operations on binary matrices.
  - `performOperation`: A thread function to perform an operation on matrices.

### Main Flow

1. The program continuously reads matrix inputs and operations until `END` is encountered.
2. Threads are created for each operation, and results are printed once all threads have completed.

### Error Handling

- Handles dimension mismatches and invalid logical values (non-binary matrices) by printing error messages.

---

## Notes

- **Matrix Operations**: All projects support operations like matrix addition, subtraction, multiplication, and logical operations (AND, OR, NOT).
- **Memory Management**: Each project includes proper memory allocation and deallocation practices to prevent memory leaks.
- **Multithreading and Shared Memory**: The respective projects implement multithreading (for parallel operations) and shared memory (for inter-process communication).

---

## Contributions

Feel free to fork the repository and contribute! Pull requests are welcome for new features, improvements, or bug fixes.
