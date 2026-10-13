# asc::discard_iterator

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

头文件路径为：`<asc/iterator>`。

`asc::discard_iterator`接收写入但丢弃赋值结果的输出迭代器。

## 声明

```cpp
namespace asc {
class discard_iterator;
} // namespace asc
```

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/iterator>
#include <asc/std/algorithm>
#include <asc/std/type_traits>

bool example()
{
    int values[] = {2, 4};
    asc::discard_iterator output;
    auto result = asc::std::copy(values, values + 2, output);
    static_assert(asc::std::is_same_v<decltype(result), asc::discard_iterator>);
    // 丢弃输出不会修改输入。
    return values[0] == 2 && values[1] == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
