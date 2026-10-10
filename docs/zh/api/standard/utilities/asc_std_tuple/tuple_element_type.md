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

`tuple_element<Index, T>::type` 标识受支持类 tuple 对象中指定索引处的元素类型。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 声明

### 原型 1

```cpp
using asc::std::tuple_element::type = T
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型 2

```cpp
using asc::std::tuple_element::type = const tuple_element_t<Index, T>
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型 3

```cpp
using asc::std::tuple_element::type = const volatile tuple_element_t<Index, T>
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型 4

```cpp
using asc::std::tuple_element::type = volatile tuple_element_t<Index, T>
```

此原型对应头文件：`<asc/std/tuple>`、`<asc/std/utility>`。

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配
- pair 操作不抛出异常
- 关系运算符均为显式提供

## 调用示例

以下片段选用具体模板实参读取嵌套类型。

```cpp
#include <asc/std/tuple>

void use_type()
{
    using selected = typename asc::std::tuple_element<0, asc::std::tuple<int>>::type;
    (void)sizeof(selected);
}
```
