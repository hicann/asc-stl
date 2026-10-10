# asc::std::vector::operator[]

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

`asc::std::vector::operator[]` 在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

### 原型 1

```cpp
const_reference asc::std::vector::operator[](size_type index) const noexcept;
```

### 原型 2

```cpp
reference asc::std::vector::operator[](size_type index) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 提供“在调用方保证索引有效时访问指定元素”所需的输入对象；类型须满足所选原型约束。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 提供“在调用方保证索引有效时访问指定元素”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `const_reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型 2 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

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

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator[](static_cast<Args&&>(args)...);
}
```

对应完整工程使用 `C++17`，并通过Host 编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../examples/explicit_allocator_vector.cpp)。
