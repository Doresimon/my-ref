## some related knowledge

### field extention - 域扩张

域扩张（field extensions）是数学分支抽象代数之域论中的主要研究对象，基本想法是从一个基域开始以某种方式构造包含它的“更大”的域。域扩张可以推广为环扩张。

`Definition`

设K和L是两个域。如果存在从K到L的域同态ι，则称(L,ι)是K的一个域扩张，记作L/K或K⊆L、K⊂L。K称为域扩张的基域，L称为K的扩域[2]:2。如果某个域F既是K的扩域，又是L的子域，则称域扩张F/K是域扩张L/K的子扩张，称F（域扩张L/K的）中间域。

`Example`

复数域 C 是实数域 R 的扩域，而 R 则是有理数域 Q 的扩域。这样，显然 C/R 也是一个域扩张。实数到复数的域扩张次数： [ C : R ] = 2。因为 C 可以看作是以 { 1, i } 为基的实向量空间。故扩张 C/R 是有限扩张。 C = R(i)，所以这个扩张是单扩张。

集合 Q(sqrt(2)={a+b * sqrt(2);a,b,\in \mathbb {Q} \}} \mathbb Q (\sqrt{2}) = \{ a+ b\sqrt{2} ; \; a, b, \in \mathbb{Q} \}是在 {\displaystyle \mathbb {Q} } \mathbb {Q} 中添加 {\displaystyle {\sqrt {2}}} {\sqrt {2}}生成的扩域，显然也是一个单扩张。它的次数是2，因为 {\displaystyle \{1,{\sqrt {2}}\}} \{ 1, \sqrt{2}\}可作为一个基。 {\displaystyle \mathbb {Q} } \mathbb {Q} 的有限扩张也称为代数数域，在代数数论有重要地位[2]:2。

`Important`

有理数的另一个扩张域是关于一个素数p的p进数域 Qp。它与 R 类似，是有理数域完备化得到的数域。但由于使用的拓扑不同，所以与 R 有着截然不同的性质。

对任何的素数p和正整数n，都存在一个元素个数为p^n的有限域，记作GF(p^n)。它是有限域GF(p)（即 Z/pZ）的扩域。


`Link`

- [wiki - cn - 域扩张](https://zh.wikipedia.org/wiki/%E5%9F%9F%E6%89%A9%E5%BC%A0)



### homomorphism - 同态

抽象代数中，同态是两个代数结构（例如群、环、或者向量空间）之间的保持结构不变的映射。英文的同态(homomorphism)来自希腊语:ὁμός (homos)表示"相同"而μορφή (morphe)表示"形态"。注意相似的词根ὅμοιος (homoios)表示"相似"出现在另一个数学概念同胚的英文(homeomorphism)中。

`同态的类型`

- 同构（isomorphism）：就是双射的同态。两个对象称为同构的，如果存在相互间的同构映射。同构的对象就其上的结构而言是无法区分的。
- 满同态（epimorphism）：就是满射的同态。
- 单同态（monomorphism）：（有时也称扩张）是单射的同态。
- 双同态（bimorphism）：若f既是满同态也是单同态，则称f为双同态。
- 自同态（endomorphism）：任何同态f : X → X称为X上的一个自同态。
- 自同构（automorphism）：若一个自同态也是同构的，那么称之为自同构。

`Link`

- [wiki - cn - 同态](https://zh.wikipedia.org/wiki/%E5%90%8C%E6%80%81)


### Frobenius endomorphism - 弗洛本尼茨自同态

    π : E → E,  (x, y) |→ (x^q, y^q)

We note that the Frobenius endomorphism maps any point in E(_Fq) to a point in
E(_Fq), but the set of points fixed by π is exactly the group E(Fq).Thus, π only
acts non-trivially on points in E(_Fq) \ E(Fq), and more generally, π^i : (x, y) |→
(x^q^i, y^q^i) only acts non-trivially on points in E(_Fq) \ E(Fq^i)

`Link`

- [wiki - en - Frobenius endomorphism](https://en.wikipedia.org/wiki/Frobenius_endomorphism)

