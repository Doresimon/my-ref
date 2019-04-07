# mnemonic(助记词)

## [BIP 32](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki)

### status

```
  BIP: 39
  Layer: Applications
  Title: Mnemonic code for generating deterministic keys
  Author: Marek Palatinus <slush@satoshilabs.com>
          Pavol Rusnak <stick@satoshilabs.com>
          Aaron Voisine <voisine@gmail.com>
          Sean Bowe <ewillbefull@gmail.com>
  Comments-Summary: Unanimously Discourage for implementation
  Comments-URI: https://github.com/bitcoin/bips/wiki/Comments:BIP-0039
  Status: Proposed
  Type: Standards Track
  Created: 2013-09-10
```

### motivation

为了便于记忆私钥, 使用助记词(mnemonic)来替代私钥.

### procedure

1. 生成助记词

   - 随机生成熵(Entropy), 128-256 bits, (16-32) bytes, 步长 32 bits
   - ENT.length := Entropy 的 bits 长度
   - CS := SHA256(ENT).split(0, ENT.length/32) (checksum)
   - MS.length := (ENT + CS).length/11 (mnemonic sentence length)

     ```
     CS = |ENT| / 32
     |MS| = |(ENT + CS)| / 11

     MS为 ENT+CS 按照11bits切分后的数组
     每个segment长度为11bits, 即取值空间为2048, 因此助记词共有2048个

     |  ENT  | CS | ENT+CS |  MS  |
     +-------+----+--------+------+
     |  128  |  4 |   132  |  12  |
     |  160  |  5 |   165  |  15  |
     |  192  |  6 |   198  |  18  |
     |  224  |  7 |   231  |  21  |
     |  256  |  8 |   264  |  24  |
     ```

   - detail

     ```
          128-bits entropy/12-words

          Rand Entropy(128 bits) ------>     SHA256

                                                |
                                              first 4 bits
                                                |

          |+++ Entropy(128 bits) +++|+++ checksum(4 bits) +++|

                                    |
                split 132-bits into 12 segments of 11-bits each
                                    |

                  |++|++|++|++|++|++|++|++|++|++|++|++|

                                    |
                    map 11bits to word, with dictionary
                                    |

      |word|word|word|word|word|word|word|word|word|word|word|word|
     ```

2. 11 bits code ==> word

3. mnemonic ==> seed

   - 助记词生成 seed, 进而生成私钥
   - PBKFD2(passphare, salt, iv, hashFunc, dkLen)
   - passphare := MS
   - salt = MS || password, password is input by user, default is ""
   - rounds := 2048, for hashFunc
   - hashFunc := HMAC-SHA512
   - dkLen := 512, in bits

4. seed ==> keys
