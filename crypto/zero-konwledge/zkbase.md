- [Fiat Shamir heuristic](https://en.wikipedia.org/wiki/Fiat%E2%80%93Shamir_heuristic)

    The Fiat–Shamir heuristic is a technique in cryptography for taking an interactive proof of knowledge and creating a digital signature based on it. 

- [Bullet proofs](https://crypto.stanford.edu/bulletproofs/)

    Short Proofs for Confidential Transactions and More.

    Bulletproofs are short non-interactive zero-knowledge proofs that require no trusted setup. A bulletproof can be used to convince a verifier that an encrypted plaintext is well formed. For example, prove that an encrypted number is in a given range, without revealing anything else about the number. Compared to SNARKs, Bulletproofs require no trusted setup. However, verifying a bulletproof is more time consuming than verifying a SNARK proof.

    Bulletproofs are designed to enable efficient confidential transactions in Bitcoin and other cryptocurrencies. Confidential transactions hide the amount that is transfered in the transaction. Every confidential transaction contains a cryptographic proof that the transaction is valid. Bulletproofs shrink the size of the cryptographic proof from over 10kB to less than 1kB. Moreover, bulletproofs support proof aggregation, so that proving that m transaction values are valid adds only O(log(m)) additional elements to the size of a single proof. If all Bitcoin transactions were confidential and used Bulletproofs, then the total size of the UTXO set would be only 17 GB, compared to 160 GB with the currently used proofs.

    Bulletproofs have many other applications in cryptographic protocols, such as shortening proofs of solvency, short verifiable shuffles, confidential smart contracts, and as a general drop-in replacement for Sigma-protocols.

    ...