# asc::std::tie

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

头文件路径为：`<asc/std/tuple>`。

`asc::std::tie`创建保存调用方左值引用的tuple。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

```cpp
namespace asc::std {
template<class ...T> [[nodiscard]] constexpr tuple<T&...> tie(T&... values) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 各被绑定左值对象的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 被绑定的各左值对象；返回的tuple保存指向它们的左值引用，对象生命周期须覆盖tuple的使用期。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `tuple<T &...>` | 返回保存调用方左值引用的tuple。 |

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/tuple>

decltype(auto) example()
{
    int left = 1;
    int right = 2;
    return asc::std::tie(left, right);
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
