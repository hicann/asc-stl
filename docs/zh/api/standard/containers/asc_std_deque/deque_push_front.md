# asc::std::deque::push_front

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

`asc::std::deque::push_front` 在容器首部插入一个元素。

标准语义参考：[cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque)。

## 函数原型

### 原型 1

```cpp
void asc::std::deque::push_front(T&& value);
```

### 原型 2

```cpp
void asc::std::deque::push_front(const T& value);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待插入到容器首部的元素值；以移动方式构造新元素，插入后源对象处于有效但未指定的移后状态。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待插入到容器首部的元素值；以复制方式构造新元素，源对象保持不变。 |

## 返回值说明

无返回值。

## 约束说明

- deque<T,A>显式allocator构造
- 有限块映射内的push/emplace/pop_front/back
- empty/size/front/back/operator[]/随机访问迭代核心
- 新端块分配时已有元素引用稳定
- clear/析构
- 仅容量充足和不抛出异常域

## 调用示例

以下 Host 片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/deque>
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

void example(asc::std::deque<int, example_allocator<int>>& values)
{
    values.push_front(7);
}
```
