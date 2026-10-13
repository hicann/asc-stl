# asc::std::uninitialized_fill

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

头文件路径为：`<asc/std/memory>`。

`asc::std::uninitialized_fill`在未构造的存储范围中按给定值构造对象。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
template<class ForwardIterator, class T> void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 指向目标未构造存储的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 待在存储中构造的对象类型，即value的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 目标存储范围的起始迭代器或指针；所指存储尚未构造对象。 |
| `last` | 输入 | 目标存储范围的结束位置，不包含该位置；范围内存储尚未构造对象。 |
| `value` | 输入 | 待复制构造到范围内每个位置的值。 |

## 返回值说明

无返回值。

## 约束说明

- 存储由调用方提供并满足对齐要求。
- 当回滚会引发异常时，Device侧相关操作必须不抛出异常。

## 调用示例

以下Host片段使用有效对象或对齐存储；构造后的对象在示例末尾销毁。

```cpp
#include <asc/std/memory>

void example()
{
    alignas(int) unsigned char storage[sizeof(int) * 4];
    int* output = reinterpret_cast<int*>(storage);
    asc::std::uninitialized_fill(output, output + 4, 7);
    asc::std::destroy_n(output, 4);
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
