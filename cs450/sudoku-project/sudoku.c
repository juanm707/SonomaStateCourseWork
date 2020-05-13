#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <ctype.h>

/* These are the only two global variables allowed in your program */
static int verbose = 0;
static int use_fork = 0;

struct thread_info {
    char values[9][9];
    int section; //section to check, 0 - 8 for row, 9 - 17 for columns, and 18 - 26 for subgrid ex 18 19 20 \n 21 22 23 ...
};

// This is a simple function to parse the --fork argument.
// It also supports --verbose, -v
void parse_args(int argc, char *argv[])
{
    int c;
    while (1)
    {
        static struct option long_options[] =
        {
            {"verbose", no_argument,       0, 'v'},
            {"fork",    no_argument,       0, 'f'},
            {0, 0, 0, 0}
        };
        int option_index = 0;
        c = getopt_long (argc, argv, "vf", long_options, &option_index);
        if (c == -1) break;

        switch (c)
        {
            case 'f':
                use_fork = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                exit(1);
        }
    }
}


void* check_component(void* t_arg) {
    static int invalid = 1;
    struct thread_info* t = (struct thread_info* )t_arg;
    char copy_v[9];
    int count = 0;

    if (t->section >= 0 && t->section <= 8) {
        if (verbose)
            printf("inside thread %d\n", t->section);
        for (int i = 0; i < 8; i++) {
            for (int j = i + 1; j < 9; j++) {
                if (t->values[t->section][i] == t->values[t->section][j]) {
                    // in case of a duplicate
                    printf("Row %d doesn't have the required values.\n", t->section + 1);
                    return (void *) t->section + 1;
                }
            }
        }
    }

    else if (t->section >= 9 && t->section <= 17) {
        if (verbose)
            printf("inside thread %d\n", t->section);
        for (int i = 0; i < 8; i++) {
            for (int j = i + 1; j < 9; j++) {
                if (t->values[i][t->section] == t->values[j][t->section]) {
                    // in case of a duplicate
                    printf("Column %d doesn't have the required values.\n", t->section - 8);
                    return (void *) t->section + 1;
                }
            }
        }
    }
    switch (t->section) {

        case 18: // check first subgrid
            if (verbose)
                printf("inside thread %d\n", 18);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The left upper subgrid doesn't have the required values.\n");
                        return (void *) 19;
                    }
                }
            }
            break;
        case 19:
            if (verbose)
                printf("inside thread %d\n", 19);
            for (int i = 0; i < 3; i++) {
                for (int j = 3; j < 6; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The middle upper subgrid doesn't have the required values.\n");
                        return (void *) 20;
                    }
                }
            }
            break;
        case 20:
            if (verbose)
                printf("inside thread %d\n", 20);
            for (int i = 0; i < 3; i++) {
                for (int j = 6; j < 9; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The right upper subgrid doesn't have the required values.\n");
                        return (void *) 21;
                    }
                }
            }
            break;
        case 21:
            if (verbose)
                printf("inside thread %d\n", 21);
            for (int i = 3; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The left middle subgrid doesn't have the required values.\n");
                        return (void *) 22;
                    }
                }
            }
            break;
        case 22:
            if (verbose)
                printf("inside thread %d\n", 22);
            for (int i = 3; i < 6; i++) {
                for (int j = 3; j < 6; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The middle middle subgrid doesn't have the required values.\n");
                        return (void *) 23;
                    }
                }
            }
            break;
        case 23:
            if (verbose)
                printf("inside thread %d\n", 23);
            for (int i = 3; i < 6; i++) {
                for (int j = 6; j < 9; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The right middle subgrid doesn't have the required values.\n");
                        return (void *) 24;
                    }
                }
            }
            break;
        case 24:
            if (verbose)
                printf("inside thread %d\n", 24);
            for (int i = 6; i < 9; i++) {
                for (int j = 0; j < 3; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The left bottom subgrid doesn't have the required values.\n");
                        return (void *) 25;
                    }
                }
            }
            break;
        case 25:
            if (verbose)
                printf("inside thread %d\n", 25);
            for (int i = 6; i < 9; i++) {
                for (int j = 3; j < 6; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The middle bottom subgrid doesn't have the required values.\n");
                        return (void *) 26;
                    }
                }
            }
            break;
        case 26: //check last subgrid
            if (verbose)
                printf("inside thread %d\n", 26);
            for (int i = 6; i < 9; i++) {
                for (int j = 6; j < 9; j++) {
                    copy_v[count] = t->values[i][j];
                    count++;
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 9; j++) {
                    if (copy_v[i] == copy_v[j]) {
                        // in case of a duplicate
                        printf("The right bottom subgrid doesn't have the required values.\n");
                        return (void *) 27;
                    }
                }
            }
            break;
    }
    free(t);
    return NULL;
}

void worker_threads(char values[9][9]) {
    void* status = NULL;
    int invalid = 0;
    int numThreads = 27;

    pthread_t threads[numThreads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < numThreads; i++) { // create 27 threads
        //pthread_t tid;
        struct thread_info* ti = malloc(sizeof(*ti));
        memcpy(ti->values, values, sizeof(ti->values));
        ti->section = i;

        if (verbose)
            printf("worker_threads() : creating thread, %d\n", i);

        pthread_create(&threads[i], &attr, check_component, ti);
    }

    for(int i = 0; i < numThreads; i++ ) {
        pthread_join(threads[i], &status);
        if ((status != NULL) && !invalid) {
            invalid = 1;
            printf("The input is not a valid Sudoku.\n");
        }
        if (verbose)
            printf("Value of Status: %d\n", (int *)status);
    }
    if (invalid == 0)
        printf("The input is a valid Sudoku.\n");

    pthread_exit(NULL);
}

void useFork(char values[9][9]) {

    int numAreasToCheck = 27;
    int invalid = 0;
    int status;
    void * s = NULL;

    for (int i = 0; i < numAreasToCheck; i++) {
        if(fork() == 0)
        {
            struct thread_info *ti = malloc(sizeof(*ti));
            memcpy(ti->values, values, sizeof(ti->values));
            ti->section = i;

            s = check_component(ti);
            if (s != NULL) {
                if (verbose)
                    printf("S: %d\n", (int *) s);
                invalid = 1;
                //free(ti);
            }
            if (verbose)
                printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(invalid);
        }
    }

    for (int i = 0; i < numAreasToCheck; i++) {
        wait(&status);
        if (verbose)
            printf("Status: %d\n", WEXITSTATUS(status));
        if (WEXITSTATUS(status)) //if true then invalid sudoku
            invalid = 1;
    }

    if (invalid == 0)
        printf("The input is a valid Sudoku.\n");
    else
        printf("The input is not a valid Sudoku.\n");
}

void read_input(char values[9][9]) {
    char number;
    int count = 0; //for output purposes
    int digitCount = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%c", &number);
            if (isspace(number)) { //if it is a whitespace character
                digitCount = 0;
                j--;
            } else {
                if(number == '-') {
                    printf("Can not have numbers less than 1!\nThe input is not a valid Sudoku.\n");
                    exit(2);
                }
                digitCount+=1;
                if (digitCount == 2) {
                    printf("Number out of range.\nThe input is not a valid Sudoku.\n");
                    exit(3);
                }
                values[i][j] = number;
                if (verbose) { // this prints the sudoku board
                    printf("%c", values[i][j]);
                    count += 1;
                    if (count % 3 == 0)
                        printf(" ");
                    if (count % 9 == 0)
                        printf("\n");
                    if (count % 27 == 0)
                        printf("\n");
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    parse_args(argc, argv);
    char v[9][9]; // Total values used in 9 x 9 sudoku is 81, stored in this char array
    read_input(v);

    if (verbose && use_fork) {
        printf("We are forking child processes as workers.\n");
        useFork(v);

    }
    else if (use_fork) {
        useFork(v);
    }
    else if (verbose) {
        printf("We are using worker threads.\n");
        worker_threads(v);
    }
    else {
        worker_threads(v);
    }

    return 0;
}

