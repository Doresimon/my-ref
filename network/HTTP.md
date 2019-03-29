# HTTP

## HTTP1.1

## HTTP2

HTTP/2 帧

HTTP/1.x 报文有一些性能上的缺点：

- Header 不像 body，它不会被压缩。

- 两个报文之间的 header 通常非常相似，但它们仍然在连接中重复传输。

- 无法复用。当在同一个服务器打开几个连接时：TCP 热连接比冷连接更加有效。

HTTP/2 引入了一个额外的步骤：它将 HTTP/1.x 消息分成帧并嵌入到流 (stream) 中。数据帧和报头帧分离，这将允许报头压缩。将多个流组合，这是一个被称为 多路复用 (multiplexing) 的过程，它允许更有效的底层 TCP 连接

HTTP 报文是使用 HTTP 的关键；它们的结构简单，并且具有高可扩展性。HTTP/2 帧机制是在 HTTP/1.x 语法和底层传输协议之间增加了一个新的中间层，而没有从根本上修改它，即它是建立在经过验证的机制之上。

## URI(Uniform Resource Identifier)

### URL(Uniform Resource Locator) 统一资源定位符

```
https://developer.mozilla.org
https://developer.mozilla.org/en-US/docs/Learn/
https://developer.mozilla.org/en-US/search?q=URL

```

结构

```
http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument

${protocol}://${host}:${port}${path}${query}${anchor}

${protocol} = {http/https, file, ssh, ftp}

${host} = {DomainName, IP}

${port} = {ProtocolStandardPort}

${path} = /*/*...

${query} = ?k=v&k=v&...

${anchor} = #name
```
