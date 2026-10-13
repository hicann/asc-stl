# asc::block_exclusive_scan

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

`asc::block_exclusive_scan` 对同一 Block 各线程的输入执行排他前缀和。

## 函数原型

### 原型 1

```cpp
asc::std::int32_t asc::block_exclusive_scan(asc::block_collective_workspace<asc::std::int32_t> workspace, asc::std::int32_t value) noexcept;
```

### 原型 2

```cpp
asc::std::uint32_t asc::block_exclusive_scan(asc::block_collective_workspace<asc::std::uint32_t> workspace, asc::std::uint32_t value) noexcept;
```

### 原型 3

```cpp
float asc::block_exclusive_scan(asc::block_collective_workspace<float> workspace, float value) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入 | 当前 Block 的集体操作工作区：存放各 warp 的部分结果，元素数不少于 Block 内 warp 数；参与线程会合期间不得复用。 |
| `value` | 输入 | 当前线程参与排他前缀和的输入值：返回本线程之前所有线程输入的前缀和（不含本线程）。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入 | 当前 Block 的集体操作工作区：存放各 warp 的部分结果，元素数不少于 Block 内 warp 数；参与线程会合期间不得复用。 |
| `value` | 输入 | 当前线程参与排他前缀和的输入值：返回本线程之前所有线程输入的前缀和（不含本线程）。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `workspace` | 输入 | 当前 Block 的集体操作工作区：存放各 warp 的部分结果，元素数不少于 Block 内 warp 数；参与线程会合期间不得复用。 |
| `value` | 输入 | 当前线程参与排他前缀和的输入值：返回本线程之前所有线程输入的前缀和（不含本线程）。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::std::int32_t` | 返回线程块广播或扫描后当前线程对应的结果。 |
| 原型 2 | `asc::std::uint32_t` | 返回线程块广播或扫描后当前线程对应的结果。 |
| 原型 3 | `float` | 返回线程块广播或扫描后当前线程对应的结果。 |

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
    return asc::block_exclusive_scan(workspace, value);
}
```
