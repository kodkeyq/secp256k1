# Secp256k1 Library
This is an easy-to-use implementation of Secp256k1 cryptography, 
realized purely in C++. With this library, you can quickly create keypairs.

No OOP was used. To create new keypair just use secp256k1_publickey function.
The unusual part of the code was made just to speed up key generation.
WORKS ONLY WITH 64-Bit compilers that support SIMD instructions (_umul128, ...). (Visual Studio 2019 was used).

Example(in Secp256k1Curve.cpp):

#include "secp256k1class.h"

Secp256k1 curve;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! k[0] - low uint64_t k[3] - high uint64_t
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

	// PRINT k, Px, Py

	// Here you can get next Key = k + k2...
	//curve.Increment();


	// This is for single use

	point P;

	P = curve.ReturnPublic(k);

	// PRINT k, P.x, P.y

	system("pause");

