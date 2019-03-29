# operator `new`

## ES5

```js
function People(name) {
  this.name = name;
  this.age = 18;

  this.__proto__.cnt = this.__proto__.cnt || 0;
  this.__proto__.cnt++;

  this.who = function() {
    console.log(`i'm ${this.name}, ${this.age} years old.`);
  };
}

var Alice = new People("alice");
var Bob = new People("bob");
People("caca"); // 此处调用时this为全局对象window, 没啥影响.

Alice.age = 20;
Alice.who();
Bob.who();

People.prototype.showCnt = function() {
  console.log("cnt is", this.cnt);
  // this === People.prototype === Alice.__proto__ === Bob.__proto__
};

People.prototype.showCnt(); // 2
Alice.showCnt(); // 2
Bob.showCnt(); // 2
```

首先定义一个函数, 此函数无返回值, 内部使用 `this` 指针来定义变量.

正常调用此函数时, `this` 会绑定为函数定义时的 `this` (即 `window` 对象).

使用 `new` 操作符会进行如下步骤

```js
{
  let o = {};
  o.__prpto__ = People.prototype;
  People.call(o);
  return o;
}
```

@[ref](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/new):

The `new` operator lets developers create an instance of a user-defined object type or of one of the built-in object types that has a constructor function.The new keyword does the following things:

1. Creates a **blank, plain JavaScript object**;

2. Links (sets the `constructor(prototype)` of) this object to another object(`__proto__`);

3. Passes the newly created object from Step 1 as the this context;

4. Returns this if the function doesn't return its own object.

## ES6

```js
class People {
  constructor(name, age = 18) {
    this.name = name;
    this.age = age;
  }
  // instance methods
  hello() {
    console.log(`hello, i'm ${this.name}`);
  }
  foo() {
    console.log("People.name", People.name);
  }
  // static methods(only for class)
  static oops() {
    console.log("oops");
    if (!this.prototype.cnt) {
      this.prototype.cnt = 0; // define a static variable
    }
    this.prototype.cnt++;
    console.log("cnt", this.prototype.cnt);
  }
}

const alice = new People("alice");
alice.hello();
alice.foo();
// alice.oops(); // not a function
People.oops();
People.oops();
```
