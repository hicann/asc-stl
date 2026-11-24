# 头文件asc/numeric

提供受检查的标量整数加减乘除和转换，返回数值与失败标志。

| API | 类型 | 语言 | 调用环境 |
| --- | --- | --- | --- |
| [asc::add_overflow](add_overflow.md) | 函数模板 | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::sub_overflow](sub_overflow.md) | 函数模板 | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::mul_overflow](mul_overflow.md) | 函数模板 | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::div_overflow](div_overflow.md) | 函数模板 | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::overflow_cast](overflow_cast.md) | 函数模板 | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::checked_result](checked_result.md) | 类模板 | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::checked_result::value](checked_result_value.md) | 公开成员 | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::checked_result::failed](checked_result_failed.md) | 公开成员 | C++17 / C++20 | Host / SIMD / SIMT |

四种算术各有对象返回和输出引用两种形式，合计九个函数模板重载。

**兼容性**

旧overflow_result/overflow由checked_result/failed替代，所有失败值改为零。扩展层不再公开五个普通饱和接口、narrow和narrow_cast；检查转换使用overflow_cast，不检查的转换使用static_cast。普通整数饱和语义仍按标准层支持版本规划，本次不新增或承诺标准饱和实现。
