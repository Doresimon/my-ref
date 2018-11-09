# SM2

## Digital Signature Algorithm

### Sign

@input

- `M` message
- `ENTL` length of uid
- `ID` uid of signer
- `sk` secret key
- `pk` public key, pk = [sk]*g
- `PARAM` {a, b, g, n, p}

@process

- `Z` = H256(ENTL || ID || a || b || g.x || g.y || pk.x || pk.y) # hash to 256 bits
- `_M` = Z || M
- `e` = Hv(_M)  # hash to scalar number
- `k` = $[1, n-1] # generatea random number
- `P` = (x, y) = [k]*g
- `r` = (e+x) % n # if r==0 or r+k==n, replay
- `s` = ((1+sk)^(-1) * (k-r*sk)) % n
- `SIG` = (r, s)

@output

`SIG` = (r, s)

### Verify

@input

- `M`
- `SIG` = (r, s)
- `Z` # Z=H256(...), unique for Signer
- `PARAM`

@Process

- check if r in [1, n-1]
- check if s in [1, n-1]
- `_M` = Z || M
- `e` = Hv(_M)
- `t` = r + s
- `P` = (x, y) = [s] * g + [t] * P
- `R` = e + x
- check if t != 0
- check if R == r

@output

- `true` iff all check return true
- `false` any check return false



## Key Exchange Protocol

## Public Key Encryption