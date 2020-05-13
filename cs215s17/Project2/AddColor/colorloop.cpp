#include <iostream>
using namespace std;

int main ()
{
	char esc = 0x1B;
	for (int a = 0; a <= 8; a++)
	{
		cout << "Attribute = " << a << endl;
		for (int f = 30; f <= 37; f++)
		{
			for (int b = 40; b <= 47; b++)
			{
				cout << esc << '[' << a << ';' << f << ';' << b << 'm';
				cout << a << ';' << f << ';' << b;
			}
			cout << esc << "[0m\n";
		}
	}
	return 0;
}
