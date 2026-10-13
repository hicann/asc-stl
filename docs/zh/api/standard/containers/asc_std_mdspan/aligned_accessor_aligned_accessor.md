# asc::std::aligned_accessor::aligned_accessor

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

头文件路径为：`<asc/std/mdspan>`。

`asc::std::aligned_accessor::aligned_accessor`按本页所列构造形态初始化`aligned_accessor`对象。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型1

```cpp
constexpr aligned_accessor() noexcept;
```

### 原型2

```cpp
template<class OtherElement, size_t OtherByteAlignment> constexpr aligned_accessor(aligned_accessor<OtherElement, OtherByteAlignment> other) noexcept;
```

### 原型3

```cpp
template<class OtherElement> constexpr aligned_accessor(default_accessor<OtherElement> accessor) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherElement` | 源对齐访问器的元素类型，须与本访问器的元素类型兼容。 |
| `OtherByteAlignment` | 源对齐访问器的字节对齐值，编译期常量；须不小于本访问器的ByteAlignment。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待转换的另一对齐访问器；其字节对齐不低于本访问器的byte_alignment，本对象取得与其等价的访问策略。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherElement` | 源default_accessor的元素类型，须与本访问器的元素类型兼容。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `accessor` | 输入 | 被转换的default_accessor对象；本对象改为按该元素类型的默认对齐执行访问。 |

## 返回值说明

无返回值。

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain pointer域。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

bool example()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    asc::std::aligned_accessor<int, 16> accessor;
    static_assert(decltype(accessor)::byte_alignment == 16);
    return accessor.access(values, 1) == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
