# asc::std::to_underlying

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

`asc::std::to_underlying`返回枚举值对应的底层整数值。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr underlying_type_t<T> to_underlying(T value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 枚举类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待转换的枚举值；返回其转换到底层整数类型后的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `underlying_type_t<T>` | 返回枚举值对应的底层整数值。 |

## 约束说明

- to_underlying仅接受枚举类型。
- unreachable保留标准语义前置条件，但不添加当前工具链不支持的noreturn属性。

## 调用示例

以下片段用具体数值展示本页调用。

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    enum class code { value = 3 };
    return asc::std::to_underlying(code::value);
}

bool verify_example()
{
    return example() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
