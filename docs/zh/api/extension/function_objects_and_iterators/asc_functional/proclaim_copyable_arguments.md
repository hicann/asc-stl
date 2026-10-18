# asc::proclaim_copyable_arguments

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

头文件路径为：`<asc/functional>`。

`asc::proclaim_copyable_arguments`包装函数对象并显式声明其参数可安全按值复制。

## 函数原型

以下为声明摘要，具体返回类型由实现定义，是可保存并调用的包装对象。

```cpp
namespace asc {
template<class Function> constexpr auto proclaim_copyable_arguments(Function&& function) noexcept;
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
| `function` | 输入（可能被移动） | 被包装的函数对象；包装器保存移除引用后的对象类型的值副本，函数对象自身借用的资源仍须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| 实现定义的可调用包装器类型 | 保存函数对象并转发调用并保留底层调用的结果类型。 |

## 约束说明

- 函数对象须可复制到包装器中，并且可通过常量函数对象按给定参数调用。
- 函数对象的复制、移动及包装构造不得抛出异常；返回包装器并不延长其捕获的外部引用的生命周期。
- 调用方须自行保证参数的复制符合使用场景；包装动作不进行运行时检查，也不修改参数对象。

## 调用示例

以下Host示例构造包装器并检查返回结果。

```cpp
#include <asc/functional>

bool example()
{
    const auto wrapped = asc::proclaim_copyable_arguments([](int value) { return value + 1; });
    return wrapped(3) == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_functional.md)
