# asc::std::make_from_tuple

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

`asc::std::make_from_tuple` 用 tuple 元素作为构造参数创建指定类型对象。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

```cpp
template<class T, class Tuple> constexpr T asc::std::make_from_tuple(Tuple&& value);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Tuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回用 tuple 元素构造的目标类型对象。 |

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/tuple>

decltype(auto) example()
{
    asc::std::tuple<int, int> values{1, 2};
    return asc::std::make_from_tuple<asc::std::pair<int, int>>(values);
}
```
