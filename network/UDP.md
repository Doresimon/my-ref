# UDP (User Datagram Protocol)

This protocol provides a procedure for application programs to send
messages to other programs with a`minimum of protocol mechanism`. The
protocol is `transaction oriented`, and `delivery and duplicate protection`
are `not guaranteed`. Applications requiring ordered reliable delivery of
streams of data should use the `Transmission Control Protocol (TCP)`.

```
Format
------


                  0      7 8     15 16    23 24    31
                 +--------+--------+--------+--------+
                 |     Source      |   Destination   |
                 |      Port       |      Port       |
                 +--------+--------+--------+--------+
                 |                 |                 |
                 |     Length      |    Checksum     |
                 +--------+--------+--------+--------+
                 |
                 |          data octets ...
                 +---------------- ...

                      User Datagram Header Format
```
