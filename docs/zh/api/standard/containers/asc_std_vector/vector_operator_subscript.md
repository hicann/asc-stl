# asc::std::vector::`operator[]`

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

头文件路径为：`<asc/std/vector>`。

`asc::std::vector::operator[]`在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

所属类型：[`asc::std::vector`](vector.md)。

### 原型1

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
const_reference operator[](size_type index) const noexcept;
```

### 原型2

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
reference operator[](size_type index) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 待访问元素的下标，从0起；本接口不检查越界，调用方须保证index < size()。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 待访问元素的下标，从0起；本接口不检查越界，调用方须保证index < size()。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `const_reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型2 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

## 约束说明

- 下标须满足`index < size()`；本接口不执行边界检查，越界访问后果未定义。
- 返回引用不延长元素生命周期；释放或重新分配存储、销毁对应元素后，原引用失效。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>
#include <memory>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};

bool example()
{
    using sequence = asc::std::vector<int, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.push_back(7);
    values[0] = 9;
    const sequence& observed = values;
    return observed[0] == 9 && values.front() == 9;
}
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../examples/explicit_allocator_vector.cpp)。

## 关联API

- [`asc::std::vector`](vector.md)
- [本头文件的接口列表](asc_std_vector.md)
