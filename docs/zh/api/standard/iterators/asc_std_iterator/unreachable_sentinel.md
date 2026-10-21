# asc::std::unreachable_sentinel

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::unreachable_sentinel`提供永远不与有效迭代器相等的哨兵对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

```cpp
namespace asc::std {
inline constexpr const unreachable_sentinel_t unreachable_sentinel;
} // namespace asc::std
```

## 约束说明

- 该哨兵与适用迭代器比较时始终表示尚未到达结束位置。
- 调用方须通过其他条件终止遍历，并保证每次解引用和递增都有效；该哨兵不检查实际边界。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    int* iterator = values;
    return iterator != asc::std::unreachable_sentinel &&
           values + 2 != asc::std::unreachable_sentinel;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
