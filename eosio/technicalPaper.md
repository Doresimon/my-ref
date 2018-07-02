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
  * xxxxxx[Deferred Transactions 延迟交易](#)
  * xxxxxx[Context Free Actions 无关上下文操作](#)
- [Token Model and Resource Usage Token 模型与资源使用](#)
  * [Objective and Subjective Measurements 客观与主观的度量](#)
  * [Receiver Pays 接收方付费](#)
  * [Delegating Capacity 委托能力](#)
  * [Separating Transaction costs from Token Value 分离交易成本与 Token 价值](#)
  * [State Storage Costs 状态存储成本](#)
  * [Block Rewards 区块奖励](#)
  * xxxxxx[Worker Proposal System - Worker提议系统](#)
- [Governance 治理](#)
  * [Freezing Accounts 冻结帐户](#)
  * [Changing Account Code 更改帐户代码](#)
  * [Constitution 宪法](#)
  * [Upgrading the Protocol & Constitution 升级协议 & 宪法](#)
    + [Emergency Changes 紧急变更](#)
- [Scripts & Virtual Machines 脚本 & 虚拟机](#)
  * [Schema Defined Actions 模式定义的操作](#)
  * [Schema Defined Database 模式定义的数据库](#)
  * xxxxxx[Generic Multi Index Database API 通用多索引数据库 API](#)
  * [Separating Authentication from Application 从应用程序中分离授权](#)
- [Inter Blockchain Communication 跨链通信](#)
  * [Merkle Proofs for Light Client Validation (LCV) 用于轻客户端的 Merkle 证明 (LCV)](#)
  * [Latency of Interchain Communication 跨链通信的延时](#)
  * [Proof of Completeness 完备性证明](#)
  * xxxxxx[Segregated Witness 隔离见证人](#)
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

应用程序开发人员需要灵活性，为用户提供免费服务; 用户不必为了使用平台或从其服务中受益而支付费用。 一个用户可以免费使用的区块链平台可能会获得更广泛的应用。 xxxxxx开发者和企业可以制定有效的货币化策略。

## Easy Upgrades and Bug Recovery 简单升级和 Bug 恢复

<!-- Businesses building blockchain based applications need the flexibility to enhance their applications with new features. The platform must support software and smart contract upgrades. -->

企业构建区块链基础的应用需要能够为应用增加新特性的灵活性。 该平台必须支持软件和智能合约的升级。

<!-- All non-trivial software is subject to bugs, even with the most rigorous of formal verification. The platform must be robust enough to fix bugs when they inevitably occur. -->

所有非同凡响的软件都会受到 bug 的影响，即便是经过了最严格意义上的验证。这个平台必须具有足够的鲁棒性以便应对不可避免出现的 bug。

## Low Latency 低延迟
<!-- A good user experience demands reliable feedback with a delay of no more than a few seconds. Longer delays frustrate users and make applications built on a blockchain less competitive with existing non-blockchain alternatives. The platform should support low latency of transactions. -->

一个好的用户体验需要可靠的反馈，延迟时间不超过几秒钟。 较长的延迟会使用户感到沮丧，使得应用程序建立在与现有非区块链替代品竞争力较弱的区块链上。 xxxxxx该平台应该支持低延迟的交易。

## Sequential Performance 时序性能
<!-- There are some applications that just cannot be implemented with parallel algorithms due to sequentially dependent steps. Applications such as exchanges need enough sequential performance to handle high volumes. Therefore, the platform should support fast sequential performance. -->

由于一些依赖时序的步骤，有些应用程序无法使用并行算法实现。 交易所等应用程序需要足够的时序性能来处理大量的数据。 因此，平台应该支持快速的时序性能。

## Parallel Performance 并发性能
<!-- Large scale applications need to divide the workload across multiple CPUs and computers. -->

大规模应用程序需要在多个 cpu 和计算机之间划分工作负载。

# xxxxxx Consensus Algorithm (BFT-DPOS) 共识算法(BFT-DPOS)

<!-- EOS.IO software utilizes the only known decentralized consensus algorithm proven capable of meeting the performance requirements of applications on the blockchain, Delegated Proof of Stake (DPOS). Under this algorithm, those who hold tokens on a blockchain adopting the EOS.IO software may select block producers through a continuous approval voting system. Anyone may choose to participate in block production and will be given an opportunity to produce blocks, provided they can persuade token holders to vote for them. -->

Eos.io 软件利用已知的分布式共识算法能够满足区块链上应用程序的性能要求。 在这种算法下，那些在区块链EOS Token的人可以通过连续的批准投票系统来选择块生产者。 任何人都可以选择参与区块生产，并将有机会生产区块，只要他们能说服Token的持有者投票给他们。

<!-- The EOS.IO software enables blocks to be produced exactly every 0.5 second and exactly one producer is authorized to produce a block at any given point in time. If the block is not produced at the scheduled time, then the block for that time slot is skipped. When one or more blocks are skipped, there is a 0.5 or more second gap in the blockchain. -->

xxxxxx
Eos.io 软件允许每0.5秒生产一个区块，准确地说有一个生产者被授权在任何特定的时间点生产一个块。 如果块不是在预定时间生成的，则跳过该时间段的块。 当一个或多个块被跳过时，在区块链中有0.5秒或更多的第二个空隙。

<!-- Using the EOS.IO software, blocks are produced in rounds of 126 (6 blocks each, times 21 producers). At the start of each round 21 unique block producers are chosen by preference of votes cast by token holders. The selected producers are scheduled in an order agreed upon by 15 or more producers. -->

xxxxxx
使用 EOS.IO 软件，每生产126个区块为一轮(每个生产者6个块，乘以21个生产者)。 在每一轮的开始，21个独立的区块产生者都是预先投片产生的。 选定的生产者按照15个或15个以上生产者商定的顺序来生产区块。

<!-- If a producer misses a block and has not produced any block within the last 24 hours they are removed from consideration until they notify the blockchain of their intention to start producing blocks again. This ensures the network operates smoothly by minimizing the number of blocks missed by not scheduling producers who are proven to be unreliable. -->

如果一个生产者错过了一个区块并且在过去的 24 小时内没有生产任何的区块，那么它将被从候选中移除，直到它在区块链中通知它要开始再次生产区块的意图。 这样通过最小化区块丢失数量（因被证实不可靠的节点不作为导致）来确保网络操作的稳定性。

<!-- Under normal conditions a DPOS blockchain does not experience any forks because, rather than compete, the block producers cooperate to produce blocks. In the event there is a fork, consensus will automatically switch to the longest chain. This method works because the rate at which blocks are added to a blockchain fork is directly correlated to the percentage of block producers that share the same consensus. In other words, a blockchain fork with more producers on it will grow in length faster than one with fewer producers, because the fork with more producers will experience fewer missed blocks. -->

在一般情况下，一个 DPOS 区块链不会经历任何的分叉，因为区块生产者是通过合作而非竞争的方式来生产区块。 即便真的出现了分叉，共识也将自动的切换到最长的链上。 之所以会这样运作，是因为区块添加到一个区块链分叉的速率与公用同一共识的区块生产者比例是相关的。 换句话说，具有更多生产者的区块链分叉会比拥有较少生产的那一个条增长的速度更快。 而且，没有一个生产者会同时在两个分叉上同时生产区块。 如果一个区块生产者被抓到做这样的事儿，那么这个生产者将很可能被投票投出。 这些双重生产行为对应密码学凭证可以用来自动的删除这些滥用者。

<!-- Furthermore, no block producer should be producing blocks on two forks at the same time. A block producer caught doing this will likely be voted out. Cryptographic evidence of such double-production may also be used to automatically remove abusers. -->
xxxxxx
此外，区块生产者不应该同时在两个分叉上出块。 此行为一经发现, 可能会被投票出局，很可能会被淘汰。 这种双重生产的加密证据也可用于自动消除滥用者。

<!-- Byzantine Fault Tolerance is added to traditional DPOS by allowing all producers to sign all blocks so long as no producer signs two blocks with the same timestamp or the same block height. Once 15 producers have signed a block the block is deemed irreversible. Any byzantine producer would have to generate cryptographic evidence of their treason by signing two blocks with the same timestamp or blockheight. Under this model a irreversible consensus should be reachable within 1 second. -->
xxxxxx
在传统的 dpos 中添加 BFT，允许所有区块生产者签署所有区块，只要没有区块生产者用同样的时间戳或同样的块高签署两个区块。 一旦15个区块生产者签署了一个区块，这个区块就被认为是不可逆转的。 任何区块生产者在BFT机制下, 想要在同一时刻或者同一区块高度下签署2个不同的区块, 都可以在加密的证据下被发现.  在这种模式下，一个不可逆转的共识应该会在1秒内达成。

## Transaction Confirmation 交易确认
<!-- Typical DPOS blockchains have 100% block producer participation. A transaction can be considered confirmed with 99.9% certainty after an average of 0.25 seconds from time of broadcast. -->
xxxxxx
通常 DPOS 区块链有 100% 的块生产者参与。 一个交易从广播开始后平均 0.25 秒就可以 99.9% 被认为是确认了。

<!-- In addition to DPOS, EOS.IO adds asynchronous Byzantine Fault Tolerance (aBFT) for faster achievement of irreversibility. The aBFT algorithm provides 100% confirmation of irreversibility within 1 second. -->
xxxxxx
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
xxxxxx
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

xxxxxx
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

xxxxxx
2018年6月发布的 EOS.IO 软件将运行单线程，但它包含了未来多线程并行执行所需的数据结构。

<!-- In an EOS.IO software-based blockchain, once parallel operation is enabled, it will be the job of the block producer to organize Action delivery into independent shards so that they can be evaluated in parallel. The schedule is the output of a block producer and will be deterministically executed, but the process for generating the schedule need not be deterministic. This means that block producers can utilize parallel algorithms to schedule transactions. -->

在一个基于 EOS.IO 软件的区块链中，一旦启用并行操作，则块生产商的工作是将 Action 交付组织到独立的分片中，以便可以并行地进行评估。 时间表是一个块生成器的输出，并且将被确定地执行，但是生成计划的过程不需要确定性。 这意味着区块生产者可以利用并行算法来调度交易。

<!-- Part of parallel execution means that when a script generates a new Action it does not get delivered immediately, instead it is scheduled to be delivered in the next cycle. The reason it cannot be delivered immediately is because the receiver may be actively modifying its own state in another shard. -->

并行执行的一方面意味着当一个脚本生成了一个新的操作，它不会立即被发送，而被安排在下一个轮训中发送。 不能立马发出的原因是接受者可能在另一个线程中活跃的变更自己的状态。

## Minimizing Communication Latency 最小化通信延迟
Latency is the time it takes for one account to send an Action to another account and then receive a response. The goal is to enable two accounts to exchange Actions back and forth within a single block without having to wait 0.5 seconds between each Action. To enable this, the EOS.IO software divides each block into cycles. Each cycle is divided into shards and each shard contains a list of transactions. Each transaction contains a set of Actions to be delivered. This structure can be visualized as a tree where alternating layers are processed sequentially and in parallel.

xxxxxx
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
xxxxxx
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
The EOS.IO software cannot obligate block producers to deliver any Action to any other account. Each block producer makes their own subjective measurement of the computational complexity and time required to process a transaction. This applies whether a transaction is generated by a user or automatically by a smart contract.

Eos.io 软件不能强制块生产商将任何操作发送到任何其他帐户。 每个块生成者对处理事务所需的计算复杂度和时间进行了自己的主观测量。 无论交易是由用户生成还是由智能合同自动生成，这一点都适用。

On a launched blockchain adopting the EOS.IO software, at a network level all transactions are billed a computational bandwidth cost based on the number of WASM instructions executed. However, each individual block producer using the software may calculate resource usage using their own algorithm and measurements. When a block producer concludes that a transaction or account has consumed a disproportionate amount of the computational capacity they simply reject the transaction when producing their own block; however, they will still process the transaction if other block producers consider it valid.

在一个启动的区块链上，采用 EOS.IO 软件，在网络层面上，所有的交易都根据执行的 WASM 指令的数量来计算一个计算带宽成本。 然而，使用该软件的每个单独的块生产者可以使用自己的算法和测量来计算资源的使用情况。 当一个块生产者得出结论认为交易或账户消耗了不成比例的计算能力时，他们在生成自己的块时拒绝交易; 然而，如果其他块生产者认为该事务有效，他们仍将处理交易。

In general, so long as even 1 block producer considers a transaction as valid and under the resource usage limits then all other block producers will also accept it, but it may take up to 1 minute for the transaction to find that producer.

一般来说，只要一个块生产商认为一项交易是有效的，并且在资源使用限制之下，那么所有其他块生产者也会接受，但为了找到生产者，交易可能需要1分钟。

In some cases, a producer may create a block that includes transactions that are an order of magnitude outside of acceptable ranges. In this case the next block producer may opt to reject the block and the tie will be broken by the third producer. This is no different than what would happen if a large block caused network propagation delays. The community would notice a pattern of abuse and eventually remove votes from the rogue producer.

在某些情况下，生产者可能会创建一个块，其中包括超出可接受范围的数量级交易。 在这种情况下，下一个区块生产商可能会选择拒绝该区块，第三个制作人将打破这一联系。 这与如果一个大块导致网络传播延迟的情况没有什么不同。 社区会注意到一种虐待模式，并最终撤销流氓制片人的选票。

This subjective evaluation of computational cost frees the blockchain from having to precisely and deterministically measure how long something takes to run. With this design there is no need to precisely count instructions which dramatically increases opportunities for optimization without breaking consensus.

这种对计算成本的主观评估使得区块链不必精确和确定地测量运行所需的时间。 有了这个设计，没有必要精确地计算指令，这将极大地增加优化的机会而不破坏共识。

## Deferred Transactions 递延交易
EOS.IO Software supports deferred transactions that are scheduled to execute in the future. This enables computation to move to different shards and/or the creation of long-running processes that continuously schedule a continuance transaction.

Eos.io 软件支持计划在未来执行的递延事务。 这使得计算能够移动到不同的碎片和 / 或创建长期运行的进程，不断地安排一个连续的交易。

## Context Free Actions 上下文自由操作
A Context Free Action involves computations that depend only on transaction data, but not upon the blockchain state. Signature verification, for example, is a computation that requires only the transaction data and a signature to determine the public key that signed the transaction. This is one of the most expensive individual computations a blockchain must perform, but because this computation is context free it can be performed in parallel.

上下文自由操作包括只依赖事务数据的计算，而不是在区块链状态。 例如，签名验证是一种只需要事务数据和签名才能确定签名事务的公钥的计算。 这是一个区块链必须执行的最昂贵的单独计算之一，但是因为这种计算是无上下文的，所以可以并行执行。

Context Free Actions are like other user Actions, except they lack access to the blockchain state to perform validation. Not only does this enable EOS.IO to process all Context Free Actions such as signature verification in parallel, but more importantly, this enables generalized signature verification.

上下文自由操作和其他用户操作一样，只是他们无法访问区块链状态来执行验证。 这不仅使 EOS.IO 能够处理所有上下文自由操作，例如并行的签名验证，而且更重要的是，这使得广义签名验证成为可能。

With support for Context Free Actions, scalability techniques such as Sharding, Raiden, Plasma, State Channels, and others become much more parallelizable and practical. This development enables efficient inter-blockchain communication and potentially unlimited scalability.

随着对上下文自由操作的支持，诸如 Sharding、雷登、等离子体、状态通道等可扩展性技术变得更具有并行性和实用性。 这种开发使得有效的区块链通信和潜在无限的可伸缩性。

# Token Model and Resource Usage 标记模型和资源使用

__PLEASE NOTE: CRYPTOGRAPHIC TOKENS REFERRED TO IN THIS WHITE PAPER REFER TO CRYPTOGRAPHIC TOKENS ON A LAUNCHED BLOCKCHAIN THAT ADOPTS THE EOS.IO SOFTWARE. THEY DO NOT REFER TO THE ERC-20 COMPATIBLE TOKENS BEING DISTRIBUTED ON THE ETHEREUM BLOCKCHAIN IN CONNECTION WITH THE EOS TOKEN DISTRIBUTION.__

请注意: 本白皮书中提及的加密令牌指的是在一个启动的区块链上采用 EOS.IO 软件的加密令牌。 它们不涉及与 EOS 令牌分布有关的 ETHEREUM 区块链上分布的 ERC-20兼容令牌。

All blockchains are resource constrained and require a system to prevent abuse. With a blockchain that uses EOS.IO software, there are three broad classes of resources that are consumed by applications:

所有的区块链都受到资源限制，需要一个防止滥用的系统。 通过使用 EOS.IO 软件的区块链，应用程序所消耗的资源有三大类:

1. Bandwidth and Log Storage (Disk); 带宽及记录储存(磁盘) ;
2. Computation and Computational Backlog (CPU); and 计算及计算积压(CPU) ; 以及
3. State Storage (RAM). 状态存储器(RAM)

Bandwidth and computation have two components, instantaneous usage and long-term usage. A blockchain maintains a log of all Actions and this log is ultimately stored and downloaded by all full nodes. With the log of Actions, it is possible to reconstruct the state of all applications.

带宽和计算有两个组成部分: 即时使用和长期使用。 区块链维护所有操作的日志，这个日志最终存储和下载所有完整的节点。 通过操作日志，可以重建所有应用程序的状态。

The computational debt is calculations that must be performed to regenerate state from the Action log. If the computational debt grows too large then, it becomes necessary to take snapshots of the blockchain's state and discard the blockchain's history. If computational debt grows too quickly then it may take 6 months to replay 1 year worth of transactions. It is critical, therefore, that the computational debt be carefully managed.

计算债务是必须执行的计算，以从 Action 日志中重新生成状态。 如果计算债务增长过大，就需要拍摄区块链状态的快照，并抛弃区块链的历史。 如果计算债务增长太快，那么可能需要6个月的时间来重新进行一年的交易。 因此，计算债务必须谨慎管理，这一点至关重要。

Blockchain state storage is information that is accessible from application logic. It includes information such as order books and account balances. If the state is never read by the application, then it should not be stored. For example, blog post content and comments are not read by application logic, so they should not be stored in the blockchain's state. Meanwhile the existence of a post/comment, the number of votes, and other properties do get stored as part of the blockchain's state.

区块链状态存储是从应用程序逻辑中可以访问的信息。 它包括订单账簿和账户余额等信息。 如果从未通过应用程序读取状态，那么它就不应该被存储。 例如，博客文章的内容和评论不是通过应用程序逻辑来读取的，所以它们不应该存储在区块链状态中。 同时，一个帖子 / 评论的存在，投票数和其他属性确实被存储为区块链状态的一部分。

Block producers publish their available capacity for bandwidth, computation, and state. The EOS.IO software allows each account to consume a percentage of the available capacity proportional to the amount of tokens held in a 3-day staking contract. For example, if a blockchain based on the EOS.IO software is launched and if an account holds 1% of the total tokens distributable pursuant to that blockchain, then that account has the potential to utilize 1% of the state storage capacity.

块生产商发布他们可用的带宽，计算和状态的能力。 Eos.io 软件允许每个账户消耗一定比例的可用容量，相当于在一个为期3天的订货合同中持有的代币数量。 例如，如果一个基于 EOS.IO 软件的区块链被启动，如果一个帐户根据该区块链持有总代币分配表的1% ，那么该帐户就有可能利用1% 的国家存储容量。

Adopting the EOS.IO software on a launched blockchain means bandwidth and computational capacity are allocated on a fractional reserve basis because they are transient (unused capacity cannot be saved for future use). The algorithm used by EOS.IO software is similar to the algorithm used by Steem to rate-limit bandwidth usage.

在一个已经启动的区块链上采用 EOS.IO 软件意味着带宽和计算能力分配在一个分数储备基础上，因为它们是暂时的(未使用的容量不能保存以备将来使用)。 Eos.io 软件所使用的算法类似于 Steem 用于速率极限带宽的算法。

## Objective and Subjective Measurements 客观和主观测量
As discussed earlier, instrumenting computational usage has a significant impact on performance and optimization; therefore, all resource usage constraints are ultimately subjective, and enforcement is done by block producers according to their individual algorithms and estimates. These would typically be implemented by a block producer via the writing of a custom plugin.

如前所述，计算机使用仪器化对性能和优化有重大影响; 因此，所有资源使用限制最终都是主观的，执行是由块生产者根据他们的个人算法和估计做的。 这些将通常由一个块生产者通过编写自定义插件来实现。

That said, there are certain things that are trivial to measure objectively. The number of Actions delivered, and the size of the data stored in the internal database are cheap to measure objectively. The EOS.IO software enables block producers to apply the same algorithm over these objective measures but may choose to apply stricter subjective algorithms over subjective measurements.

也就是说，有些事情是微不足道的，无法客观地衡量。 交付的操作数量，以及存储在内部数据库中的数据的大小是客观衡量的廉价手段。 软件允许块生产者在这些客观措施上应用相同的算法，但是可以选择适用更加严格的主观算法而不是主观测量。

## Receiver Pays 接收者付费
Traditionally, it is the business that pays for office space, computational power, and other costs required to run the business. The customer buys specific products from the business and the revenue from those product sales is used to cover the business costs of operation. Similarly, no website obligates its visitors to make micropayments for visiting its website to cover hosting costs. Therefore, decentralized applications should not force its customers to pay the blockchain directly for the use of the blockchain.

传统上，是企业支付办公空间、计算能力以及运营业务所需的其他成本。 客户从业务中购买特定的产品，这些产品的销售收入用于支付业务成本。 同样，没有任何网站要求其访问者为访问其网站以支付托管费用而进行小额支付。 因此，分布式的应用程序不应该迫使其客户直接支付区块链的使用区块链。

A launched blockchain that uses the EOS.IO software does not require its users to pay the blockchain directly for its use and therefore does not constrain or prevent a business from determining its own monetization strategy for its products.

一个启动的区块链，使用 EOS.IO 软件不要求其用户直接为其使用支付区块链，因此不会约束或阻止企业为其产品确定自己的货币化策略。

While it is true that the receiver can pay, EOS.IO enables the sender to pay for bandwidth, computation, and storage. This empowers application developers to pick the method that is best for their application. In many cases sender-pays significantly reduces complexity for application developers who do not want to implement their own rationing system. Application developers can delegate bandwidth and computation to their users and then let the “sender pays” model enforce the usage. From the perspective of the end user it is free, but from the perspective of the blockchain it is sender-pays.

虽然接收者确实可以支付，但 EOS.IO 允许发送者支付带宽、计算和存储费用。 这使应用程序开发人员能够选择最适合他们应用的方法。 在许多情况下，发送者付费大大降低了不想实现自己的配给系统的应用程序开发人员的复杂性。 应用程序开发人员可以将带宽和计算委托给用户，然后让"发送者付费"模型强制使用。 从最终用户的角度来看，它是免费的，但从封锁链的角度来看，它是发送者付费。

## Delegating Capacity 授权能力
A holder of tokens on a blockchain launched adopting the EOS.IO software who may not have an immediate need to consume all or part of the available bandwidth, can delegate or rent such unconsumed bandwidth to others; the block producers running EOS.IO software on such blockchain will recognize this delegation of capacity and allocate bandwidth accordingly.

一个区块链上的令牌持有者启动了 EOS.IO 软件，这些软件可能不需要立即消耗全部或部分可用带宽，可以将这种未消耗的带宽委托给其他人; 在这样的区块链上运行 EOS.IO 软件的块生产商将认识到这种能力下放并相应地分配带宽。

## Separating Transaction costs from Token Value 从令牌值中分离事务成本
One of the major benefits of the EOS.IO software is that the amount of bandwidth available to an application is entirely independent of any token price. If an application owner holds a relevant number of tokens on a blockchain adopting EOS.IO software, then the application can run indefinitely within a fixed state and bandwidth usage. In such case, developers and users are unaffected from any price volatility in the token market and therefore not reliant on a price feed. In other words, a blockchain that adopts the EOS.IO software enables block producers to naturally increase bandwidth, computation, and storage available per token independent of the token's value.

软件的主要好处之一是，应用程序可用的带宽数量完全独立于任何令牌价格。 如果应用程序所有者采用 EOS.IO 软件在区块链上持有相关数量的令牌，则该应用程序可以在固定状态和带宽使用范围内无限期地运行。 在这种情况下，开发商和用户不受令牌市场任何价格波动的影响，因此不依赖于价格供给。 换句话说，一个区块链，采用 EOS.IO 软件使块生产者能够自然地增加带宽，计算和存储每个令牌的价值。

A blockchain using EOS.IO software also awards block producers tokens every time they produce a block. The value of the tokens will impact the amount of bandwidth, storage, and computation a producer can afford to purchase; this model naturally leverages rising token values to increase network performance.

一个区块链使用 EOS.IO 软件也奖励块生产商的代币每次他们生产一个块。 这些代币的价值会影响到生产者能够购买的带宽、存储和计算量; 这个模型自然地利用提高标记值来提高网络性能。

## State Storage Costs 国家存储成本
While bandwidth and computation can be delegated, storage of application state will require an application developer to hold tokens until that state is deleted. If state is never deleted, then the tokens are effectively removed from circulation.

虽然带宽和计算可以下放，但应用程序状态的存储将要求应用程序开发人员持有令牌，直到该状态被删除。 如果永远不删除状态，那么代币就会被有效地从循环中删除。

## Block Rewards 块奖励
A blockchain that adopts the EOS.IO software will award new tokens to a block producer every time a block is produced. In these circumstances, the number of tokens created is determined by the median of the desired pay published by all block producers. The EOS.IO software may be configured to enforce a cap on producer awards such that the total annual increase in token supply does not exceed 5%.

一个区块链，采用 EOS.IO 软件将授予新的代币给一个块生产者每次一个块被生产。 在这种情况下，所创建的令牌数量取决于所有区块生产商公布的预期薪酬的中位数。 Eos.io 软件可以配置为强制执行生产者奖励上限，以便每年的令牌供应量增加不超过5% 。

## Worker Proposal System 员工建议制度
In addition to electing block producers, pursuant to a blockchain based on the EOS.IO software, token holders can elect a number of Worker Proposals designed to benefit the community. The winning proposals will receive tokens of up to a configured percent of the token inflation minus those tokens that have been paid to block producers. These proposals will receive tokens proportional to the votes each application has received from token holders, up to the amount they request for performing their work. The elected proposals can be replaced by newly elected proposals by token holders.

除了根据基于 EOS.IO 软件的区块链选举区块生产者外，token 持有者还可以选择一些旨在造福社区的工人提案。 获胜的提案将获得最高达到一个配置百分比的令牌通货膨胀减去那些已经支付给阻止生产者的代币。 这些提议将获得与每一申请人从象征性持有者收到的票数成比例的代币，直到他们要求表演他们的工作的数额。 选举产生的提案可以由新当选的提案所取代，由象征性的持有人提出。

The system contracts that implement Worker Proposals may not be in place at initial launch in June 2018, but the funding mechanism will. It will begin to accumulate funds at the same time block producer awards start. Since the Worker Proposal System will be implemented in WASM it can be added at a later date without a fork.

实施工人建议书的系统合同在2018年6月初次启动时可能不会到位，但供资机制将。 它将开始积累资金，同时阻止生产者奖项的开始。 由于工人建议系统将在世界工业和小型金融机构实施，因此可以在以后不用叉子的情况下添加。

# Governance 管治
Governance is the process by which people in a community:

治理是一个社区的人们通过这个过程:

1. Reach consensus on subjective matters of collective action that cannot be captured entirely by software algorithms; 就集体行动的主观事项达成共识，而软件算法不能完全掌握这些问题;
2. Carry out the decisions they reach; and 执行他们的决定; 以及
3. Alter the governance rules themselves via Constitutional amendments. 通过宪法修正案改变治理规则本身

An EOS.IO software-based blockchain implements a governance process that efficiently directs the existing influence of block producers. Absent a defined governance process, prior blockchains relied ad hoc, informal, and often controversial governance processes that result in unpredictable outcomes.

基于 EOS.IO 的区块链实现了一个治理过程，有效地指导块生产者的现有影响。 如果没有一个明确的治理过程，以前的区块链依赖于临时的、非正式的和经常有争议的治理过程，结果难以预测。

A blockchain based on the EOS.IO software recognizes that power originates with the token holders who delegate that power to the block producers. The block producers are given limited and checked authority to freeze accounts, update defective applications, and propose hard forking changes to the underlying protocol.

一个基于 EOS.IO 软件的区块链认识到，权力源于将权力委托给块生产者的令牌持有者。 封锁生产商被赋予有限的和经过检查的权力来冻结账户，更新有缺陷的应用程序，并提议对基本协议进行硬性修改。

Embedded into the EOS.IO software is the election of block producers. Before any change can be made to the blockchain these block producers must approve it. If the block producers refuse to make changes desired by the token holders then they can be voted out. If the block producers make changes without permission of the token holders then all other non-producing full-node validators (exchanges, etc) will reject the change.

嵌入到 EOS.IO 软件中的是块生产商的选举。 在对区块链做出任何改变之前，这些块生产商必须批准它。 如果区块生产者拒绝作出象征性的改变，那么他们就可以被淘汰。 如果块生产者在未经令牌持有者许可的情况下进行更改，则所有其他非生产的完整节点验证器(交换机等)将拒绝这种更改。

## Freezing Accounts 冻结帐户
Sometimes a smart contact behaves in an aberrant or unpredictable manner and fails to perform as intended; other times an application or account may discover an exploit that enables it to consume an unreasonable amount of resources. When such issues inevitably occur, the block producers have the power to rectify such situations.

有时，一个聪明的联系人表现出异常或不可预测的行为，并且没有按照预期的方式执行; 其他时候，应用程序或帐户可能会发现一个漏洞，使其能够消耗大量不合理的资源。 当这些问题不可避免地发生时，区块生产商有权纠正这种情况。

The block producers on all blockchains have the power to select which transactions are included in blocks which gives them the ability to freeze accounts. A blockchain using EOS.IO software formalizes this authority by subjecting the process of freezing an account to a 15/21 vote of active producers. If the producers abuse the power they can be voted out and an account will be unfrozen.

所有区块链上的区块生产商都有权选择哪些交易被包含在块中，这使他们有能力冻结账户。 使用 EOS.IO 软件的区块链通过将冻结账户的过程置于活跃生产者的15 / 21投票，从而使这一权力正式化。 如果生产商滥用权力，他们就可以被淘汰，账户将被解冻。

## Changing Account Code 更改帐户代码
When all else fails and an "unstoppable application" acts in an unpredictable manner, a blockchain using EOS.IO software allows the block producers to replace the account's code without hard forking the entire blockchain. Similar to the process of freezing an account, this replacement of the code requires a 15/21 vote of elected block producers.

当所有其他方法都失败时，一个"不可阻挡的应用程序"以不可预测的方式运行时，使用 EOS.IO 软件的区块链允许块生产商更换账户的代码，而无需对整个区块链进行严格的搜索。 与冻结账户的过程类似，代码的这种更换需要15 / 21的选举产生者的投票。

## Constitution 宪法
The EOS.IO software enables blockchains to establish a peer-to-peer terms of service agreement or a binding contract among those users who sign it, referred to as a "constitution". The content of this constitution defines obligations among the users which cannot be entirely enforced by code and facilitates dispute resolution by establishing jurisdiction and choice of law along with other mutually accepted rules. Every transaction broadcast on the network must incorporate the hash of the constitution as part of the signature and thereby explicitly binds the signer to the contract.

Eos.io 软件使得区块链能够在签署该协议的用户之间建立对等服务条款协议或具有约束力的合同，称为"宪法"。 这部宪法的内容界定了用户之间的义务，这些义务不能完全由法规执行，并通过确立管辖权和法律选择以及其他相互接受的规则来促进解决争端。 网络上广播的每一项交易都必须将宪法的散列内容作为签字的一部分，从而明确地将签字人与合同联系在一起。

The constitution also defines the human-readable intent of the source code protocol. This intent is used to identify the difference between a bug and a feature when errors occur and guides the community on what fixes are proper or improper.

宪法还规定了源代码协议的人类可读意图。 这个意图用于识别错误发生时的错误和特征之间的差异，并指导社区如何修正是否正确。

## Upgrading the Protocol & Constitution 提升《议定书》和《宪法》
The EOS.IO software defines the following process by which the protocol, as defined by the canonical source code and its constitution, can be updated:

Eos.io 软件定义了下列过程，根据规范源代码及其章程定义的协议可以更新:

1. Block producers propose a change to the constitution and obtains 15/21 approval. 区块生产商建议修改宪法，并获得15 / 21的批准
2. Block producers maintain 15/21 approval of the new constitution for 30 consecutive days. 街区生产商连续30天保持对新宪法的15 / 21的批准
3. All users are required to indicate acceptance of the new constitution as a condition of future transactions being processed. 所有用户都必须表明接受新宪法是未来交易处理的一个条件
4. Block producers adopt changes to the source code to reflect the change in the constitution and propose it to the blockchain using the hash of the new constitution. 区块生产商采用对源代码的修改，以反映宪法的变化，并利用新宪法的散列向区块链提出建议
5. Block producers maintain 15/21 approval of the new code for 30 consecutive days. 区块生产商连续30天保持对新代码的15 / 21的批准
6. Changes to the code take effect 7 days later, giving all non-producing full nodes 1 week to upgrade after ratification of the source code. 对代码的更改将在7天后生效，在批准源代码后，所有非生产的完整节点在1周后升级
7. All nodes that do not upgrade to the new code shut down automatically. 所有没有升级到新代码的节点都会自动关闭

By default, configuration of the EOS.IO software, the process of updating the blockchain to add new features takes 2 to 3 months, while updates to fix non-critical bugs that do not require changes to the constitution can take 1 to 2 months.

默认情况下，EOS.IO 软件的配置，更新区块链以增加新功能的过程需要2至3个月，而修复不需要修改宪法的非关键性错误需要1到2个月的时间。

### Emergency Changes 紧急情况变化
The block producers may accelerate the process if a software change is required to fix a harmful bug or security exploit that is actively harming users. Generally speaking it could be against the constitution for accelerated updates to introduce new features or fix harmless bugs.

如果需要进行软件修改以修复一个正在积极伤害用户的有害漏洞或安全漏洞，则块生产商可能会加速这一过程。 一般来说，加速更新引入新功能或修复无害错误可能违反宪法。

# Scripts & Virtual Machines 脚本和虚拟机
The EOS.IO software will be first and foremost a platform for coordinating the delivery of authenticated messages (called Actions) to accounts. The details of scripting language and virtual machine are implementation specific details that are mostly independent from the design of the EOS.IO technology. Any language or virtual machine that is deterministic and properly sandboxed with sufficient performance can be integrated with the EOS.IO software API.

Eos.io 软件将首先是一个平台，用于协调将经过身份验证的消息(称为 Actions)传递到帐户的平台。 脚本语言和虚拟机的细节是实现的具体细节，大多独立于 EOS.IO 技术的设计。 任何具有确定性且具有足够性能的语言或虚拟机都可以与 EOS.IO 软件 API 集成。

## Schema Defined Actions 架构定义的操作
All Actions sent between accounts are defined by a schema which is part of the blockchain consensus state. This schema allows seamless conversion between binary and JSON representation of the Actions.

所有在账户之间发送的操作都是由一个模式来定义的，这是区块链共识状态的一部分。 这个模式允许行动的二进制和 JSON 表示之间的无缝转换。

## Schema Defined Database 架构定义数据库
Database state is also defined using a similar schema. This ensures that all data stored by all applications is in a format that can be interpreted as human readable JSON but stored and manipulated with the efficiency of binary.

数据库状态也使用类似的模式定义。 这确保了所有应用程序存储的所有数据的格式可以被解释为人类可读的 JSON，但是存储和操作与二进制的效率。

## Generic Multi Index Database API 通用多索引数据库 API
Developing smart contracts requires a defined database schema to track, store, and find data. Developers commonly need the same data sorted or indexed by multiple fields and to maintain consistency among all the indices.

开发智能合同需要一个定义的数据库模式来跟踪、存储和查找数据。 开发人员通常需要由多个字段排序或索引相同的数据，并保持所有索引之间的一致性。

## Separating Authentication from Application 从应用程序中分离认证
To maximize parallelization opportunities and minimize the computational debt associated with regenerating application state from the transaction log, EOS.IO software separates validation logic into three sections:

为了最大化并行化的机会并最小化与事务日志中重新生成应用程序状态相关的计算债务，EOS.IO 软件将验证逻辑分为三个部分:

1. Validating that an Action is internally consistent; 确认一项行动在内部是一致的;
2. Validating that all preconditions are valid; and 确认所有先决条件都是有效的;
3. Modifying the application state. 修改应用程序状态

Validating the internal consistency of a Action is read-only and requires no access to blockchain state. This means that it can be performed with maximum parallelism. Validating preconditions, such as required balance, is read-only and therefore can also benefit from parallelism. Only modification of application state requires write access and must be processed sequentially for each application.

验证 Action 的内部一致性是只读的，并且不需要访问块状态。 这意味着可以使用最大的并行性来执行。 验证前提条件，如所需的平衡，是只读的，因此也可以从并行性中受益。 只有对应用程序状态的修改需要写入访问，并且必须为每个应用程序按顺序处理。

Authentication is the read-only process of verifying that an Action can be applied. Application is actually doing the work. In real time both calculations are required to be performed, however once a transaction is included in the blockchain it is no longer necessary to perform the authentication operations.

认证是验证一个操作是否可以应用的唯读过程。 应用程序实际上是在做这项工作。 在实时中，两个计算都需要执行，但是一旦一个交易被包含在区块链中，就不再需要执行身份验证操作。

# Inter Blockchain Communication 封锁链通信
EOS.IO software is designed to facilitate inter-blockchain communication. This is achieved by making it easy to generate proof of Action existence and proof of Action sequence. These proofs combined with an application architecture designed around Action passing enables the details of inter-blockchain communication and proof validation to be hidden from application developers, enabling high level abstractions to be presented to developers.

Eos.io 软件旨在促进区块间通信。 这是通过使生成 Action 存在的证明和 Action 序列的证明变得容易来实现的。 这些证明与围绕动作传递设计的应用程序体系结构结合在一起，可以从应用程序开发者那里隐藏区块链间通信和验证验证的细节，从而能够向开发人员提交高层抽象。



## Merkle Proofs for Light Client Validation (LCV) 轻客户验证的 Merkle 证明(LCV)
Integrating with other blockchains is much easier if clients do not need to process all transactions. After all, an exchange only cares about transfers in and out of the exchange and nothing more. It would also be ideal if the exchange chain could utilize lightweight merkle proofs of deposit rather than having to trust its own block producers entirely. At the very least a chain's block producers would like to maintain the smallest possible overhead when synchronizing with another blockchain.

如果客户端不需要处理所有的事务，那么与其他区块链集成就会容易得多。 毕竟，交易所只关心进出交易所的转移，仅此而已。 如果交易所链条能够利用轻量级的银行存款证明，而不是完全信任自己的区块生产商。 至少，一个链条生产商希望在与另一个区块链同步时保持最小的可能的开销。

The goal of LCV is to enable the generation of relatively light-weight proof of existence that can be validated by anyone tracking a relatively light-weight data set. In this case the objective is to prove that a particular transaction was included in a particular block and that the block is included in the verified history of a particular blockchain.

Lcv 的目标是能够生成相对轻量的存在证明，任何追踪相对轻量数据集的人都可以验证这一点。 在这种情况下，目标是证明某一特定交易被包含在特定块中，并证明该块包含在特定块链的验证历史中。

Bitcoin supports validation of transactions assuming all nodes have access to the full history of block headers which amounts to 4MB of block headers per year. At 10 transactions per second, a valid proof requires about 512 bytes. This works well for a blockchain with a 10 minute block interval, but is no longer "light" for blockchains with a 0.5 second block interval.

比特币支持验证事务，假设所有节点都可以访问每年4mb 的块头的完整历史。 每秒10个事务，一个有效的证明需要大约512字节。 这对于10分钟区间区间的区块链来说效果不错，但是对于0.5秒区间的区块链来说已经不再是"轻量级"了。

The EOS.IO software enables lightweight proofs for anyone who has any irreversible block header after the point in which the transaction was included. Using the hash-linked structure shown it is possible to prove the existence of any transaction with a proof less than 1024 bytes in size.

Eos.io 软件可以为任何在包含事务的点后有任何不可逆的块头标题的任何人都可以使用轻量级证明。 使用哈希链结构可以证明存在任何证明小于1024字节大小的事务。

Given any block id for a block in the blockchain, and the headers a trusted irreversible block. It is possible to prove that the block is included in the blockchain. This proof takes ceil(log2(N)) digests for its path, where N is the number of blocks in the chain. Given a digest method of SHA256, you can prove the existence of any block in a chain which contains 100 million blocks in 864 bytes.

给定区块链中的块的任何块 id，并且头部是可信任的不可逆的块。 可以证明块包含在区块链中。 这个证明以 ceil (log2(n))为路径，其中 n 是链中的块数。 给定一个 SHA256的摘要方法，您可以证明在一个包含100万块的864字节的链条中存在任何块。

There is little incremental overhead associated with producing blocks with the proper hash-linking to enable these proofs which means there is no reason not to generate blocks this way.

使用正确的哈希链接生成块来实现这些证明，这意味着没有理由不以这种方式生成块。

When it comes time to validate proofs on other chains there are a wide variety of time/ space/ bandwidth optimizations that can be made. Tracking all block headers (420 MB/year) will keep proof sizes small. Tracking only recent headers can offer a trade off between minimal long-term storage and proof size. Alternatively, a blockchain can use a lazy evaluation approach where it remembers intermediate hashes of past proofs. New proofs only have to include links to the known sparse tree. The exact approach used will necessarily depend upon the percentage of foreign blocks that include transactions referenced by merkle proof.

当需要验证其他链条上的证明时，可以进行多种多样的时间 / 空间 / 带宽优化。 跟踪所有的块头(420mb / 年)将保持小的校验尺寸。 只跟踪最近的标题可以在最小的长期存储和校验大小之间提供一种权衡。 或者，区块链可以使用一个懒惰的评估方法，它记得过去证明的中间位置。 新的证明只需要包含到已知稀疏树的链接。 所使用的确切方法必然取决于外国区块的百分比，其中包括 merkle 证明引用的事务。

After a certain density of interconnectedness, it becomes more efficient to simply have one chain contain the entire block history of another chain and eliminate the need for proofs all together. For performance reasons, it is ideal to minimize the frequency of inter-chain proofs.

在一定密度的相互联系之后，它变得更有效率，只需要一个链条包含另一个链条的整个块历史，并消除所有证明的需要。 由于性能的原因，最理想的做法是尽量减少链条间证明的频率。

## Latency of Interchain Communication 连锁通信的延迟
When communicating with another outside blockchain, block producers must wait until there is 100% certainty that a transaction has been irreversibly confirmed by the other blockchain before accepting it as a valid input. Using an EOS.IO software-based blockchain and DPOS with 0.5 second blocks and the addition of Byzantine Fault Tolerant irreversibility, this takes approximately 0.5 second. If any chain's block producers do not wait for irreversibility it would be like an exchange crediting a deposit that was later reversed and could impact the validity of the blockchain's consensus. The EOS.IO Software uses both DPOS and aBFT to provide rapid irreversibility.

当与其他外部区块链通信时，块生产者必须等到100% 确定交易已经被其他区块链不可逆转地确认，然后才能接受它作为有效的输入。 使用 EOS.IO 软件为基础的区块链和0.5秒的 DPOS，以及添加了拜占庭容错性不可逆性，这大约需要0.5秒。 如果任何一家连锁生产商不等待不可逆转性，那么它就像一个交易所信用证，存款后来被逆转，可能影响到区块链的共识的有效性。 Eos.io 软件使用 DPOS 和 aBFT 来提供快速的不可逆转性。

## Proof of Completeness 完整性的证明
When using merkle proofs from outside blockchains, there is a significant difference between knowing that all transactions processed are valid and knowing that no transactions have been skipped or omitted. While it is impossible to prove that all of the most recent transactions are known, it is possible to prove that there have been no gaps in the transaction history. The EOS.IO software facilitates this by assigning a sequence number to every Action delivered to every account. A user can use these sequence numbers to prove that all Actions intended for a particular account have been processed and that they were processed in order.

当使用外部区块链上的 merkle 证明时，知道所有已处理的事务都是有效的，而不知道没有跳过或省略了任何事务。 虽然不可能证明所有最近的交易都是已知的，但是有可能证明交易历史上没有差距。 软件通过为每个帐户发送的每个操作分配一个序列号来促进这一点。 用户可以使用这些序列号来证明所有针对特定帐户的操作都已经被处理，并按顺序进行处理。

## Segregated Witness 隔离证人
The concept of Segregated Witness (SegWit) is that transaction signatures are not relevant after a transaction is immutably included in the blockchain. Once it is immutable the signature data can be pruned and everyone else can still derive the current state. Since signatures represent a large percentage of most transactions, SegWit represents a significant savings in disk usage and syncing time.

隔离证人(SegWit)的概念是，交易签名不相关，因为交易不可改变地包含在区块链中。 一旦它是不可变的，签名数据可以被修剪，其他每个人仍然可以获得当前状态。 由于签名在大多数交易中占很大比例，因此，SegWit 在磁盘使用和同步时间方面节省了大量资金。

This same concept can apply to merkle proofs used for inter-blockchain communication. Once a proof is accepted and irreversibly logged into the blockchain, the 2KB of sha256 hashes used by the proof are no longer necessary to derive the proper blockchain state. In the case of inter-blockchain communication, this savings is 32x greater than the savings on normal signatures.

这个概念同样适用于用于块间通信的金属证明。 一旦证明被接受并且不可逆转地登录到区块链中，证明使用的2KB 的 sha256 hash 不再是获得合适的区块链状态所必需的。 在区块间通信的情况下，这种节省比普通签名节省的多32倍。

Another example of SegWit would be for Steem blog posts. Under this model a post would contain only the sha256(blog content) and the blog content would be in the segregated witness data. The block producer would verify that the content exists and has the given hash, but the blog content would not need to be stored in order to recover the current state from the blockchain log. This enables proof that the content was once known without having to store said content forever.

另一个 SegWit 的例子是 Steem 的博客文章。 在这个模型下，一个帖子只包含 sha256(博客内容)和博客内容将在隔离的证人数据。 块生成者将验证内容是否存在并且有给定的哈希值，但博客内容不需要被存储，以便从区块链日志中恢复当前状态。 这就证明了内容曾经是众所周知的，而不需要永远保存所说的内容。

# Conclusion 结论
The EOS.IO software is designed from experience with proven concepts and best practices, and represents fundamental advancements in blockchain technology. The software is part of a holistic blueprint for a globally scalable blockchain society in which decentralized applications can be easily deployed and governed.

Eos.io 软件是根据已证明的概念和最佳做法的经验设计的，它代表了区块链技术的根本性进步。 这个软件是全球可扩展的区块链社会的整体蓝图的一部分，在这个社会中，分散的应用程序可以很容易地部署和管理。

