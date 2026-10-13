# asc::std::atomic_is_lock_free

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

头文件路径为：`<asc/std/atomic>`。

`asc::std::atomic_is_lock_free`报告当前原子对象的操作是否无需锁后备实现；内存序与地址空间须符合本页限制。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
namespace asc::std {
template<class T> bool atomic_is_lock_free(const atomic<T>* object) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 原子对象保存的值类型；须为接口支持的可平凡复制类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入 | 指向存活且满足类型对齐的原子对象；读取其原子状态或实现属性，不取得对象所有权。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 标准整数/字符owning atomic别名及列出自由函数。
- bool/8/16位用32位内部存储。
- 32/64位按有符号位模式分派。
- Host和AI Core SIMT编程GM。

## 调用示例

以下Host片段使用具体整数原子对象；设备端对象须位于可访问的全局内存。

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    asc::std::atomic<int> value{1};
    return asc::std::atomic_is_lock_free(&value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
