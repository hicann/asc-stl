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

`asc::block_collective_workspace_bytes`计算指定线程数的Block集体操作所需工作区字节数。

该接口的可用位置为AI Core SIMT编程。

## 函数原型

```cpp
namespace asc {
template<class T> constexpr asc::std::size_t block_collective_workspace_bytes(asc::std::uint32_t thread_count) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 每个参与线程读写的元素类型，决定工作区的大小与对齐。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `thread_count` | 输入 | 参与操作的元素数量。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::size_t` | 返回指定线程数的集体操作所需工作区字节数。 |

## 约束说明

- T仅可为int32_t、uint32_t或float。
- thread_count必须是32的倍数且位于[32, 1024] 范围内。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/collectives>
#include <asc/std/cstddef>

__aicore__ asc::std::size_t example()
{
    // 64 participating threads form two warps and require two unsigned integers.
    return asc::block_collective_workspace_bytes<unsigned int>(64u);
}
```

## 关联API

- [本头文件的接口列表](asc_collectives.md)
