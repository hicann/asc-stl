/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Copyright 2026 湖北多样性算力应用创新研究院 */

#include <asc/mdspan>
#include <asc/iterator>
#include <asc/std/chrono>
#include <asc/std/mdspan>
#include <asc/std/memory>
#include <asc/std/mutex>
#include <asc/std/scoped_allocator>
#include <asc/std/set>
#include <asc/std/string>
#include <asc/std/vector>

int asc_stl_w09_w10_consumer_b()
{
    using extents_type = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::steps<2> strides(-3, 1);
    asc::layout_stride_relaxed::mapping<extents_type, asc::steps<2>> mapping(extents_type{}, strides, 3);
    return mapping(1, 2) == 2 && mapping.required_span_size() == 6 ? 0 : 1;
}
