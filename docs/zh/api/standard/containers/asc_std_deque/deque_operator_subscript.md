# asc::std::deque::`operator[]`

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

头文件路径为：`<asc/std/deque>`。

`asc::std::deque::operator[]`在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque)。

## 函数原型

所属类型：[`asc::std::deque`](deque.md)。

### 原型1

```cpp
// asc::std::deque 类内的声明节选；模板形参和其他成员由所属类提供。
const_reference operator[](size_type index) const noexcept;
```

### 原型2

```cpp
// asc::std::deque 类内的声明节选；模板形参和其他成员由所属类提供。
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

- 前置条件：`index < size()`；`operator[]`不执行边界检查，越界访问后果未定义。
- deque<T,A>显式allocator构造。
- 有限块映射内的push/emplace/pop_front/back。
- empty/size/front/back/`operator[]`/随机访问迭代核心。
- 新端块分配时已有元素引用稳定。
- clear/析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/deque>
#include <cstddef>
#include <memory>

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

int read_first(const asc::std::deque<int, example_allocator<int>>& values)
{
    // 先建立非空前提：空容器路径同样返回，保证每条执行路径都有返回值
    if (values.empty()) {
        return -1;
    }
    return values[0];  // 读取首元素；返回元素值的副本，不把容器内部引用传出函数
}

void write_first(asc::std::deque<int, example_allocator<int>>& values, int new_value)
{
    if (!values.empty()) {
        values[0] = new_value;  // 非空前提下经非 const 下标写入
    }
}
```

## 关联API

- [`asc::std::deque`](deque.md)
- [本头文件的接口列表](asc_std_deque.md)
