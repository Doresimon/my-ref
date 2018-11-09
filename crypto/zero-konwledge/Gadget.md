# use gadget to create simple circuit(constraint system)

## SUB GATES

### 1. AND

binary input: [`input1`, `input2`, `result`]

> (1) input1 * input2 = result

R1P input: [`inputs[n]`, `result`]

> (*) sum = sum(input[i]) - n

> (1) sum * result = 0

> (2) sum * sumInverse = 1 - result
