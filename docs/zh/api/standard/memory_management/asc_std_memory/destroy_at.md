# asc::std::destroy_at

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

`asc::std::destroy_at`调用指定对象的析构函数，结束其生命周期，但不释放调用方提供的存储。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
template<class T> constexpr void destroy_at(T* location);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 要结束生命周期的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `location` | 输入/输出 | 指向生命周期尚未结束的对象；调用结束其生命周期，不释放底层存储。 |

## 返回值说明

无返回值。

## 约束说明

- 存储由调用方提供并满足对齐要求。
- 当回滚会引发异常时，Device侧相关操作必须不抛出异常。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/memory>

struct example_value {
    static inline int alive = 0;
    int value;
    example_value() : value(23) { ++alive; }
    ~example_value() { --alive; }
};

bool verify_example()
{
    alignas(example_value) unsigned char storage[sizeof(example_value) * 1];
    auto* values = reinterpret_cast<example_value*>(storage);
    for (int index = 0; index < 1; ++index) { asc::std::construct_at(values + index); }
    const bool correct = example_value::alive == 1 && values[0].value == 23;
    for (int index = 0; index < 1; ++index) { asc::std::destroy_at(values + index); }
    return correct && example_value::alive == 0;
}
```

## 关联API

- [asc::std::construct_at](construct_at.md)
