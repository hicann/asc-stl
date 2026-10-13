# asc::std::tuple_cat（函数模板）

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

`asc::std::tuple_cat` 按顺序拼接多个 tuple 的元素。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

```cpp
template<class Tuple0, class ...Tuples> constexpr typename Tuplecatreturn<Tuple0, Tuples...>::type asc::std::tuple_cat(Tuple0&& first, Tuples&&... right);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tuple0` | 第一个待拼接的 tuple 类型；须为 tuple 类模板实例。 |
| `Tuples` | 其余各待拼接 tuple 的类型；结果按实参顺序拼接全部元素。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入/输出 | 第一个待拼接的 tuple；其元素置于结果开头，右值时元素被移动，移动后处于有效但未指定状态 |
| `right` | 输入/输出 | 其余待拼接的各 tuple；元素依次接在 first 的元素之后，右值时元素被移动，移动后处于有效但未指定状态 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `typename Tuplecatreturn<Tuple0, Tuples...>::type` | 返回按给定元素或 tuple 组合得到的新 tuple。 |

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/tuple>

template <class Tuple0, class ...Tuples>
decltype(auto) example(Tuple0 && first, Tuples &&... right)
{
    return asc::std::tuple_cat(first, right...);
}
```
