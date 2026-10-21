# asc::std::inplace_vector::~inplace_vector

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::inplace_vector::~inplace_vector`销毁`inplace_vector`对象并结束其生命周期。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

```cpp
~inplace_vector();
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- 销毁当前已构造的元素；对象析构后，其全部引用、指针及迭代器不再可用。
- 元素的对应构造、赋值和析构须满足非抛出使用域；constexpr声明不保证任意T和语言模式都能常量求值。

## 调用示例

以下片段假定object指向已构造对象；显式析构后不得再次访问对象，存储释放由调用方负责。

```cpp
#include <asc/std/inplace_vector>

using example_object = asc::std::inplace_vector<int, 8>;
void example(example_object* object)
{
    // object 指向已构造对象；析构后不得再访问该对象。
    object->~example_object();
}
```

## 关联API

- [本头文件的接口列表](asc_std_inplace_vector.md)
