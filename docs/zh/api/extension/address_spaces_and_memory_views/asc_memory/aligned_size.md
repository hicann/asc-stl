# asc::aligned_size

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

头文件路径为：`<asc/memory>`。

`asc::aligned_size` 将 `size` 向上舍入到 `alignment` 的整数倍；当 alignment 为零时返回原始 size。

## 函数原型

```cpp
template<class Integer> constexpr Integer asc::aligned_size(Integer size, Integer alignment) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Integer` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `size` | 输入 | 对象或范围的大小。 |
| `alignment` | 输入 | 要求的对齐值，单位为字节。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `Integer` | 返回原始 size。 |

## 约束说明

- Integer 必须支持整数除法、加法和乘法
- 计算结果必须能由 Integer 表示

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/memory>

decltype(auto) example()
{
    return asc::aligned_size(17u, 8u);
}
```
