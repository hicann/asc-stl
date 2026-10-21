# asc::std::unexpect_t

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

头文件路径为：`<asc/std/expected>`。

`asc::std::unexpect_t`标记以错误值原位构造expected的形式。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 声明

```cpp
namespace asc::std {
struct unexpect_t;
} // namespace asc::std
```

## 约束说明

- 该标记选择expected的错误原位构造，不包含值或错误存储，也没有Value/Error模板参数。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::unexpect_t tag{};
    asc::std::expected<int, int> result(tag, 7);
    return !result.has_value() && result.error() == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_expected.md)
