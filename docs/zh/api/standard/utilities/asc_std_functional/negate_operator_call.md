# asc::std::negate::operator()

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

`asc::std::negate::operator()` 按 `negate` 的可用运算符规则处理当前对象及操作数。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

### 原型 1

```cpp
constexpr T asc::std::negate::operator()(const T& x) const;
```

### 原型 2

```cpp
template<class T> constexpr auto asc::std::negate::operator()(T&& x) const noexcept(noexcept(-::asc::std::forward<T>(X))) -> decltype(-::asc::std::forward<T>(X));
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T` | 返回函数对象按所选实参调用得到的结果。 |
| 原型 2 | `decltype(-::asc::std::forward<T>(X))` | 返回函数对象按所选实参调用得到的结果。 |

## 约束说明

- 同时提供指定类型形式和透明调用形式

## 调用示例

以下 Host 片段以具体整数实参演示函数对象调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    return asc::std::negate<>{}(7);
}
```
