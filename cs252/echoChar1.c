#include <unistd.h>
#include <string.h>

int main(void) {
  char aString[200];
  char* stringPtr = aString;

  write(STDOUT_FILENO, "Enter a string of text: ", 24);

  read(STDIN_FILENO, stringPtr, 1);
  while(*stringPtr != '\n')
    {
      stringPtr++;
      read(STDIN_FILENO, stringPtr, 1);
    }

  // now echo to user
  write(STDOUT_FILENO, "You entered:\n",strlen("You entered:\n"));

  stringPtr = aString;
  do {
    write(STDOUT_FILENO, stringPtr, 1);
    stringPtr++;
  } while (*stringPtr != '\n');
  write(STDOUT_FILENO, stringPtr, 1);
  
  return 0;
}
