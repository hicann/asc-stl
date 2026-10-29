# asc::std::optional<T&>::`operator=`

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

头文件路径为：`<asc/std/optional>`。

`asc::std::optional<T&>::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型1

```cpp
// asc::std::optional<T&> 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr asc::std::optional<T&>& operator=(asc::std::nullopt_t) noexcept;
```

### 原型2

```cpp
// asc::std::optional<T&> 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr asc::std::optional<T&>& operator=(const asc::std::optional<T&>&) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc` | 输入 | nullopt_t空状态标记（nullopt常量）；赋值后当前optional不再引用任何对象。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `参数1` | 输入 | 复制来源optional<T&>；当前对象重新绑定到其引用的同一目标，被引用对象本身不被修改。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::std::optional<T&>&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `asc::std::optional<T&>&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 引用特化仅允许安全的同类型左值绑定。
- 采用借用指针语义，不提供容易产生悬空引用的转换。

## 调用示例

以下Host片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/optional>

bool example()
{
    int value = 7;
    asc::std::optional<int&> reference(value);
    reference = asc::std::nullopt;
    return !reference.has_value() && value == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
