#include "writeStr.h"
#include "readLn.h"
#define STRLEN 200

int main(void) {
  char aString[STRLEN];
  writeString("Enter a text string: ");
  readLn(aString, STRLEN);
  writeString("You entered:\n");
  writeString(aString);
  writeString("\n");

  return 0;
}