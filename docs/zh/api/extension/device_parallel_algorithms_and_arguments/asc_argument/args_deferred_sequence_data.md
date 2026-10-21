# asc::args::deferred_sequence::data

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

头文件路径为：`<asc/argument>`。

`asc::args::deferred_sequence::data`返回所引用延迟参数序列的首元素指针。

## 函数原型

所属类型：[`asc::args::deferred_sequence`](args_deferred_sequence.md)。

```cpp
// asc::args::deferred_sequence 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr const T* data() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `const T*` | 返回所引用延迟参数序列的首元素指针。 |

## 约束说明

- Bounds按值保存，可为no_bounds、static_bounds或runtime_bounds等可复制的边界值；包装不会自动证明或校验数据落在边界内。
- 延迟数据仅借用指针，须在实际读取时可访问且存储覆盖全部使用期；sequence的size以元素计并不得超过有效范围。

- 使用C++17，可在Host、AI Core SIMD编程 和AI Core SIMT编程中使用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/argument>

bool example()
{
    int values[] = {2, 4};
    asc::args::deferred_sequence<int> argument(values, 2);
    return argument.size() == 2 && argument.data() == values && argument.data()[1] == 4;
}
```

## 关联API

- [`asc::args::deferred_sequence`](args_deferred_sequence.md)
- [本头文件的接口列表](asc_argument.md)
