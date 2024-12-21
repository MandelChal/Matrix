
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <pthread.h>
#include <stdbool.h>
#define MAX_char 128
#define MAX_MATRICES 10
int flag_err=0;
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
// Structure to hold matrix data and operation
typedef struct {
    int rows;
    int cols;
    _Complex double **A;
    _Complex double **B;
    _Complex double **result;
    char operation[MAX_char];
} MatrixData;

// Function to parse matrix input
void parseMatrix(const char *input, int *rows, int *cols, _Complex double ***matrix) {
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

// Function to free matrix memory
void freeMatrix(int rows, _Complex double **matrix) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to print matrix
// Function to check if the first digit after the decimal point is 0
int isFirstDigitAfterDecimalZero(double num) {
    int integerPart = (int) num;
    double decimalPart = num - integerPart;

    // Get the first digit after the decimal point
    int firstDigitAfterDecimal = (int)(decimalPart * 10);

    // Check if the first digit after the decimal point is 0
    return firstDigitAfterDecimal == 0;
}
// Function to print matrix

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


// Function to add matrices
void addMatrices(int rows, int cols, _Complex double **A, _Complex double **B, _Complex double ***result) {
    *result = malloc(rows * sizeof(_Complex double *));
    for (int i = 0; i < rows; ++i) {
        (*result)[i] = malloc(cols * sizeof(_Complex double));
        for (int j = 0; j < cols; ++j) {
            (*result)[i][j] = A[i][j] + B[i][j];
            if (!isFirstDecimalPlaceZero(A[i][j])|| !isFirstDecimalPlaceZero(B[i][j])) flag_ra=1;
        }
    }
}

// Function to subtract matrices
void subtractMatrices(int rows, int cols, _Complex double **A, _Complex double **B, _Complex double ***result) {
    *result = malloc(rows * sizeof(_Complex double *));
    for (int i = 0; i < rows; ++i) {
        (*result)[i] = malloc(cols * sizeof(_Complex double));
        for (int j = 0; j < cols; ++j) {
            (*result)[i][j] = A[i][j] - B[i][j];
            if (!isFirstDecimalPlaceZero(A[i][j])|| !isFirstDecimalPlaceZero(B[i][j])) flag_ra=1;
        }
    }
}

// Function to multiply matrices
void multiplyMatrices(int rows, int cols, _Complex double **A, _Complex double **B, _Complex double ***result) {
    *result = malloc(rows * sizeof(_Complex double *));
    for (int i = 0; i < rows; ++i) {
        (*result)[i] = malloc(cols * sizeof(_Complex double));
        for (int j = 0; j < cols; ++j) {
            (*result)[i][j] = 0 + 0 * I; // Initialize with complex zero
            for (int k = 0; k < cols; ++k) {
                (*result)[i][j] += A[i][k] * B[k][j];
                if (!isFirstDecimalPlaceZero(A[i][j])|| !isFirstDecimalPlaceZero(B[i][j])) flag_ra=1;
            }
        }
    }
}

int andMatrices(int rows, int cols, _Complex double ** A, _Complex double ** B, _Complex double *** result) {
    *result = malloc(rows * sizeof(_Complex double *));
    for (int i = 0; i < rows; ++i) {
        (*result)[i] = malloc(cols * sizeof(_Complex double));
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((creal(A[i][j]) != 0 && creal(A[i][j]) != 1) || (creal(B[i][j]) != 0 && creal(B[i][j]) != 1)) {
                // Free the allocated memory before returning
                for (int k = 0; k <= i; ++k) {
                    free((*result)[k]);
                }
                free(*result);
//                printf("ERR\n");
                return -1;
            } else {
                (*result)[i][j] = (creal(A[i][j]) != 0 && creal(B[i][j]) != 0) ? 1 : 0;
                if (!isFirstDecimalPlaceZero(A[i][j])|| !isFirstDecimalPlaceZero(B[i][j])) flag_ra=1;
            }
        }
    }
    return 0;
}

int orMatrices(int rows, int cols, _Complex double **A, _Complex double **B, _Complex double ***result) {
    *result = malloc(rows * sizeof(_Complex double *));
    for (int i = 0; i < rows; ++i) {
        (*result)[i] = malloc(cols * sizeof(_Complex double));
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((creal(A[i][j]) != 0 && creal(A[i][j]) != 1) || (creal(B[i][j]) != 0 && creal(B[i][j]) != 1)) {
                // Free the allocated memory before returning
                for (int k = 0; k <= i; ++k) {
                    free((*result)[k]);
                }
                free(*result);
//                printf("ERR\n");
                return -1;
            } else {
                (*result)[i][j] = (creal(A[i][j]) != 0 || creal(B[i][j]) != 0) ? 1 : 0;
            }
        }
    }
    return 0;
}

// Function to perform operations in a thread
void* performOperation(void* arg) {
    MatrixData *data = (MatrixData*)arg;

    if (strcmp(data->operation, "ADD") == 0) {
        addMatrices(data->rows, data->cols, data->A, data->B, &data->result);
    } else if (strcmp(data->operation, "SUB") == 0) {
        subtractMatrices(data->rows, data->cols, data->A, data->B, &data->result);
    } else if (strcmp(data->operation, "MUL") == 0) {
        multiplyMatrices(data->rows, data->cols, data->A, data->B, &data->result);
    }else if (strcmp(data->operation, "AND") == 0) {

            if (andMatrices(data->rows, data->cols, data->A, data->B, &data->result) == -1) {
                flag_err=1;
                data->result = NULL;}
//        andMatrices(data->rows, data->cols, data->A, data->B, &data->result);
    } else if (strcmp(data->operation, "OR") == 0) {
//       if( orMatrices(data->rows, data->cols, data->A, data->B, &data->result)==-1)   { data->result = NULL;}
        if (orMatrices(data->rows, data->cols, data->A, data->B, &data->result) == -1) {
            flag_err=1;
            data->result = NULL;}
    }
    else {
        printf("Unknown operation: %s\n", data->operation);
    }

    pthread_exit(NULL);
}

int main() {
    int some=1;
    char input[MAX_char], operation[MAX_char];
    int rows1, cols1, rows2, cols2;
    _Complex double **A[MAX_MATRICES], **B[MAX_MATRICES];
    int matrix_count = 0;

    while (1) {  // Outer loop to continue processing
        matrix_count = 0;  // Reset matrix count for each iteration
        flag_complex=0;
        flag_ra=0;
        while (1) {
            some=1;

            if (!fgets(input, MAX_char, stdin)) {
                // Handle EOF
                return 0;
            }
            if(contains_i(input)) flag_complex=1;
            input[strcspn(input, "\n")] = 0;  // Remove trailing newline

            if (strcmp(input, "END") == 0) {
                return 0;  // Exit program if "END" is entered
            }

//            if (strncmp(input, "ADD", 3) == 0 || strncmp(input, "SUB", 3) == 0 || strncmp(input, "MUL", 3) == 0) {
//                strcpy(operation, input);
//                break;
//            }
            if (strncmp(input, "ADD", 3) == 0 || strncmp(input, "SUB", 3) == 0 ||
                strncmp(input, "MUL", 3) == 0 || strncmp(input, "AND", 3) == 0 ||
                strncmp(input, "OR", 2) == 0) {
                strcpy(operation, input);
                break;
            }
            parseMatrix(input, &rows1, &cols1, &A[matrix_count]);

            fgets(input, MAX_char, stdin);
            parseMatrix(input, &rows2, &cols2, &B[matrix_count]);

            if (rows1 != rows2 || cols1 != cols2) {
                printf("Matrices must be of the same dimensions for this operation.\n");
                continue;
            }

            matrix_count++;
            if (matrix_count >= MAX_MATRICES) {
                break;
            }
        }

        if (matrix_count == 0) {
            continue;  // No matrices entered, start over
        }

        // Rest of the processing (threads, calculations, etc.)
        pthread_t threads[MAX_MATRICES];
        MatrixData data[MAX_MATRICES];
        _Complex double **final_result = NULL;

        // Rest of the processing code, unchanged
        for (int i = 0; i < matrix_count; ++i) {
            data[i].rows = rows1;
            data[i].cols = cols1;
            data[i].A = A[i];
            data[i].B = B[i];
            strcpy(data[i].operation, operation);

            pthread_create(&threads[i], NULL, performOperation, (void *) &data[i]);
        }

        for (int i = 0; i < matrix_count; ++i) {
            pthread_join(threads[i], NULL);
            if (data[i].result == NULL) {
                final_result = NULL;
                break;
            }
            if (i == 0) {
                final_result = data[i].result;
            } else {
                _Complex double **temp = final_result;
                if (strcmp(data[i].operation, "ADD") == 0) {
                    addMatrices(data[i].rows, data[i].cols, temp, data[i].result, &final_result);
                } else if (strcmp(data[i].operation, "SUB") == 0) {
                    subtractMatrices(data[i].rows, data[i].cols, temp, data[i].result, &final_result);
                } else if (strcmp(data[i].operation, "MUL") == 0) {
                    multiplyMatrices(data[i].rows, data[i].cols, temp, data[i].result, &final_result);
                } else if (strcmp(data[i].operation, "AND") == 0) {
                    andMatrices(data[i].rows, data[i].cols, temp, data[i].result, &final_result);
                } else if (strcmp(data[i].operation, "OR") == 0) {
                    orMatrices(data[i].rows, data[i].cols, temp, data[i].result, &final_result);
                }
                freeMatrix(data[i].rows, temp);
            }
        }

    if (flag_err==1){
        printf("ERR\n");
        flag_err=0;
        some=0;
        continue;
    }
        if (final_result != NULL && some==1) {
            printMatrix(rows1, cols1, final_result);
        }

// Free memory
        for (int i = 0; i < matrix_count; ++i) {
            freeMatrix(data[i].rows, data[i].A);
            freeMatrix(data[i].rows, data[i].B);
        }
        if (final_result) {
            freeMatrix(rows1, final_result);
        }
    }
        return 0;
}
