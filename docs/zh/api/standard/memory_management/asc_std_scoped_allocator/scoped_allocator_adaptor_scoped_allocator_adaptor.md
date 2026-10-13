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

`asc::std::scoped_allocator_adaptor::scoped_allocator_adaptor`按本页所列构造形态初始化`scoped_allocator_adaptor`对象。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 函数原型

### 原型1

```cpp
constexpr scoped_allocator_adaptor();
```

### 原型2

```cpp
constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...>& outer_allocator) noexcept;
```

### 原型3

```cpp
constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterAllocator>& outer_allocator) noexcept;
```

### 原型4

```cpp
constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...>&& outer_allocator) noexcept;
```

### 原型5

```cpp
constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterAllocator>&& outer_allocator) noexcept;
```

### 原型6

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(OuterA2&& outer_allocator) noexcept;
```

### 原型7

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(OuterA2&& outer_allocator, const FirstInner& inner_allocator, const RestInner&... rest) noexcept;
```

### 原型8

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2, FirstInner, RestInner...>& outer_allocator) noexcept;
```

### 原型9

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2>& outer_allocator) noexcept;
```

### 原型10

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterA2, FirstInner, RestInner...>&& outer_allocator) noexcept;
```

### 原型11

```cpp
template<class OuterA2> constexpr scoped_allocator_adaptor(scoped_allocator_adaptor<OuterA2>&& outer_allocator) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型5的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 来源scoped_allocator_adaptor的最外层分配器类型；须支持目标转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 来源scoped_allocator_adaptor的最外层分配器类型；须支持目标转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `inner_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `rest` | 输入 | 提供“按本页所列构造形态初始化`scoped_allocator_adaptor`对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型8的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 来源scoped_allocator_adaptor的最外层分配器类型；须支持目标转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型9的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 来源scoped_allocator_adaptor的最外层分配器类型；须支持目标转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型10的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 来源scoped_allocator_adaptor的最外层分配器类型；须支持目标转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

### 原型11的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OuterA2` | 来源scoped_allocator_adaptor的最外层分配器类型；须支持目标转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer_allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |

## 返回值说明

无返回值。

## 约束说明

- 遵循scoped_allocator_adaptor的标准分配器传播、构造、销毁、比较和交换约束。
- 参与操作的分配器必须在当前可用位置有效，Device侧操作不得抛出异常。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <memory>
#include <asc/std/scoped_allocator>

template<class T>
struct ExampleAllocator : ::std::allocator<T> {
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template<class U> struct rebind { using other = ExampleAllocator<U>; };
    ExampleAllocator() = default;
    template<class U> ExampleAllocator(const ExampleAllocator<U>&) noexcept {}
};

bool example()
{
    asc::std::scoped_allocator_adaptor<ExampleAllocator<int>> allocator;
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 7);
    const bool passed = *pointer == 7;
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
    return passed;
}
```

## 关联API

- [本头文件的接口列表](asc_std_scoped_allocator.md)
