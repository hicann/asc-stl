# asc::std::philox4x32

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

头文件路径为：`<asc/std/random>`。

`asc::std::philox4x32` 提供对应随机数引擎或分布参数的类型别名。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 声明

```cpp
using asc::std::philox4x32 = philox_engine<uint_fast32_t, 32, 4, 10, 3449720151U, 2654435769U, 3528531795U, 3144134277U>
```

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式
- 不提供 SeedSequence、流式输入输出或共享全局状态

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/random>

void use_type(const asc::std::philox4x32& value)
{
    (void)value;
}
```
