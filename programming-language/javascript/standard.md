# js standard

## 模块化解决方案

### [commonJS](http://wiki.commonjs.org)

`Node.js`

`同步`加载, 一般用于服务端, 文件存在于本地的情况下. 不适合浏览器端.

```js
// export
module.exports = xxx;
exports.yyy = function(val) {
    return add(val, 1);
};

// import
const xxx = require('xxx.js');
const yyy = require('xxx.js').yyy;
```

### [requireJS](https://requirejs.org/docs/node.html)

AMD 规范 - 采用`异步`方式加载模块，模块的加载不影响它后面语句的运行。所有依赖这个模块的语句，都定义在一个回调函数中，等到加载完成之后，这个回调函数才会运行。

```js
define(function(require, exports, module) {
    //Put traditional CommonJS module content here
});
```

```js
/** 网页中引入require.js及main.js **/
<script src="js/require.js" data-main="js/main" />;
/** main.js 入口文件/主模块 **/

// 引入
require.config({
    baseUrl: 'js/lib',
    paths: {
        jquery: 'jquery.min', //实际路径为js/lib/jquery.min.js
        underscore: 'underscore.min'
    }
});

// 引入 [module, module], (nickname, nickname) =>
require(['jquery', 'underscore'], function($, _) {
    // some code here
});
```

### ES6 Module

`import`

`export`

ES6 的模块不是对象，import 命令会被 JavaScript 引擎静态分析，在编译时就引入模块代码，而不是在代码运行时加载，所以无法实现条件加载。也正因为这个，使得静态分析成为可能。

```js
export { xxx };
export { yyy };
export default { xxx, yyy };

import {xxx, yyy} from `xxx.js`
import zzz from `xxx.js`
```

## @ref

[http://www.cnblogs.com/yangshifu/p/7271661.html](http://www.cnblogs.com/yangshifu/p/7271661.html)

[https://requirejs.org/docs/commonjs.html](https://requirejs.org/docs/commonjs.html)

[http://wiki.commonjs.org/wiki/CommonJS](http://wiki.commonjs.org/wiki/CommonJS)
