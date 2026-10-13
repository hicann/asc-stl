# asc::copy_async

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

头文件路径为：`<asc/pipeline>`。

`asc::copy_async`在指定流水级提交全局内存（GM）与片上缓冲区（UB）之间的连续数据搬运。提交后须按流水线同步规则等待完成，再读取目标视图或复用源存储。

## 函数原型

### 原型1

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int16_t> destination, asc::ub_span<const asc::std::int16_t> source) noexcept;
} // namespace asc
```

### 原型2

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int32_t> destination, asc::ub_span<const asc::std::int32_t> source) noexcept;
} // namespace asc
```

### 原型3

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int8_t> destination, asc::ub_span<const asc::std::int8_t> source) noexcept;
} // namespace asc
```

### 原型4

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint16_t> destination, asc::ub_span<const asc::std::uint16_t> source) noexcept;
} // namespace asc
```

### 原型5

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint32_t> destination, asc::ub_span<const asc::std::uint32_t> source) noexcept;
} // namespace asc
```

### 原型6

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint8_t> destination, asc::ub_span<const asc::std::uint8_t> source) noexcept;
} // namespace asc
```

### 原型7

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<float> destination, asc::ub_span<const float> source) noexcept;
} // namespace asc
```

### 原型8

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int16_t> destination, asc::gm_span<const asc::std::int16_t> source) noexcept;
} // namespace asc
```

### 原型9

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int32_t> destination, asc::gm_span<const asc::std::int32_t> source) noexcept;
} // namespace asc
```

### 原型10

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int8_t> destination, asc::gm_span<const asc::std::int8_t> source) noexcept;
} // namespace asc
```

### 原型11

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint16_t> destination, asc::gm_span<const asc::std::uint16_t> source) noexcept;
} // namespace asc
```

### 原型12

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint32_t> destination, asc::gm_span<const asc::std::uint32_t> source) noexcept;
} // namespace asc
```

### 原型13

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint8_t> destination, asc::gm_span<const asc::std::uint8_t> source) noexcept;
} // namespace asc
```

### 原型14

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<float> destination, asc::gm_span<const float> source) noexcept;
} // namespace asc
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pipeline` | 输入 | 管理本次异步搬运的流水线引用；流水线须在搬运完成前有效。 |
| `stage` | 输入 | 流水级索引，须小于该流水线的级数。 |
| `destination` | 输出 | 接收搬运结果的非拥有视图；由所选原型决定其存储位于GM或UB，长度须足以容纳源数据。 |
| `source` | 输入 | 提供待搬运数据的非拥有视图；由所选原型决定其存储位于UB或GM，完成前底层存储须有效。 |

## 数据类型

支持两个方向：GM → UB、UB → GM。两个视图的元素类型必须相同，可选`int8_t`、`uint8_t`、`int16_t`、`uint16_t`、`int32_t`、`uint32_t`或`float`；每种类型和方向各有独立原型。

## 返回值说明

无返回值。

## 约束说明

- 仅可在AI Core SIMD编程中调用。
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/pipeline>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

__aicore__ void example(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int16_t> destination, asc::ub_span<const asc::std::int16_t> source)
{
    asc::copy_async(pipeline, stage, destination, source);
}
```

## 关联API

- [asc::make_pipeline](make_pipeline.md)
- [asc::pipeline_ref::producer_commit](pipeline_ref_producer_commit.md)
- [asc::pipeline_ref::consumer_wait](pipeline_ref_consumer_wait.md)
