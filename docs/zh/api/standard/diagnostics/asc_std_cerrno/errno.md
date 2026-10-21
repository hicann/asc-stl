# errno

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

头文件路径为：`<asc/std/cerrno>`。

`errno`是Host上可修改的int左值宏，用于读取C兼容接口规定的错误码；应按具体接口约定判断何时读取，成功调用不保证清零。Device不提供errno状态。

## 声明

Host通过公共头文件取得平台`<cerrno>`的errno宏；具体展开式由平台决定，ASC-STL不定义额外的errno地址获取函数。

```cpp
#include <asc/std/cerrno>
```

## 约束说明

- 仅可在Host使用errno状态；它由平台C库管理，通常为线程局部状态。
- Device仅提供EDOM、EILSEQ、ERANGE三个错误码常量，不提供errno对象。
- 只在具体C接口约定的失败条件成立时解释该错误码；需要区分旧错误时由调用方先清零。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/cerrno>

bool example()
{
    const int saved = errno;
    errno = 0;
    const bool cleared = errno == 0;
    errno = saved;
    return cleared;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cerrno.md)
