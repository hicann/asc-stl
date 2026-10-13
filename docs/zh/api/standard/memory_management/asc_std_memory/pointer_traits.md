# asc::std::pointer_traits

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

头文件路径为：`<asc/std/memory>`。

`asc::std::pointer_traits`统一访问指针类对象的元素类型与地址操作。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

### 原型1

```cpp
namespace asc::std {
template<class Ptr, class> struct pointer_traits;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> struct pointer_traits;
} // namespace asc::std
```

## 约束说明

- 支持原始指针和用户自定义fancy pointer，接口自身不分配内存。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/memory>

bool example()
{
    int value = 7;
    int* pointer = asc::std::pointer_traits<int*>::pointer_to(value);
    return pointer == &value && *pointer == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
