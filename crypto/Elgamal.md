# ElGamal Encryption System

@auther `Taher Elgamal`

@keywords `Asymmetric`, `public key`, `DHE`

@based on: `DLP`

## Encryption

### Key Generation

- params
  - `G`: cyclic group
  - `p`: order
  - `g`: generator
- sk
  - `x` :\$= [1, p - 1]
- pk
  - `h` := g<sup>x</sup>
- publish
  - (h, (G, p, g))

### Encryption

Bob wants to encrypt message `msg` to Alice under her pk `(h, (G, p, g))`

- sk
  - `y` :\$= [1, p - 1]
- pk
  - `c1` := g<sup>y</sup>
- share
  - `s` := h<sup>y</sup> := g<sup>x &middot; y</sup>
- message
  - `m` := map_to_G(`msg`)
- cipher
  - `c2` := m &middot; s
- send
  - (`c1`, `c2`)

### Decryption

Alice wants to Decrypt `(c1, c2)` with her sk `x`

- share
  - `s` := c1<sup>x</sup> = (g<sup>y</sup>)<sup>x</sup> = g<sup>x &middot; y</sup>
- message
  - `m` = c2 &middot; s <sup>-1</sup>
  - `msg` = unmap(`m`)

### Alternative Decryption (without Exponent)

- share

  - `s'` := c1<sup>(p - 1 - x)</sup>

    = g<sup>(p - 1 - x) &middot; y</sup>

- message

  - `m` := c2 &middot; s'

    = m &middot; s &middot; s'

    = m &middot; g<sup>x &middot; y</sup> &middot; g<sup>(p - 1 - x) &middot; y</sup>

    = m &middot; g <sup>(p - 1) &middot; y</sup>

    = m &middot; e <sup>y</sup>

    = m

  - `e` is identity element of G

## Signature

### Key Generation

- params
  - H := collision-resistant hash funtion
  - G := Group
  - p := order of Group G, large prime
  - g := generator
- sk
  - x :\$= [1, p - 2]
- pk
  - h := g^x mod p

### Sign

sign a message `m`

- randomness
  - `k` :\$= (1, p - 1)
  - gcd(k, p - 1) == 1 ==> make sure k<sup>-1</sup> exist.
  - `r` = g<sup>k</sup> mod (p-1)
- signature
  - `s` = (H(m) - `x` &middot; `r`) &middot; k<sup>-1</sup> mod (p-1)
  - if s==0, retry
- &sigma; = (r, s)

### Verify

with &sigma; = `(r, s)` and message `m`

- 0 < r < p
- 0 < s < p - 1
- g<sup>H(m)</sup> == h<sup>r</sup> &middot; r<sup>s</sup>
