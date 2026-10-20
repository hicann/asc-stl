# 获取与使用ASC-STL

ASC-STL是纯头文件库，最低需要C++17。将安装后的`include/`目录加入头文件搜索路径，即可按需包含头文件。

```cpp
#include <asc/std/type_traits>

static_assert(asc::std::is_same_v<int, int>);
```

## CMake

安装ASC-STL后，通过公开target链接：

```cmake
find_package(asc_stl CONFIG REQUIRED)
target_link_libraries(my_target PRIVATE asc_stl::asc_stl)
```

ASC-STL不替换Host编译器的`std`命名空间。C++ 标准库接口使用`asc::std`，昇腾扩展和Runtime接口使用`asc`。

接口的语言门控、能力宏、Host/Device和常量求值条件见[语言模式与兼容性](cpp_compatibility.md)。
