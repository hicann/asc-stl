#!/usr/bin/env python3
# Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Regressions for API Markdown and independently executed examples."""
import importlib.util
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import sys
import unittest
from unittest.mock import patch

CHECKER = Path(__file__).resolve().parents[2] / "scripts/check_api_docs.py"
sys.path.insert(0, str(CHECKER.parent))
SPEC = importlib.util.spec_from_file_location("api_docs", CHECKER)
DOCS = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(DOCS)


class DocumentationChecks(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.page = self.root / "page.md"

    def test_table_columns_and_escaped_operator(self):
        self.page.write_text("| API | Value |\n| --- | --- |\n| operator\\| | 2 |\n")
        self.assertEqual(DOCS.structure_errors(self.page), [])
        self.page.write_text("| API | Value |\n| --- | --- |\n| only one |\n")
        self.assertTrue(DOCS.structure_errors(self.page))

    def test_missing_link_and_fence(self):
        self.page.write_text("[missing](lost.md)\n```cpp\nint value;\n")
        errors = DOCS.structure_errors(self.page)
        self.assertTrue(any("missing relative link" in error for error in errors))
        self.assertTrue(any("unclosed code fence" in error for error in errors))

    def test_cpp_example_is_isolated_from_declaration(self):
        self.page.write_text("## 声明\n```cpp\nnot source\n```\n## 调用示例\n```cpp\nint value = 3;\n```\n")
        self.assertEqual(DOCS.example_source(self.page), "int value = 3;")

    def test_empty_example_and_tautology_are_rejected(self):
        self.page.write_text("## 调用示例\n```cpp\n(void)sizeof(int);\nis_same_v<selected, selected>;\n```\n")
        self.assertEqual(len(DOCS.content_errors(self.page)), 2)

    def test_runtime_failure_is_not_compile_success(self):
        compiler = shutil.which(os.environ.get("CXX") or "c++")
        if compiler is None:
            self.skipTest("C++ compiler unavailable")
        self.page.write_text("## 调用示例\n```cpp\nbool example() { return false; }\n```\n")
        spec = {"task_index": 0, "expression": "example()", "mode": "host"}
        result = DOCS.compile_example((self.root, "page.md", spec, 17, compiler, self.root))
        self.assertEqual(result["status"], "FAIL")
        self.assertEqual(result["stage"], "run")

    def test_missing_compiler_is_failure(self):
        spec = {"task_index": 0, "mode": "host"}
        result = DOCS.compile_example((self.root, "page.md", spec, 17, "/missing/compiler", self.root))
        self.assertEqual(result["status"], "FAIL")

    def test_source_preparation_preserves_entry_points_and_categories(self):
        cases = [
            ({}, "int value = 3;", "compile_only", 1),
            ({}, "static_assert(2 + 3 == 5);", "static_assert", 1),
            ({}, "int main() { return 7; }", "run", 1),
            ({"expression": "example()"}, "bool example() { return true; }", "run", 1),
            ({"mode": "runtime", "expression": "example()"}, "bool example() { return true; }", "run", 1),
            ({"mode": "simd"}, "void kernel() {}", "compile_only", 0),
            ({"mode": "simt"}, "void kernel() {}", "compile_only", 0),
        ]
        for spec, original, expected, entry_points in cases:
            with self.subTest(spec=spec, source=original):
                source, kind = DOCS.prepare_example_source(original, spec)
                self.assertEqual(kind, expected)
                self.assertIn(original, source)
                self.assertEqual(source.count("int main("), entry_points)
        source, _ = DOCS.prepare_example_source("bool example() { return false; }", {"expression": "example()"})
        self.assertIn("return (example()) ? 0 : 1;", source)

    def test_header_parse_does_not_execute_or_classify_the_removed_body(self):
        original = "#include <asc/std/tuple>\nstatic_assert(false);\nint main() { return 7; }"
        spec = {"include_only": True, "expression": "must_not_run()"}
        source, kind = DOCS.prepare_example_source(original, spec)
        self.assertEqual(kind, "header_parse")
        self.assertEqual(source, "#include <asc/std/tuple>\nint main() { return 0; }\n")

    def compile_with_results(self, spec, results):
        self.page.write_text("## 调用示例\n```cpp\nbool example() { return false; }\n```\n")
        options = dict(task_index=0, mode="host", expression="example()", npu_arch="dav-3510")
        options.update(spec)
        with patch.object(DOCS.shutil, "which", return_value="/compiler"):
            with patch.object(DOCS.subprocess, "run", side_effect=results) as command:
                result = DOCS.compile_example((self.root, "page.md", options, 17, "/compiler", self.root))
        return result, command.call_args_list

    def test_compilation_failure_does_not_execute_binary(self):
        failure = subprocess.CompletedProcess([], 1, stderr="compile diagnostic")
        result, calls = self.compile_with_results({}, [failure])
        self.assertEqual(result["status"], "FAIL")
        self.assertEqual(result["stage"], "compile")
        self.assertEqual(result["diagnostic"], "compile diagnostic")
        self.assertEqual(len(calls), 1)

    def test_device_success_only_reports_compilation(self):
        success = subprocess.CompletedProcess([], 0, stderr="")
        for mode in ("simd", "simt"):
            with self.subTest(mode=mode):
                result, calls = self.compile_with_results({"mode": mode}, [success])
                self.assertEqual((result["status"], result["stage"]), ("PASS", "device_compile"))
                self.assertEqual(len(calls), 1)
                self.assertIn("-c", calls[0].args[0])
                self.assertEqual("--enable-simt" in calls[0].args[0], mode == "simt")

    def test_host_and_runtime_preserve_execution_failure(self):
        success = subprocess.CompletedProcess([], 0, stderr="")
        failure = subprocess.CompletedProcess([], 7, stderr="runtime diagnostic")
        for mode in ("host", "runtime"):
            with self.subTest(mode=mode):
                result, calls = self.compile_with_results({"mode": mode}, [success, failure])
                self.assertEqual((result["status"], result["stage"], result["returncode"]), ("FAIL", "run", 7))
                self.assertEqual(result["diagnostic"], "runtime diagnostic")
                self.assertEqual(len(calls), 2)
                self.assertEqual(calls[1].kwargs["timeout"], 30)

    def test_missing_optional_dependency_is_not_a_pass(self):
        missing = subprocess.CompletedProcess([], 1, stderr="header not found")
        result, calls = self.compile_with_results({"required_headers": ["optional.h"]}, [missing])
        self.assertEqual(result["status"], "NOT_APPLICABLE")
        self.assertIn("optional.h", result["diagnostic"])
        self.assertEqual(len(calls), 1)
        self.assertIn("-E", calls[0].args[0])

    def test_probe_compiler_and_runtime_exceptions_remain_failures(self):
        success = subprocess.CompletedProcess([], 0, stderr="")
        timeout = subprocess.TimeoutExpired("example", 30)
        cases = [
            ({"required_headers": ["optional.h"]}, [timeout]),
            ({"required_headers": ["optional.h"]}, [OSError("probe failed")]),
            ({}, [timeout]),
            ({}, [OSError("compiler failed")]),
            ({}, [success, timeout]),
            ({}, [success, OSError("execution failed")]),
        ]
        for spec, results in cases:
            with self.subTest(spec=spec, results=results):
                result, calls = self.compile_with_results(spec, results)
                self.assertEqual(result["status"], "FAIL")
                self.assertEqual(result["diagnostic"], str(results[-1]))
                self.assertEqual(len(calls), len(results))


    def test_dangling_local_reference_and_valid_local_check(self):
        from check_doc_writing import example_errors
        for operation in ("as_const", "forward<int&>", "forward_like<int&>", "move_if_noexcept"):
            invalid = "decltype(auto) example() { int value = 7; return asc::std::" + operation + "(value); }"
            self.assertTrue(example_errors(self.page, invalid))
        valid = "bool example() { int value = 7; auto&& ref = asc::std::as_const(value); return ref == 7; }"
        self.assertEqual(example_errors(self.page, valid), [])
        external = "decltype(auto) example(int& value) { return asc::std::as_const(value); }"
        self.assertEqual(example_errors(self.page, external), [])

    def test_discarded_call_is_distinct_from_unused_argument(self):
        from check_doc_writing import example_errors
        self.assertTrue(example_errors(self.page, "void example() { (void)object.size(); }"))
        self.assertEqual(example_errors(self.page, "bool example(int unused) { (void)unused; return 2 + 3 == 5; }"), [])

    def test_heading_fence_and_encoding_rules(self):
        from check_doc_writing import format_errors
        self.page.write_text("# Title\n\n## Example\n\n```cpp\n#include <test>\n```\n")
        self.assertEqual(format_errors(self.page), [])
        self.page.write_text("# Title\n\n#### 1. Jump\ntext\n```\nsource\n```\n")
        errors = format_errors(self.page)
        self.assertTrue(any("skips" in error for error in errors))
        self.assertTrue(any("numbered" in error for error in errors))
        self.assertTrue(any("language" in error for error in errors))
        self.page.write_bytes(b"\xef\xbb\xbf# Title\n")
        self.assertTrue(any("BOM" in error for error in format_errors(self.page)))

    def test_navigation_titles_and_duplicate_targets(self):
        from check_doc_writing import navigation_errors
        api = self.root / "docs/zh/api"
        api.mkdir(parents=True)
        (api / "op.md").write_text("# `asc::operator|`\n")
        page = api / "README.md"
        page.write_text("# Map\n\n- [`asc::operator|`](op.md)\n")
        self.assertEqual(navigation_errors(self.root), [])
        page.write_text("# Map\n\n- [wrong](op.md)\n- [wrong again](op.md)\n")
        errors = navigation_errors(self.root)
        self.assertTrue(any("title differs" in error for error in errors))
        self.assertTrue(any("duplicate" in error for error in errors))

    def test_function_requires_return_section_but_type_does_not(self):
        from check_doc_writing import api_section_errors
        headings = ["产品支持情况", "功能说明", "声明", "约束说明", "调用示例", "关联API"]
        self.page.write_text("# Type\n\n" + "\n\n".join("## " + h + "\n\n内容" for h in headings))
        self.assertEqual(api_section_errors(self.page), [])
        self.page.write_text(self.page.read_text().replace("## 声明", "## 函数原型"))
        self.assertTrue(any("返回值说明" in error for error in api_section_errors(self.page)))


if __name__ == "__main__":
    unittest.main()
