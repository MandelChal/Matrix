# Matrix
Mathematical operations in matrices.

1. Complex Matrix Operations
This project provides functions to perform various operations on matrices of complex numbers. The implemented operations include addition, subtraction, multiplication, logical AND, logical OR, NOT, and transpose of matrices. The code is written in C and makes use of complex numbers provided by the <complex.h> library.

Features
Matrix Parsing
Reads a matrix from a string input in the format "(rows,cols:val1,val2,...)"
Supports both real and complex numbers.
Matrix Memory Management
Functions to allocate and free memory for matrices.
Matrix Operations
Addition: Adds two matrices.
Subtraction: Subtracts one matrix from another.
Multiplication: Multiplies two matrices.
Logical AND: Performs a logical AND operation element-wise on two matrices.
Logical OR: Performs a logical OR operation element-wise on two matrices.
Logical NOT: Performs a logical NOT operation element-wise on a matrix.
Transpose: Transposes a matrix.
Matrix Printing
Prints matrices in a readable format.
Usage
Input
The program reads matrices and operations from standard input.
Matrices should be provided in the format "(rows,cols:val1,val2,...)".
Operations can be one of ADD, SUB, MUL, AND, OR, NOT, or TRANSPOSE.
The input sequence should end with the keyword END.
Operations
ADD: Adds two matrices of the same dimensions.
SUB: Subtracts the second matrix from the first matrix of the same dimensions.
MUL: Multiplies two matrices.
AND: Performs a logical AND on two matrices of the same dimensions with binary values.
OR: Performs a logical OR on two matrices of the same dimensions with binary values.
NOT: Performs a logical NOT on a single matrix with binary values.
TRANSPOSE: Transposes a single matrix.
Output
The result of the operation is printed to the standard output.
Error Handling
If the input matrices are not of the same dimensions for applicable operations, an error message is displayed.
If an operation involves non-binary values for logical operations, an error message is displayed.
If an unknown operation is provided, an error message is displayed.
Memory Management
Allocated memory for matrices is freed after each operation to avoid memory leaks.
2. Matrix Operations with Shared Memory and Semaphores
Overview
This project implements matrix operations using shared memory and semaphores for inter-process communication. It supports various matrix operations such as addition, subtraction, multiplication, transpose, logical AND, and logical OR, with complex numbers. The application continuously reads input from shared memory, processes the input to perform the specified matrix operation, and then writes the result back to shared memory.

Files
main.c: Contains the main logic for reading from shared memory, performing matrix operations, and writing results back to shared memory.
matrix_operations.c: Contains the functions for matrix parsing, matrix operations (addition, subtraction, multiplication, transpose, logical AND, logical OR), and matrix printing.
semaphore.c: Contains functions for semaphore operations.
Prerequisites
A Linux environment for the use of shared memory and semaphores.
A C compiler (e.g., gcc).
The POSIX libraries for shared memory and semaphores (sys/ipc.h, sys/shm.h, sys/sem.h).
Setup and Compilation
Clone the repository to your local machine.
Navigate to the project directory.
Supported Operations
ADD: Adds two matrices of the same dimensions.
SUB: Subtracts the second matrix from the first matrix.
MUL: Multiplies two matrices (the number of columns in the first matrix must equal the number of rows in the second matrix).
AND: Performs a logical AND operation on two binary matrices.
OR: Performs a logical OR operation on two binary matrices.
NOT: Performs a logical NOT operation on a binary matrix.
TRANSPOSE: Transposes the matrix.
Error Handling
The program will print ERROR if the input matrices do not conform to the expected dimensions for the specified operation.
For logical operations, if any element in the matrices is not binary (0 or 1), the program will print ERR.
Memory Management
The program uses dynamic memory allocation for matrix storage.
Ensure that allocated memory is properly freed to avoid memory leaks.
Notes
The program uses shared memory and semaphores to synchronize access between processes.
The shared memory size and semaphore keys are defined as constants and can be modified as needed.
The program assumes that the shared memory and semaphore are properly set up and accessible.
3. Matrix Operations Using Multithreading
Overview
This program performs matrix operations using complex numbers. The supported operations include addition, subtraction, multiplication, logical AND, and logical OR. The program uses multithreading to perform these operations in parallel for different matrices.

Dependencies
The program requires the following standard libraries:

stdio.h for input and output functions
stdlib.h for memory allocation functions
string.h for string manipulation functions
complex.h for complex number operations
pthread.h for multithreading functions
Program Structure
Data Structures
MatrixData: A structure that holds the matrix dimensions, matrices (A and B), result matrix, and the operation to be performed.
Functions
parseMatrix: Parses a matrix input string and allocates memory for the matrix.
freeMatrix: Frees the memory allocated for a matrix.
printMatrix: Prints a matrix to the standard output.
addMatrices: Adds two matrices.
subtractMatrices: Subtracts the second matrix from the first matrix.
multiplyMatrices: Multiplies two matrices.
andMatrices: Performs a logical AND operation on two matrices. The matrices must contain only 0s and 1s.
orMatrices: Performs a logical OR operation on two matrices. The matrices must contain only 0s and 1s.
performOperation: A thread function that performs the specified operation on matrices.
Main Function
The main function handles the input and output operations and orchestrates the overall flow:

Continuously reads matrix inputs and operations until the "END" command is received.
Parses matrix input strings and stores them in arrays.
Validates the dimensions of the matrices.
Creates threads to perform the specified operations on the matrices.
Joins the threads and collects the results.
Prints the final result matrix or an error message if the operation fails.
Frees all allocated memory.
Error Handling
If the dimensions of the matrices are not the same for operations that require equal dimensions, the program prints an error message and continues to the next input.
For logical AND and OR operations, if the matrices contain values other than 0 and 1, the program sets a flag and prints ERR.
