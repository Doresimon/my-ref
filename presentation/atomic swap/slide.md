# atomic swap research

## 1. Concept

### Atomic - 原子性

In computer programming, atomic denotes a unitary action or object that is **indivisible, unchangeable, whole, and irreducible.** What this means is that either the trade will be completed in full or it will be canceled and both parties will get their coins back.

> "不成功便成仁".

### Atomic swap - 原子交换

Put simply, an atomic swap (also sometimes referred to as a **cross-chain swap or trade**) is a nearly **instantaneous exchange** of one cryptocurrency to another which *does not require a middleman or third party to oversee the transaction*.

> 去中心化, 无第三方的货币互换.

## 2. First Implementation - Decred

On September 20, 2017 **Decred** announced via Twitter that they had successfully completed an atomic swap between Decred and Litecoin. A few days later, Charlie Lee, CEO and founder of Litecoin, also announced via Twitter that the world’s first atomic swap had successfully been completed between **Bitcoin** and **Litecoin**. This caused a wave of excitement for the crypto community; many consider this an important milestone for bringing cryptocurrencies into the mainstream and predict that it will change the world of cryptocurrency forever.

* [github.com/decred/atomicswap](https://github.com/decred/atomicswap)

### process

The image below provides a visual of the steps each party performs and the
transfer of data between each party.

<img src="./workflow.svg" width="100%" height=650 />

### action

```
Commands:
  initiate <participant address> <amount>
  participate <initiator address> <amount> <secret hash>
  redeem <contract> <contract transaction> <secret>
  refund <contract> <contract transaction>
  extractsecret <redemption transaction> <secret hash>
  auditcontract <contract> <contract transaction>
```

### action detail

**`initiate <participant address> <amount>`**

The `initiate` command is performed by the initiator to create the first
contract.  The contract is created with a **locktime of 48 hours** in the future.
This command **returns the secret, the secret hash, the contract script, the
contract transaction, and a refund transaction** that can be sent after 48 hours
if necessary.

Running this command will prompt for whether to publish the contract
transaction.  If everything looks correct, the transaction should be published.
The refund transaction should be saved in case a refund is required to be made
later.

For dcratomicswap, this step prompts for the wallet passphrase.  For the
btcatomicswap and ltcatomicswap tools the wallet must already be unlocked.

**`participate <initiator address> <amount> <secret hash>`**

The `participate` command is performed by the participant to create a contract
on the second blockchain.  It operates similarly to `initiate` but requires
using the secret hash from the initiator's contract and creates the contract
with a locktime of 24 hours.

Running this command will prompt for whether to publish the contract
transaction.  If everything looks correct, the transaction should be published.
The refund transaction should be saved in case a refund is required to be made
later.

For dcratomicswap, this step prompts for the wallet passphrase.  For the
btcatomicswap and ltcatomicswap tools the wallet must already be unlocked.

**`redeem <contract> <contract transaction> <secret>`**

The `redeem` command is performed by both parties to redeem coins paid into the
contract created by the other party.  Redeeming requires the secret and must be
performed by the initiator first.  Once the initiator's redemption has been
published, the secret may be extracted from the transaction and the participant
may also redeem their coins.

Running this command will prompt for whether to publish the redemption
transaction. If everything looks correct, the transaction should be published.

For dcratomicswap, this step prompts for the wallet passphrase.  For the
btcatomicswap and ltcatomicswap tools the wallet must already be unlocked.

**`refund <contract> <contract transaction>`**

The `refund` command is used to create and send a refund of a contract
transaction.  While the refund transaction is created and displayed during
contract creation in the initiate and participate steps, the refund can also be
created after the fact in case there was any issue sending the transaction (e.g.
the contract transaction was malleated or the refund fee is now too low).

Running this command will prompt for whether to publish the redemption
transaction. If everything looks correct, the transaction should be published.

**`extractsecret <redemption transaction> <secret hash>`**

The `extractsecret` command is used by the participant to extract the secret
from the initiator's redemption transaction.  With the secret known, the
participant may claim the coins paid into the initiator's contract.

The secret hash is a required parameter so that "nonstandard" redemption
transactions won't confuse the tool and the secret can still be discovered.

**`auditcontract <contract> <contract transaction>`**

The `auditcontract` command inspects a contract script and parses out the
addresses that may claim the output, the locktime, and the secret hash.  It also
validates that the contract transaction pays to the contract and reports the
contract output amount.  Each party should audit the contract provided by the
other to verify that their address is the recipient address, the output value is
correct, and that the locktime is sensible.

### Example

##### 1. **Alice: create contract**
<!-- > **Alice create contract** -->
>
> @input:
> * Bob's address (Bitcoin)
> * amount (Bitcoin)
>
> @return:
> * secret
> * secret hash
> * contract script
> * contract transaction
> * refund transaction
>  
> @public:
> * contract transaction
>
> @send:
> * secret hash
> * contract script
> * contract transaction

##### 2. **Bob: Audit the contract**

> @input:
> * contract
> * contract transaction
>
> @return:
> * Contract address:        2MwQAMPeRGdCzFzPy7DmCnQudDVGNBFJK8S
> * Contract value:          1 BTC
> * Recipient address:       n31og5QGuS28dmHpDH6PQD5wmVQ2K2spAG
> * Author's refund address: mg9sDLhfByfAWFo4zq3JZ7nsLfsN59XPue
> * Secret hash:             29c36b8dd380e0426bdc1d834e74a630bfd5d111
> * Locktime:                2017-09-16 13:36:23 +0000 UTC
> * Locktime reached in **47h56m54s**

check everything.

##### 3. **Bob: Create contract**

> @input:
> * Alice's address (Decred)
> * amount (Decred)
> * **secret hash** (from Alice)
>
> @return:
> * ~~secret~~
> * ~~secret hash~~
> * contract script
> * contract transaction
> * refund transaction
>  
> @public:
> * contract transaction
>
> @send:
> * ~~secret hash~~
> * contract script
> * contract transaction

##### 4. **Alice: Audit the contract**

> @input:
> * contract
> * contract transaction
>
> @return:
> * Contract address:        TcZpybEVDVTuoE3TCBxW3ui12YEZWrw5ccS
> * Contract value:          1 DCR
> * Recipient address:       TsfWDVTAcsLaHUhHnLLKkGnZuJz2vkmM6Vr
> * Author's refund address: Tsh9c9aytRaDcbLLxDRcQDRx66aXATh28R3
> * Secret hash: 29c36b8dd380e0426bdc1d834e74a630bfd5d111
> * Locktime: 2017-09-15 13:51:34 +0000 UTC
> * Locktime reached in **23h58m10s**

check everything. same as step #2

##### 4. **Alice: Redeem the contract**

> @input:
> * contract script (Decred)
> * contract transaction (Decred)
> * **secret**
> * **sig**
>
> @return:
> * redeem script **(with secret)**
> * redeem transaction
>  
> @public:
> * redeem transaction

##### 5. **Bob: Extract the secret**
B may watch a block explorer to see when the Decred contract output was spent and look up the
redeeming transaction.

-. -!

> @input:
> * redeem transaction (Decred)
>
> @return:
> * **secret**

##### 6. **Bob: Redeem the contract**

> @input:
> * contract script (Bitcon)
> * contract transaction (Bitcon)
> * **secret**
> * **sig**
>
> @return:
> * redeem script
> * redeem transaction
>  
> @public:
> * redeem transaction

##### 7. DONE

















### [Atomic swap](https://en.wikipedia.org/wiki/Atomic_swap)

An atomic swap is a proposed feature in cryptocurrencies, that allows for the exchange of one cryptocurrency for another cryptocurrency without the need for a trusted third party. In traditional cryptocurrencies a trusted third party such as an cryptocurrency exchange is necessary to perform a swap of cryptocurrencies in order to prevent one party from sending a currency without receiving a currency in return.

An atomic swap system uses a hash time-locked smart contract so that a party must deliver the currency to be swapped within a specified time, or else the transaction will be cancelled. This preserves atomicity in that either the swap will take place, or no currency will be swapped.

### [Atomic cross-chain trading](https://en.bitcoin.it/wiki/Atomic_cross-chain_trading)

The problem of atomic cross-chain trading is one where (at least) two parties, Alice and Bob, own coins in separate cryptocurrencies, and want to exchange them without having to trust a third party (centralized exchange).

A non-atomic trivial solution would have Alice send her Bitcoins to Bob, and then have Bob send another cryptocurrency to Alice - but Bob has the option of going back on his end of the bargain and simply not following through with the protocol, ending up with both Bitcoins and the altcoin.

### [An article - What Are Atomic Swaps?](https://www.cryptocompare.com/coins/guides/what-are-atomic-swaps/)

#### What Are Atomic Swaps?

Atomic swaps, or atomic cross-chain trading, is the exchange of one cryptocurrency to another cryptocurrency, without the need to trust a third-party. A relatively new piece of technology, atomic cross-chain trading is looking to revolutionize the way in which users transact with each other. For example, if Alice owned 5 Bitcoins but instead wanted 100 Litecoins, she would have to go through an exchange, i.e. a third-party. However, with atomic swaps, if Bob owned 100 Litecoins but instead wanted 5 Bitcoins, then Bob and Alice could make a trade. In order to prevent, for example, Alice accepting Bob’s 100 Litecoins but then failing to send over her 5 Bitcoins, atomic swaps utilizes what is known as hash time-locked contracts (HTLCs).

Hash time-locked contracts ensure that the atomic swap process is completely trustless by ensuring both fulfill the requirements of the trade. HTLCs require the recipient of a payment to acknowledge receiving payment prior to a deadline by generating a cryptographic proof of payment. Or the recipient risks losing the right to the claim the payment, therefore returning the funds back to the sender.

Therefore, for a trade between Alice and Bob to take place, both must submit their transaction to their respective blockchain, Alice on the Bitcoin blockchain and Bob on the Litecoin blockchain. In order for Alice to claim the 100 Litecoins sent from Bob, she must produce a number that only she knows, used to generate a cryptographic hash, therefore providing proof of payment. Similarly, in order for Bob to claim the 5 Bitcoins that was sent from Alice, he must also provide the same number, that was used to generate the cryptographic hash.

#### Requirements of Atomic Swaps

As exciting as this technology is, there are some fundamental requirements for a cryptocurrency before it can successfully support atomic swaps. One such requirement is the implementation of the Lightning network.

If a hash time-locked contract can be thought of as linking two blockchains together, the lightning network can be thought of as linking payment channels together. That is, for Alice and Bob to transact with each other, they must be linked through payment channels. The lightning network allows for that.

In addition, for a transaction to occur between two different blockchains, it is necessary for both blockchains to share the same cryptographic hash function, such as SHA-256. This is to allow for the hash-time locked contract to function properly when it comes to the user providing the number that was generated via the hash function.

#### Where We Are Now

If recent news is anything to go by, the future of atomic cross-chain trading looks bright. Creator of Litecoin, Charlie Lee, successfully completed atomic swaps using Litecoin in exchange for Bitcoin, Vertcoin and Decred. With continued innovation, the desire is that the technology of atomic swaps will allow us to run decentralized exchanges that will be convenient for the average user. However, the caveat to the recent success of atomic swaps is that all those swaps required local coin daemons. What this means is, in order for the average user to perform an atomic swap between two cryptocurrencies, they would be required to download the blockchains of either currency. As you may have guessed, this process is not very practical for the average user. However, a recent successful atomic swap may have provided the solution to this problem.

The Komodo team, who themselves are currently attempting to build their own decentralized exchange called BarterDEX, is ahead of the pack having successfully completed an atomic swap using an Electrum server. This is important because the Electrum server allows a user to interact with a cryptocurrency without having to download the whole blockchain. Therefore, this makes the prospect of a decentralized exchange all the more practical.

To conclude, there are a plethora of decentralized exchanges that are utilizing this technology in-order to completely change the way we as users transact. Projects such as Blocknet, who are looking to create the internet of blockchains through the use of atomic swaps. Even the creation of semi-decentralized exchanges such as Lykke, who charge 0% commission on trades. It goes without saying that blockchain technology, but more specifically, atomic cross-chain trading, is a space to watch.

### [History](https://www.investinblockchain.com/why-atomic-swap-matters/)

On September 20, 2017 **Decred** announced via Twitter that they had successfully completed an atomic swap between Decred and Litecoin. A few days later, Charlie Lee, CEO and founder of Litecoin, also announced via Twitter that the world’s first atomic swap had successfully been completed between **Bitcoin** and **Litecoin**. This caused a wave of excitement for the crypto community; many consider this an important milestone for bringing cryptocurrencies into the mainstream and predict that it will change the world of cryptocurrency forever.

## [bitcoin wiki - atomic cross chain trading](https://en.bitcoin.it/wiki/Atomic_cross-chain_trading)

The problem of atomic cross-chain trading is one where (at least) two parties, Alice and Bob, own coins in separate cryptocurrencies, and want to exchange them without having to trust a third party (centralized exchange).

## [bitcoin script wiki(with OP CODE)](https://en.bitcoin.it/wiki/Script)

## [bitcoin developer index page](https://bitcoin.org/en/development)

## [bitcoin developer reference](https://bitcoin.org/en/developer-reference)
