# HMAC (Hash-based Message Authentication Code)

一种使用 Hash 的 MAC 方案

[@ref RFC2104](https://tools.ietf.org/html/rfc2104)

## scheme

```
H           cryptographic hash function. such as
            md5, sha1, sha256, sha3 ...
B           byte length of H's output
ipad        inner padding, the byte 0x36 repeated B times
opad        outer padding, the byte 0x5C repeated B times
msg         message string
```

```
H = SHA256
B = 256/32 = 8
HMAC(K, msg)
{
    ipad = 0x36 || 0x36 ... || 0x36 // B times
    opad = 0x5C || 0x5C ... || 0x5C // B times

    if K.byteLength > B
        K = H(K)
    else
        K = padToLen(padding = 0x00, len = B)

    return H(K^opad || H(K^ipad || msg))
}
```
