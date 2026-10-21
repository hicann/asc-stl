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

`assert`在调试构建中检查条件，条件为假时触发断言失败。

标准语义参考：[cppreference `cassert`](https://en.cppreference.com/w/cpp/header/cassert)。

## 声明

Host沿用`<assert.h>`的宏定义。以下为Device分支：

```cpp
#if defined(NDEBUG)
#define assert(expression) ((void)0)
#else
#define assert(expression) ((expression) ? (void)0 : __builtin_trap())
#endif
```

## 约束说明

- 展开结果为void表达式，不能作为if等条件使用。
- 未定义NDEBUG时检查条件；失败时Host执行平台诊断并终止，Device触发trap。
- 定义NDEBUG时不求值expression；不得依靠断言中的副作用实现正常逻辑。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/cassert>

bool example()
{
    const int value = 2 + 3;
    assert(value == 5);
    return value == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cassert.md)
