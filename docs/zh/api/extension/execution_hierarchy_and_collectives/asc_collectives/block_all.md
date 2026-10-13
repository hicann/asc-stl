# asc::block_all

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

`asc::block_all`判断同一Block的所有线程谓词是否都为true。

## 函数原型

```cpp
namespace asc {
bool block_all(asc::block_collective_workspace<asc::std::uint32_t> workspace, bool predicate) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入 | 当前线程块的集体操作工作区；参与线程会合期间不得复用。 |
| `predicate` | 输入 | 用于判断元素是否满足条件的可调用对象。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 仅可在AI Core SIMT编程中调用。
- 同一block的所有线程以相同顺序会合调用；总线程数必须为32的正整数倍。
- 工作区来自该block的动态共享UB，至少包含thread_count()/32个T，且调用期间不得被其他并发操作复用。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/collectives>

__aicore__ bool example(unsigned int* dynamic_shared_pointer, bool predicate)
{
    // 同一线程块的参与线程使用共同的动态共享工作区。
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return asc::block_all(workspace, predicate);
}
```

## 关联API

- [本头文件的接口列表](asc_collectives.md)
