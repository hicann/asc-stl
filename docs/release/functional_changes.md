# `<asc/functional>` 接口变化（未发布）

本次按 [Issue87](https://gitcode.com/cann/asc-stl/issues/87) 实现函数对象及封闭的运算性质支持表，最低支持 C++17，同时支持 C++20。

- `maximum<void>`、`minimum<void>` 改为返回公共类型的值，等价时选择左侧。依赖旧引用返回的调用方应改为接收值；结果中的指针或视图仍有自身借用要求。
- `equal_to_value<T>` 保存值，提供转发构造、异型比较和 C++17 类型推导。构造、比较与结果构造使用相应的条件 `noexcept`。
- 结合律、交换律、单位元和吸收元按精确的运算/值类型组合登记。每个二元节点转换回值类型；整数提升后的溢出风险纳入判定。未登记组合返回 `false`，对应特殊元素取值函数不可调用。
- 移除 `proclaim_return_type`、`proclaim_copyable_arguments`、`proclaims_copyable_arguments`、`proclaims_copyable_arguments_v`。普通返回类型和参数传递由调用方的函数对象直接表达。

## Changes (unreleased)

- Transparent `maximum` and `minimum` return a common value type and select the left operand on equivalence. Replace uses relying on the former reference result with value receivers; pointer/view results retain their borrowing requirements.
- `equal_to_value` owns its target and supports forwarding construction, heterogeneous equality, and C++17 deduction. Exception specifications account for the operations actually performed.
- The closed operation/type table independently records associativity, commutativity, identities, and absorbing elements. Every binary node converts back to the value type, with integral-promotion overflow included in the conditions. Unregistered pairs return `false` and have no callable element accessor.
- The four `proclaim*` interfaces listed above are removed. Express return types and argument passing directly in the operation object.
