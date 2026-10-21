# asc::std::launder

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

头文件路径为：`<asc/std/new>`。单独包含`<asc/std/memory>`不提供此函数。

`asc::std::launder`在对象生命周期转换后取得可用于访问新对象的指针。

标准语义参考：[cppreference `launder`](https://en.cppreference.com/w/cpp/utility/launder)。

## 函数原型

```cpp
namespace asc::std {
template<class T> constexpr T* launder(T* pointer) noexcept;
}
```

从C++17起提供此单一模板，可用于Host、AI Core SIMD编程和AI Core SIMT编程的相应指针域。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 当前存活对象的类型，须满足对象类型及可达存储要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向相应类型存活对象所在地址，须满足对象类型及存储可达性条件；不创建对象或延长生命周期。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T*` | 指向相同存储地址中当前存活对象的指针。 |

## 约束说明

- 调用前须在给定地址已存在类型相容的存活对象，并满足存储可达性条件；本函数不分配存储、不开始对象生命周期。
- 返回指针的使用期受当前对象和底层存储的生命周期限制；销毁对象后不得再用它访问。
- 头文件及指针的执行位置和地址空间须匹配；此调用不进行GM/UB地址空间转换。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>
#include <asc/std/new>

struct example_value {
    int value;
    explicit example_value(int initial) : value(initial) {}
};

bool example()
{
    alignas(example_value) unsigned char storage[sizeof(example_value)];
    auto* pointer = reinterpret_cast<example_value*>(storage);
    asc::std::construct_at(pointer, 3);
    asc::std::destroy_at(pointer);
    asc::std::construct_at(pointer, 7);
    const bool valid = asc::std::launder(pointer)->value == 7;
    asc::std::destroy_at(pointer);
    return valid;
}
```

## 关联API

- [本接口所属的new头文件列表](../../language_support/asc_std_new/asc_std_new.md)
- [对象构造与销毁接口](asc_std_memory.md)
