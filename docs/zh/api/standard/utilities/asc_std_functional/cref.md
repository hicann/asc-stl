# asc::std::cref

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

头文件路径为：`<asc/std/functional>`。

`asc::std::cref` 创建指向常量对象的引用包装器。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

### 原型 1

```cpp
template<class T> [[nodiscard]] constexpr reference_wrapper<const T> asc::std::cref(const T& value) noexcept;
```

### 原型 2

```cpp
template<class T> [[nodiscard]] constexpr reference_wrapper<const T> asc::std::cref(reference_wrapper<T> value) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `reference_wrapper<const T>` | 返回保存调用目标及所选参数的可调用对象或引用包装器。 |
| 原型 2 | `reference_wrapper<const T>` | 返回保存调用目标及所选参数的可调用对象或引用包装器。 |

## 约束说明

- 支持标准可调用对象和成员指针形式
- invoke_r 是经确认提供的 C++23 回移接口

## 调用示例

以下 Host 片段使用具体对象展示接口调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    int value = 3;
    return asc::std::cref(value);
}
```
