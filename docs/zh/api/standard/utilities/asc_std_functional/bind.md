# asc::std::bind

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

`asc::std::bind`把函数对象与部分参数绑定为新可调用对象。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class Fp, class ...BoundArgs> constexpr Bind<Fp, BoundArgs...> bind(Fp&& f, BoundArgs&&... bound_args);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class Rp, class Fp, class ...BoundArgs> constexpr Bindr<Rp, Fp, BoundArgs...> bind(Fp&& f, BoundArgs&&... bound_args);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fp` | 被保存或调用的函数对象类型；实际调用须接受对应实参。 |
| `BoundArgs` | 绑定时保存的实参类型列表；占位符在调用时由对应位置的实参替换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `f` | 输入/输出 | 提供“把函数对象与部分参数绑定为新可调用对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `bound_args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rp` | 显式指定的绑定调用返回类型；绑定函数的调用结果须能按此类型返回。 |
| `Fp` | 被保存或调用的函数对象类型；实际调用须接受对应实参。 |
| `BoundArgs` | 绑定时保存的实参类型列表；占位符在调用时由对应位置的实参替换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `f` | 输入/输出 | 提供“把函数对象与部分参数绑定为新可调用对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `bound_args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `Bind<Fp, BoundArgs...>` | 返回保存调用目标及所选参数的可调用对象或引用包装器。 |
| 原型2 | `Bindr<Rp, Fp, BoundArgs...>` | 返回保存调用目标及所选参数的可调用对象或引用包装器。 |

## 约束说明

- 支持标准可调用对象和成员指针形式。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    auto bound = asc::std::bind([](int left, int right) { return left + right; }, asc::std::placeholders::_1, 2);
    return bound(3);
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
