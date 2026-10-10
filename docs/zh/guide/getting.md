# 获取与使用 ASC-STL

ASC-STL 是纯头文件库，最低需要 C++17。将安装后的 `include/` 目录加入头文件搜索路径，即可按需包含头文件。

```cpp
#include <asc/std/type_traits>

static_assert(asc::std::is_same_v<int, int>);
```

## CMake

安装 ASC-STL 后，通过公开 target 链接：

```cmake
find_package(asc_stl CONFIG REQUIRED)
target_link_libraries(my_target PRIVATE asc_stl::asc_stl)
```

ASC-STL 不替换 Host 编译器的 `std` 命名空间。C++ 标准库接口使用 `asc::std`，昇腾扩展和 Runtime 接口使用 `asc`。
