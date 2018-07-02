# EOS.IO Technical White Paper v2
<!-- March 16, 2018 -->

2018年3月16日

<!-- Abstract: The EOS.IO software introduces a new blockchain architecture designed to enable vertical and horizontal scaling of decentralized applications. This is achieved by creating an operating system-like construct upon which applications can be built. The software provides accounts, authentication, databases, asynchronous communication, and the scheduling of applications across many of CPU cores or clusters. The resulting technology is a blockchain architecture that may ultimately scale to millions of transactions per second, eliminates user fees, and allows for quick and easy deployment and maintenance of decentralized applications, in the context of a governed blockchain. -->

**摘要：** EOS.IO 软件引入一种新的区块链架构设计，它使得去中心化的应用可以横向和纵向的扩展。 这通过构建一个仿操作系统的方式来实现，在它之上可以构建应用程序。 该软件提供帐户、身份验证、数据库、异步通信和跨越数百个 CPU 内核或集群的应用程序调度。 由此产生的技术是一种区块链架构，它可以扩展至每秒处理百万级交易，消除用户的手续费，并且允许快速和轻松的部署去中心化的应用。

**PLEASE NOTE: CRYPTOGRAPHIC TOKENS REFERRED TO IN THIS WHITE PAPER REFER TO CRYPTOGRAPHIC TOKENS ON A LAUNCHED BLOCKCHAIN THAT ADOPTS THE EOS.IO SOFTWARE. THEY DO NOT REFER TO THE ERC-20 COMPATIBLE TOKENS BEING DISTRIBUTED ON THE ETHEREUM BLOCKCHAIN IN CONNECTION WITH THE EOS TOKEN DISTRIBUTION.**

<!-- 请注意: 本白皮书中提及的加密令牌指的是在一个启动的区块链上采用 EOS.IO 软件的加密令牌。 它们不涉及与 EOS 令牌分布有关的 ETHEREUM 区块链上分布的 ERC-20兼容令牌。 -->

Copyright © 2018 block.one

<!-- 版权2018年封锁 -->

Without permission, anyone may use, reproduce or distribute any material in this white paper for non-commercial and educational use (i.e., other than for a fee or for commercial purposes) provided that the original source and the applicable copyright notice are cited.

<!-- 未经许可，任何人都可以使用、复制或分发本白皮书中的任何材料，以供非商业用途和教育用途(即除收费或商业用途外)的任何材料。 -->

<!-- DISCLAIMER: This EOS.IO Technical White Paper v2 is for information purposes only. block.one does not guarantee the accuracy of or the conclusions reached in this white paper, and this white paper is provided “as is”. block.one does not make and expressly disclaims all representations and warranties, express, implied, statutory or otherwise, whatsoever, including, but not limited to: (i) warranties of merchantability, fitness for a particular purpose, suitability, usage, title or noninfringement; (ii) that the contents of this white paper are free from error; and (iii) that such contents will not infringe third-party rights. block.one and its affiliates shall have no liability for damages of any kind arising out of the use, reference to, or reliance on this white paper or any of the content contained herein, even if advised of the possibility of such damages. In no event will block.one or its affiliates be liable to any person or entity for any damages, losses, liabilities, costs or expenses of any kind, whether direct or indirect, consequential, compensatory, incidental, actual, exemplary, punitive or special for the use of, reference to, or reliance on this white paper or any of the content contained herein, including, without limitation, any loss of business, revenues, profits, data, use, goodwill or other intangible losses. -->

__免责声明:__ 本 EOS.IO 技术白皮书 v2仅供参考之用。 白皮书不能保证白皮书的准确性和结论，而这份白皮书提供的是"原样"。 (三)保证适销性、适合某一特定用途、适用性、用途、所有权或不侵犯的保证; (ii)白皮书的内容不会出错; 及(iii)此等内容不会侵犯第三者权利。 一个公司及其附属机构不得对因使用、参考或依赖这一白皮书或本文所载内容而引起的任何损害赔偿，即使对此类损害的可能性提出建议，也不得对此种损害赔偿承担任何赔偿责任。 任何人或实体对任何损害、损失、赔偿责任、费用或费用，不论是直接或间接、相应、补偿、附带、实际、惩罚性或特殊用途的任何损害、损失、赔偿责任、费用或费用，包括但不限于任何业务损失、收入损失、利润损失、数据损失、使用损失、商誉损失或其他无形损失。

<!-- MarkdownTOC depth=4 autolink=true bracket=round list_bullets="-*+" -->

- [Background 背景](#)
- [Requirements for Blockchain Applications 区块链应用的要求](#)
  * [Support Millions of Users 支持数百万用户](#)
  * [Free Usage 免费使用](#)
  * [Easy Upgrades and Bug Recovery 简单升级和 Bug 恢复](#)
  * [Low Latency 低延迟](#)
  * [Sequential Performance 时序性能](#)
  * [Parallel Performance 并发性能](#)
- [Consensus Algorithm (BFT-DPOS) 共识算法(BFT-DPOS)](#)
  * [Transaction Confirmation 交易确认](#)
  * [Transaction as Proof of Stake (TaPoS) 股权证明的交易(TaPoS)](#)
- [Accounts 帐户](#)
  * [Actions & Handlers 操作 & 处理](#)
  * [Role Based Permission Management 基于角色的权限管理](#)
    + [Named Permission Levels 命名权限级别](#)
    + [Permission Mapping 权限映射](#)
    + [Evaluating Permissions 评估权限](#)
      - [Default Permission Groups 默认权限组](#)
      - [Parallel Evaluation of Permissions 权限的并行评估](#)
  * [Actions with Mandatory Delay 强制延迟的操作](#)
  * [Recovery from Stolen Keys 恢复被盗窃的密钥](#)
- [Deterministic Parallel Execution of Applications 应用程序的确定性并行执行](#)
  * [Minimizing Communication Latency 最小化通信延迟](#)
  * [Read-Only Action Handlers 只读操作处理程序](#)
  * [Atomic Transactions with Multiple Accounts 多帐户的原子化交易](#)
  * [Partial Evaluation of Blockchain State 区块链状态的部分评估](#)
  * [Subjective Best Effort Scheduling 自主最优调度](#)
  * __+++__  [Deferred Transactions 延迟交易](#)
  * __+++__  [Context Free Actions 无关上下文操作](#)
- [Token Model and Resource Usage Token 模型与资源使用](#)
  * [Objective and Subjective Measurements 客观与主观的度量](#)
  * [Receiver Pays 接收方付费](#)
  * [Delegating Capacity 委托能力](#)
  * [Separating Transaction costs from Token Value 分离交易成本与 Token 价值](#)
  * [State Storage Costs 状态存储成本](#)
  * [Block Rewards 区块奖励](#)
  * __+++__  [Worker Proposal System - Worker提议系统](#)
- [Governance 治理](#)
  * [Freezing Accounts 冻结帐户](#)
  * [Changing Account Code 更改帐户代码](#)
  * [Constitution 宪法](#)
  * [Upgrading the Protocol & Constitution 升级协议 & 宪法](#)
    + [Emergency Changes 紧急变更](#)
- [Scripts & Virtual Machines 脚本 & 虚拟机](#)
  * [Schema Defined Actions 模式定义的操作](#)
  * [Schema Defined Database 模式定义的数据库](#)
  * __+++__  [Generic Multi Index Database API 通用多索引数据库 API](#)
  * [Separating Authentication from Application 从应用程序中分离授权](#)
- [Inter Blockchain Communication 跨链通信](#)
  * [Merkle Proofs for Light Client Validation (LCV) 用于轻客户端的 Merkle 证明 (LCV)](#)
  * [Latency of Interchain Communication 跨链通信的延时](#)
  * [Proof of Completeness 完备性证明](#)
  * __+++__  [Segregated Witness 隔离见证人](#)
- [Conclusion 结论](#)

<!-- [/MarkdownTOC -->

# Background 背景

<!-- Blockchain technology was introduced in 2008 with the launch of the Bitcoin currency, and since then entrepreneurs and developers have attempted to generalize the technology to support a wider range of applications on a single blockchain platform. -->

区块链技术是通过 2008 年诞生的比特币货币得以被认知，自从那之后企业家和开发者就不断的尝试推广这一技术，以便在单一的区块链平台上支持更为广泛的应用程序。

<!-- While a number of blockchain platforms have struggled to support functional decentralized applications, application specific blockchains such as the BitShares decentralized exchange (2014) and Steem social media platform (2016) have become heavily used blockchains with tens of thousands of daily active users. They have achieved this by increasing performance to thousands of transactions per second, reducing latency to 1.5 seconds, eliminating per-transaction fees, and providing a user experience similar to those currently provided by existing centralized services. -->

而一些区块链平台努力的支持可运作的去中心化应用，具体的应用比如 BitShares 去中心化交易所 (2014) 和 Steem 社交媒体平台 (2016) 已经成为每天被成千上万活跃用户重度使用的区块链。 他们能做到这些，是通过性能的提升达到每秒处理上千交易，消除手续费和提供堪比已经存在的中心化服务的用户体验。

<!-- Existing blockchain platforms are burdened by large fees and limited computational capacity that prevent widespread blockchain adoption. -->

已存在的区块链平台承担着大量的交易费和有限的可计算能力，这都阻碍了区块链技术的大面积应用。

# Requirements for Blockchain Applications 区块链应用的要求

<!-- In order to gain widespread use, applications on the blockchain require a platform that is flexible enough to meet the following requirements: -->

为了赢得广泛的应用，构建在区块链之上的应用需要一个灵活性足以满足以下要求的平台：

## Support Millions of Users 支持数百万用户

<!-- Competing with businesses such as eBay, Uber, AirBnB, and Facebook, require blockchain technology capable of handling tens of millions of active daily users. In certain cases, an application may not work unless a critical mass of users is reached and therefore a platform that can handle very large numbers of users is paramount. -->

像 Ebay、Uber、AirBnB 和 Facebook 这样企业，他们需要区块链技术能处理每日数以千万的活跃用户。 在某些情况下，除非用户群体达到一个极庞大的量级否则应用并无用武之地，因此一个可以处理极其庞大用户的平台是至关重要的。

## Free Usage 免费使用

<!-- Application developers need the flexibility to offer users free services; users should not have to pay in order to use the platform or benefit from its services. A blockchain platform that is free to use for users will likely gain more widespread adoption. Developers and businesses can then create effective monetization strategies. -->

应用程序开发人员需要灵活性，为用户提供免费服务; 用户不必为了使用平台或从其服务中受益而支付费用。 一个用户可以免费使用的区块链平台可能会获得更广泛的应用。 __+++__
开发者和企业可以制定有效的货币化策略。

## Easy Upgrades and Bug Recovery 简单升级和 Bug 恢复

<!-- Businesses building blockchain based applications need the flexibility to enhance their applications with new features. The platform must support software and smart contract upgrades. -->

企业构建区块链基础的应用需要能够为应用增加新特性的灵活性。 该平台必须支持软件和智能合约的升级。

<!-- All non-trivial software is subject to bugs, even with the most rigorous of formal verification. The platform must be robust enough to fix bugs when they inevitably occur. -->

所有非同凡响的软件都会受到 bug 的影响，即便是经过了最严格意义上的验证。这个平台必须具有足够的鲁棒性以便应对不可避免出现的 bug。

## Low Latency 低延迟
<!-- A good user experience demands reliable feedback with a delay of no more than a few seconds. Longer delays frustrate users and make applications built on a blockchain less competitive with existing non-blockchain alternatives. The platform should support low latency of transactions. -->

一个好的用户体验需要可靠的反馈，延迟时间不超过几秒钟。 较长的延迟会使用户感到沮丧，使得应用程序建立在与现有非区块链替代品竞争力较弱的区块链上。 __+++__ 该平台应该支持低延迟的交易。

## Sequential Performance 时序性能
<!-- There are some applications that just cannot be implemented with parallel algorithms due to sequentially dependent steps. Applications such as exchanges need enough sequential performance to handle high volumes. Therefore, the platform should support fast sequential performance. -->

由于一些依赖时序的步骤，有些应用程序无法使用并行算法实现。 交易所等应用程序需要足够的时序性能来处理大量的数据。 因此，平台应该支持快速的时序性能。

## Parallel Performance 并发性能
<!-- Large scale applications need to divide the workload across multiple CPUs and computers. -->

大规模应用程序需要在多个 cpu 和计算机之间划分工作负载。

# __+++__ Consensus Algorithm (BFT-DPOS) 共识算法(BFT-DPOS)

<!-- EOS.IO software utilizes the only known decentralized consensus algorithm proven capable of meeting the performance requirements of applications on the blockchain, Delegated Proof of Stake (DPOS). Under this algorithm, those who hold tokens on a blockchain adopting the EOS.IO software may select block producers through a continuous approval voting system. Anyone may choose to participate in block production and will be given an opportunity to produce blocks, provided they can persuade token holders to vote for them. -->

Eos.io 软件利用已知的分布式共识算法能够满足区块链上应用程序的性能要求。 在这种算法下，那些在区块链EOS Token的人可以通过连续的批准投票系统来选择块生产者。 任何人都可以选择参与区块生产，并将有机会生产区块，只要他们能说服Token的持有者投票给他们。

<!-- The EOS.IO software enables blocks to be produced exactly every 0.5 second and exactly one producer is authorized to produce a block at any given point in time. If the block is not produced at the scheduled time, then the block for that time slot is skipped. When one or more blocks are skipped, there is a 0.5 or more second gap in the blockchain. -->

__+++__

Eos.io 软件允许每0.5秒生产一个区块，准确地说有一个生产者被授权在任何特定的时间点生产一个块。 如果块不是在预定时间生成的，则跳过该时间段的块。 当一个或多个块被跳过时，在区块链中有0.5秒或更多的第二个空隙。

<!-- Using the EOS.IO software, blocks are produced in rounds of 126 (6 blocks each, times 21 producers). At the start of each round 21 unique block producers are chosen by preference of votes cast by token holders. The selected producers are scheduled in an order agreed upon by 15 or more producers. -->

__+++__

使用 EOS.IO 软件，每生产126个区块为一轮(每个生产者6个块，乘以21个生产者)。 在每一轮的开始，21个独立的区块产生者都是预先投片产生的。 选定的生产者按照15个或15个以上生产者商定的顺序来生产区块。

<!-- If a producer misses a block and has not produced any block within the last 24 hours they are removed from consideration until they notify the blockchain of their intention to start producing blocks again. This ensures the network operates smoothly by minimizing the number of blocks missed by not scheduling producers who are proven to be unreliable. -->

如果一个生产者错过了一个区块并且在过去的 24 小时内没有生产任何的区块，那么它将被从候选中移除，直到它在区块链中通知它要开始再次生产区块的意图。 这样通过最小化区块丢失数量（因被证实不可靠的节点不作为导致）来确保网络操作的稳定性。

<!-- Under normal conditions a DPOS blockchain does not experience any forks because, rather than compete, the block producers cooperate to produce blocks. In the event there is a fork, consensus will automatically switch to the longest chain. This method works because the rate at which blocks are added to a blockchain fork is directly correlated to the percentage of block producers that share the same consensus. In other words, a blockchain fork with more producers on it will grow in length faster than one with fewer producers, because the fork with more producers will experience fewer missed blocks. -->

在一般情况下，一个 DPOS 区块链不会经历任何的分叉，因为区块生产者是通过合作而非竞争的方式来生产区块。 即便真的出现了分叉，共识也将自动的切换到最长的链上。 之所以会这样运作，是因为区块添加到一个区块链分叉的速率与公用同一共识的区块生产者比例是相关的。 换句话说，具有更多生产者的区块链分叉会比拥有较少生产的那一个条增长的速度更快。 而且，没有一个生产者会同时在两个分叉上同时生产区块。 如果一个区块生产者被抓到做这样的事儿，那么这个生产者将很可能被投票投出。 这些双重生产行为对应密码学凭证可以用来自动的删除这些滥用者。

<!-- Furthermore, no block producer should be producing blocks on two forks at the same time. A block producer caught doing this will likely be voted out. Cryptographic evidence of such double-production may also be used to automatically remove abusers. -->
__+++__

此外，区块生产者不应该同时在两个分叉上出块。 此行为一经发现, 可能会被投票出局，很可能会被淘汰。 这种双重生产的加密证据也可用于自动消除滥用者。

<!-- Byzantine Fault Tolerance is added to traditional DPOS by allowing all producers to sign all blocks so long as no producer signs two blocks with the same timestamp or the same block height. Once 15 producers have signed a block the block is deemed irreversible. Any byzantine producer would have to generate cryptographic evidence of their treason by signing two blocks with the same timestamp or blockheight. Under this model a irreversible consensus should be reachable within 1 second. -->
__+++__

在传统的 dpos 中添加 BFT，允许所有区块生产者签署所有区块，只要没有区块生产者用同样的时间戳或同样的块高签署两个区块。 一旦15个区块生产者签署了一个区块，这个区块就被认为是不可逆转的。 任何区块生产者在BFT机制下, 想要在同一时刻或者同一区块高度下签署2个不同的区块, 都可以在加密的证据下被发现.  在这种模式下，一个不可逆转的共识应该会在1秒内达成。

## Transaction Confirmation 交易确认
<!-- Typical DPOS blockchains have 100% block producer participation. A transaction can be considered confirmed with 99.9% certainty after an average of 0.25 seconds from time of broadcast. -->
__+++__

通常 DPOS 区块链有 100% 的块生产者参与。 一个交易从广播开始后平均 0.25 秒就可以 99.9% 被认为是确认了。

<!-- In addition to DPOS, EOS.IO adds asynchronous Byzantine Fault Tolerance (aBFT) for faster achievement of irreversibility. The aBFT algorithm provides 100% confirmation of irreversibility within 1 second. -->
__+++__

除了 DPOS，EOS.IO 还添加了异步拜占庭将军问题(aBFT) ，以更快地实现不可逆转性。 aBFT 算法在1秒内提供100% 的不可逆性确认。

## Transaction as Proof of Stake (TaPoS) 交易作为股份的证明(TaPoS)
<!-- The EOS.IO software requires every transaction to include part of the hash of a recent block header. This hash serves two purposes: -->

EOS.IO 软件需要每一个交易包含最近一个区块头的哈希值。这个哈希值有两个目的：

  1. 防止不包含区块引用的交易在分叉时重放发生；和
  2. 通知网络对应的用户和他们的股份当前在某个具体的分叉上。

<!-- Over time all users end up directly confirming the blockchain which makes it difficult to forge counterfeit chains as the counterfeit would not be able to migrate transactions from the legitimate chain. -->

随着时间的推移，所有的用户直接确认区块链，在这一链条上难以伪造假的链条，因为假的链条根本无法从合法链条上迁移交易。

# Accounts 帐户
<!-- The EOS.IO software permits all accounts to be referenced by a unique human readable name of up to 12 characters in length. The name is chosen by the creator of the account. The account creator must reserve the RAM required to store the new account until the new account stakes tokens to reserve its own RAM. -->

Eos.io 软件允许用一个唯一的可读名称长达12个字符来引用所有账户。 这个名字是由帐户的创建者选择的。 帐户创建者必须保留存储新帐户所需的内存，直到新账户注入储存其自己的内存的 token。

<!-- In a decentralized context, application developers will pay the nominal cost of account creation to sign up a new user. Traditional businesses already spend significant sums of money per customer they acquire in the form of advertising, free services, etc. The cost of funding a new blockchain account should be insignificant in comparison. Fortunately, there is no need to create accounts for users already signed up by another application. -->

在一个去中心化的场景中，应用开发者将会为新用户注册成本买单。 传统商业已经在每个客户身上花费了大量的金钱，包括广告，免费服务等形式。 比起来，资助一个新的区块链帐户的花费简直微不足道。 值得庆幸的是，对一个已经在另一个应用注册过的用户并不需要再创建新的帐户。

## Actions & Handlers 操作 & 处理
<!-- Each account can send structured Actions to other accounts and may define scripts to handle Actions when they are received. The EOS.IO software gives each account its own private database which can only be accessed by its own action handlers. Action handling scripts can also send Actions to other accounts. The combination of Actions and automated action handlers is how EOS.IO defines smart contracts. -->

每个帐户可以发送结构化的消息给其他的帐户，并且可以定义脚本来处理他们接收到的消息。 EOS.IO 软件给每个帐户提供了只有自己的消息处理脚本能访问的私有数据库。 消息处理脚本同样可以给其他帐户发送消息。 消息和自动化的消息处理的结合决定了 EOS.IO 如何定义智能合约的。

<!-- To support parallel execution, each account can also define any number of scopes within their database. The block producers will schedule transaction in such a way that there is no conflict over memory access to scopes and therefore they can be executed in parallel. -->
__+++__

为了支持并行执行，每个帐户还可以在数据库中定义任何数量的scope。 区块生产者将以一种不会对scopes发生内存访问冲突的方式安排事务，因此可以并行执行。

## Role Based Permission Management 基于角色的权限管理
<!-- Permission management involves determining whether or not an Action is properly authorized. The simplest form of permission management is checking that a transaction has the required signatures, but this implies that required signatures are already known. Generally, authority is bound to individuals or groups of individuals and is often compartmentalized. The EOS.IO software provides a declarative permission management system that gives accounts fine grained and high-level control over who can do what and when. -->

权限管理涉及判定一条消息是否被正确的授权。 权限管理最简单的形式就是检查一个交易包含必须的签名，但这意味着必须的签名是已知的。 一般情况下，权威必然是独立的个体或者个体组成的群体，并且是被划分开的。 EOS.IO 软件提供了声明式的权限管理系统，通过管理谁可以在什么时间做什么来给用户细力度和高维度的控制。

<!-- It is critical that authentication and permission management be standardized and separated from the business logic of the application. This enables tools to be developed to manage permissions in a general-purpose manner and also provide significant opportunities for performance optimization. -->

授权和权限管理被标准化和脱离应用的商业逻辑是不可取的。 这使得管理权限的工具得以被开发，既满足常规的需求又为性能优化提供了重要的可能性。

<!-- Every account may be controlled by any weighted combination of other accounts and private keys. This creates a hierarchical authority structure that reflects how permissions are organized in reality and makes multi-user control over accounts easier than ever. Multi-user control is the single biggest contributor to security, and, when used properly, it can greatly reduce the risk of theft due to hacking. -->

每一个帐户可以被任何权重组合的其他帐户和私钥管控。 这创建了分层级的权利结构，这反映了现实中的权限分配方式，并且让多用户共同管理资产变得从未如此简单。 多用户控制是安全最大的贡献者，并且，当用户使用得当，它可以极大的消除因被黑而导致被盗窃的风险。

<!-- EOS.IO software allows accounts to define what combination of keys and/or accounts can send a particular Action type to another account. For example, it is possible to have one key for a user's social media account and another for access to the exchange. It is even possible to give other accounts permission to act on behalf of a user's account without assigning them keys. -->


EOS.IO software allows accounts to define what combination of keys and/or accounts can send a particular message type to another account. 举个例子，可以指定一个密钥给一个用户的社交媒体账号，同时另一个密钥访问交易所。 甚至可以给其他帐户权限来代表自己而无需分配给他们密钥。

### Named Permission Levels 命名权限级别

<img align="right" src="http://eos.io/wpimg/diagram3.png" width="228.395px" height="300px" />

<!-- Using the EOS.IO software, accounts can define named permission levels each of which can be derived from higher level named permissions. Each named permission level defines an authority; an authority is a threshold multi-signature check consisting of keys and/or named permission levels of other accounts. For example, an account's "Friend" permission level can be set for an Action on the account to be controlled equally by any of the account's friends. -->

在 EOS.IO 软件中，帐户可以定义命名的权限级别，每一个是由更高级别的命名权限派生而来。 每一个命名的权限级别定义了一个权威；一个权威是多重签名阈值校验，它包含密钥和／或其他帐户的命名权限级别。 打个比方，一个帐户的“朋友”权限级别可以被设置为由该帐户的任何一个朋友无差别的控制。

<!-- Another example is the Steem blockchain which has three hard-coded named permission levels: owner, active, and posting. The posting permission can only perform social actions such as voting and posting, while the active permission can do everything except change the owner. The owner permission is meant for cold storage and is able to do everything. The EOS.IO software generalizes this concept by allowing each account holder to define their own hierarchy as well as the grouping of actions. -->

另一个例子是 Steem 区块链，它有三个硬编码的命名权限级别: 所有者，活跃和发布。 发布权限只能执行投票和发帖等社会活动，而主动权限可以做除更改所有者之外的所有事情。 所有者的许可是用来冷藏的，可以做任何事情。 软件通过允许每个帐户持有者定义自己的层次结构以及行动的分组，从而概括了这一概念。

### Permission Mapping 权限映射
<!-- EOS.IO software allows each account to define a mapping between a contract/action or contract of any other account and their own Named Permission Level. For example, an account holder could map the account holder's social media application to the account holder's "Friend" permission group. With this mapping, any friend could post as the account holder on the account holder's social media. Even though they would post as the account holder, they would still use their own keys to sign the Action. This means it is always possible to identify which friends used the account and in what way. -->

Eos.io 软件允许每个帐户定义合约 / 操作或任何其他账户的合约与它们自己的命名权限之间的映射。 例如，帐户持有人可以将账户持有人的社交媒体应用程序映射到帐户持有人的"朋友"权限组。 有了这个映射，任何朋友都可以在账户持有人的社交媒体上担任账户持有人。 即使他们将作为帐户持有人，他们仍然会使用自己的钥匙签署该行动。 这意味着总是有可能确定哪些朋友使用了这个账户，以何种方式使用。

### Evaluating Permissions 评估权限
<!-- When delivering an Action of type "Action", from @alice to @bob the EOS.IO software will first check to see if @alice has defined a permission mapping for @bob.groupa.subgroup.Action. If nothing is found then a mapping for @bob.groupa.subgroup then @bob.groupa, and lastly @bob will be checked. If no further match is found, then the assumed mapping will be to the named permission group @alice.active. -->

当 **@alice** 以 "**Action**" 类型发送一条消息给 **@bob** 时，EOS.IO 软件首先会检查 **@alice** 是否为 **@bob.groupa.subgroup.Action** 定义过权限映射。 如果什么都没有找到，紧接着检查 **@bob.groupa.subgroup** 映射，然后是 **@bob.groupa**，最后 **@bob** 将被检查。 如果都没有找到，那么假定映射为命名的权限群组 **@alice.active**。

<!-- Once a mapping is identified then signing authority is validated using the threshold multi-signature process and the authority associated with the named permission. If that fails, then it traverses up to the parent permission and ultimately to the owner permission, @alice.owner. -->

一旦一个映射被识别，则通过阈值多签名流程验证签名权威，并且关联权威与命名的权限。 如果失败了，则跃迁至父权限，直至拥有者权限，**@alice.owner**。

<img align="center" src="http://eos.io/wpimg/diagram2grayscale2.jpg" width="845.85px" height="500px" />

#### Default Permission Groups 默认权限组
<!-- The EOS.IO technology also allows all accounts to have an "owner" group which can do everything, and an "active" group which can do everything except change the owner group. All other permission groups are derived from "active". -->

Eos.io 技术还允许所有账户都有一个可以做任何事情的"owner"分组，以及一个除了改变所有者群体之外可以做任何事情的"active"分组。 所有其他权限组都来自"active"。

#### Parallel Evaluation of Permissions 权限的并行评估
<!-- The permission evaluation process is "read-only" and changes to permissions made by transactions do not take effect until the end of a block. This means that all keys and permission evaluation for all transactions can be executed in parallel. Furthermore, this means that a rapid validation of permission is possible without starting costly application logic that would have to be rolled back. Lastly, it means that transaction permissions can be evaluated as pending transactions are received and do not need to be re-evaluated as they are applied. -->

权限评估过程是“只读”的，并且通过交易对权限的变更在一个区块结束之前不会起作用。 这意味着对所有的交易对应的密钥和权限评估可以被并行执行。 此外，这意味着一个快速的权限验证是可行的，它无需启动会引起回滚需求的高成本的应用逻辑。 最后，这意味着交易权限可以被评估即便接收到等待的交易，并且之后无需再重新评估。

<!-- All things considered, permission verification represents a significant percentage of the computation required to validate transactions. Making this a read-only and trivially parallelizable process enables a dramatic increase in performance. -->

从各方面考虑，权限验证占据了验证交易计算量的很大比例。 让其只读和普遍的并发处理将会使得性能有一个质的飞跃。

<!-- When replaying the blockchain to regenerate the deterministic state from the log of Actions there is no need to evaluate the permissions again. The fact that a transaction is included in a known good block is sufficient to skip this step. This dramatically reduces the computational load associated with replaying an ever growing blockchain. -->

当从消息日志中重新生成确定性状态时不再需要重复的权限验证。 事实是一个交易如果被包含近了一个被认为不存在问题的区块时它就有足够的理由跳过这 步这将极大减少因为区块链增长拉去过去记录时的计算量。

#### Actions with Mandatory Delay 强制延迟的操作
<!-- Time is a critical component of security. In most cases, it is not possible to know if a private key has been stolen until it has been used. Time based security is even more critical when people have applications that require keys be kept on computers connected to the internet for daily use. The EOS.IO software enables application developers to indicate that certain Actions must wait a minimum period of time after being included in a block before they can be applied. During this time, they can be cancelled. -->

时间是安全的重要组成部分。 在大多数情况下，在使用私钥之前，不可能知道它是否被盗。 当人们的应用程序需要在连接互联网的计算机上每天使用时，基于时间的安全性就更为关键。 Eos.io 软件使应用程序开发人员能够指出，某些操作在被包含在一个块之后，必须等待一段最短的时间，然后才能应用。 在此期间，他们可以被取消。

<!-- Users can then receive notice via email or text message when one of these Actions is broadcast. If they did not authorize it, then they can use the account recovery process to recover their account and retract the Action. -->

__+++__

用户可以通过电子邮件或短信收到通知，当其中一个操作被广播时。 如果他们没有授权，那么他们可以使用帐户恢复过程来恢复他们的帐户并撤回 Action。

<!-- The required delay depends upon how sensitive an operation is. Paying for a coffee might have no delay and be irreversible in seconds, while buying a house may require a 72 hour clearing period. Transferring an entire account to new control may take up to 30 days. The exact delays are chosen by application developers and users. -->

所需的延迟取决于操作的敏感度。 花钱买咖啡可能不会有延迟，并且在几秒钟内不可逆转，而购买一所房子可能需要72小时的结算期。 将整个账户转移到新的控制中可能需要30天。 确切的延迟是由应用程序开发者和用户选择的。

## Recovery from Stolen Keys 恢复被盗窃的密钥
<!-- The EOS.IO software provides users a way to restore control of their account when keys are stolen. An account owner can use any owner key that was active in the last 30 days along with approval from their designated account recovery partner to reset the owner key on their account. The account recovery partner cannot reset control of the account without the help of the owner. -->

EOS.IO 软件提供给用户一种找回自己失窃密钥控制权的方式。 一个帐户的所有者可以使用过去 30 天任何活跃的拥有者密钥与事先指定的合作者帐户给出的批准来重置自己帐户的密钥。 帐户的恢复合作者在没有所有人帮助的情况下无法重置帐户的控制权。

<!-- There is nothing for the hacker to gain by attempting to go through the recovery process because they already "control" the account. Furthermore, if they did go through the process, the recovery partner would likely demand identification and multi-factor authentication (phone and email). This would likely compromise the hacker or gain the hacker nothing in the process. -->

黑客尝试进行恢复流程是无意义的，因为他们已经“控制”了帐户。 此外，就算他们真的进行这一流程，恢复合作者也会询问身份证明和多因素认证 (手机和邮件)。 这会让黑客脱作出让步或者无功而返。

<!-- This process is also very different from a simple multi-signature arrangement. With a multi-signature transaction, another entity is made a party to every transaction that is executed. By contrast, with the recovery process the recovery partner is only a party to the recovery process and has no power over the day-to-day transactions. This dramatically reduces costs and legal liabilities for everyone involved. -->

这一流程与简单的多重签名有很大差异。 在多重签名中，另一个公司要参与所有转账的执行，但在恢复流程中，它却只在恢复时才起作用对每天的转账无从干预。 这大大的降低了参与者的成本和法律责任。

# Deterministic Parallel Execution of Applications 应用程序的确定性并行执行
<!-- Blockchain consensus depends upon deterministic (reproducible) behavior. This means all parallel execution must be free from the use of mutexes or other locking primitives. Without locks there must be some way to guarantee that transactions that may be executed in parallel do not create non-deterministic results. -->

区块链共识取决于确定性 (可重现的) 的行为。 这意味着所有的并行计算必须是不能互斥或者具有其他锁特性的。 没有了锁就必须有一些方式可以确保所有的帐户只可以读取和写入他们自己的私有数据库。 这也意味着每个帐户处理消息是顺序的，而并发只能在帐户层面进行。

<!-- The June 2018 release of EOS.IO software will run single threaded, yet it contains the data structures necessary for future multithreaded, parallel execution. -->

__+++__

2018年6月发布的 EOS.IO 软件将运行单线程，但它包含了未来多线程并行执行所需的数据结构。

<!-- In an EOS.IO software-based blockchain, once parallel operation is enabled, it will be the job of the block producer to organize Action delivery into independent shards so that they can be evaluated in parallel. The schedule is the output of a block producer and will be deterministically executed, but the process for generating the schedule need not be deterministic. This means that block producers can utilize parallel algorithms to schedule transactions. -->

在一个基于 EOS.IO 软件的区块链中，一旦启用并行操作，则块生产商的工作是将 Action 交付组织到独立的分片中，以便可以并行地进行评估。 时间表是一个块生成器的输出，并且将被确定地执行，但是生成计划的过程不需要确定性。 这意味着区块生产者可以利用并行算法来调度交易。

<!-- Part of parallel execution means that when a script generates a new Action it does not get delivered immediately, instead it is scheduled to be delivered in the next cycle. The reason it cannot be delivered immediately is because the receiver may be actively modifying its own state in another shard. -->

并行执行的一方面意味着当一个脚本生成了一个新的操作，它不会立即被发送，而被安排在下一个轮训中发送。 不能立马发出的原因是接受者可能在另一个线程中活跃的变更自己的状态。

## Minimizing Communication Latency 最小化通信延迟
Latency is the time it takes for one account to send an Action to another account and then receive a response. The goal is to enable two accounts to exchange Actions back and forth within a single block without having to wait 0.5 seconds between each Action. To enable this, the EOS.IO software divides each block into cycles. Each cycle is divided into shards and each shard contains a list of transactions. Each transaction contains a set of Actions to be delivered. This structure can be visualized as a tree where alternating layers are processed sequentially and in parallel.

__+++__

延迟是一个帐户发送一个操作到另一个帐户，然后收到响应的时间。 目标是让两个账户在一个块内来回交换操作，而不需要在每个 Action 之间等待0.5秒。 为了实现这一点，EOS.IO 软件将每个块分成了周期。 每个周期被分成碎片，每个碎片包含一个事务列表。 每个事务包含一组要传递的操作。 这种结构可视为一棵树，其中交替的层被顺序处理和并行处理。

  区块

    区域

      循环 (顺序)

        线程 (并行)

          交易 (顺序)

            操作 (顺序)

              接受者和被通知帐户 (并行)
<!-- Transactions generated in one cycle can be delivered in any subsequent cycle or block. Block producers will keep adding cycles to a block until the maximum wall clock time has passed or there are no new generated transactions to deliver. -->

在一个循环中生成的交易可以在后续的任何一个循环或者区块中被发送。 区块生产者会持续不断的向区块中添加循环直到最大的墙上时间到了或者没有更多的新交易要发送。

<!-- It is possible to use static analysis of a block to verify that within a given cycle no two shards contain transactions that modify the same account. So long as that invariant is maintained a block can be processed by running all shards in parallel. -->

可以对一个区块使用静态分析来验证同一个循环内不存在两个线程包含同一帐户下对交易的变更。 只要保持不变一个区块就可以并行的运行所有的线程。

## Read-Only Action Handlers 只读操作处理
<!-- Some accounts may be able to process an Action on a pass/fail basis without modifying their internal state. If this is the case, then these handlers can be executed in parallel so long as only read-only Action handlers for a particular account are included in one or more shards within a particular cycle. -->
__+++__

有些账户可以在不修改其内部状态的情况下处理关于通过 / 不通过的操作。 如果是这种情况，那么只要某个特定帐户的只读操作处理程序包含在特定周期内的一个或多个分片中，那么这些处理程序就可以并行执行。

## Atomic Transactions with Multiple Accounts 多帐户的原子化交易
<!-- Sometimes it is desirable to ensure that Actions are delivered to and accepted by multiple accounts atomically. In this case both Actions are placed in one transaction and both accounts will be assigned the same shard and the Actions applied sequentially. -->

有时候，我们应该确保操作能够被多个账户以原子方式交付并被多个账户接受。 在这种情况下，两个操作都放在一个交易中，两个账户将被分配相同的分片和时序的操作。

## Partial Evaluation of Blockchain State 区块链状态的部分评估
<!-- Scaling blockchain technology necessitates that components are modular. Everyone should not have to run everything, especially if they only need to use a small subset of the applications. -->

扩展区块链技术使得组件化成为必要。每个人不应该执行所有的事务，尤其是当其只需要运行应用的一个小的子集。

<!-- An exchange application developer runs full nodes for the purpose of displaying the exchange state to its users. This exchange application has no need for the state associated with social media applications. EOS.IO software allows any full node to pick any subset of applications to run. Actions delivered to other applications are safely ignored if your application never depends upon the state of another contract. -->

一个交易所应用开发者运行一个完整节点位的是为其用户展现所有的状态。 这个交易所应用没有与社交网络建立关联的必要性。 EOS.IO 软件允许任何的完整节点选择应用的任何子集来执行。 如果你的app永远不会依赖于某个合约的状态, 那么对于这个合约的app的所有操作可以安全的忽略。

## Subjective Best Effort Scheduling 自主最优调度

<!-- The EOS.IO software cannot obligate block producers to deliver any Action to any other account. Each block producer makes their own subjective measurement of the computational complexity and time required to process a transaction. This applies whether a transaction is generated by a user or automatically by a smart contract. -->

EOS.IO 软件并不能为区块生产生者为任何其他帐户送达的任何信息负责。 每个区块生产者要对计算的发杂读和处理一个消息的时间自己进行主观上的预测。 这同时适用于用户生成的和脚本自动生成的交易。

<!-- On a launched blockchain adopting the EOS.IO software, at a network level all transactions are billed a computational bandwidth cost based on the number of WASM instructions executed. However, each individual block producer using the software may calculate resource usage using their own algorithm and measurements. When a block producer concludes that a transaction or account has consumed a disproportionate amount of the computational capacity they simply reject the transaction when producing their own block; however, they will still process the transaction if other block producers consider it valid. -->

在一个采用 EOS.IO 软件的区块链上，在网络层面上，所有的交易都根据执行的 WASM 指令的数计算出的带宽成本来收费。 然而，使用该软件的每个单独的块生产者可以使用自己的算法和度量来计算资源的使用情况。 当一个块生产者认为交易或账户消耗了不成比例的计算能力时，他们在生成自己的块时拒绝该交易; 然而，如果其他块生产者认为该交易有效，他们仍将处理交易。

<!-- In general, so long as even 1 block producer considers a transaction as valid and under the resource usage limits then all other block producers will also accept it, but it may take up to 1 minute for the transaction to find that producer. -->

一般而言，只要一个区块生产者认为交易在资源使用限度内是有效的，那么其他区块生产者就也要接受，但可能交易传递给生产者就要花费 1 分钟。

<!-- In some cases, a producer may create a block that includes transactions that are an order of magnitude outside of acceptable ranges. In this case the next block producer may opt to reject the block and the tie will be broken by the third producer. This is no different than what would happen if a large block caused network propagation delays. The community would notice a pattern of abuse and eventually remove votes from the rogue producer. -->

在某些情况下，生产者可以创建包含可接受范围之外的数量级的块。 在这种情况下，下一个区块生产者可能会选择拒绝区块和束缚将被第三个生产者打破。 这和因为区块过大导致的网络延时没什么不同。 社区会注意到模式的异常并最终会将票从流氓生产者那里删掉。

<!-- This subjective evaluation of computational cost frees the blockchain from having to precisely and deterministically measure how long something takes to run. With this design there is no need to precisely count instructions which dramatically increases opportunities for optimization without breaking consensus. -->

这种对计算成本的主观评估将区块链从必须精确和确定的预测一些东西要花多长时间来运行这一问题中解放出来。 有了这一设计就不需要精确的数指令，将极大的增加优化的可能性又不必打破共识。

__+++__

## Deferred Transactions 延迟交易

<!-- EOS.IO Software supports deferred transactions that are scheduled to execute in the future. This enables computation to move to different shards and/or the creation of long-running processes that continuously schedule a continuance transaction. -->

Eos.io 软件支持计划在未来执行的延迟交易。 这使得计算能够移动到不同的shards和/或创建长期运行的进程来对一个暂停的交易继续进行。

__+++__

## Context Free Actions 上下文无关操作

<!-- A Context Free Action involves computations that depend only on transaction data, but not upon the blockchain state. Signature verification, for example, is a computation that requires only the transaction data and a signature to determine the public key that signed the transaction. This is one of the most expensive individual computations a blockchain must perform, but because this computation is context free it can be performed in parallel. -->

上下文无关操作包括只依赖交易数据的计算，而不是区块链状态。 例如，签名验证是一种只需要交易数据和签名就能确定签名交易的公钥的计算。这是一个区块链必须执行的最昂贵的单独计算之一，但是因为这种计算是无上下文的，所以可以并行执行。

<!-- Context Free Actions are like other user Actions, except they lack access to the blockchain state to perform validation. Not only does this enable EOS.IO to process all Context Free Actions such as signature verification in parallel, but more importantly, this enables generalized signature verification. -->

上下文无关操作和其他用户操作一样，只是无法访问区块链状态来执行验证。 这不仅使 EOS.IO 能够处理所有上下文无关操作，例如并行的签名验证，而且更重要的是，这使得广义签名验证成为可能。

<!-- With support for Context Free Actions, scalability techniques such as Sharding, Raiden, Plasma, State Channels, and others become much more parallelizable and practical. This development enables efficient inter-blockchain communication and potentially unlimited scalability. -->

随着对上下文无关操作的支持，诸如 Sharding、Raiden、Plasma、State Channels等可扩展性技术变得更具有并行性和实用性。 这种开发使得跨链通信和潜在无限的可伸缩性变为可能。

# Token Model and Resource Usage 模型与资源使用

__PLEASE NOTE: CRYPTOGRAPHIC TOKENS REFERRED TO IN THIS WHITE PAPER REFER TO CRYPTOGRAPHIC TOKENS ON A LAUNCHED BLOCKCHAIN THAT ADOPTS THE EOS.IO SOFTWARE. THEY DO NOT REFER TO THE ERC-20 COMPATIBLE TOKENS BEING DISTRIBUTED ON THE ETHEREUM BLOCKCHAIN IN CONNECTION WITH THE EOS TOKEN DISTRIBUTION.__

__请注意: 本白皮书中提及的加密令牌指的是在一个启动的区块链上采用 EOS.IO 软件的加密令牌。 它们不涉及与 EOS 令牌分布有关的 ETHEREUM 区块链上分布的 ERC-20兼容令牌。__

<!-- All blockchains are resource constrained and require a system to prevent abuse. With a blockchain that uses EOS.IO software, there are three broad classes of resources that are consumed by applications: -->

所有的区块链都受到资源限制，需要一个防止滥用的系统。 通过使用 EOS.IO 软件的区块链，应用程序所消耗的资源有三大类:

1. Bandwidth and Log Storage (Disk); 带宽及记录储存(磁盘) ;
2. Computation and Computational Backlog (CPU); and 计算及计算积压(CPU) ; 以及
3. State Storage (RAM). 状态存储器(RAM)

<!-- Bandwidth and computation have two components, instantaneous usage and long-term usage. A blockchain maintains a log of all Actions and this log is ultimately stored and downloaded by all full nodes. With the log of Actions, it is possible to reconstruct the state of all applications. -->

带宽和计算有两部分，瞬时使用和长期使用。 一个区块链维持着所有消息的日志，这些日志最终由完全节点存储和下载。 通过消息日志可以重现所有应用的状态。

<!-- The computational debt is calculations that must be performed to regenerate state from the Action log. If the computational debt grows too large then, it becomes necessary to take snapshots of the blockchain's state and discard the blockchain's history. If computational debt grows too quickly then it may take 6 months to replay 1 year worth of transactions. It is critical, therefore, that the computational debt be carefully managed. -->

可计算债务是一个必须通过操作日志重新构建状态的计算结果。 如果可计算债务增长变得臃肿则有必要通过快照方式记录区块链状态，并丢弃区块链历史。 如果可计算债务增长过快，则它需要花费 6 个月时间来重放等值与 1 年的交易。 这很不可取，因此，可计算债务需要被细心的管理。。

<!-- Blockchain state storage is information that is accessible from application logic. It includes information such as order books and account balances. If the state is never read by the application, then it should not be stored. For example, blog post content and comments are not read by application logic, so they should not be stored in the blockchain's state. Meanwhile the existence of a post/comment, the number of votes, and other properties do get stored as part of the blockchain's state. -->

区块链状态存储是通过访问应用逻辑获取的信息。 它包括诸如挂单和账户余额等信息。 如果状态从未被应用读取则它不会被存储。 比如，博客发布的内容和评论如未被应用逻辑读取则他们就不应该存储在区块链状态中。 同时，发布的内容／评论的存在、投票的数量和其他属性要作为区块链状态的部分被存储下来。

<!-- Block producers publish their available capacity for bandwidth, computation, and state. The EOS.IO software allows each account to consume a percentage of the available capacity proportional to the amount of tokens held in a 3-day staking contract. For example, if a blockchain based on the EOS.IO software is launched and if an account holds 1% of the total tokens distributable pursuant to that blockchain, then that account has the potential to utilize 1% of the state storage capacity. -->

区块生产者对外发布他们可用的带宽，计算能力和状态。 EOS.IO 允许帐户按比例消耗一个 3 天对赌合约中的可用资源。 举个例子，如果一个基于 EOS.IO 的区块链启动了，一个帐户持有所有 token 发行总量的 1%，那么帐号就具有使用 1% 状态存储空间的能力。

<!-- Adopting the EOS.IO software on a launched blockchain means bandwidth and computational capacity are allocated on a fractional reserve basis because they are transient (unused capacity cannot be saved for future use). The algorithm used by EOS.IO software is similar to the algorithm used by Steem to rate-limit bandwidth usage. -->

在一个已经启动的区块链上采用 EOS.IO 软件意味着带宽和计算能力分配在一个分数储备基础上，因为它们是暂时的(未使用的容量不能保存以备将来使用)。 Eos.io 软件所使用的算法类似于 Steem 用于速率极限带宽的算法。

## Objective and Subjective Measurements 客观与主观的度量

<!-- As discussed earlier, instrumenting computational usage has a significant impact on performance and optimization; therefore, all resource usage constraints are ultimately subjective, and enforcement is done by block producers according to their individual algorithms and estimates. These would typically be implemented by a block producer via the writing of a custom plugin. -->

如前所述，检测计算使用的性能和优化的影响很大；因此，所有资源的使用限制，最终都是主观的，执行依靠个人的算法和区块生产者进行估计。

<!-- That said, there are certain things that are trivial to measure objectively. The number of Actions delivered, and the size of the data stored in the internal database are cheap to measure objectively. The EOS.IO software enables block producers to apply the same algorithm over these objective measures but may choose to apply stricter subjective algorithms over subjective measurements. -->

也就是说，有些事情是微不足道的，无法客观地衡量。 交付的操作数量，以及存储在内部数据库中的数据的大小, 客观上度量是廉价的。 软件允许块生产者在这些客观度量上应用相同的算法，但是可以选择适用更加严格的主观算法而不是主观措施。

## Receiver Pays 接收方付费

<!-- Traditionally, it is the business that pays for office space, computational power, and other costs required to run the business. The customer buys specific products from the business and the revenue from those product sales is used to cover the business costs of operation. Similarly, no website obligates its visitors to make micropayments for visiting its website to cover hosting costs. Therefore, decentralized applications should not force its customers to pay the blockchain directly for the use of the blockchain. -->

传统上来说，企业为办公场地、计算力和其他为了运行企业而需要的成本买单。 客户从企业购买具体的产品，产品销售产生的利润来盖过企业运作的成本。 类似的，没有哪个网站要求来访者为盖过运作成本而支付。 因此，去中心化应用也不应该强制用户因为使用了区块链而直接为区块链支付。

<!-- A launched blockchain that uses the EOS.IO software does not require its users to pay the blockchain directly for its use and therefore does not constrain or prevent a business from determining its own monetization strategy for its products. -->

一个使用 EOS.IO 软件启动的区块链，不要求其用户直接为其使用区块链而支付，因此不会约束或阻止企业为其产品确定自己的货币化策略。

<!-- While it is true that the receiver can pay, EOS.IO enables the sender to pay for bandwidth, computation, and storage. This empowers application developers to pick the method that is best for their application. In many cases sender-pays significantly reduces complexity for application developers who do not want to implement their own rationing system. Application developers can delegate bandwidth and computation to their users and then let the “sender pays” model enforce the usage. From the perspective of the end user it is free, but from the perspective of the blockchain it is sender-pays. -->

__+++__

虽然接收者确实可以支付，但 EOS.IO 允许发送者支付带宽、计算和存储费用。 这使应用程序开发人员能够选择最适合他们应用的方法。 在许多情况下，发送者付费大大降低了不想实现自己的配给系统的应用程序开发人员的复杂性。 应用程序开发人员可以将带宽和计算委托给用户，然后让"发送者付费"模型强制使用。 从最终用户的角度来看，它是免费的，但从封锁链的角度来看，它是发送者付费。

## Delegating Capacity 委托能力

<!-- A holder of tokens on a blockchain launched adopting the EOS.IO software who may not have an immediate need to consume all or part of the available bandwidth, can delegate or rent such unconsumed bandwidth to others; the block producers running EOS.IO software on such blockchain will recognize this delegation of capacity and allocate bandwidth accordingly. -->

一个区块链上的tokens持有者启动了 EOS.IO 软件，这些软件可能不需要立即消耗全部或部分可用带宽，可以将这种未消耗的带宽委托给其他人; 在这样的区块链上运行 EOS.IO 软件的区块生产者将认识到这种能力委托并相应地分配带宽。

## Separating Transaction costs from Token Value 分离交易成本与 Token 价值

<!-- One of the major benefits of the EOS.IO software is that the amount of bandwidth available to an application is entirely independent of any token price. If an application owner holds a relevant number of tokens on a blockchain adopting EOS.IO software, then the application can run indefinitely within a fixed state and bandwidth usage. In such case, developers and users are unaffected from any price volatility in the token market and therefore not reliant on a price feed. In other words, a blockchain that adopts the EOS.IO software enables block producers to naturally increase bandwidth, computation, and storage available per token independent of the token's value. -->

EOS.IO软件的主要好处之一是，应用程序可用的带宽数量完全独立于任何token价格。 如果应用程序所有者采用 EOS.IO 软件在区块链上持有相关数量的token，则该应用程序可以在固定状态和带宽使用范围内无限期地运行。 在这种情况下，开发者和用户不受token市场任何价格波动的影响，因此不依赖于价格反馈。 换句话说，EOS.IO 使块生产者能够独立于token的价值, 自然地增加带宽，计算和存储每个token的价值。

<!-- A blockchain using EOS.IO software also awards block producers tokens every time they produce a block. The value of the tokens will impact the amount of bandwidth, storage, and computation a producer can afford to purchase; this model naturally leverages rising token values to increase network performance. -->

一个使用 EOS.IO 软件的区块链每次在区块生产者生产出区块之后会奖励该生产者。Token 的值将影响其能购买的带宽、存储和计算资源；这一模型会自然的利用 token 值的上涨来增加网络的性能。

## State Storage Costs 状态存储成本

<!-- While bandwidth and computation can be delegated, storage of application state will require an application developer to hold tokens until that state is deleted. If state is never deleted, then the tokens are effectively removed from circulation. -->

由于带宽和计算资源可以被委托，因此应用的状态存储需要应用程序的开发者持有 token 直到状态被删除。 如果状态永远不会被删除那么 token 实质上从流通中被抹除。

## Block Rewards 块奖励

<!-- A blockchain that adopts the EOS.IO software will award new tokens to a block producer every time a block is produced. In these circumstances, the number of tokens created is determined by the median of the desired pay published by all block producers. The EOS.IO software may be configured to enforce a cap on producer awards such that the total annual increase in token supply does not exceed 5%. -->

EOS.IO 将奖励新的代币给一个块生产者。 在这种情况下，所创建的tokens数量取决于所有区块生产者公布的预期薪酬的中位数。 Eos.io 可以配置为强制执行生产者奖励上限，以便每年的令牌供应量增加不超过5% 。

__+++__

## Worker Proposal System Worker建议制度

<!-- In addition to electing block producers, pursuant to a blockchain based on the EOS.IO software, token holders can elect a number of Worker Proposals designed to benefit the community. The winning proposals will receive tokens of up to a configured percent of the token inflation minus those tokens that have been paid to block producers. These proposals will receive tokens proportional to the votes each application has received from token holders, up to the amount they request for performing their work. The elected proposals can be replaced by newly elected proposals by token holders. -->

除了基于区块链选举区块生产者外，token 持有者还可以选择一些旨在造福社区的工的提案。 获胜的提案将获得最高达到一个预配置的Token百分比减去那些已经支付给区块生产者的Token。 这些提案将获得与收到的票数成比例的代币，最高可达提案所要求的总量。 选举产生的提案可以由token 持有者新选的提案所取代。

<!-- The system contracts that implement Worker Proposals may not be in place at initial launch in June 2018, but the funding mechanism will. It will begin to accumulate funds at the same time block producer awards start. Since the Worker Proposal System will be implemented in WASM it can be added at a later date without a fork. -->

Worker Proposals的系统合约在2018年6月EOSIO主网启动时可能不会实现，但资金机制将会到位。 它将开始积累资金，在区块生产者奖励开始之后。 由于Worker Proposals系统将在WASM中实现，因此可以在以后不用分叉的情况下添加。

# Governance 治理

<!-- Governance is the process by which people in a community: -->
__+++__

治理是一个社区的人们通过:

  1. Reach consensus on subjective matters of collective action that cannot be captured entirely by software algorithms; 就集体行动的主观事项达成共识，而软件算法不能完全掌握这些问题;
  2. Carry out the decisions they reach; and 执行他们的决定; 以及
  3. Alter the governance rules themselves via Constitutional amendments. 通过宪法修正案改变治理规则本身

<!-- An EOS.IO software-based blockchain implements a governance process that efficiently directs the existing influence of block producers. Absent a defined governance process, prior blockchains relied ad hoc, informal, and often controversial governance processes that result in unpredictable outcomes. -->

基于 EOS.IO 的区块链实现了一个治理过程，有效地指导块生产者存在意义。 如果没有一个明确的治理过程，以前的区块链依赖于临时的、非正式的和经常有争议的治理过程，结果难以预测。

<!-- A blockchain based on the EOS.IO software recognizes that power originates with the token holders who delegate that power to the block producers. The block producers are given limited and checked authority to freeze accounts, update defective applications, and propose hard forking changes to the underlying protocol. -->

EOS.IO 认识到，权力源于将权力委托给块生产者的token持有者。 区块生产者被授予有限的检查权威来冻结帐户，升级有缺陷的应用程序，对底层协议提出硬分叉的改进建议。

<!-- Embedded into the EOS.IO software is the election of block producers. Before any change can be made to the blockchain these block producers must approve it. If the block producers refuse to make changes desired by the token holders then they can be voted out. If the block producers make changes without permission of the token holders then all other non-producing full-node validators (exchanges, etc) will reject the change. -->

嵌入到 EOS.IO 软件中的是块生产者的投票选举。 在对区块链没有做任何变更之前他们必须认可它。 如果区块生产者拒绝 token 持有者所预期的变更他们就会被投出。 如果区块生产者未经 token 持有者的授权作出变更，其他的非生产、完整验证 (交易所等) 会拒绝这些变更。

## Freezing Accounts 冻结帐户

<!-- Sometimes a smart contact behaves in an aberrant or unpredictable manner and fails to perform as intended; other times an application or account may discover an exploit that enables it to consume an unreasonable amount of resources. When such issues inevitably occur, the block producers have the power to rectify such situations. -->

有时一个智能合约的行为处于一种一场或不可预测的状态并且无法按照预期执行；另一些时候一个应用或帐户也许发现了一个可以销毁不可想像数量资源的漏洞。 当这些问题不可避免的发生时，区块生产者有能力来扭转这一局面。

<!-- The block producers on all blockchains have the power to select which transactions are included in blocks which gives them the ability to freeze accounts. A blockchain using EOS.IO software formalizes this authority by subjecting the process of freezing an account to a 15/21 vote of active producers. If the producers abuse the power they can be voted out and an account will be unfrozen. -->

__+++__

所有区块链上的区块生产者都有权选择哪些交易被包含在块中，这使他们有能力冻结账户。EOS.IO 通过将冻结账户的过程定为活跃生产者的__15 / 21__投票，从而使这一权力正式化。 如果块生产者滥用权力，他们就会被淘汰，账户将被解冻。

## Changing Account Code 更改帐户代码

<!-- When all else fails and an "unstoppable application" acts in an unpredictable manner, a blockchain using EOS.IO software allows the block producers to replace the account's code without hard forking the entire blockchain. Similar to the process of freezing an account, this replacement of the code requires a 15/21 vote of elected block producers. -->

当所有其他方法都失败时，一个"不可阻挡的应用程序"以不可预测的方式运行时，EOS.IO 允许区块生产者更换账户的代码，而无需对整个区块链进行严格的搜索。 与冻结账户的过程类似，代码的这种更换需要__15 / 21__的区块生产者的投票。

## Constitution 宪法

<!-- The EOS.IO software enables blockchains to establish a peer-to-peer terms of service agreement or a binding contract among those users who sign it, referred to as a "constitution". The content of this constitution defines obligations among the users which cannot be entirely enforced by code and facilitates dispute resolution by establishing jurisdiction and choice of law along with other mutually accepted rules. Every transaction broadcast on the network must incorporate the hash of the constitution as part of the signature and thereby explicitly binds the signer to the contract. -->

EOS.IO 应用使得区块链创建了一个点对点的服务条款协议或者绑定用户到一个合约，这都需要用户对其签名，简称“宪法”。 宪法的内容定义了仅仅依靠代码无法在用户间履行的义务，同时通过建立管辖权和可选的法律来解决相互间的争端。 每个在网络广播的交易都必须将宪法的哈希值作为签名的一部分，从而显性的将签名者绑定在合约中。

<!-- The constitution also defines the human-readable intent of the source code protocol. This intent is used to identify the difference between a bug and a feature when errors occur and guides the community on what fixes are proper or improper. -->

宪法还定义了人类可读意图的源代码协议。 这个意图是用来识别错误和功能之间的差异，当错误发生时，引导社区对什么是适当或不当修复。

## Upgrading the Protocol & Constitution 升级协议 & 宪法

__+++__

<!-- The EOS.IO software defines the following process by which the protocol, as defined by the canonical source code and its constitution, can be updated: -->

Eos.io 定义了下列过程，根据规范源代码及其章程定义的协议可以更新:

1. Block producers propose a change to the constitution and obtains 15/21 approval. 区块生产者建议修改宪法，并获得15 / 21的批准
2. Block producers maintain 15/21 approval of the new constitution for 30 consecutive days. 区块生产者连续30天保持对新宪法的15 / 21的批准
3. All users are required to indicate acceptance of the new constitution as a condition of future transactions being processed. 所有用户都必须表明接受新宪法作为未来交易处理的一个条件
4. Block producers adopt changes to the source code to reflect the change in the constitution and propose it to the blockchain using the hash of the new constitution. 区块生产者采用对源代码的修改，以反映宪法的变化，并将新宪法的哈希写到区块链中
5. Block producers maintain 15/21 approval of the new code for 30 consecutive days. 区块生产者连续30天保持对新代码的15 / 21的批准
6. Changes to the code take effect 7 days later, giving all non-producing full nodes 1 week to upgrade after ratification of the source code. 对代码的更改将在7天后生效，在批准源代码后，所有非生产者的完整节点在1周后升级
7. All nodes that do not upgrade to the new code shut down automatically. 所有没有升级到新代码的节点都会自动关闭

<!-- By default, configuration of the EOS.IO software, the process of updating the blockchain to add new features takes 2 to 3 months, while updates to fix non-critical bugs that do not require changes to the constitution can take 1 to 2 months. -->

按照 EOS.IO 的默认配置，添加新特性升级区块链的流程需要 2 到 3 个月，而修复一般的 bug 不需要更改宪法需要 1 到 2 个月时间。

### Emergency Changes 紧急变更
<!-- The block producers may accelerate the process if a software change is required to fix a harmful bug or security exploit that is actively harming users. Generally speaking it could be against the constitution for accelerated updates to introduce new features or fix harmless bugs. -->

区块生产者可以推荐软件的变更当 bug 是伤害性 bug 或安全溢出影响用户使用的。 一般来说，这可能是对宪法的加速更新，引进新的功能或修复无害的错误。

# Scripts & Virtual Machines 脚本和虚拟机
<!-- The EOS.IO software will be first and foremost a platform for coordinating the delivery of authenticated messages (called Actions) to accounts. The details of scripting language and virtual machine are implementation specific details that are mostly independent from the design of the EOS.IO technology. Any language or virtual machine that is deterministic and properly sandboxed with sufficient performance can be integrated with the EOS.IO software API. -->

Eos.io 软件将首先是一个平台，用于协调将经过身份验证的消息(称为 Actions)传递到帐户的平台。 脚本语言和虚拟机的具体实现与 EOS.IO 技术的设计是分离的。 任何语言或者虚拟主机，只要确定并适合沙盒，带有足够的运行效率均可以和 EOS.IO 软件 API 对接。

## Schema Defined Actions 模式定义的操作
<!-- All Actions sent between accounts are defined by a schema which is part of the blockchain consensus state. This schema allows seamless conversion between binary and JSON representation of the Actions. -->

所有在账户之间发送的操作都是由一个模式来定义的，这是区块链共识状态的一部分。 这个模式允许操作的二进制和 JSON 表示之间的无缝转换。

## Schema Defined Database 模式定义的数据库
<!-- Database state is also defined using a similar schema. This ensures that all data stored by all applications is in a format that can be interpreted as human readable JSON but stored and manipulated with the efficiency of binary. -->

数据库状态也是通过类似的模式来定义。 这是为了确保所有应用存储的数据是可以转化为人类可读的 JSON 但存储和控制时使用高效的二进制。

__+++__

## Generic Multi Index Database API 通用多索引数据库 API
<!-- Developing smart contracts requires a defined database schema to track, store, and find data. Developers commonly need the same data sorted or indexed by multiple fields and to maintain consistency among all the indices. -->

开发智能合约需要一个定义的数据库模式来跟踪、存储和查找数据。 开发人员通常需要由多个字段排序或索引相同的数据，并保持所有索引之间的一致性。

## Separating Authentication from Application 分离授权与应用
<!-- To maximize parallelization opportunities and minimize the computational debt associated with regenerating application state from the transaction log, EOS.IO software separates validation logic into three sections:

为了最大化并行化的机会并最小化与事务日志中重新生成应用程序状态相关的计算债务，EOS.IO 软件将验证逻辑分为三个部分:

1. Validating that an Action is internally consistent; 确认一项行动在内部是一致的;
2. Validating that all preconditions are valid; and 确认所有先决条件都是有效的;
3. Modifying the application state. 修改应用程序状态

Validating the internal consistency of a Action is read-only and requires no access to blockchain state. This means that it can be performed with maximum parallelism. Validating preconditions, such as required balance, is read-only and therefore can also benefit from parallelism. Only modification of application state requires write access and must be processed sequentially for each application.

验证 Action 的内部一致性是只读的，并且不需要访问块状态。 这意味着可以使用最大的并行性来执行。 验证前提条件，如所需的平衡，是只读的，因此也可以从并行性中受益。 只有对应用程序状态的修改需要写入访问，并且必须为每个应用程序按顺序处理。

Authentication is the read-only process of verifying that an Action can be applied. Application is actually doing the work. In real time both calculations are required to be performed, however once a transaction is included in the blockchain it is no longer necessary to perform the authentication operations.

认证是验证一个操作是否可以应用的唯读过程。 应用程序实际上是在做这项工作。 在实时中，两个计算都需要执行，但是一旦一个交易被包含在区块链中，就不再需要执行身份验证操作。 -->
__+++__

To maximize parallelization opportunities and minimize the computational debt associated with regenerating application state from the transaction log, EOS.IO software separates validation logic into three sections:

  1. 验证__操作__是否内部一致；
  2. 验证所有前提条件是否有效；
  3. 修改应用程序状态。

验证__操作__的内部一致性是只读的并且无需访问区块链状态。 这意味着它可以以最大并发来执行。 验证前提条件，比如需要的余额数，是只读的因此也可以受益与并行计算。 只有更改应用状态时需要写入权限并且必须顺序的执行每个应用。

身份认证是一个验证__操作__可被使用的只读过程。 应用程序实际上在发挥作用。 同一时间两者都需要被计算，然而一旦__操作__被包含进区块它就不再需要进行__操作__验证的操作了。

# Inter Blockchain Communication 跨链通信
<!-- EOS.IO software is designed to facilitate inter-blockchain communication. This is achieved by making it easy to generate proof of Action existence and proof of Action sequence. These proofs combined with an application architecture designed around Action passing enables the details of inter-blockchain communication and proof validation to be hidden from application developers, enabling high level abstractions to be presented to developers. -->
__+++__

EOS.IO 软件被设计为跨区块链通信友好的。 这是通过生成操作存在证明与操作时序证明变的简单而实现的。 这些证明与应用架构设计相结合，即围绕操作细节的跨链传输和有效性验证时隐藏应用程序开发者的架构设计。

<img align="right" src="http://eos.io/wpimg/Diagram1.jpg" width="362.84px" height="500px" />

## Merkle Proofs for Light Client Validation (LCV) 用于轻客户端的 Merkle 证明 (LCV)
<!-- Integrating with other blockchains is much easier if clients do not need to process all transactions. After all, an exchange only cares about transfers in and out of the exchange and nothing more. It would also be ideal if the exchange chain could utilize lightweight merkle proofs of deposit rather than having to trust its own block producers entirely. At the very least a chain's block producers would like to maintain the smallest possible overhead when synchronizing with another blockchain. -->

如果客户端不需要处理所有的交易会让多区块链间的整合更为轻松。 毕竟，一个交易所只需要关心交易所的入账和出账，别无他求。 如果交易所链条可以使用资金的轻量 merkle 证明，而不必非要完全依赖对它区块生产者的信任会是一个不错的主意。 至少一个链的区块生产者在与其他区块链同步时更乐意保持尽可能小的开销。

<!-- The goal of LCV is to enable the generation of relatively light-weight proof of existence that can be validated by anyone tracking a relatively light-weight data set. In this case the objective is to prove that a particular transaction was included in a particular block and that the block is included in the verified history of a particular blockchain. -->

LCV 的目标能产生相对轻量存在性证明，使得任何追踪相对轻量数据集的人可以验证其有效性。 在这种情况下，目的是为了证明一个特定的交易是包含在一个特定的区块中，区块包含在一个特定的区块链的已验证历史中。

<!-- Bitcoin supports validation of transactions assuming all nodes have access to the full history of block headers which amounts to 4MB of block headers per year. At 10 transactions per second, a valid proof requires about 512 bytes. This works well for a blockchain with a 10 minute block interval, but is no longer "light" for blockchains with a 0.5 second block interval. -->

比特币支持通过全节点的完整记录获取每年 4MB 大小的区块头信息来验证交易。 每秒 10 个交易，一个有效的证明需要 512 个字节。 这对于有 10 分钟间隔的区块链没有问题，但是对于 __0.5__ 秒间隔区块链就显得不那么“轻量”了。

<!-- The EOS.IO software enables lightweight proofs for anyone who has any irreversible block header after the point in which the transaction was included. Using the hash-linked structure shown it is possible to prove the existence of any transaction with a proof less than 1024 bytes in size. -->

EOS.IO 软件使得任何一个人只要他拥有包含交易所对应区块之后的随意一个不可逆的区块头，他就可以进行轻量证明。 使用下面展示的哈希链结构就可以使用少于 1024 字节的大小来完成任意交易的存在性证明。

<!-- Given any block id for a block in the blockchain, and the headers a trusted irreversible block. It is possible to prove that the block is included in the blockchain. This proof takes ceil(log2(N)) digests for its path, where N is the number of blocks in the chain. Given a digest method of SHA256, you can prove the existence of any block in a chain which contains 100 million blocks in 864 bytes. -->

给定区块链中的任何块 id，并且头部是可信任的不可逆的块。 可以证明块包含在区块链中。 这个证明以 ceil (log2(n))个摘要消息为路径，其中 n 是链中的块数。 给定一个 SHA256的摘要方法，您可以使用864字节证明在一个包含100万块的区块链中存在任何块。

<!-- There is little incremental overhead associated with producing blocks with the proper hash-linking to enable these proofs which means there is no reason not to generate blocks this way. -->

使用正确的哈希链接生成块来实现这些证明，这意味着没有理由不以这种方式生成块。

<!-- When it comes time to validate proofs on other chains there are a wide variety of time/ space/ bandwidth optimizations that can be made. Tracking all block headers (420 MB/year) will keep proof sizes small. Tracking only recent headers can offer a trade off between minimal long-term storage and proof size. Alternatively, a blockchain can use a lazy evaluation approach where it remembers intermediate hashes of past proofs. New proofs only have to include links to the known sparse tree. The exact approach used will necessarily depend upon the percentage of foreign blocks that include transactions referenced by merkle proof. -->

当需要验证其他链时，有譬如 时间/ 空间/ 带宽 的多样化优化可以做。 追踪全部区块头 (420 MB/年) 将保持证明体积的轻巧。 只追踪最近的头可以提供最小长期存储和证明大小来获得。 另外，一个区块链可以使用懒惰的评估方法，即它记住过去证明的中间值哈希。 新证明只需要包含指向已知稀疏树的链接。 确切的方法将取决于那些包含对 Merkle 证明引用的交易所在的外部区块的比例。

<!-- After a certain density of interconnectedness, it becomes more efficient to simply have one chain contain the entire block history of another chain and eliminate the need for proofs all together. For performance reasons, it is ideal to minimize the frequency of inter-chain proofs. -->

一定密度的联系后，将变得更为高效，一个链会包含另一个链整个区块的历史和消除证据一起，这样就不需要通信便可以验证了。 出于性能原因，应最小化的跨链证明的频率。

## Latency of Interchain Communication 跨链通信的延时
<!-- When communicating with another outside blockchain, block producers must wait until there is 100% certainty that a transaction has been irreversibly confirmed by the other blockchain before accepting it as a valid input. Using an EOS.IO software-based blockchain and DPOS with 0.5 second blocks and the addition of Byzantine Fault Tolerant irreversibility, this takes approximately 0.5 second. If any chain's block producers do not wait for irreversibility it would be like an exchange crediting a deposit that was later reversed and could impact the validity of the blockchain's consensus. The EOS.IO Software uses both DPOS and aBFT to provide rapid irreversibility. -->

当与外部区块链进行通信时，区块生产者必须等待直到 100% 确信一个交易已经被另一个区块链确认为不可逆后才会接收它成为一个有效的输入。 对于EOS.IO, DPOS，以及aBFT，这大约需要0.5秒。 如果任何一个区块生产者不等待不可逆转性，那么它就像一个交易所签署了一笔存款后来被逆转了，可能影响到区块链的共识的有效性。 Eos.io 使用 DPOS 和 aBFT 来提供快速的不可逆转性。

## Proof of Completeness 完备性证明
<!-- When using merkle proofs from outside blockchains, there is a significant difference between knowing that all transactions processed are valid and knowing that no transactions have been skipped or omitted. While it is impossible to prove that all of the most recent transactions are known, it is possible to prove that there have been no gaps in the transaction history. The EOS.IO software facilitates this by assigning a sequence number to every Action delivered to every account. A user can use these sequence numbers to prove that all Actions intended for a particular account have been processed and that they were processed in order. -->

当使用来自外部区块链的 Merkle 证明时，在已知所有交易均已验证和已知没有交易被跳过或遗忘之间有一个重要的差异。 虽然不可能证明所有最近的交易是已知的，但有没有间隙的交易历史是可以被证明的。 EOS.IO 软件在每个用户的每个传递的消息上分配了一个序列号。 一个用于可以使用这些序列号来证明所有的消息由某个特定帐户处理，只需要看它是否是按序执行的。

__+++__

## Segregated Witness 隔离见证人
<!-- The concept of Segregated Witness (SegWit) is that transaction signatures are not relevant after a transaction is immutably included in the blockchain. Once it is immutable the signature data can be pruned and everyone else can still derive the current state. Since signatures represent a large percentage of most transactions, SegWit represents a significant savings in disk usage and syncing time. -->

隔离见证人(SegWit)的概念是，交易签名在交易不可改变地包含在区块链中之后就是无关的了。 一旦它是不可变的，签名数据可以被删除掉，其他每个人仍然可以获得当前状态。 由于签名在大多数交易中占很大比例，因此，SegWit 节省了大量的磁盘使用和同步时间。

<!-- This same concept can apply to merkle proofs used for inter-blockchain communication. Once a proof is accepted and irreversibly logged into the blockchain, the 2KB of sha256 hashes used by the proof are no longer necessary to derive the proper blockchain state. In the case of inter-blockchain communication, this savings is 32x greater than the savings on normal signatures. -->

这个概念同样适用于用于跨链通信的merkle proofs。 一旦证明被接受并且不可逆转地记录到区块链中，证明使用的2KB 的 sha256 哈希 不再是获得区块链状态所必需的。 在跨链通信的情况下，这种节省比普通签名节省的多32倍。

<!-- Another example of SegWit would be for Steem blog posts. Under this model a post would contain only the sha256(blog content) and the blog content would be in the segregated witness data. The block producer would verify that the content exists and has the given hash, but the blog content would not need to be stored in order to recover the current state from the blockchain log. This enables proof that the content was once known without having to store said content forever. -->

另一个 SegWit 的例子是 Steem 的博客文章。 在这个模型下，一个帖子只包含 sha256(博客内容)和博客内容将在隔离见证人的数据中。 块生成者将验证内容是否存在并且有给定的哈希值，但博客内容不需要被存储，以便从区块链日志中恢复当前状态。 这就证明了博客内容曾经是众所周知的，而不需要永远保存这些内容。

# Conclusion 总结
<!-- The EOS.IO software is designed from experience with proven concepts and best practices, and represents fundamental advancements in blockchain technology. The software is part of a holistic blueprint for a globally scalable blockchain society in which decentralized applications can be easily deployed and governed. -->

EOS.IO 软件是从证明概念的经验和最佳实践设计而来，它代表了区块链技术的重要进步。 该软件是全球可扩展区块链社会伟大蓝图中的一部分，它将应用去中心化并得以轻松的发布和治理。

