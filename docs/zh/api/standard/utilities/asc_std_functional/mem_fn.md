# asc::std::mem_fn

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

头文件路径为：`<asc/std/functional>`。

`asc::std::mem_fn` 把成员指针包装为可调用对象。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

```cpp
template<class Rp, class T> constexpr Memfn<Rp T::*> asc::std::mem_fn(Rp T::* member) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rp` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `member` | 输入 | 提供“把成员指针包装为可调用对象”所需的数据地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `Memfn<Rp T::*>` | 返回可调用的成员指针包装器。 |

## 约束说明

- 支持标准可调用对象和成员指针形式
- invoke_r 为 C++23 回移提供的接口

## 调用示例

以下 Host 片段使用具体对象展示接口调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    struct widget { int read() const { return 3; } };
    widget value;
    auto call = asc::std::mem_fn(&widget::read);
    return call(value);
}
```
