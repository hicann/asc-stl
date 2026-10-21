# asc::std::hash

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

头文件路径为：`<asc/std/optional>`。

`asc::std::hash<asc::std::optional<T>>`由`<asc/std/optional>`提供，optional的哈希特化：空值哈希0，有值时hash<remove_const_t<T>>{}(*value)；可作为无序容器所选择的哈希器，前提是所含值的哈希与相等关系一致。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

```cpp
template <class T> struct hash<optional<T>> { size_t operator()(const optional<T>& value) const; };
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | optional所含值的类型；其hash<remove_const_t<T>>须可调用并与相等关系一致。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被计算哈希的optional对象；不含值时哈希值为0，含值时为hash<remove_const_t<T>>{}(*value)。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `size_t` | 空optional返回0；含值时返回所存值的hash结果。 |

## 约束说明

- 内层`hash<remove_const_t<T>>`须可调用，且对相等的T值返回相同结果；可调用性只是必要条件。
- 空optional的哈希值为0；含值时返回hash<remove_const_t<T>>{}(*value)。
- `operator()`接受const optional<T>& 并返回size_t，可供选择本哈希器且采用相容键相等关系的无序容器使用。
- 若元素类型落入[对象字节回退](../asc_std_bitset/hash.md)，同样要求确定字节及等价对象表示一致；含填充、被相等判断忽略的字段或非平凡状态的用户类型须提供合适的自定义哈希。包装为optional不会修复内层哈希与相等关系的失配。

## 调用示例

以下Host示例检查空值和有值时的哈希规则。

```cpp
#include <asc/std/optional>
#include <asc/std/functional>

bool example()
{
    asc::std::optional<int> empty;
    asc::std::optional<int> value(7);
    asc::std::hash<asc::std::optional<int>> hasher;
    return hasher(empty) == 0 && hasher(value) == asc::std::hash<int>{}(7);
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
