# asc::std::variant

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

头文件路径为：`<asc/std/variant>`。

`asc::std::variant`从多个备选类型中保存一个活动值。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 声明

```cpp
namespace asc::std {
template<class ...Types> class variant;
} // namespace asc::std
```

## 约束说明

- 复制构造要求所有备选类型都可复制构造。复制赋值还要求所有备选类型都可复制赋值。所有备选类型的复制构造都平凡时，包装类型的复制构造也平凡。若所有备选类型的复制赋值和析构也平凡，包装类型的复制赋值也平凡。
- Host 上，复制赋值切换备选项时，如果新类型的复制构造可能抛出异常且移动构造不会抛出异常，会先复制到临时对象。复制失败时保留原值。直接在目标位置构造新值的路径若抛出异常，对象将没有活动备选项。
- 同一活动备选项的赋值抛出异常时，活动索引保持不变，值的状态由该备选类型的赋值操作决定。

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(7);
    const bool integer = value.index() == 0 && *asc::std::get_if<0>(&value) == 7;
    value.emplace<1>(2.0F);
    return integer && value.index() == 1 && *asc::std::get_if<1>(&value) == 2.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_variant.md)
