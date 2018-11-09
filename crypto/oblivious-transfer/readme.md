# oblivious transfer (OT)

In cryptography, an oblivious transfer (OT) protocol is a type of protocol in which a sender transfers one of potentially many pieces of information to a receiver, but remains oblivious as to what piece (if any) has been transferred.

## 1–2 oblivious transfer

In a 1–2 oblivious transfer protocol, the sender has two messages __m<sub>0</sub>__ and __m<sub>1</sub>__, and the receiver has a bit __b__, and the receiver wishes to receive __m<sub>b</sub>__, without the sender learning __b__, while the sender wants to ensure that the receiver receives only one of the two messages. The protocol of Even, Goldreich, and Lempel (which the authors attribute partially to Silvio Micali), is general, but can be instantiated using RSA encryption as follows.

<img src="./img/2f9b62e2082acfd4e6e04bf17a02af6.png"/>

1. Alice has two messages, __m<sub>0</sub>__, __m<sub>1</sub>__ 
and wants to send exactly one of them to Bob. Bob does not 
want Alice to know which one he receives.
2. Alice generates an RSA key pair, comprising the modulus __N__, 
the public exponent __e__ and the private exponent __d__
3. She also generates two random values, 
__x<sub>0</sub>__, __x<sub>1</sub>__ and 
sends them to Bob along with her public modulus and exponent.
4. Bob picks __b__ to be either 0 or 1, and selects either 
the first or second __x<sub>b</sub>__.
5. He generates a random value __k__ and 
blinds __x<sub>b</sub>__ by computing 
__v = (x<sub>b</sub>+k<sup>e</sup>) mod N__, 
which he sends to Alice.
6. Alice doesn't know (and hopefully cannot determine) 
which of __x<sub>0</sub>__ and __x<sub>1</sub>__ Bob chose. 
She applies both of her random values and comes up with 
two possible values for 
__k__: __k<sub>0</sub> = (v-x<sub>0</sub>)<sup>d</sup> mod N__ and 
__k<sub>1</sub> = (v-x<sub>1</sub>)<sup>d</sup> mod N__. 
One of these will be equal to __k__ and can be correctly 
decrypted by Bob (but not Alice), while the other will 
produce a meaningless random value that does not reveal 
any information about __k__.
7. She combines the two secret messages with each of the possible keys, 
__m<sub>0</sub>' = m<sub>0</sub> + k<sub>0</sub>__ and 
__m<sub>1</sub>' = m<sub>1</sub> + k<sub>1</sub>__, 
and sends them both to Bob.
8. Bob knows which of the two messages can be 
unblinded with __k__, so he is able to 
compute exactly one of the messages 
__m<sub>b</sub>' = m<sub>b</sub> - k__

## 1-out-of-n oblivious transfer

## k-out-of-n oblivious transfer

## Generalized oblivious transfer

## paper

[Actively Secure OT Extension with Optimal Overhead](https://eprint.iacr.org/2015/546.pdf) Marcel Keller, Emmanuela Orsini, and Peter Scholl

[Secure Two-party Threshold ECDSA from ECDSA Assumptions](https://eprint.iacr.org/2018/499.pdf) Jack Doerner, Yashvanth Kondi, Eysa Lee, abhi shelat 

