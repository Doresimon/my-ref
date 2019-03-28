# ES is a simple standard.

## ES2015

1. Arrow Function

    箭头函数的 this 作用域继承自上下文

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

## ES2016

## ES2017

1.  String: padStart(), padEnd()

    字符串填充

    ```js
    let str = '15';
    str.padStart(4, '0'); // 补到4位
    ```

2.  Object.values(), Object.entries()

    返回对象的所有的值, 不是 key

    ```js
    // Object
    const alice = { name: 'alice', age: 18 };
    Object.keys(alice); // ['name', 'age']
    Object.values(alice); // ['alice', 18]
    Object.entries(alice); // [['name', 'alice'], ['age', 18]]

    // Array
    const bob = ['bob', 80];
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
        Object.assign(p2, p1) //浅拷贝

        const p3 = {}
        Object.defineProperties(
            person3,
            Object.getOwnPropertyDescriptors(person1)
        ) // 深拷贝
        ```

4.  async, await

    Async Functions (异步函数) 是 promises 和 generators(生成器) 的组合，以简化 promises 调用，提过代码的可读性，但是不打破 promises 链式调用的限制

    Promise 解决 CallBack Hell.
    Async 将 Promise 简化..

## ES2018

## ES2019

???

## @ref

[https://www.html.cn/archives/9922](https://www.html.cn/archives/9922)
