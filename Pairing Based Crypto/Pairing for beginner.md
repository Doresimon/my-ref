# a guide for Pairing

## basic concept

### `general Weierstrass equation`

<img src='./img/eb17808917afd2a3a6aff3cef321679.png'>

### `short Weierstrass equation`

<img src='./img/5588f6ee6f38d32c19c6694ff930f2e.png'>

### `Group Law`

<img src='./img/ce21f5500f00c6edad763296b9c7866.png'>


### `affine space`

equation: `E: y^2 = x^3 + a*x + b`

(x, y)

- add and double

<img src='./img/fe00247657cb7719b1699c061e86cc5.png'>

### `projective space`

equation: `Ep: Y^2*Z = X^3 + a*X*Z^2 + b*Z^3`

(X, Y, Z)

conversion:

(x, y) -> (X, Y, Z)

    (x, y) -> (x, y, 1)

(X, Y, Z) -> (x, y)

    (X, Y, Z) -> (X/Z, Y/Z)

- add: P + Q = R

<img src='./img/33c580a98ffd0b7f40fa78cc822b802.png'>


### `Jacob-quartic curve`

- equation:

J : v^2 = a*u^4 + d*u^2 + 1

- conversion:

E -> J:
(x, y) -> (U, V, W)

<img src='./img/98c450d2e382fc005e31b2f081bcd5d.png'>

J -> E:
(U, V, W) -> (x, y)

<img src='./img/812c3981f3356f6d07ad0c3e1a7755a.png'>

- add: P1 + P2 = P3

<img src='./img/72aab0389572860e5e0ce604b853f79.png'>

### other curves

`Edwards curves`

`Hessian curves`

`Montgoemry curves`
