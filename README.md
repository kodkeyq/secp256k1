# Secp256k1 Library
This is an easy-to-use implementation of Secp256k1 cryptography, 
realized purely in C++. With this library, you can quickly create keypairs.

No OOP was used. To create new keypair just use secp256k1_publickey function.
The unusual part of the code was made just to speed up key generation.
WORKS ONLY WITH 64-Bit compilers that support SIMD instructions (_umul128). (Visual Studio 2019 was used).

Example:

uint64_t k[4] = {0x82ccd56528bbb843, 0xa84c30ee2d7202c9, 0xc14c7574488a98e1, 0x6946cc76445eed61};

uint64_t Px[4], Py[4];

secp256k1_publickey(k, Px, Py);

//Then print Px, Py to visualize your public point


