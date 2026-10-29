# asc::std::construct_at

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

`asc::std::construct_at`在调用方提供且满足`T`对齐要求的存储中，以转发的实参构造`T`对象。构造成功后可通过返回指针访问该对象；对象生命周期结束时可调用`destroy_at`。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
template<class T, class ...Args> constexpr T* construct_at(T* location, Args&&... args);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 要在目标存储中构造的对象类型。 |
| `Args` | 传给`T`构造函数的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `location` | 输出 | 满足目标对象大小与对齐的未初始化存储地址；调用在该处开始对象生命周期，构造实参决定其初值。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T *` | 返回指向新构造对象的指针，其地址与`location`相同。 |

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

- [asc::std::destroy_at](destroy_at.md)
