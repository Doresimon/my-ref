# Security Base

## Integer Factorization Problem (整数分解问题 IFP)

When the numbers are sufficiently large, no efficient, non-quantum integer factorization algorithm is known.

The hardest instances of these problems (for currently known techniques) are `semiprimes`, the product of two prime numbers.

```
p*q = N

已知 N

求N的素数分解 (p, q)
```

### use case

- `RSA`

## Discrete Logarithm Problem (离散对数问题 DLP)

However, no efficient method is known for computing them in general. Several important algorithms in public-key cryptography base their security on the **assumption that the discrete logarithm problem over carefully chosen groups has no efficient solution**.

```
g^s = h  mod q

已知 h, g, q

求 s
```

- `Elgamal`

## Elliptic curve discrete logarithm problem (椭圆曲线离散对数问题 ECDLP)

The security of elliptic curve cryptography depends on the ability to **compute a point multiplication and the inability to compute the multiplicand given the original and product points**. The size of the elliptic curve determines the difficulty of the problem.

```
[s]G = P

给定 P, G

求 s
```

### use case

- `ECDSA`
- `EdDSA`
