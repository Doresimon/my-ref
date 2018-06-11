# a short introduction for `R1CS`

## 1. Simple Process

a picture from **Vitarlik**

![function to zksnark](img/process.png)


* **Computation**

      function add(x,y){
        z = x + y
        return z
      }

      function poly(x){
        z = 3 + 2*x + 5*x^2
        return z
      }

* **Algebraic Circuit**

      ## `add` doesn't need to change.
      ## solution:: [1, x, y, z]
      function add(x,y){
        z = x + y
        return z
      }

      ## `poly` needs to be exploded
      ## solution:: [1, x, t, t1, t2, z]
      function poly(x){
        t  = x * x
        t1 = 2 * x
        t2 = 5 * t
        z  = 3 + t1 + t2
        return z
      }
      ## if x is 2, solution is [1, 2, 4, 4, 20, 27],
      ## which means z = 3 + 2*x + 5*x^2 is equal if x = 2 and z = 27.

  keywords: `wire` `gate` `constant wire` `...`

  **wire**:

  for function __poly()__, __[1, x, t, t1, t2, z]__ are all wires. __'1'__ is a constant wire, __'x'__ is an input wire, __'t, t1, t2'__ are internal wire and __'z'__ is output wire.

  **gate**

  for function __poly()__, there are `add` and `mul` gates, each gate can have __many inputs__ but only __1 output__. (for now we only have basic gates.)

* **R1CS**

  * What is R1CS

    Range 1 Constraint System.

    `<a, b, c>`

    `<s . a> * <s . b> = <s . c>`
