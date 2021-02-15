#include "secp256k1class.h"

void Secp256k1::FillS()
{
	memset(S, 0u, sizeof(S));
	memcpy(S, &G, sizeof(G));

	for (uint64_t i = 1; i < 256u; i++)
	{
		S[i] = Double(*(S + i - 1u));
	}
}

point Secp256k1::Add(point A, point B)
{
	point C;
	uint256_t pin;
	uint64_t r[12];
	uint64_t* r0 = r;
	uint64_t* r1 = r + 4;
	uint64_t* r2 = r + 8;

	memset(&C, 0u, sizeof(C));
	memcpy(pin, p, sizeof(pin));
	memset(r, 0, sizeof(r));

	sub_u256(pin, B.x, r0);
	add_u256_mod(r0, A.x, pin, r0);
	inv_u256(r0, pin, r0);
	sub_u256(pin, B.y, r1);
	add_u256_mod(r1, A.y, pin, r1);
	mul_u256_mod(r0, r1, pin, r0);

	mul_u256_mod(r0, r0, pin, r1);
	add_u256_mod(A.x, B.x, pin, r2);
	sub_u256(pin, r2, r2);
	add_u256_mod(r1, r2, pin, C.x);

	sub_u256(pin, A.x, r1);
	add_u256_mod(C.x, r1, pin, r1);
	mul_u256_mod(r1, r0, pin, r1);
	add_u256_mod(r1, A.y, pin, r1);
	sub_u256(pin, r1, C.y);

	return C;
}

point Secp256k1::Double(point A)
{
	point B;
	uint256_t pin;
	uint64_t r[12];
	uint64_t* r0 = r;
	uint64_t* r1 = r + 4;
	uint64_t* r2 = r + 8;

	memset(&B, 0u, sizeof(B));
	memcpy(pin, p, sizeof(pin));
	memset(r, 0, sizeof(r));

	mul_u256_mod(A.x, A.x, pin, r0);
	add_u256_mod(r0, r0, pin, r1);
	add_u256_mod(r0, r1, pin, r1);
	add_u256_mod(A.y, A.y, pin, r0);
	inv_u256(r0, pin, r0);
	mul_u256_mod(r0, r1, pin, r0);

	mul_u256_mod(r0, r0, pin, r1);
	add_u256_mod(A.x, A.x, pin, r2);
	sub_u256(pin, r2, r2);
	add_u256_mod(r1, r2, pin, B.x);

	sub_u256(pin, A.x, r1);
	add_u256_mod(B.x, r1, pin, r1);
	mul_u256_mod(r1, r0, pin, r1);
	add_u256_mod(r1, A.y, pin, r1);
	sub_u256(pin, r1, B.y);

	return B;
}

point Secp256k1::PublicKey(uint256_t prik)
{
	point pubk;
	memset(&pubk, 0u, sizeof(pubk));
	for (uint64_t i = 0u; i < 4u; i++)
	{
		for (uint64_t j = 0u; j < 64u; j++)
		{
			if (((prik[i] >> j) & 1u) == 1u)
			{
				uint64_t shift = i * 64u + j;
				if ((equalzero_u256(pubk.x) == 1) && (equalzero_u256(pubk.y) == 1))
				{
					memcpy(&pubk, S + shift, sizeof(pubk));
				}
				else
				{
					pubk = Add(pubk, *(S + shift));
				}
			}
		}
	}
	return pubk;
}

Secp256k1::Secp256k1()
{
	FillS();
}


void Secp256k1::SetPrivateKey(uint64_t* k)
{
	memcpy(privatekey, k, sizeof(privatekey));
	publickeyp = PublicKey(privatekey);
}

void Secp256k1::SetIncrement(uint64_t* i)
{
	memcpy(inc, i, sizeof(inc));
	incp = PublicKey(inc);
}

void Secp256k1::Increment()
{
	add_u256(privatekey, inc, privatekey);
	if ((equal_u256(publickeyp.x, incp.x) == 1) && (equal_u256(publickeyp.y, incp.y) == 1))
	{
		publickeyp = Double(publickeyp);
	}
	else
	{
		publickeyp = Add(publickeyp, incp);
	}
}

point Secp256k1::ReturnPublic(uint64_t* k)
{
	point pubk;
	memset(&pubk, 0u, sizeof(pubk));
	for (uint64_t i = 0u; i < 4u; i++)
	{
		for (uint64_t j = 0u; j < 64u; j++)
		{
			if (((k[i] >> j) & 1u) == 1u)
			{
				uint64_t shift = i * 64u + j;
				if ((equalzero_u256(pubk.x) == 1) && (equalzero_u256(pubk.y) == 1))
				{
					memcpy(&pubk, S + shift, sizeof(pubk));
				}
				else
				{
					pubk = Add(pubk, *(S + shift));
				}
			}
		}
	}
	return pubk;
}

void Secp256k1::Get(uint64_t* k, uint64_t* px, uint64_t* py)
{
	memcpy(k, privatekey, sizeof(privatekey));
	memcpy(px, publickeyp.x, sizeof(publickeyp.x));
	memcpy(py, publickeyp.y, sizeof(publickeyp.y));
}