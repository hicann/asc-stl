# 头文件 asc/warp

提供线程束（Warp）内的投票、值匹配、数据交换（Shuffle）和归约功能

## 使用方式

```cpp
#include <asc/warp>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::active_mask](active_mask.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask](lane_mask.md) | 类 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::all](lane_mask_all.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::all_active](lane_mask_all_active.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::all_greater](lane_mask_all_greater.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::all_greater_equal](lane_mask_all_greater_equal.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::all_less](lane_mask_all_less.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::all_less_equal](lane_mask_all_less_equal.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::all_not_equal](lane_mask_all_not_equal.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::lane_mask](lane_mask_lane_mask.md) | 构造函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::none](lane_mask_none.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator unsigned int](lane_mask_operator_unsigned_int.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator!=](lane_mask_operator_not_equal.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator&](lane_mask_operator_bit_and.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator&=](lane_mask_operator_bit_and_assign.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator<<](lane_mask_operator_shift_left.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator<<=](lane_mask_operator_shift_left_assign.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator==](lane_mask_operator_equal.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator>>](lane_mask_operator_shift_right.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator>>=](lane_mask_operator_shift_right_assign.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator^](lane_mask_operator_bit_xor.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator^=](lane_mask_operator_bit_xor_assign.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator\|](lane_mask_operator_bit_or.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator\|=](lane_mask_operator_bit_or_assign.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::operator~](lane_mask_operator_bit_not.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::this_lane](lane_mask_this_lane.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::lane_mask::value](lane_mask_value.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_all](warp_all.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_any](warp_any.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_ballot](warp_ballot.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_match_all](warp_match_all.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_match_any](warp_match_any.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_reduce_add](warp_reduce_add.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_reduce_max](warp_reduce_max.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_reduce_min](warp_reduce_min.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_shuffle_down](warp_shuffle_down.md) | 函数模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_shuffle_idx](warp_shuffle_idx.md) | 函数模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_shuffle_result](warp_shuffle_result.md) | 类模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_shuffle_result::data](warp_shuffle_result_data.md) | 变量 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_shuffle_result::valid](warp_shuffle_result_valid.md) | 变量 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_shuffle_up](warp_shuffle_up.md) | 函数模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::warp_shuffle_xor](warp_shuffle_xor.md) | 函数模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
