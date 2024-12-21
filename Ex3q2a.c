#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX_CHAR 128
#define SHM_SIZE 2048
#define SEM_KEY 1234
#define SHM_KEY 5678
int flag_complex=0;
int flag_ra=0;
bool contains_i(const char* input_string) {
    while (*input_string) {
        if (*input_string == 'i') {
            return true;
        }
        input_string++;
    }
    return false;
}
bool isFirstDecimalPlaceZero(double number) {
    number *= 10;
    int firstDecimalPlace = (int)number % 10;

    return firstDecimalPlace == 0;
}
void parseMatrix(const char *input, int *rows, int *cols, _Complex double ** *matrix) {
    sscanf(input, "(%d,%d:", rows, cols);
    *matrix = malloc(*rows * sizeof(_Complex double *));
    for (int i = 0; i < *rows; ++i) {
        (*matrix)[i] = malloc(*cols * sizeof(_Complex double));
    }
    const char *start = strchr(input, ':') + 1;
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *cols; ++j) {
            double real, imag;
            if (sscanf(start, "%lf+%lfi", &real, &imag) == 2) {
                (*matrix)[i][j] = real + imag * I;
            } else if (sscanf(start, "%lf%lfi", &real, &imag) == 2) {
                (*matrix)[i][j] = real + imag * I;
            } else {
                sscanf(start, "%lf", &real);
                (*matrix)[i][j] = real;
            }
            start = strchr(start, ',') + 1;
        }
    }
}

void freeMatrix(int rows, _Complex double **matrix) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
// Function to print matrix
void printMatrix(int rows, int cols, _Complex double ** matrix) {
    printf("(%d,%d:",rows,cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {


            if (cimag(matrix[i][j]) == 0) {
                if (flag_complex==1)
                    printf("%d+%di", (int) creal(matrix[i][j]),(int) cimag(matrix[i][j])); // Print imaginary integer part only
//                if (creal(matrix[i][j]) == 0) {
//                    printf("0+0i"); // Print zero
//                     }
                else   if (creal(matrix[i][j]) == (int) creal(matrix[i][j])) {

                    if(flag_ra==1)
                        printf("%d.0", (int) creal(matrix[i][j])); // Print integer part only
                    else
                        printf("%d", (int) creal(matrix[i][j])); // Print integer part only
                } else {
                    double real_part = creal(matrix[i][j]);
                    // Multiplies by 10, converts to int to truncate, then back to double and divide by 10
                    double truncated = ((int)(real_part * 10)) / 10.0;
                    printf("%.1f", truncated); // Print
//                    printf("%.1f", creal(matrix[i][j])); // Print rational number with one decimal place
                }
            } else if (creal(matrix[i][j]) == 0) {
                if (cimag(matrix[i][j]) == (int) cimag(matrix[i][j])) {
                    if((int) cimag(matrix[i][j])>=0)
                        printf("%d+%di", (int) creal(matrix[i][j]),(int) cimag(matrix[i][j])); // Print imaginary integer part only
                    else
                        printf("%d%di", (int) creal(matrix[i][j]),(int) cimag(matrix[i][j])); // Print imaginary integer part only
                } else {
                    printf("%d+%.1fi",(int) creal(matrix[i][j]), cimag(matrix[i][j])); // Print rational imaginary number with one decimal place
                }
            } else {
                if (creal(matrix[i][j]) == (int) creal(matrix[i][j])) {
                    if (cimag(matrix[i][j]) == (int) cimag(matrix[i][j])) {
                        if((int) cimag(matrix[i][j])>=0)
                            printf("%d+%di", (int) creal(matrix[i][j]), (int) cimag(matrix[i][j])); // Print both integer parts
                        else
                            printf("%d%di",(int) creal(matrix[i][j]), (int) cimag(matrix[i][j])); // Print both integer parts
                    } else {
//                        if(cimag(matrix[i][j])>=0)
                        printf("%d+%.1fi",  (int) creal(matrix[i][j]), cimag(matrix[i][j])); // Print real integer part and rational imaginary part
//                        else
//                            printf("%d%.1fi", (int) creal(matrix[i][j]), cimag(matrix[i][j])); // Print real integer part and rational imaginary part
                    }
                } else {
                    if (cimag(matrix[i][j]) == (int) cimag(matrix[i][j])) {
                        if((int) cimag(matrix[i][j])>=0)
                            printf("%.1f+%di", creal(matrix[i][j]), (int) cimag(matrix[i][j])); // Print rational real part and integer imaginary part
                        else
                            printf("%.1f%di", creal(matrix[i][j]), (int) cimag(matrix[i][j])); // Print rational real part and integer imaginary part
                    } else {
                        if((int) cimag(matrix[i][j])>=0)
                            printf("%.1f+%.1fi",creal(matrix[i][j]), cimag(matrix[i][j])); // Print both rational parts
                        else
                            printf("%.1f%.1fi", creal(matrix[i][j]), cimag(matrix[i][j])); // Print both rational parts
                    }
                }
            }

            if (j < cols - 1) printf(",");
        }
        if (i < rows - 1) printf(",");
    }
    printf(")\n");
}


void transposeMatrix(int rows, int cols, _Complex double **matrix, _Complex double ** *result) {
    *result = malloc(cols * sizeof(_Complex double *));
    for (int i = 0; i < cols; ++i) {
        (*result)[i] = malloc(rows * sizeof(_Complex double));
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            (*result)[j][i] = matrix[i][j];
        }
    }
}

void addMatrices(int rows, int cols, _Complex double **A, _Complex double **B, _Complex double ** *result) {
    *result = malloc(rows * sizeof(_Complex double *));
    for (int i = 0; i < rows; ++i) {
        (*result)[i] = malloc(cols * sizeof(_Complex double));
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            (*result)[i][j] = A[i][j] + B[i][j];
            if (!isFirstDecimalPlaceZero(A[i][j])|| !isFirstDecimalPlaceZero(B[i][j])) flag_ra=1;
        }
    }
}

void multiplyMatrices(int rows, int cols, _Complex double ** A, _Complex double ** B, _Complex double ** * result) {
    * result = malloc(rows * sizeof(_Complex double * ));
    for (int i = 0; i < rows; ++i) {
        ( * result)[i] = malloc(cols * sizeof(_Complex double));
        for (int j = 0; j < cols; ++j) {
            ( * result)[i][j] = 0 + 0 * I; // Initialize with complex zero
            for (int k = 0; k < cols; ++k) {
                ( * result)[i][j] += A[i][k] * B[k][j];
                if (!isFirstDecimalPlaceZero(A[i][j])|| !isFirstDecimalPlaceZero(B[i][j])) flag_ra=1;
            }
        }
    }
}

// Function to subtract matrices
void subtractMatrices(int rows, int cols, _Complex double ** A, _Complex double ** B, _Complex double ** * result) {
    * result = malloc(rows * sizeof(_Complex double * ));
    for (int i = 0; i < rows; ++i) {
        ( * result)[i] = malloc(cols * sizeof(_Complex double));
        for (int j = 0; j < cols; ++j) {
            ( * result)[i][j] = A[i][j] - B[i][j];
            if (!isFirstDecimalPlaceZero(A[i][j])|| !isFirstDecimalPlaceZero(B[i][j])) flag_ra=1;
        }
    }
}
int andMatrices(int rows, int cols, _Complex double ** A, _Complex double ** B, _Complex double ** * result) {
    * result = malloc(rows * sizeof(_Complex double * ));
    for (int i = 0; i < rows; ++i) {
        ( * result)[i] = malloc(cols * sizeof(_Complex double));
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((creal(A[i][j]) != 0 && creal(A[i][j]) != 1) || (creal(B[i][j]) != 0 && creal(B[i][j]) != 1)) {
                // Free the allocated memory before returning
                for (int k = 0; k <= i; ++k) {
                    free(( * result)[k]);
                }
                free( * result);
                return -1;
            } else {
                ( * result)[i][j] = (creal(A[i][j]) != 0 && creal(B[i][j]) != 0) ? 1: 0;
            }
        }
    }
    return 0;
}

// Function to perform logical OR on matrices
int orMatrices(int rows, int cols, _Complex double ** A, _Complex double ** B, _Complex double ** * result) {
    * result = malloc(rows * sizeof(_Complex double * ));
    for (int i = 0; i < rows; ++i) {
        ( * result)[i] = malloc(cols * sizeof(_Complex double));
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((creal(A[i][j]) != 0 && creal(A[i][j]) != 1) || (creal(B[i][j]) != 0 && creal(B[i][j]) != 1)) {
                // Free the allocated memory before returning
                for (int k = 0; k <= i; ++k) {
                    free(( * result)[k]);
                }
                free( * result);
                return -1;
            } else {
                ( * result)[i][j] = (creal(A[i][j]) != 0 || creal(B[i][j]) != 0) ? 1: 0;
            }
        }
    }
    return 0;
}

void semOp(int sem_id, int op) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = op;
    sb.sem_flg = 0;
    if (semop(sem_id, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }
}
void clearSharedMemory(int shm_id) {
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    memset(shm_ptr, 0, SHM_SIZE);

    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
}
int main() {

    // Access shared memory segment
    int shm_id = shmget(SHM_KEY, SHM_SIZE, 0666);
    clearSharedMemory(shm_id);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Access semaphore
    int sem_id = semget(SEM_KEY, 1, 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(1);
    }

    while (1) {
        // Lock semaphore
        semOp(sem_id, -1);

        char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
        if (shm_ptr == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        if (strlen(shm_ptr) == 0) {
            // Unlock semaphore
            semOp(sem_id, 1);
            sleep(1);
            continue;
        }
        flag_complex=0;
        flag_ra=0;
        char input1[MAX_CHAR], input2[MAX_CHAR], operation[MAX_CHAR];
        sscanf(shm_ptr, "%[^;];%[^;];%[^;]", input1, input2, operation);
        if(contains_i(input1)) flag_complex=1;
        // Clear shared memory after reading

        int rows1, cols1, rows2, cols2;
        _Complex double **A, **B, **result;

        if (strcmp(input2, "NOT") == 0 || strcmp(input2, "NOT\n") == 0 || strcmp(input2, "TRANSPOSE") == 0 || strcmp(input2, "TRANSPOSE\n") == 0) {
            parseMatrix(input1, &rows1, &cols1, &A);

            if (strcmp(input2, "NOT") == 0 || strcmp(input2, "NOT\n") == 0) {
                for (int i = 0; i < rows1; ++i) {
                    for (int j = 0; j < cols1; ++j) {
                        A[i][j] = !A[i][j];
                    }
                }
                printMatrix(rows1, cols1, A);
            } else if (strcmp(input2, "TRANSPOSE") == 0 || strcmp(input2, "TRANSPOSE\n") == 0) {
                transposeMatrix(rows1, cols1, A, &result);
                printMatrix(cols1, rows1, result);
                freeMatrix(cols1, result);
            }

            freeMatrix(rows1, A);
        } else {
            parseMatrix(input1, &rows1, &cols1, &A);
            parseMatrix(input2, &rows2, &cols2, &B);

//            if (strcmp(operation, "ADD") == 0 || strcmp(operation, "ADD\n") == 0) {
//                if (rows1 != rows2 || cols1 != cols2) {
//                    printf("ERROR\n");
//                } else {
//                    addMatrices(rows1, cols1, A, B, &result);
//                    printMatrix(rows1, cols1, result);
//                    freeMatrix(rows1, result);
//                }
//            } else if (strcmp(operation, "MUL") == 0 || strcmp(operation, "MUL\n") == 0) {
//                if (cols1 != rows2) {
//                    printf("ERROR\n");
//                } else {
//                    multiplyMatrices(rows1, cols1, rows2, cols2, A, B, &result);
//                    printMatrix(rows1, cols2, result);
//                    freeMatrix(rows1, result);
//                }
//            }
            if (strcmp(operation, "ADD") == 0 || strcmp(operation, "ADD\n") == 0) {
                addMatrices(rows1, cols1, A, B, & result);
            } else if (strcmp(operation, "SUB") == 0 || strcmp(operation, "SUB\n") == 0) {
                subtractMatrices(rows1, cols1, A, B, & result);
            } else if (strcmp(operation, "MUL") == 0 || strcmp(operation, "MUL\n") == 0) {
                multiplyMatrices(rows1, cols1, A, B, & result);
            } else if (strcmp(operation, "AND") == 0 || strcmp(operation, "AND\n") == 0) {
                int res_and = andMatrices(rows1, cols1, A, B, & result);
                if (res_and == -1) {
                    printf("ERR\n");
                    continue;
                }
            } else if (strcmp(operation, "OR") == 0 || strcmp(operation, "OR\n") == 0) {
                int res_or = orMatrices(rows1, cols1, A, B, & result);
                if (res_or == -1) {
                    printf("ERR\n");
                    continue;
                }
            } else {
                printf("Unknown operation.\n");
                return 1;
            }

            printMatrix(rows1, cols1, result);
            freeMatrix(rows1, result);
            freeMatrix(rows1, A);
            freeMatrix(rows2, B);
        }

        // Clear shared memory
        memset(shm_ptr, 0, SHM_SIZE);
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Unlock semaphore1
        semOp(sem_id, 1);
    }

    return 0;
}

