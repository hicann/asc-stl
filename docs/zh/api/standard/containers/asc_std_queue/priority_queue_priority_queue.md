# asc::std::priority_queue::priority_queue

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

头文件路径为：`<asc/std/queue>`。

`asc::std::priority_queue::priority_queue`按本页所列构造形态初始化`priority_queue`对象。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 函数原型

### 原型1

```cpp
constexpr priority_queue();
```

### 原型2

```cpp
constexpr priority_queue(const Compare& compare);
```

### 原型3

```cpp
constexpr priority_queue(const Compare& compare, Container&& container);
```

### 原型4

```cpp
constexpr priority_queue(const Compare& compare, const Container& container);
```

### 原型5

```cpp
template<class Alloc> constexpr priority_queue(const Alloc& allocator);
```

### 原型6

```cpp
template<class Alloc> constexpr priority_queue(const Compare& compare, Container&& container, const Alloc& allocator);
```

### 原型7

```cpp
template<class Alloc> constexpr priority_queue(const Compare& compare, const Alloc& allocator);
```

### 原型8

```cpp
template<class Alloc> constexpr priority_queue(const Compare& compare, const Container& container, const Alloc& allocator);
```

### 原型9

```cpp
template<class Alloc> constexpr priority_queue(const priority_queue<T, Container, Compare>& compare, const Alloc& allocator);
```

### 原型10

```cpp
template<class Alloc> constexpr priority_queue(priority_queue<T, Container, Compare>&& compare, const Alloc& allocator);
```

### 原型11

```cpp
template<class InputIterator> constexpr priority_queue(InputIterator first, InputIterator last, const Compare& compare, Container&& container);
```

### 原型12

```cpp
template<class InputIterator> constexpr priority_queue(InputIterator first, InputIterator last, const Compare& compare, const Container& container);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `container` | 输入/输出 | 提供“按本页所列构造形态初始化`priority_queue`对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `container` | 输入 | 提供“按本页所列构造形态初始化`priority_queue`对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `container` | 输入/输出 | 提供“按本页所列构造形态初始化`priority_queue`对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型8的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `container` | 输入 | 提供“按本页所列构造形态初始化`priority_queue`对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型9的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型10的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入/输出 | 用于确定元素顺序的比较对象。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型11的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `container` | 输入/输出 | 提供“按本页所列构造形态初始化`priority_queue`对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型12的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `container` | 输入 | 提供“按本页所列构造形态初始化`priority_queue`对象”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

无返回值。

## 约束说明

- priority_queue<T,Container,Compare=less<typename Container::value_type>>的显式兼容Container合同：T必须等于Container::value_type，Container的构造/front/`operator[]`/push_back/emplace_back/pop_back/size/empty/swap及allocator操作必须在当前执行空间有效，Compare必须定义Device可调的strict-weak-order且可在已验证移动交换域使用。
- 交付container_type/value_compare/value_type/size_type/reference/const_reference及protected c/comp，default/Compare/Container/copy/move/allocator构造及赋值，N4861两类InputIterator构造，empty/size/top、lvalue/rvalue push、void emplace、pop，member/non-member swap、uses_allocator特化，以及Compare+Container、InputIterator+Compare+Container、Compare+Container+Alloc三类显式Container CTAD。
- 堆序语义为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <vector>
#include <functional>
#include <asc/std/queue>

bool example()
{
    asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>> values;
    values.push(1);
    values.push(3);
    values.push(2);
    return values.size() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_queue.md)
