# asc::std::ref

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

`asc::std::ref`创建不拥有对象的可复制引用包装器。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr reference_wrapper<T> ref(T& value) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr reference_wrapper<T> ref(reference_wrapper<T> value) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被包装对象的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 被包装的左值对象；返回的reference_wrapper<T> 保存指向它的引用，对象生命周期须覆盖包装器使用期。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被包装对象的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 已有的reference_wrapper对象；返回指向同一目标的reference_wrapper<T>。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `reference_wrapper<T>` | 返回保存调用目标及所选参数的可调用对象或引用包装器。 |
| 原型2 | `reference_wrapper<T>` | 返回保存调用目标及所选参数的可调用对象或引用包装器。 |

## 约束说明

- 支持标准可调用对象和成员指针形式。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    int value = 3;
    return asc::std::ref(value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
