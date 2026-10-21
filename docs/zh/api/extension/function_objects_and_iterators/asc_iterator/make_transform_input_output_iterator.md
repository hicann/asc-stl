# asc::make_transform_input_output_iterator

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

`asc::make_transform_input_output_iterator`创建同时具有输入和输出变换的迭代器。

## 函数原型

```cpp
namespace asc {
template <class Iterator, class InputFunction, class OutputFunction>
constexpr asc::transform_input_output_iterator<InputFunction, OutputFunction, Iterator>
make_transform_input_output_iterator(Iterator iterator, InputFunction input_function, OutputFunction output_function);
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Iterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `InputFunction` | 读取变换的可调用对象类型：读取时按input_function(*底层迭代器)变换。 |
| `OutputFunction` | 写入变换的可调用对象类型：写入时先经output_function变换再存入底层迭代器。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iterator` | 输入 | 被包装的底层迭代器：读写实际作用于该迭代器所指位置。 |
| `input_function` | 输入 | 读取变换对象：解引用读取结果为input_function(*底层迭代器)。 |
| `output_function` | 输入 | 写入变换对象：赋给本迭代器的值先经output_function变换再写入底层位置。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::transform_input_output_iterator<InputFunction, OutputFunction, Iterator>` | 返回保存调用方参数的迭代器适配器；底层范围须在使用期间保持有效。 |

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下Host示例使用具体输入，在对象存活期内检查结果。

```cpp
#include <asc/iterator>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    int indices[4] = {3, 2, 1, 0};
    auto iterator = asc::make_transform_input_output_iterator(
        values, [](int value) { return value; }, [](int value) { return value; });
    *iterator = 9;
    return (*iterator).read() == 9 && values[0] == 9;
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
