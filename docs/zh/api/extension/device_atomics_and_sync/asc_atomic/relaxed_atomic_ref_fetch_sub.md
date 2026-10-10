# asc::relaxed_atomic_ref::fetch_sub

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

头文件路径为：`<asc/atomic>`。

`asc::relaxed_atomic_ref::fetch_sub` 原子减去操作数并返回修改前的值。

## 函数原型

```cpp
T asc::relaxed_atomic_ref::fetch_sub(T operand) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operand` | 输入 | 参与本次原子读取、写入或读改写操作的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回修改前的值。 |

## 约束说明

- 仅可在 AI Core SIMT 编程中调用
- 参数类型、取值范围、会合要求和对象生命周期必须满足页面声明

## 调用示例

以下 AI Core SIMT 片段使用调用方管理的 GM 原子单元；初始化与并发访问须满足本页约束。

```cpp
#include <asc/atomic>

__aicore__ decltype(auto) example(int* gm_cell)
{
    // gm_cell 指向调用方管理的 GM 整数单元。
    asc::relaxed_atomic_ref<int> value(*gm_cell);
    return value.fetch_sub(1);
}
```
