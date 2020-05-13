/* stringInHex.c
 * displays each character in "Hello world" in hex
 * and the address where it is stored.
 * 2017-09-29: Bob Plantz
 */

#include <stdio.h>

int main(void) {
  char* stringPtr = "Hello world.\n";

  while (*stringPtr != '\0')
    {
      printf("%p: ", stringPtr);
      printf("0x%02x\n", *stringPtr);
      stringPtr++;
    }

  printf("%p: ", stringPtr);
  printf("0x%02x\n", *stringPtr);

  return 0;
}
