# asc::std::bind_front

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

`asc::std::bind_front`把调用参数固定在函数对象实参列表的前部。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

```cpp
namespace asc::std {
template<class Fn, class ...Args> constexpr auto bind_front(Fn&& function, Args&&... args) noexcept(is_nothrow_constructible_v<tuple<decay_t<Args>...>, Args&&...>);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fn` | 被调用的函数、函数指针、成员指针或函数对象类型。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 提供“把调用参数固定在函数对象实参列表的前部”使用的对象引用；被引用对象须在调用期间有效。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `auto` | 返回保存调用目标及所选参数的可调用对象或引用包装器。 |

## 约束说明

- 支持标准可调用对象和成员指针形式。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    auto bound = asc::std::bind_front([](int left, int right) { return left + right; }, 2);
    return bound(3);
}

bool verify_example()
{
    return example() == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
