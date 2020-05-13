#include <unistd.h>

int main(void) {
  char aLetter = 'A';
  write(STDOUT_FILENO, &aLetter, 1);
  return 0;
}
