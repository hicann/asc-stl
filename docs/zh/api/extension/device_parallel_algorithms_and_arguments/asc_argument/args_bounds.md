# asc::args::bounds

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

头文件路径为：`<asc/argument>`。

`asc::args::bounds` 创建编译期或运行期参数边界对象。

## 函数原型

### 原型 1

```cpp
template<auto Lower, auto Upper> constexpr asc::args::static_bounds<Lower, Upper> asc::args::bounds() noexcept;
```

### 原型 2

```cpp
template<class T> constexpr asc::args::runtime_bounds<T> asc::args::bounds(T lower, T upper) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Lower` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `Upper` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lower` | 输入 | 提供“创建编译期或运行期参数边界对象”所需的输入对象；类型须满足所选原型约束。 |
| `upper` | 输入 | 提供“创建编译期或运行期参数边界对象”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::args::static_bounds<Lower, Upper>` | 返回编译期或运行期参数边界对象。 |
| 原型 2 | `asc::args::runtime_bounds<T>` | 返回编译期或运行期参数边界对象。 |

## 约束说明

- 使用 C++17，可在 Host、AI Core SIMD 编程 和 AI Core SIMT 编程中使用
- Bounds 必须为 asc::args::no_bounds 或 asc::args::static_bounds
- 延迟指针在使用时不得为空，调用方存储必须覆盖整个使用周期

## 调用示例

以下片段给出具体模板实参和调用对象。

```cpp
#include <asc/argument>

decltype(auto) example()
{
    return asc::args::bounds<0, 10>();
}
```
