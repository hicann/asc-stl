# asc::std::piecewise_construct_t::~piecewise_construct_t

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

头文件路径为：`<asc/std/utility>`。

`asc::std::piecewise_construct_t::~piecewise_construct_t`销毁`piecewise_construct_t`对象并结束其生命周期。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
constexpr ~piecewise_construct_t() noexcept;
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下片段假定object指向已构造对象；显式析构后不得再次访问对象，存储释放由调用方负责。

```cpp
#include <asc/std/new>
#include <asc/std/utility>

using example_object = asc::std::piecewise_construct_t;
void example(example_object* object)
{
    // object 指向已构造对象；析构后不得再访问该对象。
    object->~example_object();
}

bool verify_example()
{
    alignas(example_object) unsigned char storage[sizeof(example_object)];
    auto* first = ::new (static_cast<void*>(storage)) example_object();
    example(first);
    auto* second = ::new (static_cast<void*>(storage)) example_object();
    const bool reused = static_cast<void*>(second) == static_cast<void*>(storage);
    example(second);
    return reused;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
