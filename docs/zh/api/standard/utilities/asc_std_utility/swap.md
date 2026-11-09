# asc::std::swap

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

头文件为 `<asc/std/utility>`。交换两个对象的值，或逐元素交换两个同长数组。以下原型以等价的公开类型条件表达约束，省略实现使用的内部返回别名。

## 函数原型

```cpp
template <class T>
constexpr void swap(T& left, asc::std::type_identity_t<T>& right)
    noexcept(asc::std::is_nothrow_move_constructible_v<T> && asc::std::is_nothrow_move_assignable_v<T>);
```

```cpp
template <class T, asc::std::size_t N>
constexpr void swap(T (&left)[N], T (&right)[N])
    noexcept(asc::std::is_nothrow_swappable_v<T>);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `T` | 输入 | 两个对象或数组元素的类型。 |
| `N` | 输入 | 两个数组的相同长度。 |
| `left` | 输入/输出 | 第一个有效对象或数组。 |
| `right` | 输入/输出 | 第二个有效对象或数组。 |

## 返回值说明

无返回值。

## 约束说明

普通对象重载要求类型可移动构造并可移动赋值；数组重载要求元素可交换，且不覆盖可适用的数组参数相关查找重载。Device 支持满足类型约束的原生 GM/UB 算术对象引用，以寄存器临时值完成交换；调用方须保证地址有效并提供必要的线程间同步。Host 保留按对象类型构造临时值的行为。

## 调用示例

```cpp
#include <asc/std/utility>

bool example()
{
    int left = 2, right = 7;
    asc::std::swap(left, right);
    int first[] = {1, 2}, second[] = {3, 4};
    asc::std::swap(first, second);
    return left == 7 && right == 2 && first[0] == 3 && first[1] == 4 && second[0] == 1;
}
```

## 关联API

- [<asc/std/utility>](asc_std_utility.md)
- [swap(unique_lock/shared_lock)](../../concurrency/asc_std_mutex/swap.md)
