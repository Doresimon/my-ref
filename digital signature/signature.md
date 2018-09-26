# Signature Algorithms

# BLS
In cryptography, the Boneh–Lynn–Shacham (BLS) signature scheme allows a user to verify that a signer is authentic. The scheme uses a bilinear pairing for verification, and signatures are elements of an elliptic curve group. Working in an elliptic curve group provides some defense against index calculus attacks (with the caveat that such attacks are still possible in the target group GT of the pairing), allowing shorter signatures than FDH signatures for a similar level of security. Signatures produced by the BLS signature scheme are often referred to as short signatures, BLS short signatures, or simply BLS signatures. The signature scheme is provably secure (the scheme is existentially unforgeable under adaptive chosen-message attacks) assuming both the existence of random oracles and the intractability of the computational Diffie–Hellman problem in a gap Diffie–Hellman group.[1]
```
keywords:
    elliptic curve
    bilinear pairing
```
- [wiki-BLS](https://en.wikipedia.org/wiki/Boneh%E2%80%93Lynn%E2%80%93Shacham)



# FDH
In cryptography, the Full Domain Hash (FDH) is an RSA-based signature scheme that follows the hash-and-sign paradigm. It is provably secure (i.e., is existentially unforgeable under adaptive chosen-message attacks) in the random oracle model. FDH involves hashing a message using a function whose image size equals the size of the RSA modulus, and then raising the result to the secret RSA exponent.
- [wiki-FDH](https://en.wikipedia.org/wiki/Full_Domain_Hash)


# CLS
Camenisch-Lysyanskaya signature scheme (Crypto 2004)
* [paper](https://eprint.iacr.org/2012/562.pdf)
* [CL02b](https://groups.csail.mit.edu/cis/pubs/lysyanskaya/cl02b.pdf)

# ECDSA

# DSA

# EDDSA

# BBS

# BBS+