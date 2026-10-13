# asc::std::tuple_element::type

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

头文件路径为：`<asc/std/tuple>`、`<asc/std/utility>`。

`tuple_element<Index, T>::type`标识受支持类tuple对象中指定索引处的元素类型。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 声明

### 原型1

```cpp
// asc::std::tuple_element 类内的声明节选；模板形参和其他成员由所属类提供。
using type = T;
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型2

```cpp
// asc::std::tuple_element 类内的声明节选；模板形参和其他成员由所属类提供。
using type = const tuple_element_t<Index, T>;
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型3

```cpp
// asc::std::tuple_element 类内的声明节选；模板形参和其他成员由所属类提供。
using type = const volatile tuple_element_t<Index, T>;
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型4

```cpp
// asc::std::tuple_element 类内的声明节选；模板形参和其他成员由所属类提供。
using type = volatile tuple_element_t<Index, T>;
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配。
- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/tuple>
#include <asc/std/type_traits>

bool example()
{
    using Tuple = asc::std::tuple<int, float>;
    static_assert(asc::std::is_same_v<asc::std::tuple_element<1, Tuple>::type, float>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
