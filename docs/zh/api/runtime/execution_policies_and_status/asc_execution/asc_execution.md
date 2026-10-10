# 头文件 asc/execution

统一导出设备端执行策略、执行要求和提交状态相关接口

## 使用方式

```cpp
#include <asc/execution>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::execution_errc](execution_errc.md) | 枚举 | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::backend_error](execution_errc_backend_error.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::insufficient_storage](execution_errc_insufficient_storage.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::invalid_argument](execution_errc_invalid_argument.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::success](execution_errc_success.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::execution_status](execution_status.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::execution_status::code](execution_status_code.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::execution_status::execution_status](execution_status_execution_status.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::execution_status::native_code](execution_status_native_code.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::execution_status::success](execution_status_success.md) | 成员函数 | C++17+ | Host | Ascend 950 |
