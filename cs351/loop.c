#include <stdio.h>
 
int main () {
  int acc = 0;
  int i = 10;

  /* while loop execution */
  while( i > 0 ) {
    acc = acc + 2;
    i = i - 1;
   }
  printf("Value of acc: %d\n", acc);
  return acc;
}
