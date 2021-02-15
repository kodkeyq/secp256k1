#pragma once

#ifndef _UINT256MATH_H
#define _UINT256MATH_H

#include <stdint.h>
#include <memory.h>
#include <intrin.h>

//compare functions

uint64_t equalzero_u256(uint64_t* a);

uint64_t equalone_u256(uint64_t* a);

uint64_t equal_u256(uint64_t* a, uint64_t* b);

uint64_t more_u256(uint64_t* a, uint64_t* b);

//non-modular functions

void add_u256(uint64_t* a, uint64_t* b, uint64_t* c);

void sub_u256(uint64_t* a, uint64_t* b, uint64_t* c);

void mul_u256(uint64_t* a, uint64_t* b, uint64_t* c);

inline void div_u256(uint64_t* a, uint64_t* b, uint64_t* q, uint64_t* r);

//modular functions

void add_u256_mod(uint64_t* a, uint64_t* b, uint64_t* p, uint64_t* c);

void mul_u256_mod(uint64_t* a, uint64_t* b, uint64_t* p, uint64_t* c);

void inv_u256(uint64_t* a, uint64_t* m, uint64_t* b);

//special functions

void add_u512(uint64_t* a, uint64_t* b, uint64_t* c);

void add_u320(uint64_t* a, uint64_t* b, uint64_t* c);

void sub_u320(uint64_t* a, uint64_t* b, uint64_t* c);

void mul_u256_u64(uint64_t* a, uint64_t b, uint64_t* c);

inline void mul_u256_small(uint64_t* a, uint64_t* b, uint64_t* c);

#endif