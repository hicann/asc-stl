# asc::maximum::operator()

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

头文件：`<asc/functional>`。比较一次，比较等价时选左侧，再构造较大值结果。

## 声明

```cpp
// Inside the typed form; declaration constraints are omitted.
constexpr T operator()(const T& left, const T& right) const
    noexcept(/* comparison, bool conversion, and both result constructions */);

// Inside the void specialization.
template<class Left, class Right>
constexpr auto operator()(Left&& left, Right&& right) const
    noexcept(/* comparison, bool conversion, and both result constructions */)
    -> asc::std::common_type_t<asc::std::decay_t<Left>, asc::std::decay_t<Right>>;
```

## 约束说明

比较表达式为static_cast<bool>(left < right)，真时选右，否则选左。透明版以原类型const左值比较，仅在选中后转发构造结果；指定类型版从const T&构造。两侧结果构造均须有效，比较/布尔转换或构造无效时排除重载。noexcept还计入相关临时析构。

结果为完整、无顶层cv的非数组值类型；透明实参去引用后须为完整、非volatile的非数组对象。临时实参可直接传入，结果若含指针/视图仍按自身规则借用。异型比较遵循普通C++转换。严格浮点配置下，NaN导致比较假并取左，同类型正负零取左侧符号；不使用fmin/fmax规则。

C++17和C++20均支持。Host、SIMT、SIMD标量调用须满足当前调用域的比较、转换、构造和析构要求；Device调用遵守无异常执行约定。

## 调用示例

```cpp
#include <asc/functional>
#include <asc/std/type_traits>

bool example()
{
    int left = 3;
    int right = 7;
    auto result = asc::maximum<>{}(left, right);
    static_assert(asc::std::is_same_v<decltype(result), int>);
    return result == 7 && &result != &left && &result != &right;
}
```

## 关联API

- [本头文件的接口列表与运算支持表](asc_functional.md)
