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
import argparse
import json
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

    def test_std_header_registry_joins_pages_and_rejects_duplicate_ownership(self):
        shared = self.root / "test/docs/examples.json"
        shared.parent.mkdir(parents=True)
        shared.write_text("{}")
        registry = self.root / "test/cases/asc/std/array/examples.json"
        registry.parent.mkdir(parents=True)
        directory = "docs/zh/api/standard/containers/asc_std_array"
        spec = {"standards": [17, 20], "expression": "example()", "mode": "host"}
        registry.write_text(json.dumps({"directory": directory, "examples": {"array.md": spec}}))
        expected = {f"{directory}/array.md": spec}
        self.assertEqual(DOCS.example_registry(self.root), expected)
        shared.write_text(json.dumps(expected))
        with self.assertRaisesRegex(ValueError, "Duplicate"):
            DOCS.example_registry(self.root)
        registry.unlink()
        with self.assertRaisesRegex(ValueError, "under their public header"):
            DOCS.example_registry(self.root)

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

    def test_structure_gate_checks_root_example_links(self):
        page = self.root / "examples/README.md"
        page.parent.mkdir()
        page.write_text("[missing example](missing/main.cpp)\n")
        registry = self.root / "test/docs/examples.json"
        registry.parent.mkdir(parents=True)
        registry.write_text("{}")
        errors = DOCS.check_structure(self.root)
        self.assertTrue(any("missing relative link: missing/main.cpp" in error for error in errors))

    def test_cpp_example_is_isolated_from_declaration(self):
        self.page.write_text("## 声明\n```cpp\nnot source\n```\n## 调用示例\n```cpp\nint value = 3;\n```\n")
        self.assertEqual(DOCS.example_source(self.page), "int value = 3;")

    def test_empty_example_and_tautology_are_rejected(self):
        self.page.write_text("## 调用示例\n```cpp\n(void)sizeof(int);\nis_same_v<selected, selected>;\n```\n")
        self.assertEqual(len(DOCS.content_errors(self.page)), 2)

    def test_corrupted_declaration_names_are_rejected(self):
        names = ("Ascinternal::Isnonnarrowingconvertible", "Zvfunctors::Viewsize",
                 "Detail::Scaledelementtype", "DECIMALDIG")
        for name in names:
            with self.subTest(name=name):
                self.page.write_text("## 声明\n```cpp\n" + name + ";\n```\n")
                self.assertTrue(DOCS.content_errors(self.page))
        self.page.write_text("## 声明\n```cpp\nusing result = Value;\n```\n")
        self.assertEqual(DOCS.content_errors(self.page), [])

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

    def test_registered_sdk_example_keeps_project_and_external_dependency_flags(self):
        registry = self.root / "test/docs/examples.json"
        registry.parent.mkdir(parents=True)
        registry.write_text(json.dumps({"page.md": {"standards": [17, 20], "mode": "simt", "sdk": "cann",
                                                   "include_flags": ["-I", "/project/include", "-DPROJECT_SIMT=1"],
                                                   "include_dirs": ["docs/examples/parallel"],
                                                   "required_headers": ["dlpack/dlpack.h"]}}))
        args = argparse.Namespace(root=self.root, standard=17, mode="simt", extra_include=[Path("/external")],
                                  npu_arch="dav-3510", compiler="bisheng", jobs=1)
        with patch.object(DOCS, "compile_example", side_effect=lambda task: task[2]):
            selected = DOCS.check_examples(args)[0]
        with patch.dict(os.environ, {"ASCEND_HOME_PATH": "/sdk"}):
            prepared = DOCS.prepared_spec(selected)
        self.assertEqual(prepared["include_flags"],
                         ["-I", "/project/include", "-DPROJECT_SIMT=1", "-I",
                          str(self.root / "docs/examples/parallel"), "-I", "/external", "-I", "/sdk/include"])
        self.assertEqual(prepared["required_headers"], ["dlpack/dlpack.h", "acl/acl.h"])
        command = DOCS.example_command(self.root, prepared, 17, "bisheng", self.root / "example.asc")
        self.assertIn("-DPROJECT_SIMT=1", command)
        self.assertIn("-c", command)
        self.assertNotIn("-lascendcl", command)
        self.assertFalse(any(flag.startswith("-Wl,") for flag in command))

    def test_runtime_sdk_example_retains_required_host_link_flags(self):
        with patch.dict(os.environ, {"ASCEND_HOME_PATH": "/sdk"}):
            prepared = DOCS.prepared_spec({"mode": "runtime", "sdk": "cann", "link_flags": ["-pthread"]})
        command = DOCS.example_command(self.root, prepared, 20, "c++", self.root / "example.cpp")
        self.assertIn("-pthread", command)
        self.assertIn("-lascendcl", command)
        self.assertNotIn("-c", command)

    def test_runtime_examples_stop_before_executing_later_cases(self):
        registry = self.root / "test/docs/examples.json"
        registry.parent.mkdir(parents=True)
        registry.write_text(json.dumps({name: {"standards": [17, 20], "mode": "runtime"}
                                        for name in ("a.md", "b.md", "c.md")}))
        args = argparse.Namespace(root=self.root, standard=17, mode="runtime", extra_include=[],
                                  npu_arch="dav-3510", compiler="c++", jobs=8)
        results = [{"page": "a.md", "status": "PASS"}, {"page": "b.md", "status": "FAIL"}]
        with patch.object(DOCS, "compile_example", side_effect=results) as execute:
            records = DOCS.check_examples(args)
        self.assertEqual(execute.call_count, 2)
        self.assertEqual([record["status"] for record in records], ["PASS", "FAIL", "NOT_RUN"])
        self.assertEqual(records[-1]["page"], "c.md")

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

    def test_expected_termination_requires_exact_exit_and_complete_marker_line(self):
        spec = {"expected_exit": 42, "expected_output": "EXPECTED_TERMINATION"}
        cases = [(42, "EXPECTED_TERMINATION\n", "PASS"), (0, "EXPECTED_TERMINATION\n", "FAIL"),
                 (42, "prefix EXPECTED_TERMINATION\n", "FAIL"), (-6, "EXPECTED_TERMINATION\n", "FAIL")]
        for code, output, expected in cases:
            with self.subTest(code=code, output=output):
                process = subprocess.CompletedProcess([], code, stdout=output, stderr="")
                with patch.object(DOCS.subprocess, "run", return_value=process):
                    result = DOCS.run_example(self.root / "binary", {}, "run", spec)
                self.assertEqual((result["status"], result["stage"]), (expected, "expected_termination"))
                self.assertEqual(result["returncode"], code)

    def test_expected_termination_registration_rejects_ambiguous_protocols(self):
        from api_docs_inventory import registered_page_errors
        page = "page.md"
        self.page.write_text("example")
        base = {"mode": "host", "standards": [17, 20], "expected_exit": 42}
        for update in ({}, {"expected_output": ""}, {"expected_output": "one\ntwo"},
                       {"expected_exit": 7}, {"mode": "runtime", "expected_output": "marker"}):
            with self.subTest(update=update):
                self.assertTrue(registered_page_errors(self.root, {page: dict(base, **update)}, {page}))
        self.assertEqual(registered_page_errors(self.root, {page: dict(base, expected_output="marker")}, {page}), [])

    def test_structure_gate_rejects_unregistered_examples(self):
        coverage = {"errors": [], "unregistered_pages": ["docs/zh/api/missing.md"]}
        with patch.object(DOCS, "check_writing", return_value=[]):
            with patch.object(DOCS, "coverage_inventory", return_value=coverage):
                errors = DOCS.check_structure(self.root)
        self.assertTrue(any("lack validation registration: 1" in error for error in errors))

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


    def write_cli_fixture(self, specs, expression="true"):
        registry = self.root / "test/docs/examples.json"
        registry.parent.mkdir(parents=True)
        registry.write_text(json.dumps(specs))
        for page in specs:
            target = self.root / page
            target.parent.mkdir(parents=True, exist_ok=True)
            text = "## 调用示例\n```cpp\nbool example() { return " + expression + "; }\n```\n"
            target.write_text(text)
            translated = self.root / page.replace("docs/zh/api/", "docs/en/api/")
            translated.parent.mkdir(parents=True, exist_ok=True)
            translated.write_text(text)

    def invoke_cli(self, arguments):
        report = self.root / "report.json"
        command = [sys.executable, str(CHECKER), "--root", str(self.root), "--examples", "--report", str(report)]
        result = subprocess.run([*command, *arguments], capture_output=True, text=True, check=False)
        return result.returncode, json.loads(report.read_text())

    def test_cli_reports_real_failure_and_does_not_claim_pass(self):
        page = "docs/zh/api/example.md"
        self.write_cli_fixture({page: {"standards": [17], "mode": "host", "expression": "example()"}}, "false")
        result, report = self.invoke_cli(["--require-all"])
        self.assertEqual(result, 1)
        self.assertEqual(report["status"], "FAIL")
        self.assertEqual(report["examples"][0]["compile_returncode"], 0)
        self.assertEqual(report["examples"][0]["returncode"], 1)

    def test_cli_distinguishes_optional_skip_from_strict_partial_execution(self):
        core = "docs/zh/api/core.md"
        optional = "docs/zh/api/optional.md"
        specs = {page: {"standards": [17], "mode": "host", "expression": "example()"}
                 for page in (core, optional)}
        specs[optional]["required_headers"] = ["asc_stl_intentionally_missing_dependency.h"]
        self.write_cli_fixture(specs)
        result, report = self.invoke_cli(["--dependencies", "optional", "--require-all"])
        self.assertEqual((result, report["status"], report["passed"]), (77, "NOT_APPLICABLE", 0))
        result, report = self.invoke_cli(["--require-all"])
        self.assertEqual((result, report["status"], report["not_applicable"]), (2, "PARTIAL", 1))
        result, report = self.invoke_cli(["--dependencies", "core", "--require-all"])
        self.assertEqual((result, report["status"], report["passed"]), (0, "PASS", 1))

    def test_empty_selection_and_not_run_are_not_success(self):
        self.write_cli_fixture({"docs/zh/api/example.md": {"standards": [20], "mode": "host"}})
        result, report = self.invoke_cli(["--standard", "17"])
        self.assertEqual((result, report["status"]), (77, "NOT_APPLICABLE"))
        report = DOCS.example_report([{"status": "PASS"}, {"status": "NOT_RUN"}])
        self.assertEqual(DOCS.example_exit_code(report, False), 1)

    def test_translation_checks_preserve_literal_content_and_reject_code_drift(self):
        from api_docs_inventory import code_tokens
        self.assertEqual(code_tokens('int x = 3; // Chinese comment'), code_tokens('int x=3; /* English */'))
        self.assertNotEqual(code_tokens("long long value"), code_tokens("longlong value"))
        self.assertNotEqual(code_tokens("x + + y"), code_tokens("x ++ y"))
        self.assertNotEqual(code_tokens('"a b"'), code_tokens('"ab"'))
        self.assertNotEqual(code_tokens('R"tag(a b)tag"'), code_tokens('R"tag(ab)tag"'))
        page = "docs/zh/api/example.md"
        self.write_cli_fixture({page: {"standards": [17], "mode": "host", "expression": "example()"}})
        (self.root / "docs/en/api/example.md").write_text("## Example\n```cpp\nbool example() { return false; }\n```\n")
        result, report = self.invoke_cli(["--require-all"])
        self.assertEqual((result, report["status"]), (1, "FAIL"))
        self.assertTrue(report["coverage"]["errors"])

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
