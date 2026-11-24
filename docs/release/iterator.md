# Iterator adaptors

Implements the data-access and read/write adapters described in [Issue #88](https://gitcode.com/cann/asc-stl/issues/88).
The independent iterators own their descriptor and callable state, borrow data, and support C++17 and C++20.
Complete navigation protocols are provided under the documented constraints. Legacy categories and C++20 concepts
are specified separately. Output proxies preserve old postincrement targets; zip proxies support constrained tuple
conversion, assignment, movement and swapping.

## Migration

- Construct strided access with `first, extent, stride`, including negative strides. Its `base()` returns the anchor.
- Counting access stores an origin and logical position separately. Use `index()` in place of the former `base()`.
- Use `==` and `!=` in place of `zip.equal`; supply a common length for zipped ranges.
- `zip_transform_iterator` is the alias `transform_iterator<zip_function<F>, zip_iterator<I...>>`.
- Read/write transformations must preserve logical values on readback. Use directional adapters for lossy conversion.

The existing release feature macros are unchanged; this header introduces no separate delivery or Runtime query.
See the [Chinese API](../zh/api/extension/function_objects_and_iterators/asc_iterator/asc_iterator.md) and
[English API](../en/api/extension/function_objects_and_iterators/asc_iterator/asc_iterator.md).
