# a short introduction for `R1CS`



## 1. Simple Process

a picture from **Vitarlik**

![function to zksnark](img/process.png)

* **Computation**

      function add(x,y){
        z = x + y
        return z
      }

      function poly(x){
        z = 3 + 2*x + 5*x^2
        return z
      }

* **Algebraic Circuit**

      ## `add` doesn't need to change.
      ## solution:: [1, x, y, z]
      function add(x,y){
        z = x + y
        return z
      }

      ## `poly` needs to be exploded
      ## solution:: [1, x, t, t1, t2, z]
      function poly(x){
        t  = x * x
        t1 = 2 * x
        t2 = 5 * t
        z  = 3 + t1 + t2
        return z
      }
      ## if x is 2, solution is [1, 2, 4, 4, 20, 27],
      ## which means z = 3 + 2*x + 5*x^2 is equal if x = 2 and z = 27.

  keywords: `wire` `gate` `constant wire` `...`

  **wire**:

  for function __poly()__, __[1, x, t, t1, t2, z]__ are all wires. __'1'__ is a constant wire, __'x'__ is an input wire, __'t, t1, t2'__ are internal wire and __'z'__ is output wire.

  **gate**

  for function __poly()__, there are `add` and `mul` gates, each gate can have __many inputs__ but only __1 output__. (for now we only have basic gates.)

* **R1CS**

  * What is R1CS

    Range 1 Constraint System.

    `<a, b, c>`

    `<s · a> * <s · b> = <s · c>`

    a, b, c are vectors and `<a, b, c>` is one constraint, a constraint system includes many different constraints.

    `<a1, b1, c1>` `<a2, b2, c2>` `<a3, b3, c3>` `...`

  * for example:

    `poly(x) =  z = 3 + 2*x + 5*x^2`

    `solution s = [1, x, t, t1, t2, z]`

    `gate t = x * x` >>> `<a1, b1, c1>`

        a = [0, 1, 0, 0, 0, 0]
        b = [0, 1, 0, 0, 0, 0]
        c = [0, 0, 1, 0, 0, 0]

    `gate t1 = x2 * x` >>> `<a2, b2, c2>`

        a = [2, 0, 0, 0, 0, 0]
        b = [0, 1, 0, 0, 0, 0]
        c = [0, 0, 0, 1, 0, 0]

    `gate t2 = 5 * t` >>> `<a3, b3, c3>`

        a = [5, 0, 0, 0, 0, 0]
        b = [0, 0, 1, 0, 0, 0]
        c = [0, 0, 0, 0, 1, 0]

    `gate z = 3 + t1 + t2 = (3 + t1 + t2) * 1 ` >>> `<a4, b4, c4>`

        a = [3, 0, 0, 1, 1, 0]
        b = [1, 0, 0, 0, 0, 0]
        c = [0, 0, 0, 0, 0, 1]

    `R1CS result` >>> put all <a_i,b_i,c_i> together.(i = 1,2,3,4)

        A =
        [0, 1, 0, 0, 0, 0]
        [2, 0, 0, 0, 0, 0]
        [5, 0, 0, 0, 0, 0]
        [3, 0, 0, 1, 1, 0]
        B =
        [0, 1, 0, 0, 0, 0]
        [0, 1, 0, 0, 0, 0]
        [0, 0, 1, 0, 0, 0]
        [1, 0, 0, 0, 0, 0]
        C =
        [0, 0, 1, 0, 0, 0]
        [0, 0, 0, 1, 0, 0]
        [0, 0, 0, 0, 1, 0]
        [0, 0, 0, 0, 0, 1]

* **QAP**
    * What is QAP

      Quadratic Arithmetic Programs

    * Example

        For matrix __A B C__ , construct __Aq Bq Cq__. Use [Lagrange's interpolation](https://en.wikipedia.org/wiki/Lagrange_polynomial).

        ![Lagrange's interpolation](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5a/Lagrange_polynomial.svg/440px-Lagrange_polynomial.svg.png)

        for matrix __A__, choose first column __[0, 2, 5, 3]__:

          A =
          1: [0, 1, 0, 0, 0, 0]
          2: [2, 0, 0, 0, 0, 0]
          3: [5, 0, 0, 0, 0, 0]
          4: [3, 0, 0, 1, 1, 0]

        We need to construct a polynomial __f(x)__ which satisfies:

          f(1) = 0, f(2) = 2, f(3) = 5, f(4) = 3
          also
          it cross points (1,0) (2,3) (3,5) (4,3)

        This is a little hard. We use __decomposition__: Let __f(x) = f1(x) + f2(x) + f3(x) + f4(x)__, where:

          f1(1) = 0, f1(2) = 0, f1(3) = 0, f1(4) = 0
          f2(1) = 0, f2(2) = 2, f2(3) = 0, f2(4) = 0
          f3(1) = 0, f3(2) = 0, f3(3) = 5, f3(4) = 0
          f4(1) = 0, f4(2) = 0, f4(3) = 0, f4(4) = 3
          except the diagonal, all equal to __ZERO__

        Now __f1234(x)__ can be constructed easily with

          f1(x) = (x-2)(x-3)(x-4)/(1-2)(1-3)(1-4) * 0 = 0
          f2(x) = (x-1)(x-3)(x-4)/(2-1)(2-3)(2-4) * 2 = -12 + 19 * x + -8 * x^2 +  1 * x^3
          f3(x) = (x-1)(x-2)(x-4)/(3-1)(3-2)(3-4) * 5 = 20 + -35 * x + 35/2 * x^2 + -5/2 * x^3
          f4(x) = (x-1)(x-2)(x-3)/(4-1)(4-2)(4-3) * 3 = -3 + 11/2 * x + -3 * x^2 + 1/2 * x^3   

        Then add them together, we get __f(x)__

          f(x) = 5 + -21/2 * x + 13/2 * x^2 + -1 * x^3

        Then we get first row of __Aq__, extracting coefficients in ascending order:

          [5, -21/2, 13/2, -1]

        Use same operating process for column 2,3,4,5,6 of Matrix __A__, getting row 2,3,4,5,6 of __Aq__.

          Aq =
          Aq1: [5, -21/2, 13/2, -1]
          Aq2: [...]
          Aq3: [...]
          Aq4: [...]
          Aq5: [...]
          Aq6: [...]

        And __Bq Cq__ . So __A__ is 4x6 and then __Aq__ is 6x4.

        Like

          A·s * B·s = C·s

        We use

          Aq·s * Bq·s - Cq·s
          = [xx, xx, xx, xx] * [xx, xx, xx, xx] - [xx, xx, xx, xx]
          = [xxx, xxx, xxx, xxx, xxx, xxx, xxx] -> R
          "O(3) * O(3) - O(3) = O(6)"

        For x = 1, 2, 3, 4

          R(x) = 0

        Now we use Zq(x) = (x-1)(x-2)(x-3)(x-4) and construct an equation:

          R(x) = H * Zq(x)

          Zq(x) = (x-1)(x-2)(x-3)(x-4) = 24 + -50 * x + 35 * x^2 + -10 * x^3 + 1 * x^4

          Zq = [24, -50, 35, -10, 1]

          this is for purpose that when x = 1, 2, 3, 4, equation R(x) = H * Zq(x) holds.

          calculate H = R / Zq, division has no remainder, so it's easy to compute.

        Soooooo, QAP is finished, including

          Aq : 6x4 Matrix
          Bq : 6x4 Matrix
          Cq : 6x4 Matrix
          Zq : 1x4 Vector
          H :  1x3 Vector

        We call it __QAP instance__.

        Notice that every number above will be substituted with __finite field elements__, which is used in Crypto.

        __Usage::__ if someone give you a solution `s`, check:

          Aq·s * Bq·s - Cq·s ?= H * Zq


## 2. Zero Knowledge
  But, how could we verify `Aq·s * Bq·s - Cq·s ?= H * Zq` without knowing `s` ?

  We have master's support !

  The paper [PGHR13](https://www.microsoft.com/en-us/research/wp-content/uploads/2016/02/pinocchio.pdf) has a complete scheme. Following pictures are simple reviews.

  ![PGHR-1](img/PGHR-1.png)

  ![PGHR-2](img/PGHR-2.png)

  ![PGHR-3](img/PGHR-3.png)

  ![PGHR-4](img/PGHR-4.png)

  ![PGHR-5](img/PGHR-5.png)

  With Ellpitic Curve and amazing Pairing Theory, everything can be done easily.

  So we jump this part...

## 3. An Example of Sudoku
capture from [https://blockchain.iethpay.com/zero-knowledge-zkSNARKs.html](https://blockchain.iethpay.com/zero-knowledge-zkSNARKs.html)
![img](https://blockchain.iethpay.com/images/2017/12/%E9%9B%B6%E7%9F%A5%E8%AF%86%E8%AF%81%E6%98%8E%E5%88%86%E4%BA%AB_%E5%8C%97%E4%BA%AC_12.27.006.jpeg)
![img](https://blockchain.iethpay.com/images/2017/12/%E9%9B%B6%E7%9F%A5%E8%AF%86%E8%AF%81%E6%98%8E%E5%88%86%E4%BA%AB_%E5%8C%97%E4%BA%AC_12.27.007.jpeg)
![img](https://blockchain.iethpay.com/images/2017/12/%E9%9B%B6%E7%9F%A5%E8%AF%86%E8%AF%81%E6%98%8E%E5%88%86%E4%BA%AB_%E5%8C%97%E4%BA%AC_12.27.008.jpeg)
![img](https://blockchain.iethpay.com/images/2017/12/%E9%9B%B6%E7%9F%A5%E8%AF%86%E8%AF%81%E6%98%8E%E5%88%86%E4%BA%AB_%E5%8C%97%E4%BA%AC_12.27.009.jpeg)

## 4. Current Tools

#### SNARK

1. [__scipr-lab__ - libsnark](https://github.com/scipr-lab/libsnark)

    a godlike Repository......

    a bunch of Publications......

    [scipr-lab official website - Succinct Computational Integrity and Privacy Research](http://www.scipr-lab.org/)

    __Official Documentation:__

    More precisely, libsnark provides a C++ implementation of a preprocessing zk-SNARK for an NP-complete language similar to arithmetic circuit satisfiability. The libary also includes functionality for constructing instances of the NP-language, "bottom up", using gagdet classes.

    __Good:__

    `gadgetlib1` has many components:

      curves, hash(sha256, knapsack), merkle tree,  basic gadgets.

    `gadgetlib2` has good remarks for readers.

    __Usage:__

    mainly use its `r1cs_ppzksnark`. See [Zcash's source codes](https://github.com/zcash/zcash/tree/master/src/snark).

2. [__akosba__ - jsnark](https://github.com/akosba/jsnark)

    __Official Documentation:__

    "a Java library for building circuits for preprocessing zk-SNARKs. The library uses libsnark as a backend, and can integrate circuits produced by the Pinocchio compiler when needed by the programmer."

    The code consists of two main parts:

    > __JsnarkCircuitBuilder:__ A Java project that has a Gadget library for building/augmenting circuits. (Check the src/examples package)

    > __libsnark/src/interface:__ A C++ interface to libsnark which accepts circuits produced by either the circuit builder or by Pinocchio's compiler directly.

    __Good:__

    > compose libsnark's `variable` `linear item` `linear combination` to `Wire` type.

    > output 2 files:
    >> `xx.arith` for circuit in R1CS format
    >>
    >> `xx.in` for solution input, corresponding to xx.arith with wire's id.

    __Bad:__

    > `xx.arith` and `xx.in` are produced at the same run.

    > need to implement Custom CircuitGenerator class and Override `buildCircuit()` `generateSampleInput()`

    __Process:__
    > `generateCircuit()`: generates the arithmetic circuit and the constraints.

    > `evalCircuit()`: evaluates the circuit.

    > `prepFiles()`: This produces two files: <circuit name>.arith and <circuit name>.in. The first file specifies the arithemtic circuit in a way that is similar to how Pinocchio outputs arithmetic circuits, but with other kinds of instructions, like: xor, or, pack and assert. The second file outputs a file containing the values for the input and prover free witness wires. This step must be done after calling evalCircuit() as some witness values are computed during that step.

    > `runLibsnark()`: This runs the libsnark interface with the two files produced in the last step. This can also be done manually outside the circuit if needed.

    __Example:__

    `SHA256` `input="abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl"` 64*8 = 512 bits

        Total Number of Constraints :  44780

        * G1 elements in PK: 315933
        * Non-zero G1 elements in PK: 240466
        * G2 elements in PK: 44463
        * Non-zero G2 elements in PK: 13650
        * PK size in bits: 73402616 ~= 8.75 MB

        * G1 elements in VK: 75
        * G2 elements in VK: 5
        * VK size in bits: 26597 ~= 3.25 KB

        * G1 elements in proof: 7
        * G2 elements in proof: 1
        * Proof size in bits: 2294


3. [__akosba__ - xjsnark](https://github.com/akosba/xjsnark)

    "a high-level framework for developing applications for zk-SNARKs. xJsnark aims at bridging the gap between high-level programming and performance. xJsnark's front end is currently developed as a java extension on top of Jetbrains MPS V 3.3.5. __At this point, xJsnark produces circuits using the same format as jsnark, which are transformed to r1cs constraints using the jsnark-libsnark interface.__"

    [paper link](http://www.cs.umd.edu/~akosba/papers/xjsnark.pdf)

    __Good:__

      > if .. else ..

      > for ..

      > children function, use codes repeatly

      > almost every commonly used grammar
      >> `+ - * /`
      >>
      >> `>> << | & ^ ~`

      > wire operation
      >> `EQ NEQ` - check if wires are equal
      >>
      >> `NOT AND OR`

      > many predefined number types
      >> `uint_size` size can be a number for the type's bit length

      > do a great optimization for circuit, it reduce sha256's gate quantity from 34844 to 26052 with arithmetic minimization

    __Bad:__

      > DSL - Domain Specific Language
      >> need to use `MPS` IDE
      >>
      >> need time to learn its new grammar

      > this tool only generate circuit file: `xxx.arith`. need to use jsnark interface to run libsnark with `xxx.arith` to generate QAP, pk, vk, proof ... It only generate a optimized R1CS.

      > functions still need to be wrote by programmer.

    `SHA256`

        Circuit file size:  1.4 MB
        Number of total mul gates before arithmetic minimization =  34844
        Number of total mul gates after  arithmetic minimization =  26052
        Total Savings due to arithmetic minimizations = 8792

        * G1 elements in PK: 188021
        * Non-zero G1 elements in PK: 144597
        * G2 elements in PK: 25875
        * Non-zero G2 elements in PK: 7749
        * PK size in bits: 43814876 ~= 5.22 MB

        * G1 elements in VK: 11
        * G2 elements in VK: 5
        * VK size in bits: 6181 ~= 0.75 KB

        * G1 elements in proof: 7
        * G2 elements in proof: 1
        * Proof size in bits: 2294




4. [__o1-labs__ - snarky](https://github.com/o1-labs/snarky)

  `snarky` is an `OCaml` front-end for writing R1CS SNARKs. It is modular over the backend SNARK library, and comes with backends from libsnark.

5. [__jancarlsson__ - snarklib](https://github.com/jancarlsson/snarklib)

  __Author:__

  The `snarklib template library` is a complete redesign of the libsnark library developed by the SCIPR Lab and contributors. All code is new except for x86-64 assembly language taken directly from libsnark. The theoretical ideas and algorithms are from libsnark and associated academic/industrial research. This project is about software engineering only. The theory and algorithms in snarklib are the creative work of others, not this author.

  The author of snarklib has no relationship with the SCIPR Lab project or affiliated contributors.

6. [__jancarlsson__ - snarkfront](https://github.com/jancarlsson/snarkfront)

  A C++ embedded domain specific language for zero knowledge proofs.

  Evolve from `snarklib`.



7. [__JacobEberhardt__ - ZoKrates](https://github.com/JacobEberhardt/ZoKrates)

  "Zokrates is a toolbox for zkSNARKs on Ethereum."

  * use docker
  * use *.code file to write functions, like python
  * generate solidity smart contract for verifier.

  `SHA256`

        Number of constraints: 932609

        * G1 elements in PK: 7184
        * Non-zero G1 elements in PK: 5644
        * G2 elements in PK: 1026
        * Non-zero G2 elements in PK: 514
        * PK size in bits: 1832174 ~= 0.22 MB

        * G1 elements in VK: 258
        * G2 elements in VK: 5
        * VK size in bits: 84974 ~= 10.37 KB

        Verification key in Solidity compliant format:
        {
      		vk.A = Pairing.G2Point([0x216e5a7c82764695b058b18e00adf4348997369c39a34ca51d593e0b0ab391cf, 0x21b9a8987a68e8fe303fdd890f5ccf57d2f52ab69c6b8ab71e2d2570774be86a], [0x65f8fc5371b757b6a5dae12a704676bc5c0146451fae85e2c76ed0bca7ec32e, 0x155becfe1c656a63aa0fc84b336af8da64cc4561fae5351f3befc3c9f2a1a307]);
      		vk.B = Pairing.G1Point(0xe65a98ea5f47122913b6c976929e1ea914076d31884a96f91cad9d6dc53387f, 0x91a96d8ee3922523f59c15102985e7d61fa1fc11c54e2dc330dbcc9612be26d);
      		vk.C = Pairing.G2Point([0x5d45730253b742adf970455f1abb7e0b000b33df325861930c72037534bca25, 0x2d295aca166786a7d17531309123cfdfec5f61c440ffb0764ff15922f46608a4], [0x2b22f521f6ff2c109a73ff81218acce62e47cfccd1a13e31bb79fdb19dadcdb6, 0x1114023a18c8beb61af792d9047fd4b9b4bf4dec3d7ba8ace6c3203e1d17b5d7]);
      		vk.gamma = Pairing.G2Point([0x18528b93eededaaaf364a52fbae7e0f6e299e7ba3e05bc1dcdac30f319537bca, 0xd0db77e25384aae4816548562ead1b0daf284246a78467370f5eb1c5a1b2127], [0x59f6f26330ea308e7bf0a874ef174632f43febddda08913e88b92462edff694, 0x1c5fb7f2c109765703ccc041de1ebc1faf36b3944aa3c1ace984dba2b95c71d7]);
      		vk.gammaBeta1 = Pairing.G1Point(0x1177e9f12bd304f12c8b7568ff60edef32bd99ff9659305e2bef639f877b472a, 0x2a0f869cc8908e26c67faf433e025d7913de0e2e3386af1d5bd6016aa4aae6fb);
      		vk.gammaBeta2 = Pairing.G2Point([0x9e8d77ed07e592be0a0fad2a6e8c08d62f38c7de602f2ad344552042c2effe5, 0x1ad0dfeea89377d6d36174082b2ac4ad2850495b881c2fd8c35e423781b0cedd], [0x2cab2785e758cb811f6b1b7c52cf4664f29013c7ff3e1f4eb73bcfd845482427, 0x194fe047dc68c7d29b44882e5e44357fec1846eac775dadcc852f65c832caba3]);
      		vk.Z = Pairing.G2Point([0x20bff22103d781dbbf110c846fd9403cc84a866a8376257d22bdbb7d4b616682, 0x1d8a04a003aee469e411330c35310a3f0b0243318c6a31219a2339e4a2829071], [0x5a4cae94991073803bd9e95d79ff9e72806fffdeba715d1a01e55b9aacd03d1, 0xc337eda7d36f8583ac128ab226518b233f7c50fda9511f3b62fd8e2f6768085]);
      		vk.IC = new Pairing.G1Point[](257);
      		vk.IC[0] = Pairing.G1Point(0x243f5972b6f7af12e3fe9ed15ec97747f32917f5aa6d932d2117bc96359cadb2, 0x4b7d0e15697af7d868b8a3c650e72b1632c456dcf42a3542611f0cfb564a117);
      		vk.IC[1] = Pairing.G1Point(0x17315f71b55d4d5fa2887f9e4560ef74b5ce7897c54eac988b6f988120b31dc3, 0x251285ccec4c3ca8acb5962366ae1f28e0c31dcd14ecebb08f8ebd87d9bf716a);
      		vk.IC[2] = Pairing.G1Point(0x2564e423ebdbf9df5e8bbcfd43c1e3c3fbf14e8b930e241d6849e37aefddb8e9, 0xcb2c926af2d372a5630285fe5dc047473235eec7051b02e64c9a11257c8eedf);
              ...
      		vk.IC[254] = Pairing.G1Point(0x2c090e1cae2770630f9c251468fbf9904d77e3ed9bae25c380310813f80f3540, 0x227fa609a591d78b5840d29b988f67c018ff6e901aab68ba266d2e4a6748c8a6);
      		vk.IC[255] = Pairing.G1Point(0x1f5fc3668a1fffd86bfc2c78ff2807f4be726dc1a46bae1d0f9c51e5f3cbc2c, 0x116969967e47160bfba781e26129b93bc779ebbf32ba220103d04770ad2347e);
      		vk.IC[256] = Pairing.G1Point(0x19875afc3d27b638c558932386ac6a471fed41b98bae8b5f60c8e5f28331d712, 0x12d676eae104ac560e6d1c718ccace977183b64bbace5d4f4e86f7895aa99d3e);
        }

        * G1 elements in proof: 7
        * G2 elements in proof: 1
        * Proof size in bits: 2294
        Proof:
        A = 0x1e536419b485478cee59b56a450c1792d63cf76e677a970622324395b912c58e, 0x23fe14a886119a7d07fa67d77e2ff3697eb76c02a1d0087ebf7ba18d8d2a345d
        A_p = 0xba79e6c1167a3d92e8891db4446156e5cae25e151303c6432f2b14b74cd41cb, 0x2f0e5277bcd950cfedd27a5cf90caf7e47d8433f901c3cd6460e938c6efc3fb9
        B = [0x2b8934ed3993625f918dadcc275686f8658b86f7ace2b87143fa4c08c48e6eb, 0x225baac932aa658c2bc1df3e6af2dddac9da50fa5535666123ff939b343419b0], [0x2279b837883c7bf2d657a90d30775d0d2030b13be29e84004c9fc7274b73395f, 0x1842e86fcecddd9bcc17699a32505b278318573ba16ddf6991e7b7af536f6bc0]
        B_p = 0xf47c6f2aa8224e6a55269484d96c68716e679bd65d4d506cfab5742ba5b5ce9, 0x26341f1e9b56f562af797a66e5a2fcbb2e20a77203af62ea6742e84907daaa8
        C = 0x22512d3dc8ebe12ccb56a41b9cd9d6078c6555b5f6263c82a379304d24fce584, 0x14be51dbc3c8d5211c3d946be5cd88bcff4a958bbd32fa23068fe9627b1cc9af
        C_p = 0x15097ca8cece18c0727c724c35bbc61314cb659ee5b0d3b418a0dbaaeefbabae, 0x206b011a1c10ef1713afb220ce5eddd473d1f3d34baf1efe40cb76b34bf63043
        H = 0x7662dbfd890ee7607ce75d7f035c0d055d84dcb209625f59f4ba7640d67c463, 0x13114a255ff69f2aa4d7cff95d87a366d19b5763f518334a6c3ae3946fa6c140
        K = 0xb5fdc28f26f8a094b98791656c69e1a90db201c88d1dd987701662bf747ff3b, 0x2283b0e80e73f099597b011860a603db77f9ab30351dfa7162e871799f42a9d5



#### STARK

8. [__elibensasson__ - libSTARK](https://github.com/elibensasson/libSTARK)

  It has example on  DPM (DNA fingerprint blacklist).













## Further Reading

* [__Gregory Maxwell:__ The first successful Zero-Knowledge Contingent  Payment](https://bitcoincore.org/en/2016/02/26/zero-knowledge-contingent-payments-announcement/)
* [__Github:__ Pay to Sudoku](https://github.com/zcash-hackworks/pay-to-sudoku)
