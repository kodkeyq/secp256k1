#pragma once
#ifndef _SECP256K1CLASS_H
#define _SECP256K1CLASS_H

#include <stdint.h>
#include <memory.h>
#include "uint256math.h"

typedef uint64_t uint256_t[4];

struct point
{
	uint256_t x;
	uint256_t y;
};

static const point G =
{
	{ 0x59F2815B16F81798,0x029BFCDB2DCE28D9,0x55A06295CE870B07,0x79BE667EF9DCBBAC },
	{ 0x9C47D08FFB10D4B8, 0xFD17B448A6855419, 0x5DA4FBFC0E1108A8, 0x483ADA7726A3C465 }
};

static const uint256_t p = { 0xFFFFFFFEFFFFFC2F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF };
static const uint256_t n = { 0xBFD25E8CD0364141,0xBAAEDCE6AF48A03B,0xFFFFFFFFFFFFFFFE,0xFFFFFFFFFFFFFFFF };
static const uint256_t h = { 0x0000000000000001,0x0000000000000000,0x0000000000000000,0x0000000000000000 };
static const uint256_t a = { 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000 };
static const uint256_t b = { 0x0000000000000007,0x0000000000000000,0x0000000000000000,0x0000000000000000 };

class Secp256k1
{
private:
	point S[256];
	//point SB[32];

	uint256_t privatekey;
	point publickeyp;

	uint256_t inc;
	point incp;

	void FillS();
	
	//void FillSB(uint8_t byte);

	point PublicKey(uint256_t prik);

	point Add(point A, point B);

	point Double(point A);
public:
	Secp256k1();

	//Secp256k1(uint8_t Byte);

	point ReturnPublic(uint64_t* k);

	//point ReturnPublicB(uint64_t* k);

	void SetPrivateKey(uint64_t* k);

	void SetIncrement(uint64_t* i);

	void Increment();

	void Get(uint64_t* k, uint64_t* px, uint64_t* py);
};

#endif

