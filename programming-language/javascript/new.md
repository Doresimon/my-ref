# operator `new`

## ES5 用法

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

@ref:

The `new` operator lets developers create an instance of a user-defined object type or of one of the built-in object types that has a constructor function.The new keyword does the following things:

Creates a **blank, plain JavaScript object**;

Links (sets the `constructor(prototype)` of) this object to another object(`__proto__`);

Passes the newly created object from Step 1 as the this context;

Returns this if the function doesn't return its own object.
