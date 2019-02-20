# Simple Schnorr Multi-Signatures with Applications to Bitcoin

## Scheme `MuSig`

-   Group Parameter: (**G**,_p_,_g_)

    -   _`p`_ : _k_-bit big number.
    -   **`G`** : Group of order _`p`_.
    -   _`g`_ : generator of **`G`**.

-   hash funtions: {0,1}<sup>\*</sup> => {0,1}<sup>_l_</sup>

    -   H<sub>com</sub>
    -   H<sub>agg</sub>
    -   H<sub>sig</sub>

-   Key Generation

    -   each signer generates a random private key
    -   _`x`_ : _`x`_ <-\$- **Z**<sub>_p_</sub>
    -   compute public key
    -   _`X`_ : _`X`_ = _g_<sup>_x_</sup>

-   Signing

    -   master public key
        -   _`L`_ = {_X_<sub>1</sub>, _X_<sub>2</sub>, ... , _X_<sub>n</sub>}
        -   for _i_ in _n_
        -   _`a`_<sub>i</sub> = H<sub>agg</sub>(_L_, _X_<sub>i</sub>)
        -   aggregate public key
        -   **X** = **&prod;** _X_<sub>_i_</sub><sup>_a_<sub>_i_</sub></sup>
    -   randomness
        -   each signer generates a random big number `r`
        -   _`r`_ : _`r`_ <-\$- **Z**<sub>_p_</sub>
        -   compute `R`
        -   _`R`_ : _`R`_ = _g_<sup>_r_</sup>
        -   compute `t`
        -   _`t`_ : _`t`_ = H<sub>com</sub>(_R_)
    -   【ROUND1】
        -   brodcast _`t`_
        -   receive all _`t`_ from others
    -   【ROUND2】
        -   brodcast _`R`_
        -   receive all _`R`_ from others
    -   check
        -   _`t`_<sub>_i_</sub> == H<sub>com</sub>(_`R`_<sub>_i_</sub>)
    -   master Randomness & Challenge
        -   **R** = **&prod;** _R_<sub>_i_</sub>
        -   **c** = H<sub>sig</sub>(**X**,**R**, _m_)
    -   small _`s`_
        -   _`s`_ = _`r`_ + **c** &middot; _`a`_ &middot; _`x`_ mod _`p`_
    -   【ROUND3】
        -   brodcast _`s`_
        -   receive all _`s`_ from others
    -   master _`s`_
        -   **s** = **&sum;** _s_<sub>_i_</sub> mod _p_
    -   master signature
        -   **&sigma;** = (**R**, **s**)

-   Verification
    -   Given
        -   _`L`_ = {_X_<sub>1</sub>, _X_<sub>2</sub>, ... , _X_<sub>n</sub>}
        -   _`m`_ => message
        -   **&sigma;** = (**R**, **s**)
    -   Compute
        -   _`a`_<sub>i</sub> = H<sub>agg</sub>(_L_, _X_<sub>i</sub>)
        -   **X** = **&prod;** _X_<sub>_i_</sub><sup>_a_<sub>_i_</sub></sup>
        -   **c** = H<sub>sig</sub>(**X**,**R**, _m_)
    -   verify
        -   g<sup>**s**</sup> == **R** &middot; **X**<sup>**c**</sup>
