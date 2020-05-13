//
//  main.cpp
//  rgb
//
//  Created by Gurman Gill on 2/7/17.
//  Copyright © 2017 Gurman Gill. All rights reserved.
//

#include <iostream>
using namespace std;

enum class color: uint
{
  redMask = 0xFF000000,
  greenMask = 0x00FF0000,
  blueMask = 0x0000FF00,
  alphaMask = 0x000000FF
};

int main(int argc, const char * argv[]) {

  cout << "Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): ";
  uint pixel;
  cin >> hex >> pixel; // std::hex allows us to read in a hex value

  // Use bitwise AND to isolate individual color channels red, green, blue and alpha) from this pixel

  uint redChannel = pixel & uint(color::redMask);
  uint greenChannel = pixel & uint(color::greenMask);
  uint blueChannel = pixel & uint(color::blueMask);
  uint alphaChannel = pixel & uint(color::alphaMask);

  // Right shift the value into the range 0-255 and store it into an uint8_t (1 byte integer)
  uint8_t red = redChannel >> 24;
  uint8_t green = greenChannel >> 16;
  uint8_t blue = blueChannel >> 8;
  uint8_t alpha = alphaChannel;

  cout << endl << "Your color contains:" << endl;
  cout << int(red) << " of 255 red" << endl;
  cout << int(green) << " of 255 green" << endl;
  cout << int(blue) << " of 255 blue" << endl;
  cout << int(alpha) << " of 255 alpha" << endl;

  return 0;
}
