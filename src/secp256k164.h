#pragma once
#ifndef _SECP256K164_H
#define _SECP256K164_H

#include <stdint.h>
#include <memory.h>
#include "uint256math.h"

void secp256k1_init();

void secp256k1_publickey(uint64_t* k, uint64_t* Px, uint64_t* Py);

void secp256k1_double(uint64_t* Ax, uint64_t* Ay, uint64_t* Bx, uint64_t* By);
//!!!!!!!!!!!!!!!!!!!!!IMPORTANT YOU HAVE TO CHECK IF Two points are equal before use add function, YOU CANT ADD TWO EQUAL POINTS, USE DOUBLE!
//FOR THIS USE UINT256MATH equal_u256
void secp256k1_add(uint64_t* Ax, uint64_t* Ay, uint64_t* Bx, uint64_t* By, uint64_t* Cx, uint64_t* Cy);

#endif
