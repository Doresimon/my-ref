# Boneh–Lynn–Shacham Signature Scheme

## Origin

[[BLS01]Short signatures from the Weil pairing](https://www.iacr.org/archive/asiacrypt2001/22480516.pdf)

[[BGLS03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps](http://crypto.stanford.edu/~dabo/papers/aggreg.pdf)

[[ABLS18]BLS Multi-Signatures With Public-Key Aggregation](https://crypto.stanford.edu/~dabo/pubs/papers/BLSmultisig.html)

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


# [BGLS03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps

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

`Aggregated Signature` = `σ` = `MulAll(σi)`

### Aggregate Verifcation

We are given an aggregate signature σ <--- G1 for an aggregating subset
of users U, indexed as before, and are given the original messages Mi <--- {0, 1}∗ and public
keys vi <--- G2 for all users ui <--- U. To verify the aggregate signature σ,

1. ensure that the messages Mi are all distinct, and reject otherwise; and
2. compute hi = H(Mi) for 1 ≤ i ≤ k = |U|, and accept if e(σ, g2) = MulAll(e(hi, vi)) holds.

`e(σ, g2)` == `MulAll(e(hi, vi))` 

## Application

### Verifiably Encrypted Signatures

"
Next, we show an application of aggregate signatures to `verifiably encrypted signatures`. Verifiably
encrypted signatures are used in applications such as `online contract signing`. Suppose Alice
wants to show Bob that she has signed a message, but does not want Bob to possess her signature
of that message. (Alice will give her signature to Bob only when a certain event has occurred, e.g.,
Bob has given Alice his signature on the same message.) Alice can achieve this by encrypting her
signature using the public key of a trusted third party, and sending this to Bob along with a proof
that she has given him a valid encryption of her signature. Bob can verify that Alice has signed the
message, but cannot deduce any information about her signature. Later in the protocol, if Alice is
unable or unwilling to reveal her signature, Bob can ask the third party to reveal Alice’s signature.
"

### Verifiably Encrypted Signatures via Aggregation

1. Alice wishes to create a verifiably encrypted signature, which Bob will verify; Carol is the adjudicator. Alice and Carol’s keys are both generated under the underlying signature scheme’s
key-generation algorithm.
2. Alice creates a signature `σ` on `M` under her public key. She forges a signature `σ'` on some
random message `M'` under Carol’s public key. She then combines `σ` and `σ'`, obtaining an
aggregate `w`. The verifiably encrypted signature is the pair `(w, M')`.
3. Bob validates Alice’s verifiably encrypted signature (w, M') on M by checking that w is a
valid aggregate signature by Alice on M and by Carol on M'.
4. Carol adjudicates, given a verifiably encrypted signature (w, M') on M by Alice, by computing
a signature σ' on M' under her key, and removing σ' from the aggregate; what remains is
Alice’s ordinary signature σ.

### The Bilinear Verifiably-Encrypted Signature Scheme

The bilinear verifiably encrypted signature scheme is built on the bilinear aggregate signature
scheme of the previous section. It shares the key-generation algorithm with the underlying aggregate
scheme. Moreover, the adjudicator’s public and private information is simply an aggregate-signature
keypair. The scheme comprises the seven algorithms described below:

__Key Generation.__ KeyGen and AdjKeyGen are the same as KeyGen in the co-GDH signature
scheme.

__Signing, Verification.__ Sign and Verify are the same as in the co-GDH signature scheme.

__VESig Creation.__ Given a secret key `x <--- Zp`, a message `M <--- {0, 1}*`, and an adjudicator’s public
key `v' <--- G2`, compute `h = H(M)`, where `h <--- G1`, and `σ = h^x`. Select r at random from Zp
and set `µ = f(g2)^r `and `σ' = f(v')^r`. Aggregate σ and σ' as `w = σ·σ' <--- G1`. The verifiably
encrypted signature is the pair `(w, µ)`. (This can also be viewed as ElGamal encryption of σ
under the adjudicator’s key.)

__VESig Verification.__ Given a public key v, a message M, an adjudicator’s public key v', and a
verifiably encrypted signature (w, µ), set h H(M); accept if e(w, g2) = e(h, v) · e(µ, v')
holds.

__Adjudication.__ Given an adjudicator’s public key v' and corresponding private key `x' <--- Zp`, a
certified public key `v`, and a verifiably encrypted signature `(w, µ)` on some message `M`, ensure
that the verifiably encrypted signature is valid; then output `σ = w/µ^x'`.

# [[ABLS18] BLS Multi-Signatures With Public-Key Aggregation](https://crypto.stanford.edu/~dabo/pubs/papers/BLSmultisig.html)

based on bls aggregate signature, just when m1...mi are the same. 

## public parameter

`H0(m1, m2, ... mn)` a hash function that map M^n ---> R^n, where R^n = {1, 2, ... 2^n}

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

~~For the aggregating subset of users U ⊆ U, assign to each user an index i, ranging
from 1 to k = |U|. Each user ui 2 U provides a signature σi <--- G1 on a message Mi <--- {0, 1}*
of his choice. The messages Mi must all be distinct. Compute σ = MulAll(σi). The aggregate
signature is σ <-- G1.~~

~~`Aggregated Signature` = `σ` = `MulAll(σi)`~~

1. compute `(t1, t2 ... tn)` = `H0(pk1, pk2, ... pkn) <---  R^n`
2. compute `σ` = `MulAll(σi^ti)` = `σ1^t1 · σ2^t2 · ... · σn^tn`

### Aggregate Verification

~~We are given an aggregate signature σ <--- G1 for an aggregating subset
of users U, indexed as before, and are given the original messages Mi <--- {0, 1}∗ and public
keys vi <--- G2 for all users ui <--- U. To verify the aggregate signature σ,~~

1. ~~ensure that the messages Mi are all distinct, and reject otherwise; and~~
2. ~~compute hi = H(Mi) for 1 ≤ i ≤ k = |U|, and accept if e(σ, g2) = MulAll(e(hi, vi)) holds.~~

~~`e(σ, g2)` == `MulAll(e(hi, vi))`~~

1. compute `(t1, t2 ... tn)` = `H0(pk1, pk2, ... pkn)`
2. compute aggregated public key `apk` = `pk1^t1 · pk2^t2 · ... · pkn^tn`

`e(g1, σ)` == `e(apk, H(m))`