# asc::make_zip_function

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

`asc::make_zip_function`创建把asc::zip_iterator解引用产生的引用代理展开后调用目标函数的适配器。

## 函数原型

```cpp
namespace asc {
template <class Function>
constexpr asc::zip_function<Function> make_zip_function(Function function);
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Function` | 对输入值执行本页操作的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入 | 被适配的目标函数对象：收到asc::zip_iterator的引用代理时展开其全部元素并按function(元素…)调用。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::zip_function<Function>` | 返回把asc::zip_iterator解引用产生的引用代理展开后调用目标函数的适配器。 |

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下Host示例使用具体输入，在对象存活期内检查结果。

```cpp
#include <asc/iterator>
bool example()
{
    int left = 2;
    int right = 3;
    const auto callable = asc::make_zip_function([](int a, int b) { return a + b; });
    const auto iterator = asc::make_zip_iterator(&left, &right);
    return callable(*iterator) == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
