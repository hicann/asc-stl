# 头文件asc/type_traits

提供六组编译期布尔查询，供模板识别扩展格式、选择相等路径及检查重定位和原生限定条件。标准分类由asc::std保持。

| API |
| --- |
| [asc::is_bitwise_comparable](is_bitwise_comparable.md) |
| [asc::is_bitwise_comparable_v](is_bitwise_comparable_v.md) |
| [asc::is_trivially_relocatable](is_trivially_relocatable.md) |
| [asc::is_trivially_relocatable_v](is_trivially_relocatable_v.md) |
| [asc::is_low_precision](is_low_precision.md) |
| [asc::is_low_precision_v](is_low_precision_v.md) |
| [asc::is_extended_floating_point](is_extended_floating_point.md) |
| [asc::is_extended_floating_point_v](is_extended_floating_point_v.md) |
| [asc::is_packed_numeric](is_packed_numeric.md) |
| [asc::is_packed_numeric_v](is_packed_numeric_v.md) |
| [asc::is_address_space_qualified](is_address_space_qualified.md) |
| [asc::is_address_space_qualified_v](is_address_space_qualified_v.md) |

## 行为约定

所有类模板派生自asc::std::bool_constant，变量模板严格投影对应::value。按位比较仅认证const同型左值相等，不保证排序。true声明要求平凡复制、唯一表示、比较无副作用/异常且不依赖地址或可变外部状态；正负零、NaN、padding和用户相等关系须按真实语义处理。未提供相等运算的类型默认false，十种ASC包装的按位可比性也均为false。

一般类/联合体的两项对象性质默认false。重定位默认限无顶层cv的标准标量及登记数值类型，须同时平凡复制、平凡右值构造及平凡析构。只有这两项性质的类模板允许对完整用户类/联合体作完整特化，保留标准布尔特征形式；所有翻译单元须在首次使用前一致可见。不得特化_v、cv/ref、数组、指针或标准/ASC/SDK类型。分类和地址检测不允许用户特化，也不读取嵌套typedef或属性作为声明。

| 输入 | 格式分类 | 按位比较 | 重定位 | 地址限定 |
| --- | --- | --- | --- | --- |
| const T | 与T相同 | 与T相同 | false | 去掉指针自身cv/ref |
| volatile T / const volatile T | 与T相同 | false | false | 同上，保留pointee限定 |
| 引用 | false | false | false | 去引用后查询 |
| 数组、void、函数 | false | false | false | false |
| 普通指针、成员指针、枚举、nullptr_t | false | 默认false | 非cv标量按通用规则 | false |

三项分类只去顶层cv，不做数组退化。未登记类型含未完成类，格式分类稳定为false；直接查询未完成类/联合体及其cv形式的两项对象性质须诊断。引用/数组先按表处理，指针不要求被指对象完整。后置特化不受支持，跨翻译单元不一致未必能诊断。

## 格式矩阵

| 类型 | 低精度 | 扩展单元素浮点 | 打包 |
| --- | --- | --- | --- |
| float16、bfloat16、float8_e4m3fn、float8_e5m2、hifloat8 | true | true | false |
| float8_e8m0、int4 | true | false | false |
| float4_e2m1x2、float4_e1m2x2、int4x2 | true | false | true |

标准算术、普通数组、聚合和未登记格式为false；数据格式身份不提供算术/转换能力。类型/格式登记与numeric_types共用一份，任意包含顺序一致，type_traits不引入转换实现或CANN Runtime。

## 编译条件与地址限定

Host无需SDK，支持C++17/C++20；原生适配首批为Ascend950、CANN9.2.0-beta.2/BiSheng15。half、bfloat16_t、float8_e4m3_t、float8_e5m2_t、hifloat8_t、float8_e8m0_t、float4_e2m1x2_t、float4_e1m2x2_t按格式独立登记。SIMD int4x2_t也为低精度打包类型，其9.2类表示非平凡复制、重定位为false；新SDK若采用独立内建表示，按其实际平凡性质判断。原生::int4、half2等普通向量未登记。

纯SIMT的GM/UB拼写擦除为普通指针，限定查询为false；混合SIMT VF及SIMD控制段保留限定。只检测直接pointee，保留其cv：G为GM指针时G*为false、__gm__ G*为true；支持合法的对象/void指针。其他未支持前端或限定、对象本身及引用、成员/函数指针和视图为false。查询不推断指针值的实际空间/有效性，memory使用同一私有识别信息映射其空间值。

## 生命周期边界

本头提供查询，不提供搬移算法。C++17最低依据N4659，合法构造目标后以源存储释放/合法复用结束源生命周期；平凡析构/标量伪析构调用不单独作为源已结束的证明。C++20的memcpy/memmove等指定操作须满足隐式生命周期类型及子对象规则，且仍需单独结束源生命周期。普通字节循环不获得额外构造权限。

调用方保证大小、对齐、可访问性、有效对象和非重叠存储，排除基类/潜在重叠子对象、非法union活动成员及重复销毁。自引用和资源类默认false；用户true声明须保证三项平凡性质且无地址修复或额外生命周期副作用。编译器重定位内建不直接扩大本版集合。
