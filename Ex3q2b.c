#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define MAX_CHAR 128
#define SHM_SIZE 2048
#define SEM_KEY 1234
#define SHM_KEY 5678

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};
void parseMatrix(const char * input, int * rows, int * cols, _Complex double ** * matrix) {
    sscanf(input, "(%d,%d:", rows, cols);
    * matrix = malloc( * rows * sizeof(_Complex double * ));
    for (int i = 0; i < * rows; ++i) {
        ( * matrix)[i] = malloc( * cols * sizeof(_Complex double));
    }
    const char * start = strchr(input, ':') + 1;
    for (int i = 0; i < * rows; ++i) {
        for (int j = 0; j < * cols; ++j) {
            double real, imag;
            if (sscanf(start, "%lf+%lfi", & real, & imag) == 2) {
                ( * matrix)[i][j] = real + imag * I;
            } else if (sscanf(start, "%lf%lfi", & real, & imag) == 2) {
                ( * matrix)[i][j] = real + imag * I;
            } else {
                sscanf(start, "%lf", & real);
                ( * matrix)[i][j] = real;
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

void writeToSharedMemory(int shm_id, const char *data) {
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    strncpy(shm_ptr, data, SHM_SIZE);
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
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

int main() {
    char input1[MAX_CHAR], input2[MAX_CHAR], operation[MAX_CHAR];
    int rows1, cols1, rows2, cols2;
    _Complex double **A, **B;

    // Create shared memory segment
    int shm_id = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Create semaphore
    int sem_id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if (sem_id == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize semaphore to 1 (unlocked)
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(1);
    }

    while (1) {
        fgets(input1, MAX_CHAR, stdin);
        if (strcmp(input1, "END") == 0 || strcmp(input1, "END\n") == 0) {
            break;
        }
        parseMatrix(input1, &rows1, &cols1, &A);

        fgets(input2, MAX_CHAR, stdin);
        if (strcmp(input2, "END") == 0 || strcmp(input2, "END\n") == 0) {
            break;
        }

        char shared_data[SHM_SIZE] = {0};

        if (strcmp(input2, "NOT") == 0 || strcmp(input2, "NOT\n") == 0 || strcmp(input2, "TRANSPOSE") == 0 || strcmp(input2, "TRANSPOSE\n") == 0) {
            snprintf(shared_data, SHM_SIZE, "%s;%s", input1, input2);
        } else {
            parseMatrix(input2, &rows2, &cols2, &B);
            fgets(operation, MAX_CHAR, stdin);
            snprintf(shared_data, SHM_SIZE, "%s;%s;%s", input1, input2, operation);
            freeMatrix(rows2, B);
        }

        // Lock semaphore
        semOp(sem_id, -1);

        // Write to shared memory
        writeToSharedMemory(shm_id, shared_data);

        // Unlock semaphore
        semOp(sem_id, 1);

        freeMatrix(rows1, A);
    }

    // Cleanup
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}

