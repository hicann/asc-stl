# asc::std::scoped_allocator_adaptor::scoped_allocator_adaptor

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

头文件路径为：`<asc/std/scoped_allocator>`。

`asc::std::scoped_allocator_adaptor::scoped_allocator_adaptor` 按本页所列构造形态初始化 `scoped_allocator_adaptor` 对象。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 函数原型

### 原型 1

```cpp
constexpr scoped_allocator_adaptor();
```

### 原型 2

```cpp
constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...>& outer_allocator) noexcept;
```

### 原型 3

```cpp
constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterAllocator>& outer_allocator) noexcept;
```

### 原型 4

```cpp
constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...>&& outer_allocator) noexcept;
```

### 原型 5

```cpp
constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterAllocator>&& outer_allocator) noexcept;
```

### 原型 6

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(OuterA2&& outer_allocator) noexcept;
```

### 原型 7

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(OuterA2&& outer_allocator, const FirstInner& inner_allocator, const RestInner&... rest) noexcept;
```

### 原型 8

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2, FirstInner, RestInner...>& outer_allocator) noexcept;
```

### 原型 9

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2>& outer_allocator) noexcept;
```

### 原型 10

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterA2, FirstInner, RestInner...>&& outer_allocator) noexcept;
```

### 原型 11

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterA2>&& outer_allocator) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型 5 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `inner_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `rest` | 输入 | 提供“按本页所列构造形态初始化 `scoped_allocator_adaptor` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 10 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型 11 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

## 约束说明

- 遵循 scoped_allocator_adaptor 的标准分配器传播、构造、销毁、比较和交换约束
- 参与操作的分配器必须在当前可用位置有效，Device 侧操作不得抛出异常

## 调用示例

以下 Host 片段使用显式提供的分配器并完整释放存储；设备端须改用目标位置可调用的分配器。

```cpp
#include <asc/std/scoped_allocator>
#include <functional>
#include <memory>
#include <string>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

void example()
{
    asc::std::scoped_allocator_adaptor<example_allocator<int>> allocator{};
    (void)allocator.outer_allocator();
}
```
