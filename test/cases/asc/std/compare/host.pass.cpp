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

#include <asc/std/compare>

static_assert(asc::std::compare_strong_order_fallback(1, 2) == asc::std::strong_ordering::less);
static_assert(asc::std::compare_weak_order_fallback(1, 1) == asc::std::weak_ordering::equivalent);
static_assert(asc::std::compare_partial_order_fallback(2, 1) == asc::std::partial_ordering::greater);

int main()
{}
