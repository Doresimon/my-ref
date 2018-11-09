#  Zero-Knowledge Succinct Non-interactive ARgument of Knowledge (zkSNARKS)

### [lib snark github](https://github.com/scipr-lab/libsnark.git)

### [What is zk-SNARKs? An Introduction to this Privacy Protocol](https://blockonomi.com/zk-snarks-privacy/)

### [Non-interactive zero-knowledge proof](https://en.wikipedia.org/wiki/Non-interactive_zero-knowledge_proof)

## Vitalik Burterin's posts x 3

### 1. [Quadratic Arithmetic Programs: from Zero to Hero - Vitalik Burterin](https://medium.com/@VitalikButerin/quadratic-arithmetic-programs-from-zero-to-hero-f6d558cea649)

### 2. [Exploring Elliptic Curve Pairings - Vitalik Burterin](https://medium.com/@VitalikButerin/exploring-elliptic-curve-pairings-c73c1864e627)

### 3. [Zk-SNARKs: Under the Hood - Vitalik Burterin](https://medium.com/@VitalikButerin/zk-snarks-under-the-hood-b33151a013f6)

## a good article in chinese

[零知识证明与zkSNARK](https://www.jianshu.com/p/b6a14c472cc1)


## [Arithmetic circuit complexity](https://en.wikipedia.org/wiki/Arithmetic_circuit_complexity)

## tool chains around libSNARK

### [snarky](https://github.com/o1-labs/snarky)
in `caml` language.
[O1 lab official site](https://o1labs.org/)

### [snarklib](https://github.com/jancarlsson/snarklib)
a more clear implentation of zksnark changed from libsnark.
### [snarkfront](https://github.com/jancarlsson/snarkfront)
a C++ embedded domain specific language for zero knowledge proofs
### [ZoKrates](https://github.com/JacobEberhardt/ZoKrates)
a toolbox for zkSNARKS on **Ethereum** (`Rust`). In this repo, author implent a tool to convert verification function to **smart contract** for Ethereum in solidity language. The proof can be published and every one can verify.



## some knowledge from internet

### [an introduction in Chinese.](https://blockchain.iethpay.com/zero-knowledge-zkSNARKs.html)

## constructions of some constraints in R1CS format.

1. Mul
> out = in1 * in2

> `in1` * `in2` = `out`

2. Or
> out = in1 | in2

> `in1` * `in2` = `in1` + `in2` - `out`

3. Xor
> out = in1 ^ in2

> 2 * `in1` * `in2` = `in1` + `in2` - `out`

4. Split(Unpack)
> out[i] = BitOf(in, i)

> 1 * `in` = __SUM__( `out[i]` * (2^i) )

5. Pack
> out = SUM(in[i]*2^i)

> 1 * __SUM__( `in[i]` * (2^i) ) = `out`
