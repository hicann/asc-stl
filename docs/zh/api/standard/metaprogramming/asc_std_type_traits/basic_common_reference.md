# asc::std::basic_common_reference

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

头文件路径为：`<asc/std/type_traits>`。

`basic_common_reference` 是用户特化的公共引用类型计算点，接收两个类型及其限定传播模板。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
template<class, class, template<...> class, template<...> class, class> struct asc::std::basic_common_reference
```

## 约束说明

- 提供特征类以及标准的 _t、_v 辅助形式

## 调用示例

以下 Host 片段实例化自定义点的主模板；需要指定公共引用类型时，由用户针对自有类型提供特化。

```cpp
#include <asc/std/type_traits>

void example()
{
    using customization = asc::std::basic_common_reference<int, long,
        asc::std::type_identity_t, asc::std::type_identity_t>;
    (void)sizeof(customization);
}
```
