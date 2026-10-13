# asc::std::to_integer

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

头文件路径为：`<asc/std/cstddef>`。

`asc::std::to_integer`把std::byte转换为指定整数类型。

标准语义参考：[cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef)。

## 函数原型

```cpp
namespace asc::std {
template<class Integer> constexpr Integer to_integer(byte value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Integer` | 转换目标的整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待转换的byte值；返回其底层unsigned char值转换到Integer的结果。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `Integer` | 返回当前`byte`所表示的指定整数类型数值。 |

## 约束说明

- 提供标准声明。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/cstddef>

decltype(auto) example()
{
    return asc::std::to_integer<unsigned int>(asc::std::byte{7});
}
```

## 关联API

- [本头文件的接口列表](asc_std_cstddef.md)
