# asc::std::move_iterator::iterator_concept

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

`asc::std::move_iterator::iterator_concept`标识迭代器满足的概念类别标签。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

所属类型：[`asc::std::move_iterator`](move_iterator.md)。

```cpp
// move_iterator 类内声明节选；类模板参数和其余成员由所属类提供。
using iterator_concept = conditional_t<random_access_iterator<Iter>, random_access_iterator_tag,
    conditional_t<bidirectional_iterator<Iter>, bidirectional_iterator_tag,
    conditional_t<forward_iterator<Iter>, forward_iterator_tag, input_iterator_tag>>>;
```

以上使用公开类型表达与实际选择逻辑等价的类型；连续迭代器在此映射为随机访问标签。

## 约束说明

- 底层迭代器须支持本页操作；自减要求双向遍历，位移和下标要求相应随机访问操作。
- 适配器不拥有底层元素；解引用通过`asc::std::iter_move`访问元素，移动后的值遵守元素类型的约定。
- 解引用、箭头及下标访问须指向有效元素；返回引用或指针的寿命受底层对象约束。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    using selected = typename asc::std::move_iterator<int*>::iterator_concept;
    static_assert(asc::std::is_same_v<selected, asc::std::random_access_iterator_tag>);
    return true;
}
```

## 关联API

- [`asc::std::move_iterator`](move_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
