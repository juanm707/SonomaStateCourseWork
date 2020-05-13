#include "readLn.h"
#include "writeStr.h"
#define STRLEN 5

int main(void) {
  char aString[STRLEN];
  writeStr("Enter a text string: ");
  readLn(aString, STRLEN);
  writeStr("You entered:\n");
  writeStr(aString);
  writeStr("\n");

  return 0;
}
