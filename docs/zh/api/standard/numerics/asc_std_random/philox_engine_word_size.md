# asc::std::philox_engine::word_size

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

`asc::std::philox_engine::word_size`给出当前随机引擎的默认种子、递推参数或轮次数值。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 声明

所属类型：[`asc::std::philox_engine`](philox_engine.md)。

```cpp
// asc::std::philox_engine 类内的声明节选；模板形参和其他成员由所属类提供。
static constexpr size_t word_size = WordSize;
```

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式。
- 不提供SeedSequence、流式输入输出或共享全局状态。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    using Engine = asc::std::philox4x32;
    static_assert(Engine::word_size == 32);
    Engine engine(7);
    const auto first = engine();
    engine.seed(7);
    // 重设相同种子应重现序列的第一个值。
    return engine() == first;
}
```

## 关联API

- [`asc::std::philox_engine`](philox_engine.md)
- [本头文件的接口列表](asc_std_random.md)
