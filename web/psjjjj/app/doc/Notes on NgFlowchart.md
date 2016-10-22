Notes on NgFlowchart
==============
关于 NgFlowchart 源代码的一些笔记。

flowchart-constant
-----------
在本段函数中记录了 `constants.*` 常数。

调用
```
angular
  .module('flowchart')
  .constant('flowchartConstants', constants);
```
函数。这个函数类似于 `$provide.constant()` ，定义为：

>Register a **constant service** with the **$injector**, such as a string, a number, an array, an object or a function. Like the value, it is not possible to inject other services into a constant.

因此上述函数会将`constants`常数导出为全局可见的`flowchart-constant`。

topsort-service
-----------
本函数返回一个 list ，为通过所有边连接的 node 进行 **排序**，从第一个（没有输入的）节点开始。在我们的程序里，为什么需要排序呢？

调用
```
angular
  .module('flowchart')
  .factory('Topsortservice', Topsortservice);
```
函数，将 `Topsortservice` 导出为全局可见的 **service factory** ，以生成一个 service 。可以看成 *一个函数* ？？不是很懂。

modelvalidation-service
-------
判断某个model是否合法，合法则返回之，否则抛出错误。

定义子类 `ModelvalidationError` ，为错误类型。 `ModelvalidationError.prototype` 为函数的 *原型* ？不是很懂。

调用
```
angular
  .module('flowchart')
  .service('Modelvalidation', Modelvalidation);
```
导出为一个 **service** ，可以被 `new` 出来。可以看成 *一个类* ？？不是很懂。

model-service
-----
参数中包括不少 `Callback` ，那是什么？不懂。

据说含有类内变量
```
var connectorsHtmlElements = {};
var canvasHtmlElement = null;
var svgHtmlElement = null;
```
吗？不是很懂。

定义的子类包括 `modelservice.connectors` 、 `modelservice.nodes` 、 `modelservice.edges` 三个主要成员，以及很多功能函数。

To be continued.
