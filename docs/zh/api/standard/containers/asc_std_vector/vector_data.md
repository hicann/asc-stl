# asc::std::vector::data

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

`asc::std::vector::data` 返回所管理或所观察连续存储的首地址。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

### 原型 1

```cpp
const_pointer asc::std::vector::data() const noexcept;
```

### 原型 2

```cpp
pointer asc::std::vector::data() noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `const_pointer` | 返回所管理或所观察连续存储的首地址。 |
| 原型 2 | `pointer` | 返回所管理或所观察连续存储的首地址。 |

## 约束说明

- vector<T,A>显式allocator构造
- empty/size/capacity/data/begin/end/operator[]/front/back
- reserve与容量内push_back/emplace_back/pop_back/clear
- 同allocator或允许传播域的移动构造/赋值与析构
- 仅A为Device可调、容量充足、元素和allocator操作不抛出异常的域

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>
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

void example(asc::std::vector<int, example_allocator<int>>& object)
{
    (void)object.data();
}
```

对应完整工程使用 `C++17`，并通过Host 编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../examples/explicit_allocator_vector.cpp)。
