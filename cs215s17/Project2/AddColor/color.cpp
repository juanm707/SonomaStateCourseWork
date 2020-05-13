#include <iostream>
using namespace std;

int main ()
{
	char esc = 0x1B;
	cout << esc << "[7;37;47m\n";
	cout << esc << "[7;30;40m" << "30;40" << esc << "[1;37;47m\n";
	cout << esc << "[7;31;41m" << "31;41" << esc << "[1;37;47m\n";
	cout << esc << "[7;32;42m" << "32;42" << esc << "[1;37;47m\n";
	cout << esc << "[7;33;43m" << "33;43" << esc << "[1;37;47m\n";
	cout << esc << "[7;34;44m" << "34;44" << esc << "[1;37;47m\n";
	cout << esc << "[7;35;45m" << "35;45" << esc << "[1;37;47m\n";
	cout << esc << "[7;36;46m" << "36;46" << esc << "[1;37;47m\n";
	cout << esc << "[7;37;47m" << "37;47" << esc << "[1;37;47m\n";
	return 0;
}
