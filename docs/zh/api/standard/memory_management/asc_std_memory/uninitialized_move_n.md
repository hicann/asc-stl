# asc::std::uninitialized_move_n

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

`asc::std::uninitialized_move_n`从`first`起移动最多`count`个对象，在`result`起始的未初始化存储逐个构造对象，并返回输入和输出各自的末尾。非正计数不构造对象。

## 函数原型

```cpp
namespace asc::std {
template<class InputIterator, class Size, class ForwardIterator> pair<InputIterator, ForwardIterator> uninitialized_move_n(InputIterator first, Size count, ForwardIterator result);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `count` | 输入 | 参与操作的元素数量。 |
| `result` | 输出 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `pair<InputIterator, ForwardIterator>` | `first`成员是完成移动后的输入迭代器，`second`成员是已构造输出范围的尾后迭代器；两者分别属于输入与输出范围。 |

## 约束说明

- 存储由调用方提供并满足对齐要求。
- 当回滚会引发异常时，Device侧相关操作必须不抛出异常。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>

bool example()
{
    alignas(int) unsigned char storage[sizeof(int) * 4];
    int* output = reinterpret_cast<int*>(storage);
    int input[4] = {1, 2, 3, 4};
    const auto ends = asc::std::uninitialized_move_n(input, 4, output);
    const bool valid = ends.first == input + 4 && ends.second == output + 4
        && output[0] == 1 && output[3] == 4;
    asc::std::destroy_n(output, 4);
    return valid;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
