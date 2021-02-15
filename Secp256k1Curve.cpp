// Secp256k1Curve.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdint.h>
#include <iomanip>
#include "secp256k1class.h"

using namespace std;

void printk(uint64_t* k, uint64_t* Px, uint64_t* Py)
{
	cout << "0x" << hex << setw(16) << setfill('0');

	for (int64_t i = 3; i >= 0; i--)
	{
		cout <<  *(k + i);
	}
	cout << endl << "0x";
	for (int64_t i = 3; i >= 0; i--)
	{
		cout <<  *(Px + i);
	}
	cout << endl << "0x";
	for (int64_t i = 3; i >= 0; i--)
	{
		cout << *(Py + i);
	}
	cout << endl;
	return;
}

int main()
{
	Secp256k1 curve;

	uint64_t k[4] = { 0x1111111111111111,0x1111111111111111,0x1111111111111111,0x1111111111111111 };

	uint64_t Px[4], Py[4];

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IMPORTANT - USE x64 bit system and debug-mode!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// This is used for bruteforce - next should be curve.Increment();
	curve.SetPrivateKey(k);

	// curve.SetIncrement(k2);

	curve.Get(k, Px, Py);

	printk(k, Px, Py);

	// Here you can get next Key = k + k2...
	//curve.Increment();


	// This is for single use

	point P;

	P = curve.ReturnPublic(k);

	printk(k, P.x, P.y);

	system("pause");
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
