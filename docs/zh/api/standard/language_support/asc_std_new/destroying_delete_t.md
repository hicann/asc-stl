# asc::std::destroying_delete_t

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

头文件路径为：`<asc/std/new>`。

`asc::std::destroying_delete_t`提供可用于普通重载选择的空标签类型。从C++17起，标签类型与对应对象`asc::std::destroying_delete`均可使用。

标准语义参考：[cppreference `new`](https://en.cppreference.com/w/cpp/header/new)。

## 声明

```cpp
namespace asc::std {
struct destroying_delete_t;
} // namespace asc::std
```

## 约束说明

- 标签的声明不执行对象销毁或内存释放。
- 编译器销毁型delete机制受语言及Host标准类型规则约束；本库标签不为C++17增加该语言机制，也不承诺替代编译器要求的Host标准类型。

## 调用示例

以下示例检查公开标签的类型和对应对象，可在C++17和C++20使用。

```cpp
#include <asc/std/new>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_empty_v<asc::std::destroying_delete_t>);
    static_assert(asc::std::is_same_v<decltype(asc::std::destroying_delete), const asc::std::destroying_delete_t>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_new.md)
