# Boneh–Lynn–Shacham Signature Scheme

## Origin

[[BLS04]Short signatures from the Weil pairing](https://www.iacr.org/archive/asiacrypt2001/22480516.pdf)

[[BGSL03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps](http://crypto.stanford.edu/~dabo/papers/aggreg.pdf)

# [BLS04]Short signatures from the Weil pairing

## Assumption

- the existence of `random oracles`

- the intractability of the `computational Diffie–Hellman problem` in a `gap Diffie–Hellman group`

## Why pairing

A `gap group` is a group in which the `computational Diffie–Hellman problem`
is intractable but the `decisional Diffie–Hellman problem` can be efficiently solved.

## Scheme

### Key Generation

select a random integer x from `Zr`

```js
x  <--- $ --- [0, r-1]
```

`private key` = `x`

`public key` = `g^x`

### Signing

`message` = `m`

`hash of message` = `h` = `H(m)`

`sig` = `h^x`

### Verification

`e(sig, g)` == `e(H(m), g^x)`


# [BGSL03]Aggregate and Verifiably Encrypted Signatures from Bilinear Maps