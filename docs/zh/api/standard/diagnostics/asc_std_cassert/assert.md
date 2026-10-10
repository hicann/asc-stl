# assert

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/std/cassert>`。

`assert` 在调试构建中检查条件，条件为假时触发断言失败。

标准语义参考：[cppreference `cassert`](https://en.cppreference.com/w/cpp/header/cassert)。

## 声明

```cpp
#define assert(expression) ((expression) ? void(0) : implementation-defined diagnostic followed by termination)
```

## 约束说明

- 宏值取决于 NDEBUG
- 展开结果为可用于条件判断的 true 或 false 表达式

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cassert>

#ifndef assert
#error "assert is required by this public Header"
#endif
```
