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
	string str1, str2;
	getline(cin, str1);
	Polynomial pol1(str1);
	cout << "Enter the polynomial 2: " << endl;
	getline(cin, str2);
	Polynomial pol2(str2);
	cout << "Enter random number: " << endl;
	double number;
	cin >> number;
	cout << "polynomial1 + number = " << pol1 + number << endl;
	cout << "polynomial2 + number = " << pol2 + number << endl;
	cout << "polynomial1 * number = " << pol1 * number << endl;
	cout << "polynomial2 * number = " << pol1 + number << endl;
	cout << "polynomial1 + polynomial2 = " << pol1 + pol2 << endl;
	cout << "polynomial1 * polynomial2 = " << pol1 * pol2 << endl;

	cout << "Enter the value of x: " << endl;
	cin >> number;
	cout << str1 << " = " << pol1.Calculate(number) << endl;
	cout << str2 << " = " << pol2.Calculate(number) << endl;
	_getch();

	//4x^9 + 3x^7 + 5x^3 + 3x^2 + 2x + 4
	//2x^7 + 3x^6 + 2x^5 + 5x^4 + 2x^3 + 2x^2
}
