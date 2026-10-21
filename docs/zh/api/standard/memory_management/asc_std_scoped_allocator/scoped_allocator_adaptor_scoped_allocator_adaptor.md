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

所属类型：[`scoped_allocator_adaptor`](scoped_allocator_adaptor.md)。原型1适用于两种偏特化；2、3仅适用于没有内层分配器的偏特化；4仅适用于至少一个内层分配器的偏特化。复制/移动特殊成员遵循隐式声明规则，不提供跨外层类型的转换构造模板。

### 原型1

```cpp
constexpr scoped_allocator_adaptor() = default;
```

### 原型2

```cpp
constexpr explicit scoped_allocator_adaptor(const OuterAllocator& outer) noexcept;
```

### 原型3

```cpp
constexpr explicit scoped_allocator_adaptor(OuterAllocator&& outer) noexcept;
```

### 原型4

```cpp
constexpr scoped_allocator_adaptor(const OuterAllocator& outer,
    const FirstInner& first, const RestInner&... rest) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2、3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer` | 输入 | 用于复制或移动初始化外层基类的分配器对象；不取得其所有分配的独占所有权。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `outer` | 输入 | 用于复制初始化外层分配器。 |
| `first` | 输入 | 第一个内层分配器，用于初始化内层适配器。 |
| `rest` | 输入 | 其余内层分配器，按顺序复制初始化。 |

## 返回值说明

无返回值。

## 约束说明

- 默认构造及复制/移动特殊成员是否可用取决于各分配器类型。
- 所列显式接收分配器的构造为`noexcept`；其内部复制/移动操作不得抛出异常。
- 构造只保存分配器状态，不分配或构造元素。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>
#include <asc/std/scoped_allocator>
#include <memory>
#include <limits>

template<class T>
struct example_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template<class U> struct rebind { using other = example_allocator<U>; };
    int identity = 0;
    T* allocate(size_type count) { return std::allocator<T>{}.allocate(count); }
    void deallocate(T* address, size_type count) { std::allocator<T>{}.deallocate(address, count); }
    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(T); }
};

bool example()
{
    using adaptor = asc::std::scoped_allocator_adaptor<example_allocator<int>>;
    adaptor allocator(example_allocator<int>{7});
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 9);
    const bool valid = allocator.outer_allocator().identity == 7 && *pointer == 9;
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
    return valid;
}
```

## 关联API

- [本头文件的接口列表](asc_std_scoped_allocator.md)
