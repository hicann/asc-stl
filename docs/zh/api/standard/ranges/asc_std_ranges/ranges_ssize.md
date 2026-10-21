# asc::std::ranges::ssize

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::ssize(range)`读取范围大小并转换为有符号整数；左值和满足size调用条件的右值均可传入。

## 声明

该公开名称为常量可调用对象，不是自由函数；其实现类不属于公开契约。以下仅查询对象类型，object_type是示例名称。调用形式见参数说明及示例。

```cpp
using object_type = decltype(asc::std::ranges::ssize);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |

## 返回值说明

令`SignedSize = make_signed_t<decltype(ranges::size(range))>`。当`sizeof(ptrdiff_t) > sizeof(SignedSize)`时返回`ptrdiff_t`，否则返回`SignedSize`。结果只保存数量，不借用范围。

## 约束说明

- 对转发传入的范围对象，其命名左值调用`ranges::size`须有效；既可接受左值，也可接受满足条件的右值。
- 有符号结果须能表示数量；查询不返回元素引用，范围对象无需覆盖整数结果的后续使用期。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>
#include <asc/std/cstddef>

struct example_range {
    unsigned char size() const noexcept { return 3; }
};

bool example()
{
    const auto count = asc::std::ranges::ssize(example_range{});
    static_assert(asc::std::is_same_v<asc::std::remove_cv_t<decltype(count)>, asc::std::ptrdiff_t>);
    return count == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
