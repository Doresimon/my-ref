# Password-Based Key Derivation Function 2 (PBKDF2)

[@ref RFC2898](https://tools.ietf.org/html/rfc2898#section-5.2)

[@ref NIST800-132](https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-132.pdf)

## scheme

```
   PBKDF2 (P, S, c, dkLen)

   Options:        PRF        underlying pseudorandom function (hLen
                              denotes the length in octets of the
                              pseudorandom function output)

   Input:          P          password, an octet string
                   S          salt, an octet string
                   c          iteration count, a positive integer
                   dkLen      intended length in octets of the derived
                              key, a positive integer, at most
                              (2^32 - 1) * hLen

   Output:         DK         derived key, a dkLen-octet string
```

PRF can use [HMAC](../hmac/HMAC.md)

```
PBKDF2 (P, S, c, dkLen)
{
   if dkLen > (2^32 - 1) * hLen
      return ERROR_DKLEN_TO_LONG

   len = CEIL(dkLen / hLen) // 输出的 block 个数
   off = dkLen - (l-1) * hLen // 最后一个 block 的偏移量

   for i in 1 to len
      T[i] = F(P, S, c, i)

      F(P, S, c, i) = {
         U[1] = PRF(P, S || INT_32_BE(i))
         ret = U[1]
         for j in 2 to c
            U[j] = PRF(P, U[j-1])
            ret = ret ^ U[j]

         return ret // U[1]^U[2]...^U[c]
      }

   DK = T[1] || T[2] || ... || T[l].split(0, off-1) // 将所有结果拼接起来
}
```
