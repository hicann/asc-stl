# asc::std::tuple_cat（函数模板）

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

头文件路径为：`<asc/std/tuple>`。

`asc::std::tuple_cat`按顺序拼接多个tuple的元素。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

### 无参数重载

```cpp
namespace asc::std {
constexpr tuple<> tuple_cat() noexcept;
} // namespace asc::std
```

### 拼接重载的调用形式摘要

以下为省略内部返回类型计算的声明摘要；`auto`用于说明推导结果，不是头文件中返回类型拼写的逐字转录。实际返回类型是按输入顺序拼接元素类型得到的`asc::std::tuple`。

```cpp
namespace asc::std {
template<class... Tuples> constexpr auto tuple_cat(Tuples&&... tuples);
} // namespace asc::std
```

## 参数说明

无参数重载不接受实参，返回`tuple<>`。

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tuples` | 待拼接的各输入类型；须满足当前实现支持的tuple-like协议。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tuples` | 输入/输出 | 待拼接对象，元素按实参顺序组成结果；左值元素按对应类型复制，右值元素可被移动。 |

## 返回值说明

| 适用重载 | 返回值类型 | 含义 |
| --- | --- | --- |
| 无参数重载 | `tuple<>` | 返回空tuple。 |
| 拼接重载 | `asc::std::tuple<结果元素类型...>`（类型说明） | 按顺序拼接各输入对象的元素类型；输入tuple自身的引用及cv限定不附加到元素上，元素类型本身是引用时仍保留引用。 |

## 约束说明

- 输入须通过当前实现的tuple-like类型检查，且对应的`tuple_size`、元素类型及`get`访问均可用；仅有相似成员名称不足以满足该协议。
- 结果元素须能从对应输入元素构造。结果含引用元素时，被引用存储须在使用结果期间保持有效。
- 拼接逻辑本身不申请动态存储；元素构造是否分配内存由元素类型决定。无参数重载具有`noexcept`，拼接重载没有`noexcept`声明。

## 调用示例

以下Host示例给出具体输入，并在对象仍有效时检查结果。

```cpp
#include <asc/std/tuple>

bool example()
{
    const auto left = asc::std::make_tuple(1, 2);
    const auto right = asc::std::make_tuple(3);
    const auto joined = asc::std::tuple_cat(left, right);
    return asc::std::get<0>(joined) == 1 && asc::std::get<2>(joined) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
