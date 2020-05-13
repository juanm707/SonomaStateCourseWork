#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "constants.h"
#include "parsetools.h"

void syserror(const char *, const char *);
extern int errno;

int main() {
    // Buffer for reading one line of input
    char line[MAX_LINE_CHARS];
    // holds separated words based on whitespace
    char *line_words[MAX_LINE_WORDS + 1];

    int pfd1[2]; // pipes
    int pfd2[2];

    // Loop until user hits Ctrl-D (end of input)
    // or some other input error occurs
    while (fgets(line, MAX_LINE_CHARS, stdin)) {
        int num_words = split_cmd_line(line, line_words);
        int firstCommand = 1;
        for (int i = 0; i < num_words; i++) {
            //printf("%s\n", line_words[i]);

            // first word has to be a function
            char *functionToBeCalled = line_words[i];
            char *functionArgs[MAX_LINE_WORDS]; // The function arguments, first one is always the cmd itself
            functionArgs[0] = line_words[i];

            printf("Command to be executed: %s\n", functionArgs[0]);

            int argC = 1; // Argument count for array[argC], 1 because 0 is the cmd
            pid_t pid; // capturing PID when using fork()
            int _pipe = 0; // are we using pipes bool

            int needToReadFirstPipe = 0;
            int hasReadFirstPipe = 0;
            int needToWriteFirstPipe = 0;
            int needToReadSecondPipe = 0;
            int needToWriteSecondPipe = 0;

            int _secondPipe = 0; // Do we write to a next pipe?
            int nextCommandUsesPrevPipe = 0; // does the next command use the previous pipe?
            int printToScreen = 0; // should we print to screen? Used when the next word is NULL
            int in_redirection = 0; // Input redirection bool
            int out_redirection = 0; // Output redirection bool

            if (num_words > 1) { // If we at least have some cmd and something else like <,>,|,file.*,-x etc...

                int fd; // file descriptor for input redirection
                int out_fd; // file descriptor for output redirection

                for (int j = i + 1; j < num_words + 1; j++) { // Looping through the WHOLE line

                    if (argC == 0) // Reset argument count for next phase
                        functionToBeCalled = line_words[j];

                    if (line_words[j] == NULL || *(line_words[j]) == PIPE || *(line_words[j]) == INPUT_REDIRECT ||
                        *(line_words[j]) == OUTPUT_REDIRECT) {

                        //do pipe stuff like pipe() dup2() close(), error check, or i/o redirection...
                        if (line_words[j] == NULL) {
                            // if the next thing is null, do nothing special, just fork and exec cmd with arguments
                            printToScreen = 1;
                            if (needToReadFirstPipe) {
                                hasReadFirstPipe = 1;
                            }
                        }
                        else if (*(line_words[j]) == PIPE) {
                            // We found a pipe
                            if (_pipe) {
                                // if we still need to read from the first pipe, make a new one
                                if (pipe(pfd2) == -1) // create a pipe
                                    syserror( "Could not create a pipe", "");
                                else {
                                    printf("Created a second pipe.\n");
                                    _secondPipe = 1;
                                    needToReadSecondPipe = 1;
                                    needToWriteSecondPipe = 1;
                                }
                            }
                            else {
                                _pipe = 1; // set pipe bool to true

                                if (pipe(pfd1) == -1) // create a pipe
                                    syserror("Could not create a pipe", "");
                                else {
                                    printf("Created a first pipe.\n");
                                }
                                // so since we found a pipe, the next "word" in line_words should be a cmd
                                nextCommandUsesPrevPipe = 1;
                                needToReadFirstPipe = 1;
                                needToWriteFirstPipe = 1;
                            }
                        }
                        else if (*(line_words[j]) == INPUT_REDIRECT) {
                            char * inputFilename = line_words[++j];
                            // check for the next possible thing: pipe or output redirection, where is output going
                            // is this possible?? cmd < file < something
                            char * outRedir_or_pipe = line_words[++j];
                            if (outRedir_or_pipe == NULL) {
                                //do nothing
                            }
                            else if (*outRedir_or_pipe == PIPE) {

                            }
                            else if (*outRedir_or_pipe == OUTPUT_REDIRECT) {
                                char * outputFileName = line_words[++j];
                                printf("Redirect Output File Name: %s\n", outputFileName);
                                out_fd = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC);
                                printf("File Descriptor OUT: %d\n", out_fd);
                                out_redirection = 1;
                            }

                            int errnum; // error checking
                            fd = open(inputFilename, O_RDONLY); // fd for [ cmd [args]+ < file ]
                            printf("File Descriptor IN: %d\n", fd);
                            printf("Redirect Input File Name: %s\n", inputFilename);
                            errnum = errno; // error checking
                            fprintf(stderr, "Value of errno: %d\n", errno); // error checking
                            perror("Error printed by perror"); // error checking
                            fprintf(stderr, "Error opening file: %s\n", strerror( errnum )); // error checking
                            in_redirection = 1;
                        }
                        // set last arg to NULL
                        functionArgs[argC] = NULL;
                        argC = 0; // reset arg count for next command in line, if any

                        switch (pid = fork()) {
                            case -1:
                                syserror("First fork failed", "");
                                break;
                            case 0:
                                printf("Inside the child!\n");
                                if (_pipe) {
                                    if (!firstCommand) {
                                        // if this is not the first command, I want to read from the read end of pipe
                                        if (needToReadFirstPipe) {
                                            // read from first pipe
                                            dup2(pfd1[0], 0); // stdin points to read end of pipe
                                            close(pfd1[0]);
                                            close(pfd1[1]);
                                        }

                                        else if (out_redirection) { // TODO: check this one
                                            dup2(out_fd, 1);
                                            close(out_fd);
                                        }
                                        else if (printToScreen){
                                            // after pipe | cmd NULL, we just write to stdout aka screen
                                        }
                                    }
                                    else {
                                        // if we are the first command, and since pipe was true, we have to write to
                                        // the write end of the pipe. So now stdout points to the write end.
                                        // This makes it so that when the process writes to stdout, it ACTUALLY writes into the pipe.
                                        if (needToWriteFirstPipe) {
                                            dup2(pfd1[1], 1);
                                            close(pfd1[1]);
                                            close(pfd1[0]);
                                        }
                                    }
                                }
                                if (in_redirection) {
                                    dup2(fd, 0);
                                    if (out_redirection) {
                                        dup2(out_fd, 1);
                                        close(out_fd);
                                    }
                                    close(fd);
                                }
                                execvp(functionToBeCalled, functionArgs);
                                syserror("Could not exec: ", functionToBeCalled);
                                break;
                            default:
                                fprintf(stderr, "The first child's pid is: %d\n", pid);
                                if (_pipe) { // if we did pipe, close the file descriptors
                                    if (hasReadFirstPipe){
                                        close(pfd1[0]);
                                        hasReadFirstPipe = 0;
                                        needToReadFirstPipe = 0;
                                    }
                                    else if (needToReadFirstPipe) {
                                        //close(pfd1[0]);
                                        close(pfd1[1]);
                                    }
                                    
                                    if (needToWriteFirstPipe) {
                                        // first pipe was already written to
                                        needToWriteFirstPipe = 0;
                                    }

                                    if (!nextCommandUsesPrevPipe) {
                                        _pipe = 0; // reset to zero since it was set and used
                                        //close(pfd1[0]); // close read end since it was read already
                                    }
                                    else
                                        nextCommandUsesPrevPipe = 0;
                                }

                                firstCommand = 0; // no longer the first command
                                printToScreen = 0; // reset to 0 if needed
                                if (in_redirection) // if we used input redirection, close the file descriptor
                                    close(fd);
                                if (out_redirection) // if we used output redirection, close the file descriptor
                                    close(out_fd);

                                pid_t cpid = waitpid(pid, NULL, 0); // See child pid that was return, if any
                                printf("Child pid = %d\n", cpid);
                                memset(functionArgs, 0, sizeof(functionArgs)); // reset argument array after waiting for child
                                break;
                        }
                    } else {
                        // build argument array
                        functionArgs[argC] = line_words[j];
                        argC++;
                    }
                    i = j; // not sure about this
                } // what is the new value for i !
            }

            // single command, no arguments ex: whoami, ls, pwd
            else {
                switch (pid = fork()) {
                    case -1:
                        syserror("First fork failed", "");
                        break;
                    case 0:
                        execlp(functionToBeCalled, functionToBeCalled, NULL);
                        syserror("Could not exec: ", functionToBeCalled);
                        break;
                    default:
                        fprintf(stderr, "The child's pid is: %d\n", pid);
                        waitpid(pid,NULL, 0);
                        break;
                }
            }
        }
    }
    return 0;
}

void syserror(const char *s, const char *cmd)
{
    extern int errno;
    fprintf(stderr, "%s%s\n", s, cmd);
    fprintf(stderr, " (%s)\n", strerror(errno));
    exit(1);
}
