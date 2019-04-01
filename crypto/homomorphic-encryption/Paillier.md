# Paillier Crypto System

[wiki](https://en.wikipedia.org/wiki/Paillier_cryptosystem)

[paper](http://120.52.51.16/www.cs.tau.ac.il/~fiat/crypt07/papers/Pai99pai.pdf)

author: `Pascal Paillier`

keywords: `asymmetric algorithm`, `n-th residue classes`, `homomorphic`

base on: `integer factorization`

## intro

### key generation

1. `p`, `q` <--\$-- large prime => gcd(pq, (p-1)(q-1))==1
2. `n` = `p` &middot; `q`
3. &lambda; = lcm(`p`-1,`q`-1)
4. g <--\$-- **Z**<sup>\*</sup><sub>N<sup>2</sup></sub>
5. &mu; = (L(g<sup>&lambda;</sup> mod n<sup>2</sup>))<sup>-1</sup> mod n
6. L(x) = (x-1)/n => the `quotient` of `a` divided by `b`
7. `pk` = (n, g)
8. `sk` = (&lambda;, &mu;)

notice: if `p` and `q` are equal in length, then can choose

- `g` = n + 1

- &lambda; = &phi;(n)

- &mu;
  = &phi;(n)<sup>-1</sup>
  = &lambda;<sup>-1</sup> mod n
  = (p-1) &middot; (q-1)

### encryption

1. @`msg` {String}
2. `m` = hash(msg) => [0, n)
3. `r` <--\$-- (0, n) and **Z**<sup>\*</sup><sub>N<sup>2</sup></sub>
4. `c` = g<sup>m</sup> &middot; r<sup>n</sup> mod n<sup>2</sup>

### decryption

1. @c => cipher
2. m = L(c<sup>&lambda;</sup> mod n<sup>2</sup>) &middot; &mu; mod n

### homomorphic

1. addition

   E(m<sub>1</sub>, r<sub>1</sub>) &middot; E(m<sub>2</sub>, r<sub>2</sub>) mod n<sup>2</sup>
   = (g<sup>m<sub>1</sub></sup> &middot; r<sub>1</sub><sup>n</sup>) &middot; (g<sup>m<sub>2</sub></sup> &middot; r<sub>2</sub><sup>n</sup>)
   = g<sup>(m<sub>1</sub> + m<sub>2</sub>)</sup> &middot; r<sub>1</sub><sup>n</sup> &middot; r<sub>2</sub><sup>n</sup>

2. multiplicationi of number(not cipher)

   E(m, r)<sup>k</sup> mod n<sup>2</sup>
   = (g<sup>m</sup> &middot; r<sup>n</sup>)<sup>k</sup>
   = g<sup>m &middot; k</sup> &middot; r<sup>n &middot; k</sup>
