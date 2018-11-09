# [Fast Secure Multiparty ECDSA with Practical Distributed Key Generation and Applications to Cryptocurrency Custody]

based on paper

_Fast Secure Multiparty ECDSA with Practical
Distributed Key Generation and Applications to
Cryptocurrency Custody∗_

by Yehuda Lindelly, Ariel Nofy, Samuel Ranellucciz

## Protocol F_ECDSA

### Auiliary Input

- paramater: (__G__, G, q)

    curve params, generator, prime base.

- number of parties: `n`

### Key Generation

1. Pi sends (init; G; G; q) to F_mult to run the initialization phase.

    F_mult.init(E(G), G, q)

2. Pi sends (input; sidgen) to F_mult, and receives back (input; sidgen; xi). (Denote x = SUM(x_l) and Q = x · G.)

    `x_i` := F_mult.input(sid_gen)

3. Pi waits to receive (input; 0) to F_mult.

    await F_mult.input()

4. Pi sends (element-out; 0) to F_mult.

    F_mult.element-out(0)

5. Pi receives (element-out; 0; Q) from F_mult.

    `Q` := await F_mult.element-out(0)

6. Output: Pi locally stores Q as the ECDSA public-key.

    {x_i, Q} 

    where Q = [x]G, x = SUM(x_i)

- `F_mult`
    - init
    - input
    - element-out
    - affine
    - mult
