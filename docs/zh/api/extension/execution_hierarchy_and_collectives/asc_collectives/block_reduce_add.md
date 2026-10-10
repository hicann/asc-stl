# asc::block_reduce_add

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

`asc::block_reduce_add` 对同一线程块内参与调用的线程值求和，并返回归约结果。调用线程须按集体操作的会合要求同时参与，工作区在调用期间不得被其他操作复用。

## 函数原型

### 原型 1

```cpp
asc::std::int32_t asc::block_reduce_add(asc::block_collective_workspace<asc::std::int32_t> workspace, asc::std::int32_t value) noexcept;
```

### 原型 2

```cpp
asc::std::uint32_t asc::block_reduce_add(asc::block_collective_workspace<asc::std::uint32_t> workspace, asc::std::uint32_t value) noexcept;
```

### 原型 3

```cpp
float asc::block_reduce_add(asc::block_collective_workspace<float> workspace, float value) noexcept;
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入/输出 | 当前线程块的集体操作工作区；容量须满足参与线程数，调用期间不得并发复用。 |
| `value` | 输入 | 当前线程提供的一个待归约值。 |

## 数据类型

支持 `int32_t`、`uint32_t` 和 `float`；工作区元素类型、输入值类型和返回值类型必须一致。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::std::int32_t` | 返回参与线程输入值的有符号整数和。 |
| 原型 2 | `asc::std::uint32_t` | 返回参与线程输入值的无符号整数和。 |
| 原型 3 | `float` | 返回参与线程输入值的浮点和。 |

## 约束说明

- 仅可在 AI Core SIMT 编程中调用
- 参数类型、取值范围、会合要求和对象生命周期必须满足页面声明

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(unsigned int* dynamic_shared_pointer, unsigned int value)
{
    // 指针须指向当前线程块至少两个元素的动态共享 UB。
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return asc::block_reduce_add(workspace, value);
}
```

## 关联 API

- [asc::make_block_collective_workspace](make_block_collective_workspace.md)
- [asc::block_reduce_max](block_reduce_max.md)
- [asc::block_reduce_min](block_reduce_min.md)
