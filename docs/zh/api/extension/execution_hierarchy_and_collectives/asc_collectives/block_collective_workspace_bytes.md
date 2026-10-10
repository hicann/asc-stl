# asc::block_collective_workspace_bytes

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

`asc::block_collective_workspace_bytes` 计算指定线程数的 Block 集体操作所需工作区字节数。

该接口的可用位置为 AI Core SIMT 编程。

## 函数原型

```cpp
template<class T> constexpr asc::std::size_t asc::block_collective_workspace_bytes(asc::std::uint32_t thread_count) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `thread_count` | 输入 | 参与操作的元素数量。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::size_t` | 返回指定线程数的集体操作所需工作区字节数。 |

## 约束说明

- T 仅可为 int32_t、uint32_t 或 float
- thread_count 必须是 32 的倍数且位于 [32, 1024] 范围内

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/collectives>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

__aicore__ asc::std::size_t example()
{
    // 64 个参与线程对应两个线程束的工作区。
    return asc::block_collective_workspace_bytes<unsigned int>(64u);
}
```
