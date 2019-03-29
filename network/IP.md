# IP (Internet Protocol)

@[rfc760](https://tools.ietf.org/rfc/rfc760.txt)
@[rfc791](https://tools.ietf.org/rfc/rfc791.txt)

The function or purpose of Internet Protocol is to move datagrams
through an interconnected set of networks.

## protocol hierarchy

```
                 +------+ +-----+ +-----+     +-----+
                 |Telnet| | FTP | | TFTP| ... | ... |
                 +------+ +-----+ +-----+     +-----+
                       |   |         |           |
                      +-----+     +-----+     +-----+
                      | TCP |     | UDP | ... | ... |
                      +-----+     +-----+     +-----+
                         |           |           |
                      +--------------------------+----+
                      |    Internet Protocol & ICMP   |
                      +--------------------------+----+
                                     |
                        +---------------------------+
                        |   Local Network Protocol  |
                        +---------------------------+

                         Protocol Relationships
```

## Transmission Path

```
   Application                                           Application
   Program                                                   Program
         \                                                   /
       Internet Module      Internet Module      Internet Module
             \                 /       \                /
             LNI-1          LNI-1      LNI-2         LNI-2
                \           /             \          /
               Local Network 1           Local Network 2



                            Transmission Path
```

## GateWay

```
                   +-------------------------------+
                   | Internet Protocol & ICMP & GGP|
                   +-------------------------------+
                           |                 |
                 +---------------+   +---------------+
                 |   Local Net   |   |   Local Net   |
                 +---------------+   +---------------+

                           Gateway Protocols
```

## header

### `IPv4`

```
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                    Example Internet Datagram Header
```

- Version: 4 bits

  The Version field indicates the format of the internet header. This
  document describes version 4.

- IHL: 4 bits

  Internet Header Length is the length of the internet header **in 32
  bit words**, and thus points to the beginning of the data. Note that
  the minimum value for a correct header is 5.

- Type of Service: 8 bits

  measured in octets

- Total Length: 16 bits

- Identification: 16 bits

- Flags: 3 bits

- Fragment Offset: 13 bits

- Time to Live: 8 bits

- Protocol: 8 bits

  This field indicates the next level protocol used in the data
  portion of the internet datagram. The values for various protocols
  are specified in [RFC 762].

- Header Checksum: 16 bits

- Source Address: 32 bits

- Destination Address: 32 bits

### `IPv6`

[@rfc2460](https://tools.ietf.org/rfc/rfc2460.txt)

```
IPv6 Header Format

   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version| Traffic Class |           Flow Label                  |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Payload Length        |  Next Header  |   Hop Limit   |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   +                                                               +
   |                                                               |
   +                         Source Address                        +
   |                                                               |
   +                                                               +
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   +                                                               +
   |                                                               |
   +                      Destination Address                      +
   |                                                               |
   +                                                               +
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Version              4-bit Internet Protocol version number = 6.

   Traffic Class        8-bit traffic class field.  See section 7.

   Flow Label           20-bit flow label.  See section 6.

   Payload Length       16-bit unsigned integer.  Length of the IPv6
                        payload, i.e., the rest of the packet following
                        this IPv6 header, in octets.  (Note that any
                        extension headers [section 4] present are
                        considered part of the payload, i.e., included
                        in the length count.)

   Next Header          8-bit selector.  Identifies the type of header
                        immediately following the IPv6 header.  Uses the
                        same values as the IPv4 Protocol field [RFC-1700
                        et seq.].

   Hop Limit            8-bit unsigned integer.  Decremented by 1 by
                        each node that forwards the packet. The packet
                        is discarded if Hop Limit is decremented to
                        zero.

   Source Address       128-bit address of the originator of the packet.
                        See [ADDRARCH].

   Destination Address  128-bit address of the intended recipient of the
                        packet (possibly not the ultimate recipient, if
                        a Routing header is present).  See [ADDRARCH]
                        and section 4.4.

```
