# asc::std::erase_if

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::erase_if`按谓词从固定容量容器中移除元素并返回删除数量。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

```cpp
namespace asc::std {
template<class T, asc::std::size_t Capacity, class Predicate> typename inplace_vector<T, Capacity>::size_type erase_if(inplace_vector<T, Capacity>& values, Predicate predicate);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | inplace_vector的元素类型。 |
| `Capacity` | inplace_vector的固定容量，编译期常量。 |
| `Predicate` | 一元谓词类型；以元素为实参调用，返回值须可转换为bool。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 被清理的固定容量容器；使谓词为真的元素全部被移除，其余元素前移并保持相对次序。 |
| `predicate` | 输入 | 一元谓词；对每个元素调用一次，返回true的元素被移除。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `typename inplace_vector<T, Capacity>::size_type` | 返回删除数量。 |

## 约束说明

- 元素保存在固定容量的对象内存中，不进行动态分配。
- `try_`插入在容量不足时返回空结果；`unchecked_`插入要求调用前仍有容量。
- Host提供完整接口，设备端仅提供不抛出异常的接口。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 8> values;
    const auto first = values.try_push_back(2);
    const auto second = values.try_push_back(3);
    if (!first || !second) {
        return false;
    }

    const auto erased = asc::std::erase_if(values, [](int value) { return value % 2 == 0; });
    return erased == 1 && values.size() == 1 && values[0] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_inplace_vector.md)
