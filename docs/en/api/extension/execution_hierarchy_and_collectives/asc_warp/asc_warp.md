# Header asc/warp

Provides voting, value matching, data exchange (shuffle), and reduction within a warp

## Usage

```cpp
#include <asc/warp>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::active_mask](active_mask.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask](lane_mask.md) | Class | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all](lane_mask_all.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_active](lane_mask_all_active.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_greater](lane_mask_all_greater.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_greater_equal](lane_mask_all_greater_equal.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_less](lane_mask_all_less.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_less_equal](lane_mask_all_less_equal.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_not_equal](lane_mask_all_not_equal.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::lane_mask](lane_mask_lane_mask.md) | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::none](lane_mask_none.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator unsigned int](lane_mask_operator_unsigned_int.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator!=`](lane_mask_operator_not_equal.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator&](lane_mask_operator_bit_and.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator&=](lane_mask_operator_bit_and_assign.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator<<`](lane_mask_operator_shift_left.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator<<=`](lane_mask_operator_shift_left_assign.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator==`](lane_mask_operator_equal.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator>>`](lane_mask_operator_shift_right.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator>>=`](lane_mask_operator_shift_right_assign.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator^](lane_mask_operator_bit_xor.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator^=](lane_mask_operator_bit_xor_assign.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator\|](lane_mask_operator_bit_or.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator\|=](lane_mask_operator_bit_or_assign.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator~](lane_mask_operator_bit_not.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::this_lane](lane_mask_this_lane.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::value](lane_mask_value.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_all](warp_all.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_any](warp_any.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_ballot](warp_ballot.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_match_all](warp_match_all.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_match_any](warp_match_any.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_reduce_add](warp_reduce_add.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_reduce_max](warp_reduce_max.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_reduce_min](warp_reduce_min.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_down](warp_shuffle_down.md) | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_idx](warp_shuffle_idx.md) | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_result](warp_shuffle_result.md) | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_result::data](warp_shuffle_result_data.md) | Variable | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_result::valid](warp_shuffle_result_valid.md) | Variable | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_up](warp_shuffle_up.md) | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_xor](warp_shuffle_xor.md) | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
