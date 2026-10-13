# asc::block_broadcast

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

头文件路径为：`<asc/collectives>`。

`asc::block_broadcast`把指定源线程的值广播给同一Block的所有线程。

## 函数原型

### 原型1

```cpp
namespace asc {
asc::std::int32_t block_broadcast(asc::block_collective_workspace<asc::std::int32_t> workspace, asc::std::int32_t value, asc::std::uint32_t source_thread) noexcept;
} // namespace asc
```

### 原型2

```cpp
namespace asc {
asc::std::uint32_t block_broadcast(asc::block_collective_workspace<asc::std::uint32_t> workspace, asc::std::uint32_t value, asc::std::uint32_t source_thread) noexcept;
} // namespace asc
```

### 原型3

```cpp
namespace asc {
float block_broadcast(asc::block_collective_workspace<float> workspace, float value, asc::std::uint32_t source_thread) noexcept;
} // namespace asc
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入 | 当前线程块的集体操作工作区；参与线程会合期间不得复用。 |
| `value` | 输入 | 待广播的值：仅source_thread线程提供的值被使用，其余线程传入的该值被忽略。 |
| `source_thread` | 输入 | 广播源线程在当前线程块内的线程索引；该参数为标量索引，不涉及存储生命周期。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入 | 当前线程块的集体操作工作区；参与线程会合期间不得复用。 |
| `value` | 输入 | 待广播的值：仅source_thread线程提供的值被使用，其余线程传入的该值被忽略。 |
| `source_thread` | 输入 | 广播源线程在当前线程块内的线程索引；该参数为标量索引，不涉及存储生命周期。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入 | 当前线程块的集体操作工作区；参与线程会合期间不得复用。 |
| `value` | 输入 | 待广播的值：仅source_thread线程提供的值被使用，其余线程传入的该值被忽略。 |
| `source_thread` | 输入 | 广播源线程在当前线程块内的线程索引；该参数为标量索引，不涉及存储生命周期。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::std::int32_t` | 返回线程块广播或扫描后当前线程对应的结果。 |
| 原型2 | `asc::std::uint32_t` | 返回线程块广播或扫描后当前线程对应的结果。 |
| 原型3 | `float` | 返回线程块广播或扫描后当前线程对应的结果。 |

## 约束说明

- 仅可在AI Core SIMT编程中调用。
- 同一block的所有线程以相同顺序会合调用；总线程数必须为32的正整数倍。
- 工作区来自该block的动态共享UB，至少包含thread_count()/32个T，且调用期间不得被其他并发操作复用。
- source_thread是block内展平的线程编号，必须小于总线程数，所有线程传入相同编号。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(unsigned int* dynamic_shared_pointer, unsigned int value)
{
    // 从当前线程块的第 0 个线程广播输入值。
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return asc::block_broadcast(workspace, value, 0u);
}
```

## 关联API

- [本头文件的接口列表](asc_collectives.md)
