# asc::std::is_sufficiently_aligned

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

`asc::std::is_sufficiently_aligned`判断指针是否满足指定编译期对齐要求。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
template<size_t ByteAlignment, class ElementType> [[nodiscard]] bool is_sufficiently_aligned(ElementType* pointer) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ByteAlignment` | 所要求的字节对齐，须满足下述编译期有效性条件。 |
| `ElementType` | 视图访问的元素类型，决定读取、变换和返回值的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 仅检查地址是否满足ByteAlignment指定的字节对齐；不读取指向的对象，也不调整该地址。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 本重载只接受原始对象指针`ElementType*`，不接受fancy pointer对象。
- `ByteAlignment`须为2的非负整数次幂；当元素类型非void时还须不小于`alignof(ElementType)`。
- 只检查地址数值是否满足指定字节对齐；不读取对象，也不保证该地址有足够存储或存在存活对象。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>

bool example()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    return asc::std::is_sufficiently_aligned<16>(values)
        && !asc::std::is_sufficiently_aligned<16>(values + 1);
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
