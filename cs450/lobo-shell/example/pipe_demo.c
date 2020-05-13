#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>

void syserror(const char *);

int main(void)
{
    int pfd[2];
    pid_t pid;

    if (pipe(pfd) == -1)
        syserror( "Could not create a pipe" );

    switch ( pid = fork() ) {
        case -1: 
            syserror("First fork failed");
            break;
        case  0: 
            if (close(0) == -1)
                syserror("Could not close stdin");
            dup(pfd[0]);
            if (close(pfd[0]) == -1 || close(pfd[1]) == -1)
                syserror( "Could not close pfds from first child" );
            execlp("wc", "wc", NULL);
            syserror("Could not exec wc");
            break;
        default:
            fprintf(stderr, "The first child's pid is: %d\n", pid);
            break;
    }

    switch ( pid = fork() ) {
        printf("Inside the second fork()\n");
        case -1: 
            syserror( "Second fork failed" );
            break;
        case  0: 
            if (close(1) == -1)
                syserror("Could not close stdout");
            dup(pfd[1]);
            if (close(pfd[0]) == -1 || close(pfd[1]) == -1)
                syserror( "Could not close pfds from second child" );
            execlp("who", "who", NULL);
            syserror( "Could not exec who" );
            break;
        default:
            fprintf(stderr, "The second child's pid is: %d\n", pid);
            break;
    }
    
    if (close(pfd[0]) == -1)
        syserror( "Parent could not close stdin" );
    if (close(pfd[1]) == -1)
        syserror( "Parent could not close stdout" );

    while ( wait(NULL) != -1)
        ;
}

void syserror(const char *s)
{
    extern int errno;
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, " (%s)\n", strerror(errno));
    exit(1);
}

