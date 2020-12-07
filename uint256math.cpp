#include "uint256math.h"

const uint64_t count = 4;
const uint64_t count_2 = 2 * count;
const uint64_t count_4 = 4 * count;

//variables used for mul_u256_mod
//static uint64_t p[5] = { 0xFFFFFFFEFFFFFC2F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF };
//static uint64_t mp[5] = { 0x2F00000000000000,0xFFFFFFFFFEFFFFFC,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0x00FFFFFFFFFFFFFF };//p << 48, p*m = p* 2^48//2^256 - p

uint64_t equalzero_u256(uint64_t* a)
{
	uint64_t zero = 0;
	if ((*a == 0) && (*(a+1) == 0) && (*(a+2) == 0) && (*(a+3) == 0)) zero = 1;
	return zero;
}

uint64_t equal_u256(uint64_t* a, uint64_t* b)
{
	uint64_t equal = 0;
	if ((*a == *b) && (*(a + 1) == *(b + 1)) && (*(a + 2) == *(b + 2)) && (*(a + 3) == *(b + 3))) equal = 1;
	return equal;
}

uint64_t equalone_u256(uint64_t* a)
{
	uint64_t one = 0;
	if ((*a == 1) && (*(a + 1) == 0) && (*(a + 2) == 0) && (*(a + 3) == 0)) one = 1;
	return one;
}

uint64_t more_u256(uint64_t* a, uint64_t* b)
{
	/*if ((*a != *b) && (*a > * b)) return 1;
	if ((*(a + 1) != *(b + 1)) && (*(a + 1) > * (b + 1))) return 1;
	if ((*(a + 2) != *(b + 2)) && (*(a + 2) > * (b + 2))) return 1;
	if ((*(a + 3) != *(b + 3)) && (*(a + 3) > * (b + 3))) return 1;

	return 0;*/

	uint64_t result = 0;
	for (int64_t i = 3; i >= 0; i--)
	{
		if (a[i] != b[i])
		{
			if (a[i] > b[i])	result = 1;
			break;
		}
	}
	return result;
}

void add_u256(uint64_t* a, uint64_t* b, uint64_t* c)
{
/*	uint64_t result;
	uint64_t carry;
	
	result = *a + *b;
	carry = (~(*a) < (*b));
	*c = result;

	result = *(a + 1) + *(b + 1) + carry;
	carry = ((~(*(a + 1)) == *(b + 1)) & carry) | (~(*(a + 1)) < *(b + 1));
	*(c + 1) = result;

	result = *(a + 2) + *(b + 2) + carry;
	carry = ((~(*(a + 2)) == *(b + 2)) & carry) | (~(*(a + 2)) < *(b + 2));
	*(c + 2) = result;

	*(c + 3) = *(a + 3) + *(b + 3) + carry;*/
	uint8_t carry = 0;
	carry = _addcarry_u64(carry, *a, *b, c);
	carry = _addcarry_u64(carry, *(a+1), *(b+1), c+1);
	carry = _addcarry_u64(carry, *(a+2), *(b+2), c+2);
	carry = _addcarry_u64(carry, *(a+3), *(b+3), c+3);

		
	return;
}

void add_u512(uint64_t* a, uint64_t* b, uint64_t* c)
{
/*	uint64_t result;
	uint64_t carry;

	result = *a + *b;
	carry = (~(*a) < (*b));
	*c = result;

	result = *(a + 1) + *(b + 1) + carry;
	carry = ((~(*(a + 1)) == *(b + 1)) & carry) | (~(*(a + 1)) < *(b + 1));
	*(c + 1) = result;


	result = *(a + 2) + *(b + 2) + carry;
	carry = ((~(*(a + 2)) == *(b + 2)) & carry) | (~(*(a + 2)) < *(b + 2));
	*(c + 2) = result;

	result = *(a + 3) + *(b + 3) + carry;
	carry = ((~(*(a + 3)) == *(b + 3)) & carry) | (~(*(a + 3)) < *(b + 3));
	*(c + 3) = result;

	result = *(a + 4) + *(b + 4) + carry;
	carry = ((~(*(a + 4)) == *(b + 4)) & carry) | (~(*(a + 4)) < *(b + 4));
	*(c + 4) = result;

	result = *(a + 5) + *(b + 5) + carry;
	carry = ((~(*(a + 5)) == *(b + 5)) & carry) | (~(*(a + 5)) < *(b + 5));
	*(c + 5) = result;

	result = *(a + 6) + *(b + 6) + carry;
	carry = ((~(*(a + 6)) == *(b + 6)) & carry) | (~(*(a + 6)) < *(b + 6));
	*(c + 6) = result;

	*(c + 7) = *(a + 7) + *(b + 7) + carry;*/

	uint8_t carry = 0;
	carry = _addcarry_u64(carry, *a, *b, c);
	carry = _addcarry_u64(carry, *(a + 1), *(b + 1), c + 1);
	carry = _addcarry_u64(carry, *(a + 2), *(b + 2), c + 2);
	carry = _addcarry_u64(carry, *(a + 3), *(b + 3), c + 3);
	carry = _addcarry_u64(carry, *(a + 4), *(b + 4), c + 4);
	carry = _addcarry_u64(carry, *(a + 5), *(b + 5), c + 5);
	carry = _addcarry_u64(carry, *(a + 6), *(b + 6), c + 6);
	carry = _addcarry_u64(carry, *(a + 7), *(b + 7), c + 7);

	return;
}

void add_u320(uint64_t* a, uint64_t* b, uint64_t* c)
{
/*	uint64_t result;
	uint64_t carry;

	result = *a + *b;
	carry = (~(*a) < (*b));
	*c = result;

	result = *(a + 1) + *(b + 1) + carry;
	carry = ((~(*(a + 1)) == *(b + 1)) & carry) | (~(*(a + 1)) < *(b + 1));
	*(c + 1) = result;

	result = *(a + 2) + *(b + 2) + carry;
	carry = ((~(*(a + 2)) == *(b + 2)) & carry) | (~(*(a + 2)) < *(b + 2));
	*(c + 2) = result;

	result = *(a + 3) + *(b + 3) + carry;
	carry = ((~(*(a + 3)) == *(b + 3)) & carry) | (~(*(a + 3)) < *(b + 3));
	*(c + 3) = result;

	*(c + 4) = *(a + 4) + *(b + 4) + carry;*/

	uint8_t carry = 0;
	carry = _addcarry_u64(carry, *a, *b, c);
	carry = _addcarry_u64(carry, *(a + 1), *(b + 1), c + 1);
	carry = _addcarry_u64(carry, *(a + 2), *(b + 2), c + 2);
	carry = _addcarry_u64(carry, *(a + 3), *(b + 3), c + 3);
	carry = _addcarry_u64(carry, *(a + 4), *(b + 4), c + 4);

	return;
}

void mul_u256_u64(uint64_t* a, uint64_t b, uint64_t* c)
{
	uint64_t z[count + 1] ;
	uint64_t w[count + 1];

	*(z + 4) = 0;
	*w = 0;

	*(z) = _umul128(*a, b, z + 1);
	*(z + 2) = _umul128(*(a + 2), b, z + 3);

	*(w + 1) = _umul128(*(a + 1), b, w + 2);
	*(w + 3) = _umul128(*(a + 3), b, w + 4);

	add_u320(z, w, c);

	return;
}

void sub_u256(uint64_t* a, uint64_t* b, uint64_t* c)
{
/*	uint64_t result;
	uint64_t carry;

	result = *a - *b;
	carry = (*a < *b);
	*c = result;

	result = *(a+1) - *(b+1) - carry;
	carry = (((*(a+1) == *(b+1)) & carry) | (*(a+1) < *(b+1)));
	*(c+1) = result;

	result = *(a+2) - *(b+2) - carry;
	carry = ((((*a+2) == *(b+2)) & carry) | (*(a+2) < *(b+2)));
	*(c+2) = result;

	*(c+3) = *(a+3) - *(b+3) - carry;*/

	uint8_t carry = 0;
	carry = _subborrow_u64(carry, *a, *b, c);
	carry = _subborrow_u64(carry, *(a + 1), *(b + 1), c + 1);
	carry = _subborrow_u64(carry, *(a + 2), *(b + 2), c + 2);
	carry = _subborrow_u64(carry, *(a + 3), *(b + 3), c + 3);

	return;
}

void sub_u320(uint64_t* a, uint64_t* b, uint64_t* c)
{
/*	uint64_t result;
	uint64_t carry;

	result = *a - *b;
	carry = (*a < *b);
	*c = result;

	result = *(a + 1) - *(b + 1) - carry;
	carry = (((*(a + 1) == *(b + 1)) & carry) | (*(a + 1) < *(b + 1)));
	*(c + 1) = result;

	result = *(a + 2) - *(b + 2) - carry;
	carry = ((((*a + 2) == *(b + 2)) & carry) | (*(a + 2) < *(b + 2)));
	*(c + 2) = result;

	result = *(a + 3) - *(b + 3) - carry;
	carry = ((((*a + 3) == *(b + 3)) & carry) | (*(a + 3) < *(b + 3)));
	*(c + 3) = result;

	*(c + 4) = *(a + 4) - *(b + 4) - carry;*/

	uint8_t carry = 0;
	carry = _subborrow_u64(carry, *a, *b, c);
	carry = _subborrow_u64(carry, *(a + 1), *(b + 1), c + 1);
	carry = _subborrow_u64(carry, *(a + 2), *(b + 2), c + 2);
	carry = _subborrow_u64(carry, *(a + 3), *(b + 3), c + 3);
	carry = _subborrow_u64(carry, *(a + 4), *(b + 4), c + 4);

	return;
}

void mul_u256(uint64_t* a, uint64_t* b, uint64_t* c)
{
	uint64_t z[count_2];
	uint64_t p_z[count_4];
	uint64_t z_size = sizeof(z);
	uint64_t p_z_size = sizeof(p_z);

	memset(z, 0, z_size);

	memset(p_z, 0, p_z_size);

	*(p_z) = _umul128(*a, *b, p_z + 1);
	*(p_z + 1 + count_2) = _umul128(*a, *(b + 1), p_z + 2 + count_2);
	*(p_z + 2) = _umul128(*a, *(b + 2), p_z + 3);
	*(p_z + 3 + count_2) = _umul128(*a, *(b + 3), p_z + 4 + count_2);

	add_u512(z, p_z, z);
	add_u512(z, p_z + count_2, z);
	memset(p_z, 0, p_z_size);

	*(p_z + 1) = _umul128(*(a + 1), *b, p_z + 1 + 1);
	*(p_z + 1 + count_2 + 1) = _umul128(*(a + 1), *(b + 1), p_z + 2 + count_2 + 1);
	*(p_z + 2 + 1) = _umul128(*(a + 1), *(b + 2), p_z + 3 + 1);
	*(p_z + 3 + count_2 + 1) = _umul128(*(a + 1), *(b + 3), p_z + 4 + count_2 + 1);

	add_u512(z, p_z, z);
	add_u512(z, p_z + count_2, z);
	memset(p_z, 0, p_z_size);

	*(p_z + 2) = _umul128(*(a + 2), *b, p_z + 1 + 2);
	*(p_z + 1 + count_2 + 2) = _umul128(*(a + 2), *(b + 1), p_z + 2 + count_2 + 2);
	*(p_z + 2 + 2) = _umul128(*(a + 2), *(b + 2), p_z + 3 + 2);
	*(p_z + 3 + count_2 + 2) = _umul128(*(a + 2), *(b + 3), p_z + 4 + count_2 + 2);

	add_u512(z, p_z, z);
	add_u512(z, p_z + count_2, z);
	memset(p_z, 0, p_z_size);

	*(p_z + 3) = _umul128(*(a + 3), *b, p_z + 1 + 3);
	*(p_z + 1 + count_2 + 3) = _umul128(*(a + 3), *(b + 1), p_z + 2 + count_2 + 3);
	*(p_z + 2 + 3) = _umul128(*(a + 3), *(b + 2), p_z + 3 + 3);
	*(p_z + 3 + count_2 + 3) = _umul128(*(a + 3), *(b + 3), p_z + 4 + count_2 + 3);

	add_u512(z, p_z, z);
	add_u512(z, p_z + count_2, z);

	memcpy(c, z, z_size);
	return;
}

void mul_u256_small(uint64_t* a, uint64_t* b, uint64_t* c)
{
	uint64_t z[8];
	uint64_t p_z[16];

	memset(z, 0, sizeof(z));

	for (uint64_t i = 0; i < 4; i++)
	{
		uint64_t x = *(a + i);
		if (x != 0)
		{
			memset(p_z, 0, sizeof(p_z));

			for (uint64_t j = 0; j < 4; j++)
			{

				uint64_t y = *(b + j);
				if (y != 0) *(p_z + 8 * (1 & j) + j + i) = _umul128(x, y, p_z + 8 * (1 & j) + j + i + 1);
			}

			add_u512(z, p_z, z);
			add_u512(z, p_z + 8, z);
		}
	}

	memcpy(c, z, sizeof(z) / 2);
	return;
}

void add_u256_mod(uint64_t* a, uint64_t* b, uint64_t* p, uint64_t* c)
{
/*	uint64_t result;
	uint64_t carry;

	result = *a + *b;
	carry = (~(*a) < (*b));
	*c = result;

	result = *(a + 1) + *(b + 1) + carry;
	carry = ((~(*(a + 1)) == *(b + 1)) & carry) | (~(*(a + 1)) < *(b + 1));
	*(c + 1) = result;

	result = *(a + 2) + *(b + 2) + carry;
	carry = ((~(*(a + 2)) == *(b + 2)) & carry) | (~(*(a + 2)) < *(b + 2));
	*(c + 2) = result;

	result = *(a + 3) + *(b + 3) + carry;
	carry = ((~(*(a + 3)) == *(b + 3)) & carry) | (~(*(a + 3)) < *(b + 3));
	*(c + 3) = result;*/

	uint8_t carry = 0;
	carry = _addcarry_u64(carry, *a, *b, c);
	carry = _addcarry_u64(carry, *(a + 1), *(b + 1), c + 1);
	carry = _addcarry_u64(carry, *(a + 2), *(b + 2), c + 2);
	carry = _addcarry_u64(carry, *(a + 3), *(b + 3), c + 3);

	carry = (~more_u256(p, c) | carry) & 1;
	if (carry == 1)	sub_u256(c, p, c);

	return;
}

void mul_u256_mod(uint64_t* a, uint64_t* b,uint64_t* p, uint64_t* c)
{
	const uint64_t r = 4294968273u;
	uint64_t z[8];
	uint64_t A[5];
	uint64_t B[5];
	uint64_t C[4];

	mul_u256(a, b, z);

	memcpy(B, z, sizeof(z) / 2);
	memcpy(A, z + 4, sizeof(z) / 2);

	*(A + 4) = 0;
	*(B + 4) = 0;

	if (more_u256(p, A) == 0) sub_u256(A, p, A);
	mul_u256_u64(A, r, A);
	add_u320(B, A, B);

	memset(A, 0, sizeof(A));
	memset(C, 0, sizeof(C));

	*A = *(B + 4);
	*(B + 4) = 0;

	*C = _umul128(r, *A, C + 1);
	add_u256_mod(C, B, p, c);

	return;
}

inline void shiftsub_u256(uint64_t* a, uint64_t* b, uint64_t* q, uint64_t* r)
{
	const uint64_t s = sizeof(uint64_t) * 4u;
//	const uint64_t c2_0 = 0x1u;
//	const uint64_t c2_1 = 0x2u;
//	const uint64_t c2_2 = 0x4u;
//	const uint64_t c2_4 = 0x10u;
//	const uint64_t c2_8 = 0x100u;
//	const uint64_t c2_16 = 0x10000u;
//	const uint64_t c2_32 = 0x100000000u;

	uint64_t i = 3u;
	uint64_t j = 3u;

	while (*(a + i) == 0u)	i--;
	while (*(b + j) == 0u)	j--;

/*	uint64_t l = *(a + i);
	uint64_t m = 0u;

	if (l >= c2_32) { l >>= 32; m += 32u; }
	if (l >= c2_16) { l >>= 16; m += 16u; }
	if (l >= c2_8) { l >>= 8; m += 8u; }
	if (l >= c2_4) { l >>= 4; m += 4u; }
	if (l >= c2_2) { l >>= 2; m += 2u; }
	if (l >= c2_1) { m += 1u; }

	uint64_t n = *(b + j);
	uint64_t o = 0u;
	if (n >= c2_32) { n >>= 32; o += 32u; }
	if (n >= c2_16) { n >>= 16; o += 16u; }
	if (n >= c2_8) { n >>= 8; o += 8u; }
	if (n >= c2_4) { n >>= 4; o += 4u; }
	if (n >= c2_2) { n >>= 2; o += 2u; }
	if (n >= c2_1) { o += 1u; }*/
	
	unsigned long m = 0u;
	unsigned long o = 0u;
	if (_BitScanReverse64(&m, *(a + i)) == 0)
	{
		m = 0u;
	}
	if (_BitScanReverse64(&o, *(b + j)) == 0)
	{
		o= 0u;
	}
	uint64_t k = 64u * i + (uint64_t)m;
	uint64_t x = 64u * j + (uint64_t)o;
	uint64_t q_in[4];
	uint64_t a_in[4];

	memset(q_in, 0u, s);
	memcpy(a_in, a, s);

	if (k >= x)
		{
			uint64_t b_in[4];
			memcpy(b_in, b, s);
			if (k > (x + 1u))
			{
				uint64_t y = (k - x - 1) / 64u;
				uint64_t t = (k - x - 1) % 64u;
				memmove(b_in + y, b_in, sizeof(uint64_t) * (4u - y));
				memset(b_in, 0, sizeof(uint64_t)*y);

			//	if (*q_in != 0) *(q_in + y) = 1u;

				if (t != 0)
				{
					*(b_in + 3) = (*(b_in + 3) << t) | (*(b_in + 2) >> (64 - t));
					*(b_in + 2) = (*(b_in + 2) << t) | (*(b_in + 1) >> (64 - t));
					*(b_in + 1) = (*(b_in + 1) << t) | (*b_in >> (64 - t));
					*b_in <<= t;
					//*(q_in+y) <<= t;
				}
				*(q_in + y) = (uint64_t)1u << t;

				sub_u256(a_in, b_in, a_in);
				uint64_t q_in_saved[4];
				memcpy(q_in_saved, q_in, s);
				while (more_u256(b_in, a_in) == 0)
				{
					sub_u256(a_in, b_in, a_in);
					add_u256(q_in, q_in_saved, q_in);
				}
			}
			else if (k <= (x + 1u))
			{
				if (more_u256(b_in, a_in) == 0)
				{
					uint64_t one[4] = { 1,0,0,0 };
					while (more_u256(b_in, a_in) == 0)
					{
						sub_u256(a_in, b_in, a_in);
						add_u256(q_in, one, q_in);
					}
				}

			}

		}
		else if (k < x)
		{
		//TODO EXPECTION HERE
		}

	memcpy(q, q_in, s);
	memcpy(r, a_in, s);

	return;
}

void div_u256(uint64_t* a, uint64_t* b, uint64_t* q, uint64_t* r)
{
	const uint64_t s = sizeof(uint64_t) * 4u;
	if ((*(a + 1) != 0) || (*(a + 2) != 0) || (*(a + 3) != 0) ||(*(b + 1) != 0) || (*(b + 2) != 0) || (*(b + 3) != 0))
	{
		uint64_t a_in[4];
		uint64_t b_in[4];
		uint64_t q_in[4];
		uint64_t hq_in[4];

		memcpy(b_in, b, s);
		memcpy(a_in, a, s);
		memset(q_in, 0, s);
		memset(hq_in, 0, s);

		for (uint64_t i = 0u; i < 16u; i++)
		{
			if ((more_u256(b_in, a_in) == 1))
			{
				*q_in = i;
				memcpy(r, a_in, s);
				memcpy(q, q_in, s);
				return;
			}
			sub_u256(a_in, b_in, a_in);
		}

		*q_in = 16u;

		while (more_u256(b_in, a_in) == 0)
		{
			shiftsub_u256(a_in, b_in, hq_in, a_in);
			add_u256(q_in, hq_in, q_in);
		}
		memcpy(q, q_in, s);
		memcpy(r, a_in, s);
	
	}
	else
	{
		uint64_t ain = *a;
		uint64_t bin = *b;
		memset(q, 0, s);
		memset(r, 0, s);
		*q = ain / bin;
		*r = ain % bin;
	}

	return;
}

void inv_u256(uint64_t* a, uint64_t* m, uint64_t* b)
{
	const uint64_t s = sizeof(uint64_t) * 4u;
	uint64_t a_in[4];
	uint64_t b_in[4];
	uint64_t x[4];
	uint64_t y[4];
	uint64_t q[4];
	uint64_t r[4];

	memset(x, 0, s);
	memset(y, 0, s);
	memset(q, 0, s);
	memset(r, 0, s);

	memcpy(a_in, a, s);
	memcpy(b_in, m, s);

	y[0] = 1;

	while (1)
	{
		if (equalone_u256(a_in) == 1)
		{
			memcpy(b, y, s);
			break;
		}
		div_u256(b_in, a_in, q, b_in);
		mul_u256_small(q, y, r);
		add_u256(x, r, x);
		if (equalone_u256(b_in) == 1)
		{
			sub_u256(m, x, b);
			break;
		}
		div_u256(a_in, b_in, q, a_in);
		mul_u256_small(q, x, r);
		add_u256(y, r, y);
	}

	return;
}
