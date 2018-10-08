# Shamir's Secret Sharing

__Shamir's Secret Sharing__ is an algorithm in cryptography created by __Adi Shamir__. 
It is a form of secret sharing, where a secret is divided into parts, giving each participant its own unique part.

To reconstruct the original secret, a minimum number of parts is required. 
In the threshold scheme this number is less than the total number of parts. 
Otherwise all participants are needed to reconstruct the original secret.

## Scheme

### Preparation

secret is `s` = `a0`

threahold is `(k, n)`

create `f(x) = a0 + a1·x^1 + a2·x^2 + ... + a(k-1)·x^(k-1)`

where `a0 = s`, `a1,a2,...,a(k-1) <---$--- Zp`

calculate D(i) = (i, f(i))

where i is 1, 2, ... n

D(0) = (0, f(0)) is ths secret

send D(i) to each participant.

### Reconstruction

## [wiki](https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing)