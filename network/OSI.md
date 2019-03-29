# OSI（Open System Interconnection）开放系统互连参考模型

Open Systems Interconnection model (OSI model)

## OSI[https://en.wikipedia.org/wiki/OSI_model]

X.200

```
Layer 1: Physical Layer
Layer 2: Data Link Layer
Layer 3: Network Layer
Layer 4: Transport Layer
Layer 5: Session Layer
Layer 6: Presentation Layer
Layer 7: Application Layer :: HTTP, HTTPS, Telnet, FTP, SMTP, DNS, DHCP
```

`应用层` Application Layer

网络服务与最终用户的一个接口。
协议有：HTTP FTP TFTP SMTP SNMP DNS TELNET HTTPS POP3 DHCP

`表示层` Presentation Layer

数据的表示、安全、压缩。（在五层模型里面已经合并到了应用层）
格式有，JPEG、ASCll、DECOIC、加密格式等 `Telnet` (a remote terminal access protocol)

`会话层` Session Layer

建立、管理、终止会话。（在五层模型里面已经合并到了应用层）
对应主机进程，指本地主机与远程主机正在进行的会话 `RPC`

full-duplex, half-duplex, or simplex operation, and establishes procedures for checkpointing, suspending, restarting, and terminating a session.

`传输层` Transport Layer

定义传输数据的协议端口号，以及流控和差错校验。
协议有：`TCP` `UDP`，数据包一旦离开`网卡`即进入网络传输层.

`UDP` UDP-Lite `TCP` `Multipath TCP` SCTP DCCP RUDP

`网络层` Network Layer

进行逻辑地址寻址，实现不同网络之间的路径选择。
协议有：ICMP IGMP `IP（IPV4 IPV6）` ARP RARP

`数据链路层` Data Link Layer

建立逻辑连接、进行硬件地址寻址、差错校验 [2] 等功能。（由底层网络定义协议）
将比特组合成字节进而组合成帧，用 MAC 地址访问介质，错误发现但不能纠正。

`物理层` Physical Layer

建立、维护、断开物理连接。（由底层网络定义协议）

TCP/IP 层级模型结构，应用层之间的协议通过逐级调用传输层（Transport layer）、网络层（Network Layer）和物理数据链路层（Physical Data Link）而可以实现应用层的应用程序通信互联。
应用层需要关心应用程序的逻辑细节，而不是数据在网络中的传输活动。应用层其下三层则处理真正的通信细节。在 Internet 整个发展过程中的所有思想和着重点都以一种称为 RFC（Request For Comments）的文档格式存在。针对每一种特定的 TCP/IP 应用，有相应的 RFC [3] 文档。
一些典型的 TCP/IP 应用有 FTP、Telnet、SMTP、SNTP、REXEC、TFTP、LPD、SNMP、NFS、INETD 等。RFC 使一些基本相同的 TCP/IP 应用程序实现了标准化，从而使得不同厂家开发的应用程序可以互相通信

## TCP/IP

```
Link layer
Internet layer
Transport layer
Application layer
```

- Link Layer ---> L1,L2 (Physical, Data Link)

  This is the layer in which all higher-level protocols, such as `SMTP`, `FTP`, `SSH`, `HTTP`, operate. Processes are addressed via ports which essentially represent services.

- Internet Layer ---> L3 (Network)

  The internet layer has the responsibility of `sending packets` across potentially multiple networks.

  Internet Protocol version 4 (`IPv4`) `32 bit`

  Internet Protocol version 6 (`IPv6`) `128 bit`

- Transport layer ---> L4 (Transport)

  The transport layer establishes basic data channels that applications use for task-specific data exchange.

- Application layer ---> L5,L6,L7 (Session, Presentation, Application)

## full-duplex 全双工

可相互通信, 同时通信

## half-duplex 半双工

可相互通信, 不可同时

## TLS (Transport Layer Security)

In applications design, `TLS` is usually implemented `on top of Transport Layer protocols`, encrypting all of the protocol-related data of protocols such as HTTP, FTP, SMTP, NNTP and XMPP.

### Digital certificates

认证了某主体对公钥的使用权, 需要第三方认证机构

TLS typically relies on a set of trusted third-party certificate authorities to establish the authenticity of certificates.

### Key exchange or key agreement

RSA

DHE-RSA

ECDHE-RSA

DHE-DSS

ECDHE-ECDSA

PSK-RSA

SRP-RSA

### Cipher

`block cipher`

AES/DES/IDEA - GCM/CCM/CBC

`stream cipher`

ChaCha20-poly1305

### Data integrity

HMAC-MD5 (Hash-based Message Authentication Code)

HMAC-SHA1

HMAC-SHA256/384

### Basic TLS handshake

```
client                                      server
           ### Negotiation phase ###
        ------ ClientHello ----------->

        <----- ServerHello ------------
        <----- Certificate ------------
        <----- ServerKeyExchange ------
        <----- ServerHelloDone --------

        ------ ClientKeyExchange ----->


        ------ ChangeCipherSpec ------>
        ------ Finished -------------->


        <---- ChangeCipherSpec --------
        <---- Finished  ---------------

```
