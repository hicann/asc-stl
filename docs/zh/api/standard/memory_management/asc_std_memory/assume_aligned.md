# asc::std::assume_aligned

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

`asc::std::assume_aligned`在调用方保证对齐前置条件时向编译器表达指针对齐信息。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
template<size_t Align, class T> [[nodiscard]] constexpr T* assume_aligned(T* pointer) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Align` | 所要求的字节对齐，须满足下述编译期有效性条件。 |
| `T` | 被构造、销毁或管理的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 须已满足模板实参指定字节对齐的地址；函数不调整地址，不满足对齐要求时行为未定义。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T *` | 返回与输入地址相同的指针，并向编译器声明其满足指定对齐要求。 |

## 约束说明

- 本重载只接受原始对象指针`T*`，不接受fancy pointer对象。
- `Align`须为2的非负整数次幂；当元素类型非void时还须不小于`alignof(T)`。
- 输入地址必须已满足指定字节对齐；本函数表达对齐假设，不检查、修复或分配地址。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>

bool example()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    int* pointer = asc::std::assume_aligned<16>(values);
    return pointer == values && pointer[2] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
