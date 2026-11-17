# asc::std::philox_engine::set_counter

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

`asc::std::philox_engine::set_counter`设置计数器型随机数引擎的当前位置。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

所属类型：[`asc::std::philox_engine`](philox_engine.md)。

```cpp
// asc::std::philox_engine 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr void set_counter(const asc::std::array<UIntType, WordCount>& counter) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `counter` | 输入 | 完整计数器字数组，长度为WordCount；按高位字到低位字传入，各字限制在WordSize位内，并重置块内输出位置。 |

## 返回值说明

无返回值。

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式。
- 不提供SeedSequence、流式输入输出或共享全局状态。
- 计数器定位的是输出块，而不是单个输出字。`philox4x32`每块产生4个32位输出；定位第`i`个输出时先设置块计数器`i/4`，再`discard(i%4)`。计数器数组按高位字在前传入，低64位块编号`b`对应`{0,0,b>>32,b&0xffffffff}`。`set_counter`丢弃已有块内缓存位置并保留种子产生的key。

## 调用示例

以下Host片段模拟Dropout算子分块时的随机流定位：后续分块从全局第5个随机样本开始，而不是重新从第0个开始。真实批量用法需让每个元素或分块具有明确的全局索引。

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::philox4x32 whole(7), tile(7);
    asc::std::uniform_real_distribution<float> uniform;
    whole.discard(5);
    tile.set_counter({0, 0, 0, 1});
    tile.discard(1);
    for (int i = 0; i < 7; ++i) {
        if (uniform(whole) != uniform(tile)) return false;
    }
    return true;
}
```

## 关联API

- [`asc::std::philox_engine`](philox_engine.md)
- [本头文件的接口列表](asc_std_random.md)
