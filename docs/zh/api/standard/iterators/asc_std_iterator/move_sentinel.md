# asc::std::move_sentinel

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

`asc::std::move_sentinel`把底层哨兵适配为移动迭代器的结束位置。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

```cpp
namespace asc::std {
template<class Sent> class move_sentinel;
} // namespace asc::std
```

## 约束说明

- 哨兵类型须支持对应构造、转换或赋值操作，并可与配套底层迭代器比较。
- 哨兵不拥有底层范围，也不能解引用；其结束标记须在比较期间有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::move_sentinel<int*> sentinel(values + 2);
    asc::std::move_iterator<int*> iterator(values);
    return sentinel.base() == values + 2 && iterator != sentinel;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
