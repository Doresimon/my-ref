# Delegated Proof of Stake

## Some links

* [详解DPoS共识算法](https://zhuanlan.zhihu.com/p/34107097)

* [全栈区块链](https://zhuanlan.zhihu.com/fullstackblockchain)

* [Delegated Proof of Stake (DPOS) vs Proof of Work (POW)](http://bytemaster.github.io/bitshares/2015/01/04/Delegated-Proof-of-Stake-vs-Proof-of-Work/)

* [Delegated Proof-of-Stake Consensus](https://bitshares.org/technology/delegated-proof-of-stake-consensus/)

* [DPOS机制](https://bitcoin-on-nodejs.ebookchain.org/3-%E6%BA%90%E7%A0%81%E8%A7%A3%E8%AF%BB/9-DPOS%E6%9C%BA%E5%88%B6.html)

* [DPOS共识算法-by BM](http://me.tryblockchain.org/blockchain-dpos-bm-eos.html)

* [DPOS Consensus Algorithm - The Missing White Paper](https://steemit.com/dpos/@dantheman/dpos-consensus-algorithm-this-missing-white-paper)

* [__Bitshare__ - Graphene Technical Documentation](http://docs.bitshares.org/)

* [__Bitshare__ - DPOS](https://bitshares.org/technology/delegated-proof-of-stake-consensus/)

* [__Bitshare__ - Graphene's Feature](https://bitshares.org/technology/industrial-performance-and-scalability/)

* [__Bitshare__ - doxygen](https://bitshares.org/doxygen/)

* [__Github__ - cryptonomex/graphene](https://github.com/cryptonomex/graphene)

* [__Github__ - cryptonomex/graphene - wiki](https://github.com/cryptonomex/graphene/wiki/Home/cdc8ea8133a999afef8051700a4ce8edb0988ec4)

* [__Github__ - bitshares/bitshares-core](https://github.com/bitshares/bitshares-core)


### Cryptonomex - GRAPHENE Developer

## Knowledge

The questions that must be answered by any consensus process include, but are not limited to:
<!-- 任何共识过程必须回答的问题包括但不限于： -->

* `Who` should produce the next block of updates to apply to the database?
* `When` should the next block be produced?
* `What` transactions should be included in the block?
* `How` are `changes` to the protocol `applied`?
* `How` should `competing transaction histories` be resolved?

<!-- * `谁`应该产生应用于数据库的下一个更新区块？
* `什么时候`应该生产下一个区块？
* `什么交易`应该包括在该块？
* `如何`对当前的协议进行`更改`？
* 应该`如何`解决`'竞争性交易历史'`？ -->

### 1. Block Production by Elected `Witnesses` - 通过当选的`见证人`生产区块

The term `witness` was chosen because it is a legally neutral word that is `free from regulation`. Traditional contracts often have a place for witnesses to sign. For extremely important contracts, a `public notary` is sometimes used. Neither witnesses nor notaries are party to the contract, but they serve a very important role of `certifying that the contract was signed by the specified individuals at the specified time`. In BitShares, witnesses serve a similar role of `validating signatures` and `timestamping transactions` by `including them in blocks`.

Under `DPOS`, the `stakeholders` can elect `any number of witnesses` to `generate blocks`. A block is a group of transactions which update the state of the database. Each account is allowed one vote per share per witness, a process known as `approval voting`. The top N witnesses by total approval are selected. The number (N) of witnesses is defined such that at least 50% of voting stakeholders believe there is sufficient decentralization. When stakeholders expresses their desired number of witnesses, they must also `vote for at least that many witnesses`. A stakeholder cannot vote for more decentralization than witnesses for which they actually cast votes.

Each time witnesses produce a block, they are `paid` for their services. Their `pay rate` is set by the `stakeholders` via their `elected delegates` (to be discussed later). If a witness `fails` to produce a block, then they are `not paid`, and may be `voted out in the future`.

The slate of active witnesses is `updated once` every `maintenance interval (1 day)` when the votes are tallied. The witnesses are then `shuffled`, and each witness is given a turn to produce a block at a fixed schedule of one block every 2 seconds. `After all witnesses have had a turn, they are shuffled again`. If a witness does not produce a block in their time slot, then that time slot is `skipped`, and the next witness produces the next block.

Anyone can monitor network health by observing the witness participation rate. Historically, BitShares has maintained 99% witness participation. Any time witness participation falls below a certain level, users of the network can allow more time for transactions to confirm, and be extra vigilant about their network connectivity. This property gives BitShares the unique advantage of being able to alert users of potential problems less than 1 minute after the trouble arises.

### 2. Parameter Changes by Elected `Delegates` - 通过当选的`代表`更改参数

`Delegates` are elected in a manner similar to witnesses. A delegate becomes a `co-signer` on a `special account` that has the privilege of proposing changes to the network parameters. This account is known as the `genesis account`. These parameters include everything from `transaction fees`, to `block sizes`, `witness pay`, and `block intervals`. After the majority of delegates have approved a proposed change, the `stakeholders` are granted a `2 week review period` during which they may `vote out delegates` and `nullify the proposed changes`.

<!-- `代表`以与证人类似的方式选出。`代表`成为特殊帐户的共同签名者，该帐户有权提出对网络参数的更改。这个账户被称为`创世账户`。这些参数包括`交易费用`，`区块大小`，`证人工资`和`区块间隔`。 在大多数`代表`批准了提议的变更后，`stakeholders` 被授予 `2周的审查期`，在此期间他们可以为代表`投票`并`取消`提议的变更。 -->

This design was chosen to ensure that delegates technically have `no direct power` and that all `changes` to the network parameters are `ultimately approved by the stakeholders`. This is done to protect the delegates against regulations that may apply to managers or administrators of cryptocurrencies. Under DPOS, we can truly say that the `administrative authority rests in the hands of the users`, rather than either the delegates or witnesses.

<!-- 这种设计的选择是为了确保`代表`在技术上没有直接的权力，并且网络参数的所有变更最终都得到了`利益相关方stakeholders`的批准。这样做是为了保护代表不受可能适用于加密货币的经理或管理员的规定的影响。在DPOS下，我们可以确切地说，行政权力掌握在`用户`手中，而`不是代表或见证人`。 -->

Unlike witnesses, delegates are `not paid positions`. However, these parameters are `not expected to change often`.

<!-- 与见证人不同，`代表`不会获得报酬。然而，区块链的参数预计`不会`经常变化。 -->

The `genesis account` can technically perform any action that any other account can perform, which means it is possible to `send funds` to the genesis account or specify the genesis account as an `escrow agent`. The genesis account can also be used to `issue new assets`. There are untold number of applications where elected delegates can aid the stakeholders in performing tasks that demand a high degree of trust and accountability.

<!-- `创世帐户`可以在技术上执行任何其他帐户可以执行的操作，这意味着可以将资金发送到`创世帐户`或指定`创世帐户`作为托管代理。 `创世帐户`也可以用来发行新资产。 这里有无数的应用程序，其中当选的代表可以帮助利益相关者执行需要高度信任和问责的任务。 -->

### 3. Changing the Rules (aka Hard Forks) - 改变区块链规则: `硬分叉`

From time to time, it is necessary to `upgrade` a network to `add new features`. Under `DPOS`, `all changes must be triggered by active stakeholder approval`. While it is technically possible for the witnesses to collude and change their software unilaterally, it is not in their interest to do so. Witnesses are selected based upon their commitment to remain neutral to blockchain policy. Remaining neutral protects witnesses against allegations that they are the administrators/managers/owners/operators of the network. A witness is merely an employee of the stakeholders.

<!-- 有时需要对网络升级, 添加新功能。 在`DPOS`下，`所有的改变必须由活跃的持股人批准`。虽然技术上`见证人`可以单方面串通和改变他们的软件，但这样做并不符合他们的利益。 见证人的选取是基于他们对区块链政策保持`中立`的承诺的。 保持中立保护了`见证人`免受被认为是网络的管理员/经理/业主/经营者的指控。证人只是`持股人`的雇员。 -->

Developers may implement whatever changes they deem appropriate, so long as those changes are `contingent upon stakeholder approval`. This policy protects the developers as much as it protects the stakeholders and ensures that no individual has unilateral control over the direction of the network.

<!-- `开发人员`可以实施他们认为合适的任何更改，只要这些更改得到了`股东`的批准。 这项政策可以保护`开发者`如同它可以保护`股东`，并确保没有任何人单方面控制网络的走向。 -->

The `threshold` for changing the rules is the same as `replacing 51% of the elected witnesses`. The more stakeholder participation in electing witnesses, the harder it becomes to change the rules.

<!-- 改变规则的“门槛”与“代替51％的证人”相同。 股东越多的参与到选举证人环节中，规则就越难改变。 -->

Ultimately, `changing the rules depends upon everyone on the network to upgrade their software`, and no blockchain level protocol can enforce how rules are changed. This means that hard-forking “bug fixes” can be rolled out without requiring a vote of the stakeholders, so long as they remain true to the universally expected behavior of the code.

<!-- 最终，“改变规则取决于网络上的每个人升级他们的软件”，并且没有区块链协议可以强制规定规则如何改变。 这意味着只要坚持代码普遍预期的行为，就可以在不需要利益相关方投票的情况下推出硬分叉“错误修复”。 -->

In practice, only `security critical hard-forks` should be implemented in such a manner. The developers and witnesses should `wait for the stakeholders` to approve even the most minor changes.

<!-- 实际上，只有`安全的, 关键性的硬分叉`应该以这种方式进行。 即使是非常小的改动, `开发者`和`见证人`也应该等待`股东`的批准。 -->

### 4. Double Spend Attack - 双重支付攻击

`A double spend` can occur `anytime a blockchain reorganization` excludes a transaction previously included. This means that the `witnesses had a communication breakdown caused by disruptions in the infrastructure of the Internet`. With DPOS, the probability of a communication breakdown enabling a double spend attack is very low.

<!-- 在区块链重组的任何时候，“双重花费”都可能会导致排除之前包含的交易。 这意味着“证人因因特网基础设施中断导致通信故障”。 使用DPOS，导致双重支出攻击的通信中断概率非常低。 -->

The network is able to monitor its own health and can immediately detect any loss in communication which shows up as witnesses failing to produce blocks on schedule. `When this occurs, it may be necessary for users to wait until half of the witnesses have confirmed their transactions, which could be up to a minute or two.`

<!-- 该网络能够监测自己的健康状况，并可以立即检测到通信中出现的任何损失，因为目击者未能按计划生产积木。“当这种情况发生时，用户可能需要等到一半的证人证实他们的交易，这可能长达一两分钟。” -->

### 5. Transactions as Proof of Stake - 交易作为股权证明

Each transaction on the network may `optionally` include the `hash of a recent block`. If this is done, the signer of the transaction can be confident that their transaction may not be applied to any blockchain that does not include that block. A side effect of this process is that, over time, `all stakeholders end up directly certifying the long-term integrity of the transaction history`.

<!-- 网络上的每个事务可以可选地包括最近块的散列。 如果这样做，交易的签署人可以确信他们的交易可能不适用于任何不包含该区块的区块链。 这个过程的一个副作用是，随着时间的推移，所有利益相关者最终会直接证明交易历史的长期完整性。 -->

### 6. Blockchain Reorganizations - 区块链重构

Because all witnesses are elected, highly accountable, and granted dedicated time slots to produce blocks, there is `rarely any situation where two competing chains can exist`. From time to time, network latency will prevent one witness from receiving the prior block in time. If this happens, the next witness will resolve the issue by building on whichever block they received first. With 99% witness participation, a transaction has a 99% chance of being confirmed after a single witness.

<!-- 由于所有证人都是选举产生的，高度负责任的，并且授予专门的时间段来生产区块，所以很少有任何情况下可以存在两个竞争性的链子。 如果发生这种情况，下一个证人将通过建立在他们首先收到的任何区块上来解决问题。凭借99％的证人参与，一次交易有99％的机会在一名证人之后得到证实。 -->

While the system is robust against natural chain reorganization events, there is still some potential for software bugs, network interruptions, or incompetent or malicious witnesses to create multiple competing histories that are longer than a block or two. The software always selects the blockchain with the highest witness participation rate. A witness operating on their own can only produce one block per round and will always have a lower participation rate than the majority. There is nothing that any witness (or minority group of witnesses) can do to produce a blockchain with a higher participation rate. The participation rate is calculated by comparing the expected number of blocks produced vs the actual number of blocks produced.

<!-- 尽管该系统对于自然连锁重组事件具有强大的威力，但仍然存在一些潜在的软件错误，网络中断或无能或恶意的证人创造长于一个或两个块的多个竞争历史。 软件始终选择证人参与率最高的区块链。证人自己经营的每轮只能产生一个街区，参与率总是比大多数人低。 没有任何证人（或少数证人）能够做出更高参与率的区块链。 参与率通过比较产生的块的预期数量与实际产生的块的数量来计算。 -->

### 7. Maximally Decentralized - 最大限度的去中心化

Under DPOS, every stakeholder has influence that is directly proportional to their stake, and no stakeholders are excluded from exercising this influence. Every other consensus system on the market excludes the vast majority of stakeholders from participating. There are many different ways that alternatives exclude stakeholders. Some alternatives use invite-only systems. Others exclude participation by making it cost more to participate than they earn. Still other systems technically allow everyone to participate, but they can be safely ignored by a few large players who produce the vast majority of all blocks. Only DPOS ensures that block production is evenly distributed among the most people and that everyone has an economically viable way to influence who those people are.

<!-- 在DPOS下，每个利益相关者的影响力与其利益成正比，没有利益相关者被排除在行使这种影响力之外。市场上的其他每个共识系统都不包括绝大多数利益相关者参与。 替代方法有许多不同的方式排除利益相关者。 其他人通过让参与费用高于他们的收入来排除参与。 还有其他系统在技术上允许每个人参与，但是他们可以被产生绝大多数块的一些大型玩家安全地忽略。 只有DPOS确保块生产平均分配给大多数人，并且每个人都有一种经济可行的方式来影响这些人是谁。 -->