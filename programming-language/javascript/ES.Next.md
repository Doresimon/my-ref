# ES is a simple standard.

## ES2015

1. Arrow Function

   箭头函数的 `this` 作用域继承自上下文

   ```js
   // 以前
   const _ = this
   function(x){
       _.xxx
   }
   // 现在
   //// const _ = this
   (x)=>{
       this.xxx
   }
   ```

2. Promise

   针对 callback hell.

   ```js
   // resolve 对应 then()
   // reject 对应 catch()
   const wait = () => {
     return new Promise((resolve, reject) => {
       setTimeout(resolve, 1000);
     });
   };

   wait()
     .then(() => {
       console.log("Promised to run 1000ms later");
       return wait();
     })
     .then(() => {
       console.log("Promised to run 1000ms + 1000ms later");
     });
   ```

3. `let`, `const`, `var`

   - `var` 传统的函数作用域, 变量前置
   - `let` 块级作用域, 不前置
   - `const` 块级作用域, let 的锁定版, 不前置

   目测不太需要 var 了...

4. Class

   传统上，JavaScript 是唯一一个基于`原型继承`的主流语言。

   class 是一个语法糖, 便于创建类, 便于继承.

   ```js
   class Person {
     constructor(name, age) {
       this.name = name;
       this.age = age;
     }
   }

   class Eighteen extends Person {
     constructor(name) {
       super(name, 18);
     }
   }

   const alice = new Eighteen("alice");
   ```

   **Class 没有显式的类变量声明，但必须在 构造函数(constructor) 中初始化所有变量。**

   keywords:

   - extends
   - constructor
   - super
   - getter
   - setter

5. Modules

   上古时代, ES 的模块有三个标准竞争, [@link](./standard.md)

   - AMD
   - RequireJS
   - CommonJS

   如今新增自身标准

   1. export

   ```js
   const alice = {
     name: "alice"
   };
   const bob = {
     name: "bob"
   };
   export { alice };
   export { bob };
   export default { alice, bob };
   ```

   2. import

   ```js
   import * from 'xxx.js'
   import Couple from 'xxx.js'
   import {alice, bob} from 'xxx.js'
   import Couple as CP from 'xxx.js'
   ```

6. Template Literal

   更方便的字符串创建

   ```js
   const alice = "alice";
   const age = 18;

   const intro = `I'm ${alice}, ${age + 10} years old.`;
   ```

7. Default parameter

   ```js
   const func = (name, age = 18) => {
     // ...
   };
   ```

8. spread operator `...`

   类似 golang, 将数组展开

   ```js
   const aa = [1, 2, 3, 4, 5, 6];
   const bb = [0, ...aa]; // 0,1,2,3,4,5,6

   const alice = {
     name: "alice",
     edu: {
       school: "fdu"
     }
   };
   const bob = { ...alice }; // 此处为浅拷贝 shallow copy

   //// ... 用作剩余参数(rest parameter)
   function hello(name, age, ...other) {
     for (let i = 0; i < other.length; i++) {
       console.log(other[i]);
     }
   }
   ```

9. Destructuring assignments (解构)

   `=` 赋值时只取右边变量的部分属性值

   ```js
   const alice = {
     name: "alice",
     age: 18,
     school: {
       name: "fdu"
     }
   };
   const { name: herName, age, school: school } = alice;
   console.log(herName, age, school_name);
   ```

10. Enhanced object literals

    ```js
    // 原来
    const something = "y";
    const x = {
      something: something
    };
    // 现在
    const something = "y";
    const x = {
      something // 给属性默认添加 key
    };
    ```

11. `for`

    `forEach`, `for...of`, `for...in`

    ```js
    // normal for loop
    for (let i = 0; i < arr.length; i++) {
      // code

      break;
      continue;
    }

    // forEach
    arr.forEach(value => {
      // code
      break; // do not work
      continue; // do not work

      return false;// break the loop
      return true;// continue the loop
    });

    // for of
    // Array, String, TypedArray, Map, Set
    for(const iterator of arr){
      // code
      break;
      continue;
    }

    // for of 循环一个对象
    for(const prop of Object.keys(obj)){
        const v = obj[prop]
       // code
    }
    // for of 循环一个对象
    for(const v of Object.values(obj)){
       // code
    }

    // for in
    // 循环对象的可枚举属性
    // 也可循环一个数组
    for(const key in obj){
        const v = obj[key]//obj.getProperty(key)
    }
    ```

12. `Map`

    `Map` 对象保存键值对。**任何值(对象或者原始值) 都可以作为一个键或一个值。**

    一个 `Map` 对象在迭代时会根据对象中元素的插入顺序来进行 , 一个 `for...of` 循环在每次迭代后会返回一个形式为[`key`, `value`]的数组。

    键的比较是基于 "`SameValueZero`" 算法：**NaN 是与 NaN 相等的（虽然 NaN !== NaN）**，**剩下所有其它的值是根据 === 运算符的结果判断是否相等**。在目前的 ECMAScript 规范中，-0 和+0 被认为是相等的，尽管这在早期的草案中并不是这样。

    - Object vs Map

      Object 和 Map 类似, 早期 Object 都是当作 Map 来使用.

      1. 一个 `Object` 的键只能是字符串或者 `Symbols`，但一个 `Map` 的键可以是`任意值`，包括**函数、对象、基本类型**。

      2. `Map` 中的键值是有序的，而添加到 `Object` 中的键则不是。因此，当对它进行遍历时，`Map` 对象是按插入的顺序返回键值。

      3. `Map.size` 直接获取元素个数

      4. `Map` 支持 `for...of` => `for(const [k, v] of someMap){...}`

      5. `Map` 在频繁 `CRUD` 场景下性能较好.

    ```js
    const map = new Map();
    map.set(1, "aaa");
    map.set({ name: 1 }, "bbb");

    console.log(map.get(1));
    console.log(map.get({ name: 1 })); // undefined
    ```

13. `Set`

    `Set` 为对象值的集合, **Set 中的元素只会出现一次(唯一性)**

    `NaN`, `undefined` 均可以储存在 `Set` 中.

    可用于数组去重.

## ES2016

1. Array.prototype.includes()

   ```js
   // before 用于判断数组中存在某个值
   arr.indexOf("xxx") !== -1;
   // now
   arr.includes("xxx" === true;
   ```

2. Exponent operator `**`

   ```js
   const pow = 10;
   // before
   Math.pow(2, pow);

   // now
   2 ** pow;
   ```

## ES2017

1.  String: padStart(), padEnd()

    字符串填充

    ```js
    let str = "15";
    str.padStart(4, "0"); // 补到4位
    ```

2.  Object.values(), Object.entries()

    返回对象的所有的值, 不是 key

    ```js
    // Object
    const alice = { name: "alice", age: 18 };
    Object.keys(alice); // ['name', 'age']
    Object.values(alice); // ['alice', 18]
    Object.entries(alice); // [['name', 'alice'], ['age', 18]]

    // Array
    const bob = ["bob", 80];
    Object.keys(bob); // ['0', '1']
    Object.values(bob); // ['bob', 18]
    Object.entries(bob); // [['0', 'bob'], ['1', 18]]
    ```

3.  Object.getOwnPropertyDescriptors()

    此方法返回对象的所有自有（非继承的）属性描述符。

    JavaScript 中的任何对象都有一组属性，每个属性都有一个描述符。

    描述符是属性(property) 的一组特性(attributes)，它由以下的子集组成：

    - value：属性的值
    - writable：true 表示改属性可以被修改
    - get：属性的 getter 函数，在读取属性时调用
    - set：属性的 setter 函数，在属性设置值时调用
    - configurable：如果为 false ，则不能删除属性，也不能更改任何属性，但值除外
    - enumerable：如果属性是可枚举的，则为 true

    Object.getOwnPropertyDescriptors(obj) 接受一个对象，并返回一个带有描述符集的对象。

    ```js
    const p1 = {
        name:'p1',
        mom:{
            name:'alice'
            age:18
        }
    }
    const p2 = {}
    Object.assign(p2, p1) // shallow copy

    const p3 = {}
    Object.defineProperties(
        person3,
        Object.getOwnPropertyDescriptors(person1)
    ) // deep copy
    ```

4.  async, await

    Async Functions (异步函数) 是 promises 和 generators(生成器) 的组合，以简化 promises 调用，提过代码的可读性，但是不打破 promises 链式调用的限制

    Promise 解决 CallBack Hell.
    Async 将 Promise 简化..

5.  共享内存 和 Atomics (`TODO`)

## ES2018

1. `Rest`(剩余)/`Spread`(展开) 属性

   ```js
   // rest
   const { first, second, ...others } = {
     first: 1,
     second: 2,
     third: 3,
     fourth: 4,
     fifth: 5
   };
   // spread
   const items = { first, second, ...others };
   ```

2. Asynchronous iteration （异步迭代）

   略...

3. Promise.prototype.finally()

   resolve() => then()

   reject() => catch()

   \* => finally()

   ```js
   const wait = () => {
     return new Promise((resolve, reject) => {
       if (ok) {
         resolve("ok");
       } else {
         reject("not ok");
       }
     });
   };

   wait.then(ret){
       ret === 'ok'
   }.catch(err){
       err === 'not ok'
   }.finally(){
       console.log('always come here')
   }
   ```

4. Regex 的很多新特性 (`TODO`)

## ES2019

??? Can u come slower?

## @ref

[https://www.html.cn/archives/9922](https://www.html.cn/archives/9922)
