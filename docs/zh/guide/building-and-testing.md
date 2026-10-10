# 构建与测试

ASC-STL 本身不生成动态库或静态库。CMake 构建用于验证头文件、消费者配置和测试。

```bash
cmake -S . -B build/ci -DCMAKE_BUILD_TYPE=Release
cmake --build build/ci
ctest --test-dir build/ci --output-on-failure
```

## API 文档

仓库交付已审定的 Markdown、示例源码和图片资源。网页构建、发布及文档仓级检查由正式接收文档的项目负责；ASC-STL 不要求开源使用者运行内部接口投影工具。
