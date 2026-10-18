# asc::std::vector::size_type

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

`asc::std::vector::size_type`标识容器大小的无符号类型。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 声明

所属类型：[`asc::std::vector`](vector.md)。

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
using size_type = asc::std::size_t;
```

## 约束说明

在泛型代码中可通过所属类型的`size_type`声明大小变量，无需硬编码底层整数类型；该别名与其他成员类型的关系见所属类型页面。

- 此别名表示所属类型用于元素数量或大小的无符号整数类型；读取类型本身不分配内存，也不访问元素。
- 构造、分配和访问的运行条件见所属类型[asc::std::vector](vector.md)。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <memory>
#include <asc/std/vector>
#include <asc/std/cstddef>
#include <asc/std/type_traits>

bool example()
{
    using Vector = asc::std::vector<int, ::std::allocator<int>>;
    static_assert(asc::std::is_same_v<Vector::size_type, asc::std::size_t>);
    Vector values(::std::allocator<int>{});
    values.push_back(7);
    const Vector::size_type count = values.size();
    return count == 1;
}
```

## 关联API

- [`asc::std::vector`](vector.md)
- [本头文件的接口列表](asc_std_vector.md)
