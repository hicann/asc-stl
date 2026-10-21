# asc::std::vector::push_back

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

`asc::std::vector::push_back`在容器尾部插入一个元素。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

所属类型：[`asc::std::vector`](vector.md)。

### 原型1

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
void push_back(T&& value);
```

### 原型2

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
void push_back(const T& value);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入（可能被移动） | 提供插入到容器末尾的元素；函数可能移动该实参，移动后其处于有效但未指定状态。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待插入到容器尾部的元素值；以复制方式构造新元素，源对象保持不变。 |

## 返回值说明

无返回值。

## 约束说明

- 左值重载要求`T`可由`const T&`构造，右值重载要求`T`可由`T&&`构造；当前两种重载还均要求`T`可由`T&&`构造，以满足扩容路径的编译要求，事先预留容量不免除此要求。
- 容量不足时会扩容并移动原元素；扩容后原指针、引用及迭代器失效。成功插入后`size()`增加`1`。
- 在Device侧调用时，分配器及相关元素操作须可用于相应编程模式且不抛出异常，并须保证分配成功或事先预留足够容量。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.push_back(static_cast<Args&&>(args)...);
}
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../examples/explicit_allocator_vector.cpp)。

## 关联API

- [`asc::std::vector`](vector.md)
- [本头文件的接口列表](asc_std_vector.md)
