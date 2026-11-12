# CANN_ASC_STL_LIB_*

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

查询本库满足的标准特性修订版本。[完整清单](../../../../guide/std_feature_test.md)列出标准名、值、条件和未报告原因。

## 声明

对象式宏，满足对应标准修订时定义为标准年月整数，未满足时不定义。名称映射为 `__cpp_lib_x` → `CANN_ASC_STL_LIB_x`。

## 约束说明

查询当前翻译单元的语言、编译器及执行配置；不代表宿主 std 或产品发布版本。

## 调用示例

```cpp
#include <asc/std/version>
#include <asc/std/array>

#if defined(CANN_ASC_STL_LIB_to_array) && CANN_ASC_STL_LIB_to_array >= 201907L
constexpr auto values = asc::std::to_array({2, 4});
static_assert(values[0] == 2 && values[1] == 4);
#else
#error "ASC-STL to_array revision 201907 is required"
#endif
```

## 关联API

- [本头文件的接口列表](asc_std_version.md)
