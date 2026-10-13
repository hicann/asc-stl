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

`asc::make_zip_function`创建把tuple参数展开后调用目标函数的适配器。

## 函数原型

```cpp
namespace asc {
template<class Function> constexpr asc::zip_function<Function> make_zip_function(Function function);
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Function` | 对输入值执行本页操作的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入 | 被适配的目标函数对象：收到tuple型引用时展开其全部元素并按function(元素…)调用。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::zip_function<Function>` | 返回把tuple参数展开后调用目标函数的适配器。 |

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下片段使用具体数组和可调用对象构造迭代器。实际使用时底层范围须保持有效。

```cpp
#include <asc/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    int indices[4] = {3, 2, 1, 0};
    return asc::make_zip_function([](int left, int right) { return left + right; });
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
