# Boneh–Lynn–Shacham Signature Scheme

## Origin

[[BLS01]Short signatures from the Weil pairing](https://www.iacr.org/archive/asiacrypt2001/22480516.pdf)

[[BGLS03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps](http://crypto.stanford.edu/~dabo/papers/aggreg.pdf)

[[ABLS18]BLS Multi-Signatures With Public-Key Aggregation](https://crypto.stanford.edu/~dabo/pubs/papers/BLSmultisig.html)

[[full version] Compact Multi-Signatures for Smaller Blockchains](https://eprint.iacr.org/2018/483.pdf)

# [[BLS01]Short signatures from the Weil pairing](https://www.iacr.org/archive/asiacrypt2001/22480516.pdf)

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
6. `p` prime

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

(g2, v, h, σ) is a valid co-Diffie-Hellman tuple

# [[BGLS03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps](http://crypto.stanford.edu/~dabo/papers/aggreg.pdf)

## Scheme

### Key Generation

For a particular user, pick random x <---\$--- Zp, and compute v = g2^x. The user’s
public key is v <-- G2. The user’s secret key is x <-- Zp.

- `private key` = `x`

- `public key` = `v` = `g2^x`

### Signing

For a particular user, given the secret key x and a message M <-- {0,1 }\*, compute
h = H(M), where h <-- G1, and σ = h^x. The signature is σ <-- G1.

- `sig` = `σ` = `h^x` = `H(M)^x`

### Verification

Given user’s public key v, a message M, and a signature σ, compute h = H(M);
accept if e(σ, g2) = e(h, v) holds.

- `e(σ, g2)` == `e(h, v)`

### Aggregation

For the aggregating subset of users U ⊆ U, assign to each user an index i, ranging
from 1 to k = |U|. Each user ui 2 U provides a signature σi <--- G1 on a message Mi <--- {0, 1}\*
of his choice. The messages Mi must all be distinct. Compute σ = MulAll(σi). The aggregate
signature is σ <-- G1.

- `Aggregated Signature` = `σ` = `MulAll(σi)`

### Aggregate Verifcation

We are given an aggregate signature σ <--- G1 for an aggregating subset
of users U, indexed as before, and are given the original messages Mi <--- {0, 1}∗ and public
keys vi <--- G2 for all users ui <--- U. To verify the aggregate signature σ,

1. ensure that the messages Mi are all distinct, and reject otherwise; and
2. compute hi = H(Mi) for 1 ≤ i ≤ k = |U|, and accept if e(σ, g2) = MulAll(e(hi, vi)) holds.

- `e(σ, g2)` == `MulAll(e(hi, vi))` == &prod;e(h, vi) == e(h, &prod;vi)

## attack

if A wants to fake a signature of B,
A generates skA, then generates pkA = g^skA \* pkB^(-1).
when aggregating verification running,

- &prod;e(h, vi) = e(h, v0 &middot; v1 ... &middot; (g<sup>sk<sub>A</sub></sup> &middot; g<sup>-sk<sub>B</sub></sup>) )
- e(σ, g2) = e(∏σ<sub>i</sub>, g<sub>2</sub>) ==> notice, there is no B's sig, the verification can pass.

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

**Key Generation.** KeyGen and AdjKeyGen are the same as KeyGen in the co-GDH signature
scheme.

**Signing, Verification.** Sign and Verify are the same as in the co-GDH signature scheme.

**VESig Creation.** Given a secret key `x <--- Zp`, a message `M <--- {0, 1}*`, and an adjudicator’s public
key `v' <--- G2`, compute `h = H(M)`, where `h <--- G1`, and `σ = h^x`. Select r at random from Zp
and set `µ = f(g2)^r`and `σ' = f(v')^r`. Aggregate σ and σ' as `w = σ·σ' <--- G1`. The verifiably
encrypted signature is the pair `(w, µ)`. (This can also be viewed as ElGamal encryption of σ
under the adjudicator’s key.)

**VESig Verification.** Given a public key v, a message M, an adjudicator’s public key v', and a
verifiably encrypted signature (w, µ), set h H(M); accept if e(w, g2) = e(h, v) · e(µ, v')
holds.

**Adjudication.** Given an adjudicator’s public key v' and corresponding private key `x' <--- Zp`, a
certified public key `v`, and a verifiably encrypted signature `(w, µ)` on some message `M`, ensure
that the verifiably encrypted signature is valid; then output `σ = w/µ^x'`.

# [[ABLS18] BLS Multi-Signatures With Public-Key Aggregation](https://crypto.stanford.edu/~dabo/pubs/papers/BLSmultisig.html)

based on bls aggregate signature, just when m1...mi are the same.

## public parameter

- `H0(m1, m2, ... mn)` a hash function that map M^n ---> R^n, where R^n = {1, 2, ... 2^n}

## Scheme

### Key Generation

For a particular user, pick random x <---\$--- Zp, and compute v = g2^x. The user’s
public key is v <-- G2. The user’s secret key is x <-- Zp.

- `private key` = `x`

- `public key` = `v` = `g2^x`

### Signing

For a particular user, given the secret key x and a message M <-- {0,1 }\*, compute
h = H(M), where h <-- G1, and σ = h^x. The signature is σ <-- G1.

- `sig` = `σ` = `h^x` = `H(M)^x`

### Verification

- `e(σ, g2)` == `e(h, v)`

Given user’s public key v, a message M, and a signature σ, compute h = H(M);
accept if e(σ, g2) = e(h, v) holds.

### Aggregation

~~For the aggregating subset of users U ⊆ U, assign to each user an index i, ranging
from 1 to k = |U|. Each user ui 2 U provides a signature σi <--- G1 on a message Mi <--- {0, 1}\*
of his choice. The messages Mi must all be distinct. Compute σ = MulAll(σi). The aggregate
signature is σ <-- G1.~~

~~`Aggregated Signature` = `σ` = `MulAll(σi)`~~

1. compute `(t1, t2 ... tn)` = `H0(pk1, pk2, ... pkn) <--- R^n`
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

# [[full version] Compact Multi-Signatures for Smaller Blockchains](https://eprint.iacr.org/2018/483.pdf)

define a multisignature scheme as algorithms `Pg`, `Kg`, `Sign`, `KAg`, and `Vf`.
A trusted party generates the system parameters par Pg. Every signer generates a key pair
`(pk, sk)` <---\$--- `Kg(par)`, and signers can collectively sign a message m by each calling
the interactive algorithm `Sign(par, PK, sk, m)`, where PK is the set of the public
keys of the signers, and sk is the signer’s individual secret key. At the end of the
protocol, every signer outputs a signature `σ`. Algorithm `KAg` on input a set of
public keys `PK` outputs a single aggregate public key `apk`. A verifier can check
the validity of a signature `σ` on message `m` under an aggregate public key `apk` by
running `Vf(par, apk, m, σ)` which outputs 0 or 1 indicating that the signatures
is invalid or valid, respectively.

More precisely, we extend the definition of multisignatures
with two algorithms. `SAg` takes input a set of tuples, each tuple containing an
aggregate public key `apk`, a message `m`, and a multisignature `σ`, and outputs
a single aggregate multisignature `Σ`. `AVf` takes input a set of tuples,
each tuple containing an aggregate public key `apk` and a message `m`, and an aggregate
multisignature `Σ`, and outputs 0 or 1 indicating that the aggregate multisignatures is
invalid or valid, respectively. Observe that any multisignature scheme
can be transformed into an aggregate multisignature scheme in a trivial manner,
by implementing `SAg(par, fapk i, mi, σig)` to output `Σ (σ1,.., σn)`, and
`AVf(par, {apki, mi}, (σ1,..., σn))` to output 1 if all individual multisignatures
are valid. The goal however is to have `Σ` much smaller than the concatenation
of the individual multisignatures, and ideally of constant size.

## Public Key Aggregate Signature

Our pairing-based multi-signature with `public-key aggregation` `MSP` is built from
the BLS signature scheme [13]. The scheme is secure in the plain public key
model, and assumes hash functions H0: {0, 1}∗ <--- G2 and H1: {0, 1}∗ <--- Zq.

`Parameters Generation.`
Pg(κ) sets up bilinear group (q, G1, G2, Gt, e, g1, g2)
G(κ) and outputs `par` = `(q, G1, G2, Gt, e, g1, g2)`.

`Key Generation.`
The key generation algorithm Kg(par) chooses `sk <---$--- Zq`,
computes `pk` = `g2^sk`, and outputs `(pk, sk)`.

`Key Aggregation.`

```js
// KAg({pk1, pk2, ..., pkn}) outputs
apk <--- MulAll(pki^(H1(pki,{pk1,pk2...pkn})))
```

`Signing.`
Signing is a single round protocol. `Sign(par, {pk1, ..., pkn}, ski, m)`
computes `si` <--- `H0(m)^ai·ski`, where `ai = H1(pki, {pk1, pk2 ... pkn})`. Send `si` to a
designated combiner who computes the final signature as `σ = MulAll(sj)`. This
designated combiner can be one of the signers or it can be an external party.

`Multi-Signature Verification.`

```js
// Vf(par, apk, m, σ) outputs 1 iff
e(σ, g2^(−1)) · e(H0(m), apk) ?= O
```

`Batch verification.`
We note that a set of b multi-signatures can be verified as
a batch faster than verifying them one by one. To see how, suppose we are given
triples `(mi, σi, apki)` for i = 1,...,b, where apk i is the aggregated public-key
used to verify the multi-signature `σi` on `mi`. If all the messages m1,...,mb are
distinct then we can use signature aggregation as in (1) to verify all these triples
as a batch:

- Compute an aggregate signature `~σ = σ1 · σ2 · ... · σb` <--- G1,
- Accept all b multi-signature tuples as valid iff

  `e(~σ, g2) == e(H0(m1), apk1) · e(H0(m2), apk2) · ... · e(H0(mn), apkn)`

This way, verifying the b multi-signatures requires only b+1 pairings instead
of 2b pairings to verify them one by one. This simple batching procedure can
only be used when all the messages `m1, ..., mb` are distinct. If some messages
are repeated then batch verification can be done by first choosing random exponents
`ρ1,...,ρb <---$---{1,...,2^κ}`, where κ is a security parameter, computing
`~σ = σ1^ρ1 · σ2^ρ2 · ... · σb^ρb` <--- G2, and checking that

`e(~σ, g2) ?= e(H0(m1), apk^ρ1)·...·e(H0(mb),apkb^ρb)`

Of course the pairings on the right hand side can be coalesced for repeated
messages.

## Signature Aggregate Scheme (based on public key aggregate signature)

`Signing.`

Sign(par, _PK_, ski, m) computes `si = H(apk, m)^(ai·ski)`, where apk = KAg(par, _PK_)
and `ai = H0(pki, {pk1,...,pkn})`. The designated combiner collect all signatures si and computes
the final signature

```js
σ = MullAll(sj);
```

_PK_ is public key set of all signers.

`Multi-Signature Verification.`

```js
// Vf(par, apk, m, σ) outputs 1 if and only if
e(σ, g2^(−1)) · e(H(apk, m), apk) ?= O
```

`Signature Aggregation.`

```js
// SAg(par, {(apk1, m1, σ1)},...,{(apkn, mn, σn)}) outputs
Σ = MulAll(σi);
```

`Aggregate Signature Verification.`

```js
// AVf({(apki, mi)}, Σ) outputs 1 if and only if
e(Σ; g2^(−1)) · MullAll(e(H(apki, mi), apki)) ?= (O of Gt).
```

## Accountable-Subgroup Multisignatures

Micali, Ohta, and Reyzin [38] defined an accountable-subgroup multisignature
scheme as a multisignature scheme where any subset `S` of a group of signers PK
can create a valid multisignature that can be verified against the public keys of
signers in the subset. An `ASM` scheme can be combined with an arbitrary access
structure over PK to determine whether the subset S is authorized to sign on
behalf of PK. For example, requiring that `|S| ≥ t` turns the `ASM` scheme into a
type of threshold signature scheme whereby the signature also authenticates the
set of signers that participated.
