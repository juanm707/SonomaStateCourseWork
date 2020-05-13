/* echoDecHexAddr.c
 * Prompts user to enter a number in decimal, another in
 * hexadecimal then echoes both in both bases, also showing
 * where values are stored.
 * 2017-09-29: Bob Plantz
 */

#include <stdio.h>

int main (void) {
  int x;
  unsigned int y;

  while (1) { //loop forever
    
    printf("Enter a decimal integer (0 to quit): ");
    scanf("%i", &x);
    if (x == 0) break; //out of loop

    printf("Enter a bit pattern in hexadecimal: ");
    scanf("%x", &y);
    if (y == 0) break; //out of loop

    printf("%i is stored as %#010x at %p, and\n", x, x, &x);
    printf("%#010x represents the decimal integer %d stored at %p\n\n", y, y, &y);
  }// end while loop

  printf("End of program");
  return 0;
}
