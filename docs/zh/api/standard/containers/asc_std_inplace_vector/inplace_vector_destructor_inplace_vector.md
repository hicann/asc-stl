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

`asc::std::inplace_vector::~inplace_vector` 销毁 `inplace_vector` 对象并结束其生命周期。

该接口的可用位置为 Host（完整接口）、Device（非抛出子集）。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

```cpp
~inplace_vector();
```

## 参数说明

无参数。

## 约束说明

- 最终C++26标准inplace_vector/erase/erase_if合同：Host交付除P4022R0已删除try_append_range外的完整构造、赋值、迭代、访问、修改、try/unchecked、比较、swap、容量、零容量empty/trivial与constexpr/约束合同
- Device交付固定容量内联存储的非抛子合同，包括观察/迭代/operator[]/front/back、不抛出异常拷移赋值析构、try/unchecked后插、pop_back/clear、不抛出异常 erase/erase_if/swap、相等与不抛出异常三路比较、完整零容量核心
- Host 提供完整接口，设备端仅提供不抛出异常的接口

## 调用示例

以下片段假定 object 指向已构造对象；显式析构后不得再次访问对象，存储释放由调用方负责。

```cpp
#include <asc/std/inplace_vector>

using example_object = asc::std::inplace_vector<int, 8>;
void example(example_object* object)
{
    // object 指向已构造对象；析构后不得再访问该对象。
    object->~example_object();
}
```
