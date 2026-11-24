# 头文件asc/cmath

## 使用方式

```cpp
#include <asc/cmath>
```

## 功能说明

提供精确整数数学及弧度正弦/余弦的组合计算。最低C++17，支持C++20。

| API | 用途 |
| --- | --- |
| [asc::ceil_div](ceil_div.md) | 返回精确整数商向正无穷取整的值；正负操作数组合均适用。 |
| [asc::floor_div](floor_div.md) | 返回精确整数商向负无穷取整的值。它与负数的 C++ 向零截断不同。 |
| [asc::round_up](round_up.md) | 返回不小于非负整数 a 的最小正整数 b 的倍数。b 可以是任意正整数。 |
| [asc::integer_pow](integer_pow.md) | 精确计算整数底数的非负整数次幂，返回底数类型 T。 |
| [asc::integer_sqrt](integer_sqrt.md) | 精确返回非负整数平方根向下取整的 T 值 r，满足无界数学关系 r² <= value < (r+1)²。 |
| [asc::mul_hi](mul_hi.md) | 令 W 为 T 的无符号值位数，返回完整数学乘积 floor(left*right/2^W)，即乘积的高 W 位。 |
| [asc::sincos](sincos.md) | 输入角度单位为弧度，一次调用将正弦写入 sin_out、余弦写入 cos_out，返回 void。 |

整数模板同类型输入并返回T；sincos按各重载的类型和执行空间调用。完整前置条件、特殊值、精度与输出对象要求见各API页面。
