# typeof vs instance of

## typeof

```js
class People {}

console.log("true", typeof true); // number
console.log("NaN", typeof NaN); // number
console.log("Infinity", typeof Infinity); // number
console.log("1", typeof 1); // number
console.log("''", typeof ""); // string
console.log("[]", typeof []); // object
console.log("{}", typeof {}); // object
console.log("null", typeof null); // object
console.log("undefined", typeof undefined); // undefined
console.log("() => {}", typeof (() => {})); // function
console.log("class{}", typeof People); // function
console.log("Symbol('...')", typeof Symbol("s")); // symbol
```

可能的返回值

- boolean => `true`, `false`
- number => `1`, `2.3`, `NaN`, `Infinity`
- string => `''`, `""`, `"1231"`
- object => `object`, `null`, `array`
- undefined => `undefined`
- function => `function`, `class`
- symbol => `symbol`

## instance of

The `instanceof` operator tests whether the prototype property of a constructor appears anywhere in the `prototype chain` of an object.

从对象的`原型链`中寻找是否存在所判定的原型.

要有原型链, 才能用来判断, 否则直接 `false`

可用于判断精确类型.

```js
function Car(make, model, year) {
  this.make = make;
  this.model = model;
  this.year = year;
}
let someCar = new Car("Honda", "Accord", 1998);

console.log(someCar instanceof Car); // true
console.log(someCar instanceof Object); // true

console.log([1, 2, 3] instanceof Array); // true

// 基本类型需要慎用
console.log(1 instanceof Number); // false
console.log(Number(1) instanceof Number); // false
console.log(new Number(1) instanceof Number); // true
```
