# asc::std::list::emplace_back

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

头文件路径为：`<asc/std/list>`。

`asc::std::list::emplace_back` 在容器尾部直接构造元素。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `list`](https://en.cppreference.com/w/cpp/header/list)。

## 函数原型

```cpp
template<class ...Args> reference asc::std::list::emplace_back(Args&&... args);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `reference` | 返回原位构造的元素引用或所选原型规定的插入结果。 |

## 约束说明

- Host及AI Core SIMT 编程下list<T,A>显式GM arena allocator构造
- empty/size/front/back/begin/end
- push/emplace/pop_front/back/clear
- 双向迭代核心、移动构造/赋值、移动前迭代器继续遍历目标节点及析构
- 仅容量充足和不抛出异常值/allocator域
- Host 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/list>
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

decltype(auto) example(asc::std::list<int, example_allocator<int>>& values)
{
    return values.emplace_back(7);
}
```
