#include <iostream>
#include <string>
#include "Polynomials.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	cout << "Enter the polynomial 1: " << endl;
	string str;
	getline(cin, str);
	Polynomial pol1(str);
	cout << "Enter the polynomial 2: " << endl;
	getline(cin, str);
	Polynomial pol2(str);
	cout << "Enter random number: " << endl;
	double number;
	cin >> number;
	cout << "polynomial1 + number = " << pol1 + number << endl;
	cout << "polynomial2 + number = " << pol2 + number << endl;
	cout << "polynomial1 * number = " << pol1 * number << endl;
	cout << "polynomial2 * number = " << pol1 + number << endl;
	cout << "polynomial1 + polynomial2 = " << pol1 + pol2 << endl;
	cout << "polynomial1 * polynomial2 = " << pol1 * pol2 << endl;
	_getch();
}
