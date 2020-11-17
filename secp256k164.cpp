#include "secp256k164.h"


static uint64_t p[4] = { 0xFFFFFFFEFFFFFC2F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF };
static uint64_t Gx[4] = { 0x59F2815B16F81798,0x029BFCDB2DCE28D9,0x55A06295CE870B07,0x79BE667EF9DCBBAC };
static uint64_t Gy[4] = { 0x9C47D08FFB10D4B8,0xFD17B448A6855419,0x5DA4FBFC0E1108A8,0x483ADA7726A3C465 };
uint64_t Gx_data[256][4];
uint64_t Gy_data[256][4];
const uint64_t key_length_bits = 256;
const uint64_t s = sizeof(uint64_t) * 4;
const uint64_t s5 = sizeof(uint64_t) * 20;

void secp256k1_double(uint64_t* Ax, uint64_t* Ay, uint64_t* Bx, uint64_t* By)
{
#define r0 &r[0]
#define r1 &r[4]
#define r2 &r[8]
#define r3 &r[12]
#define r4 &r[16]

	uint64_t r[20];
	uint64_t m[4];
	uint64_t Bx_in[4];
	uint64_t By_in[4];

	memset(r, 0, s5);

	mul_u256_mod(Ax, Ax, r0);
	add_u256_mod(r0, r0, r1);
	add_u256_mod(r0, r1, r1);
	add_u256_mod(Ay, Ay, r2);
	inv_u256(r2, p, r3);
	mul_u256_mod(r3, r1, m);

	memset(r, 0, s5);

	mul_u256_mod(m, m, r0);
	add_u256_mod(Ax, Ax, r1);
	sub_u256(p, r1, r3);
	add_u256_mod(r0, r3, Bx_in);

	memset(r, 0, s5);

	sub_u256(p, Ax, r0);
	add_u256_mod(Bx_in, r0, r1);
	mul_u256_mod(r1, m, r2);
	add_u256_mod(r2, Ay, r3);
	sub_u256(p, r3, By_in);

	memcpy(Bx, Bx_in, s);
	memcpy(By, By_in, s);
#undef r0
#undef r1
#undef r2
#undef r3
#undef r4
	return;
}

void secp256k1_add(uint64_t* Ax, uint64_t* Ay, uint64_t* Bx, uint64_t* By, uint64_t* Cx, uint64_t* Cy)
{
#define r0 &r[0]
#define r1 &r[4]
#define r2 &r[8]
#define r3 &r[12]
#define r4 &r[16]

	uint64_t r[20];
	uint64_t m[4];
	uint64_t xp[4];
	uint64_t yp[4];
	uint64_t xr[4];
	uint64_t yr[4];
	uint64_t xq[4];
	uint64_t yq[4];

	memset(r, 0, s5);
	memset(m, 0, s);
	memset(xr, 0, s);
	memset(yr, 0, s);

	if (more_u256(Ax, Bx) == 0)
	{
			memcpy(xq, Ax, s);
			memcpy(yq, Ay, s);
			memcpy(xp, Bx, s);
			memcpy(yp, By, s);
	}
	else
	{
			memcpy(xq, Bx, s);
			memcpy(yq, By, s);
			memcpy(xp, Ax, s);
			memcpy(yp, Ay, s);
	}

	sub_u256(xp, xq, r0);
	inv_u256(r0, p, r1);
	sub_u256(p, yq, r2);
	add_u256_mod(yp, r2, r3);
	mul_u256_mod(r1, r3, m);

	memset(r, 0, s5);

	mul_u256_mod(m, m, r0);
	add_u256_mod(xq, xp, r1);
	sub_u256(p, r1, r3);
	add_u256_mod(r0, r3,xr);

	memset(r, 0, s5);

	sub_u256(p, xp, r0);
	add_u256_mod(xr, r0, r1);
	mul_u256_mod(r1, m, r2);
	add_u256_mod(r2, yp, r3);
	sub_u256(p, r3, yr);

	memcpy(Cx, xr, s);
	memcpy(Cy, yr, s);

#undef r0
#undef r1
#undef r2
#undef r3
#undef r4

return;
}

void secp256k1_init()
{
	memcpy(&Gx_data[0], Gx, s);
	memcpy(&Gy_data[0], Gy, s);

	for (uint64_t i = 1; i < key_length_bits; i++)	secp256k1_double(Gx_data[i - 1], Gy_data[i - 1], Gx_data[i], Gy_data[i]);
	return;
}

void secp256k1_publickey(uint64_t* k, uint64_t* Px, uint64_t* Py)
{
	memset(Px, 0, sizeof(uint64_t) * s);
	memset(Py, 0, sizeof(uint64_t) * s);

	bool first_add = true;
	for (uint64_t i = 0u; i < 4u; i++)
	{
		for (uint64_t j = 0u; j < 64u; j++)
		{
			if (((k[i] >> j) & 1u) == 1u)
			{
				uint64_t shift = i * 64u + j;
				if (first_add)
				{
					memcpy(Px, Gx_data[shift], s);
					memcpy(Py, Gy_data[shift], s);
					first_add = false;
				}
				else secp256k1_add(Px, Py, Gx_data[shift], Gy_data[shift], Px, Py);
			}
		}
	}
	return;
}