# asc::std::tuple_element

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

头文件路径为：`<asc/std/array>`、`<asc/std/tuple>`、`<asc/std/utility>`。

`asc::std::tuple_element<Index, T>` 取得受支持类 tuple 对象中指定索引处的元素类型；索引必须小于元素数量。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 声明

### 原型 1

```cpp
template<class T, class U> struct asc::std::tuple_element
```

此原型对应头文件：`<asc/std/array>`。

### 原型 2

```cpp
template<size_t Index, class ...Types> struct asc::std::tuple_element
```

此原型对应头文件：`<asc/std/array>`。

### 原型 3

```cpp
template<size_t Index, class T, T ...Indices> struct asc::std::tuple_element
```

此原型对应头文件：`<asc/std/array>`、`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型 4

```cpp
template<size_t Index, class T, class U> struct asc::std::tuple_element
```

此原型对应头文件：`<asc/std/array>`。

### 原型 5

```cpp
template<size_t Index, class T, size_t N> struct asc::std::tuple_element
```

此原型对应头文件：`<asc/std/array>`。

### 原型 6

```cpp
template<size_t Index, class T> class asc::std::tuple_element
```

此原型对应头文件：`<asc/std/array>`、`<asc/std/tuple>`、`<asc/std/utility>`。

### 原型 7

```cpp
template<size_t Index, class T> struct asc::std::tuple_element
```

此原型对应头文件：`<asc/std/array>`、`<asc/std/tuple>`、`<asc/std/utility>`。

## 约束说明

- 支持包括零在内的所有 N
- 成员函数和自由函数均不抛出异常
- 构造、赋值、交换及相关自由函数均不进行动态内存分配
- pair 操作不抛出异常
- 关系运算符均为显式提供

## 调用示例

以下片段用具体模板实参实例化类型；实际对象仍须满足本页构造与生命周期约束。

```cpp
#include <asc/std/array>

void use_type()
{
    using selected = asc::std::tuple_element<0, asc::std::array<int, 2>>;
    (void)sizeof(selected);
}
```
