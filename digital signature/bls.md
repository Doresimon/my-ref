# Boneh–Lynn–Shacham Signature Scheme

## Origin

[[BLS01]Short signatures from the Weil pairing](https://www.iacr.org/archive/asiacrypt2001/22480516.pdf)

[[BGSL03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps](http://crypto.stanford.edu/~dabo/papers/aggreg.pdf)

# [BLS01]Short signatures from the Weil pairing

## Assumption

- the existence of `random oracles`

- the intractability of the `computational Diffie–Hellman problem` in a `gap Diffie–Hellman group`

## Why pairing

A `gap group` is a group in which the `computational Diffie–Hellman problem`
is intractable but the `decisional Diffie–Hellman problem` can be efficiently solved.

## Public Parameter

1. `G1` and `G2` are two (multiplicative) cyclic groups of prime order `p`
2. `g1` is a generator of G1 and `g2` is a generator of G2
3. `f()` is a computable isomorphism from G2 to G1, with `f(g2) = g1`
4. `e` is a computable bilinear map `e : G1 × G2 ---> GT`
5. `H : {0; 1}∗ ---> G1`, random oracle
6.  `p` prime


## Scheme

### Key Generation

select a random integer x from `Zp`

```js
x  <--- $ --- [0, p-1]
```

`private key` = `x`

`public key` = `g2^x`

### Signing

`message` = `m`

`hash of message` = `h` = `H(m)`

`sig` = `σ`= `h^x`

### Verification

`e(σ, g2)` == `e(H(m), g2^x)`

(g2; v; h; σ) is a valid co-Diffie-Hellman tuple


# [BGSL03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps

## Scheme

### Key Generation

For a particular user, pick random x <---$--- Zp, and compute v = g2^x. The user’s
public key is v <-- G2. The user’s secret key is x <-- Zp.

`private key` = `x`

`public key` = `v` = `g2^x`

### Signing

For a particular user, given the secret key x and a message M <-- {0,1 }*, compute
h = H(M), where h <-- G1, and σ = h^x. The signature is σ <-- G1.

`sig` = `σ` = `h^x` = `H(M)^x`

### Verification

`e(σ, g2)` == `e(h, v)`

Given user’s public key v, a message M, and a signature σ, compute h = H(M);
accept if e(σ, g2) = e(h, v) holds.

### Aggregation

For the aggregating subset of users U ⊆ U, assign to each user an index i, ranging
from 1 to k = |U|. Each user ui 2 U provides a signature σi <--- G1 on a message Mi <--- {0, 1}*
of his choice. The messages Mi must all be distinct. Compute σ = MulAll(σi). The aggregate
signature is σ <-- G1.

`Aggregated Signatur` = `σ` = `MulAll(σi)`

### Aggregate Verifcation

We are given an aggregate signature σ <--- G1 for an aggregating subset
of users U, indexed as before, and are given the original messages Mi <--- {0, 1}∗ and public
keys vi <--- G2 for all users ui <--- U. To verify the aggregate signature σ,

1. ensure that the messages Mi are all distinct, and reject otherwise; and
2. compute hi = H(Mi) for 1 ≤ i ≤ k = |U|, and accept if e(σ; g2) = MulAll(e(hi; vi)) holds.

`e(σ; g2)` == `MulAll(e(hi; vi))` 