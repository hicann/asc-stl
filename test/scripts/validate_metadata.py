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

import argparse
import json
import logging
from pathlib import Path
import re


ALLOWED_STATUSES = {
    "passed",
    "failed",
    "blocked_environment",
    "not_applicable",
    "not_implemented",
    "not_run",
}
FORBIDDEN_HEADER_PATTERNS = {
    "CUDA namespace": re.compile(r"\bcuda::"),
    "CUDA include": re.compile(r"[<\"]cuda/"),
    "NVIDIA namespace": re.compile(r"\bnv::"),
    "NVIDIA include": re.compile(r"[<\"]nv/"),
    "CCCL macro": re.compile(r"\b_CCCL_[A-Za-z0-9_]*"),
    "libcudacxx macro": re.compile(r"\b_LIBCUDACXX_[A-Za-z0-9_]*"),
    "retired ascend namespace": re.compile(r"ascend::std"),
    "retired ascend include": re.compile(r"[<\"]ascend/std/"),
    "retired ASCEND macro": re.compile(r"\b_ASCEND_[A-Za-z0-9_]*"),
    "retired unprefixed ASCEND macro": re.compile(r"\bASCEND_DEVICE_CODE\b"),
    "invalid device attribute": re.compile(r"__attribute__\s*\(\(\s*device\s*\)\)"),
    "retired ordinary API macro": re.compile(r"\b_ACCL_HOST_DEVICE\b"),
}
REQUIRED_TEST_BY_APPLICABILITY = {
    "host_header": "host_header",
    "host_semantic": "host_semantic",
    "device_header": "device_header",
    "device_compile": "device_compile",
    "cannsim_runtime": "cannsim_runtime",
}
EXPECTED_TEST_NAME = {
    "host_header": "header.host.{case_id}",
    "host_semantic": "semantic.host.{case_id}",
    "device_header": "header.device.{case_id}",
    "device_compile": "semantic.device.{case_id}",
    "cannsim_runtime": "semantic.cannsim.{case_id}",
}
REQUIRED_APPLICABILITY = {
    "host_header",
    "host_semantic",
    "device_header",
    "device_compile",
    "cannsim_runtime",
    "public_aggregation",
}
COMMIT_PATTERN = re.compile(r"[0-9a-f]{40}")
CANONICAL_CASE_FILES = {
    "host_semantic": Path("host.pass.cpp"),
    "device_compile": Path("device.compile.cpp"),
}
CANONICAL_CANNSIM_FILES = {
    Path("kernel.cpp"),
    Path("launcher.cpp"),
    Path("launcher.h"),
    Path("main.cpp"),
    Path("kernel_spec.json"),
}
PROHIBITED_CASE_FILES = {"CMakeLists.txt", "npu_lib.cmake", "run_cannsim_test.sh"}


def load_json(path: Path):
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise ValueError(f"cannot read valid JSON from {path}: {error}") from error


def add_unique(value, seen, label, errors):
    if value in seen:
        errors.append(f"duplicate {label}: {value}")
    seen.add(value)


def is_valid_target_api(api: str):
    if api.startswith("asc::std::"):
        return len(api) > len("asc::std::")
    if api.startswith("asc::"):
        return len(api) > len("asc::")
    if api.startswith("hw::"):
        return len(api) > len("hw::")
    return re.fullmatch(
        r"(?:[A-Z][A-Z0-9_]*|assert|offsetof|__accl_lib_<[A-Za-z0-9_]+>)",
        api,
    ) is not None


def get_case_identity(target: str):
    for prefix, public_group, internal_group in (
        ("asc/std/", "public", None),
        ("asc/", "public_entry", "extension"),
        ("hw/", "public_entry", "hw"),
    ):
        if not target.startswith(prefix):
            continue
        case_relative = target.removeprefix(prefix)
        if case_relative.endswith(".h"):
            case_relative = case_relative[:-2]
        if "/" not in case_relative and not case_relative.startswith("_"):
            case_relative = f"{public_group}/{case_relative}"
        elif internal_group:
            case_relative = f"{internal_group}/{case_relative}"
        return case_relative, case_relative.replace("/", ".")
    raise ValueError(f"unsupported ASC-STL header domain: {target}")


def validate_required_infrastructure(test_root: Path, errors):
    infrastructure_root = test_root / "infrastructure"
    required_infrastructure = {
        infrastructure_root / "header/header_host.cpp.in",
        infrastructure_root / "header/header_device.cpp.in",
        infrastructure_root / "cannsim/smoke/kernel.cpp",
        infrastructure_root / "cannsim/smoke/launcher.cpp",
        infrastructure_root / "cannsim/smoke/launcher.h",
        infrastructure_root / "cannsim/smoke/main.cpp",
        infrastructure_root / "cannsim/acl_runtime.h",
        test_root / "scripts/run_cannsim_test.sh",
        test_root / "scripts/test_cannsim_runner_failures.sh",
        test_root / "scripts/validate_metadata.py",
    }
    for path in sorted(required_infrastructure):
        if not path.is_file():
            errors.append(f"canonical test infrastructure is missing: {path.relative_to(test_root)}")


def validate_expected_case_files(test_root: Path, expected_case_files, errors):
    for path, applicability_key in sorted(expected_case_files.items()):
        if not path.is_file():
            errors.append(
                f"applicable {applicability_key} is missing canonical source: "
                f"{path.relative_to(test_root)}"
            )

    cases_root = test_root / "cases"
    actual_case_files = set()
    for pattern in ("host.pass.cpp", "device.compile.cpp"):
        actual_case_files.update(path for path in cases_root.rglob(pattern) if path.is_file())
    unexpected_case_files = sorted(actual_case_files - set(expected_case_files))
    for path in unexpected_case_files:
        errors.append(f"canonical semantic source has no applicable metadata mapping: {path.relative_to(test_root)}")


def is_allowed_case_file(relative_path: Path) -> bool:
    if relative_path in CANONICAL_CASE_FILES.values() or relative_path.parts[0] == "support":
        return True
    return (
        relative_path.parts[0] == "cannsim"
        and Path(*relative_path.parts[1:]) in CANONICAL_CANNSIM_FILES
    )


def validate_registered_case_files(test_root: Path, registered_case_roots, errors):
    cases_root = test_root / "cases"
    for path in sorted(candidate for candidate in cases_root.rglob("*") if candidate.is_file()):
        matching_roots = [root for root in registered_case_roots if path.is_relative_to(root)]
        if not matching_roots:
            errors.append(f"canonical case file has no metadata target mapping: {path.relative_to(test_root)}")
            continue
        case_root = max(matching_roots, key=lambda root: len(root.parts))
        relative_path = path.relative_to(case_root)
        if not is_allowed_case_file(relative_path):
            errors.append(f"unexpected file in canonical case bundle: {path.relative_to(test_root)}")


def get_cannsim_files(cannsim_root: Path):
    if not cannsim_root.is_dir():
        return set()
    return {path.relative_to(cannsim_root) for path in cannsim_root.iterdir() if path.is_file()}


def validate_cannsim_bundle(test_root: Path, cannsim_root: Path, errors):
    actual_files = get_cannsim_files(cannsim_root)
    for path in sorted(CANONICAL_CANNSIM_FILES - actual_files):
        errors.append(
            "applicable cannsim_runtime is missing canonical source: "
            f"{(cannsim_root / path).relative_to(test_root)}"
        )
    for path in sorted(actual_files - CANONICAL_CANNSIM_FILES):
        relative = (cannsim_root / path).relative_to(test_root)
        errors.append(f"unexpected file in canonical cannsim bundle: {relative}")

    spec_path = cannsim_root / "kernel_spec.json"
    if not spec_path.is_file():
        return
    try:
        spec = load_json(spec_path)
    except ValueError as error:
        errors.append(str(error))
        return
    if not isinstance(spec, dict) or not spec:
        errors.append(f"{spec_path.relative_to(test_root)}: kernel spec must be a non-empty object")


def validate_cannsim_cases(test_root: Path, expected_cannsim_cases, errors):
    cases_root = test_root / "cases"
    actual_cannsim_cases = {path for path in cases_root.rglob("cannsim") if path.is_dir()}
    for cannsim_root in sorted(expected_cannsim_cases):
        validate_cannsim_bundle(test_root, cannsim_root, errors)

    for cannsim_root in sorted(actual_cannsim_cases - expected_cannsim_cases):
        errors.append(
            "canonical cannsim bundle has no applicable metadata mapping: "
            f"{cannsim_root.relative_to(test_root)}"
        )


def validate_prohibited_case_files(test_root: Path, errors):
    cases_root = test_root / "cases"
    for path in cases_root.rglob("*"):
        if path.is_file() and path.name in PROHIBITED_CASE_FILES:
            errors.append(f"per-case infrastructure is prohibited: {path.relative_to(test_root)}")


def validate_case_layout(
    test_root: Path,
    registered_case_roots,
    expected_case_files,
    expected_cannsim_cases,
    errors,
):
    validate_required_infrastructure(test_root, errors)
    validate_expected_case_files(test_root, expected_case_files, errors)
    validate_registered_case_files(test_root, registered_case_roots, errors)
    validate_cannsim_cases(test_root, expected_cannsim_cases, errors)
    validate_prohibited_case_files(test_root, errors)


def validate_header_rules(path: Path, relative_path: str, canonical_copyright: str, errors):
    text = path.read_text(encoding="utf-8")
    leading = re.match(r"\A\s*(/\*.*?\*/)", text, re.DOTALL)
    leading_text = leading.group(1) if leading else ""
    if (
        leading_text.count("Apache License, Version 2.0") != 1
        or leading_text.count("Copyright 2026") != 1
        or leading_text.count(canonical_copyright) != 1
    ):
        errors.append(f"{relative_path}: missing the canonical repository Apache-2.0 copyright header")
    elif leading:
        second = re.match(r"\s*(/\*.*?\*/)", text[leading.end():], re.DOTALL)
        if second and "Copyright 2026" in second.group(1) and "Apache License, Version 2.0" in second.group(1):
            errors.append(f"{relative_path}: duplicate repository copyright header")

    for label, pattern in FORBIDDEN_HEADER_PATTERNS.items():
        if pattern.search(text):
            errors.append(f"{relative_path}: contains forbidden {label}")

    for include in re.findall(r"^\s*#\s*include\s+([^\s]+)", text, re.MULTILINE):
        if re.match(r'"(?:asc/std|asc|hw)/', include):
            errors.append(f"{relative_path}: project includes must use angle brackets: {include}")


def read_canonical_copyright(include_root: Path, errors):
    author_file = include_root.parent / ".author"
    try:
        author = author_file.read_text(encoding="utf-8").strip()
    except OSError as error:
        errors.append(f"cannot read canonical repository author from {author_file}: {error}")
        return None
    if not author:
        errors.append(f"canonical repository author is empty: {author_file}")
        return None
    return f"Copyright 2026 {author}"


def validate_cccl_baseline(manifest, errors):
    cccl_baseline = manifest.get("cccl_baseline")
    if not isinstance(cccl_baseline, dict):
        errors.append("headers.json: cccl_baseline must be an object")
        return
    if not COMMIT_PATTERN.fullmatch(str(cccl_baseline.get("commit", ""))):
        errors.append("headers.json: cccl_baseline.commit must be a full Git commit")
    if not isinstance(cccl_baseline.get("version"), str) or not cccl_baseline["version"]:
        errors.append("headers.json: cccl_baseline.version must be a non-empty string")


def validate_migration_source(manifest, errors):
    migration_source = manifest.get("migration_source")
    if not isinstance(migration_source, dict):
        errors.append("headers.json: migration_source must be an object")
        return
    repository = migration_source.get("repository")
    if not isinstance(repository, str) or not repository:
        errors.append("headers.json: migration_source.repository must be a non-empty string")
    checkout_commit = migration_source.get("checkout_commit", "")
    if not COMMIT_PATTERN.fullmatch(str(checkout_commit)):
        errors.append("headers.json: migration_source.checkout_commit must be a full Git commit")


def validate_runtime_backend(manifest, errors):
    expected = {
        "name": "cannsim",
        "toolkit_version": "9.0.0",
        "toolkit_sha256": "946d7bfd3c3f7b45e511126d67507d1dba57004243a18175148c582106b0dfa1",
        "compile_soc": "Ascend950PR_9599",
        "simulator_soc": "Ascend950",
        "smoke_test": "cannsim.smoke",
        "fixture": "asc_stl_cannsim_ready",
    }
    if manifest.get("runtime_backend") != expected:
        errors.append("headers.json: runtime_backend must record the reviewed cannsim backend and fixture")


def validate_top_level_metadata(manifest, exclusions, errors):
    if manifest.get("schema_version") != 1:
        errors.append("headers.json: unsupported schema_version")
    if exclusions.get("schema_version") != 1:
        errors.append("header_exclusions.json: unsupported schema_version")
    validate_cccl_baseline(manifest, errors)
    validate_migration_source(manifest, errors)
    validate_runtime_backend(manifest, errors)

    expected_categories = {
        "implementation_fragment",
        "paired_header",
        "generated_header",
        "external_header",
        "special_context",
    }
    allowed_categories = set(exclusions.get("allowed_categories", []))
    if allowed_categories != expected_categories:
        errors.append("header_exclusions.json: allowed_categories must match the reviewed category set")
    return allowed_categories


def validate_header_identity(header, prefix, state, errors):
    header_id = header.get("id")
    source = header.get("source")
    source_commit = header.get("source_commit")
    target = header.get("target")
    if not isinstance(header_id, str) or not re.fullmatch(r"[a-z][a-z0-9_]*", header_id):
        errors.append(f"{prefix}: id must match [a-z][a-z0-9_]*")
    else:
        add_unique(header_id, state["ids"], "header id", errors)
    valid_source = isinstance(source, str) and re.match(
        r"include/(?:asc/std|asc|hw)/", source
    )
    if not valid_source:
        errors.append(f"{prefix}: source must be an ASC_AGENT asc_stl include path")
    if not COMMIT_PATTERN.fullmatch(str(source_commit or "")):
        errors.append(f"{prefix}: source_commit must be a full Git commit")
    if not isinstance(target, str) or not re.match(r"(?:asc/std|asc|hw)/", target):
        errors.append(f"{prefix}: target must start with asc/std/, asc/, or hw/")
        return None
    if source != f"include/{target}":
        errors.append(f"{prefix}: source and target header paths do not correspond")
    add_unique(target, state["registered_paths"], "header target", errors)
    return target


def resolve_header_paths(target, prefix, roots, copyright_text, errors):
    include_root = roots["include"]
    test_root = roots["test"]
    case_relative, case_id = get_case_identity(target)
    target_path = include_root / target
    if not target_path.resolve().is_relative_to(include_root.resolve()):
        errors.append(f"{prefix}: target escapes the include root: {target}")
        return None
    if not target_path.is_file():
        errors.append(f"{prefix}: target does not exist: {target}")
    else:
        validate_header_rules(target_path, target, copyright_text, errors)
    return {
        "target": target,
        "target_path": target_path,
        "case_id": case_id,
        "case_root": test_root / "cases" / case_relative,
    }


def validate_header_dependencies(header, prefix, resolved, state, errors):
    dependencies = header.get("dependencies")
    valid_list = isinstance(dependencies, list) and all(isinstance(item, str) for item in dependencies)
    if not valid_list:
        errors.append(f"{prefix}: dependencies must be a string list")
        return
    state["recorded_dependencies"].append((prefix, resolved["target"], dependencies))
    target_path = resolved["target_path"]
    if not target_path.is_file():
        return
    header_text = target_path.read_text(encoding="utf-8")
    included = re.findall(
        r'^\s*#\s*include\s+<(?P<path>(?:asc/std|asc|hw)/[^>]+)>',
        header_text,
        re.MULTILINE,
    )
    if dependencies != included:
        errors.append(
            f"{prefix}: dependencies do not match direct ASC-STL includes: "
            f"recorded={dependencies}, actual={included}"
        )


def validate_header_provenance(header, prefix, errors):
    apis = header.get("apis")
    upstream = header.get("upstream")
    upstream_tests = header.get("upstream_tests")
    if not isinstance(apis, list) or not all(isinstance(api, str) and api for api in apis):
        errors.append(f"{prefix}: apis must be a string list")
    elif any(not is_valid_target_api(api) for api in apis):
        errors.append(f"{prefix}: APIs must use an approved ASC-STL target domain")
    if not isinstance(upstream, str) or not re.match(
        r"libcudacxx/include/(?:cuda/std|cuda|nv)/", upstream
    ):
        errors.append(f"{prefix}: upstream must be a CCCL repository-relative include path")
    valid_tests = isinstance(upstream_tests, list) and all(
        isinstance(test, str) and test for test in upstream_tests
    )
    if not valid_tests:
        errors.append(f"{prefix}: upstream_tests must be a string list")


def validate_test_applicability(header, prefix, resolved, state, test_root):
    errors = state["errors"]
    tests = header.get("tests")
    applicability = header.get("applicability")
    if not isinstance(tests, dict) or not isinstance(applicability, dict):
        errors.append(f"{prefix}: tests and applicability must be objects")
        return False
    valid_applicability = set(applicability) == REQUIRED_APPLICABILITY and all(
        isinstance(value, bool) for value in applicability.values()
    )
    if not valid_applicability:
        errors.append(f"{prefix}: applicability must contain the complete reviewed boolean key set")
    validate_test_names(tests, applicability, prefix, resolved["case_id"], state)
    register_case_sources(applicability, prefix, resolved["case_root"], state, test_root)
    return True


def validate_test_names(tests, applicability, prefix, case_id, state):
    errors = state["errors"]
    for applicability_key, test_key in REQUIRED_TEST_BY_APPLICABILITY.items():
        if applicability.get(applicability_key) is True and not tests.get(test_key):
            errors.append(f"{prefix}: applicable {applicability_key} is missing tests.{test_key}")
        if applicability.get(applicability_key) is False and test_key in tests:
            errors.append(f"{prefix}: inapplicable {applicability_key} must not map tests.{test_key}")
        if test_key in tests:
            expected_name = EXPECTED_TEST_NAME[test_key].format(case_id=case_id)
            if tests[test_key] != expected_name:
                errors.append(f"{prefix}: tests.{test_key} must use stable name {expected_name}")
    unknown_keys = sorted(set(tests) - set(REQUIRED_TEST_BY_APPLICABILITY.values()))
    if unknown_keys:
        errors.append(f"{prefix}: tests contains unknown mappings: {', '.join(unknown_keys)}")
    for test_name in tests.values():
        if not isinstance(test_name, str) or not test_name:
            errors.append(f"{prefix}: test names must be non-empty strings")
        else:
            add_unique(test_name, state["test_names"], "CTest name", errors)


def register_case_sources(applicability, prefix, case_root, state, test_root):
    errors = state["errors"]
    for applicability_key, relative_path in CANONICAL_CASE_FILES.items():
        source_path = case_root / relative_path
        if applicability.get(applicability_key) is True:
            state["expected_case_files"][source_path] = applicability_key
        elif source_path.is_file():
            relative = source_path.relative_to(test_root)
            errors.append(f"{prefix}: inapplicable {applicability_key} has canonical source {relative}")
    cannsim_root = case_root / "cannsim"
    if applicability.get("cannsim_runtime") is True:
        state["expected_cannsim_cases"].add(cannsim_root)
    elif cannsim_root.is_dir():
        relative = cannsim_root.relative_to(test_root)
        errors.append(f"{prefix}: inapplicable cannsim_runtime has canonical bundle {relative}")


def validate_optional_header_fields(header, prefix, target_path, errors):
    implementation = header.get("internal_implementation")
    if implementation is not None:
        valid_name = isinstance(implementation, str) and re.fullmatch(r"_ACCL_[A-Z0-9_]+", implementation)
        if not valid_name:
            errors.append(f"{prefix}: internal_implementation must name an _ACCL_* identifier")
        elif target_path.is_file() and implementation not in target_path.read_text(encoding="utf-8"):
            errors.append(f"{prefix}: internal_implementation is not present in the target header")
    validate_gate_status(header.get("gate_status"), prefix, errors)
    validate_last_validation(header.get("last_validation"), prefix, errors)


def validate_gate_status(gate_status, prefix, errors):
    if gate_status is None:
        return
    if not isinstance(gate_status, dict) or not gate_status:
        errors.append(f"{prefix}: gate_status must be a non-empty object")
        return
    for gate, result in gate_status.items():
        if not isinstance(result, dict) or result.get("status") not in ALLOWED_STATUSES:
            errors.append(f"{prefix}: {gate} has an unknown status")
        elif not isinstance(result.get("evidence"), str) or not result["evidence"].strip():
            errors.append(f"{prefix}: {gate} must record evidence or a reason")


def validate_last_validation(validation, prefix, errors):
    if validation is None:
        return
    if not isinstance(validation, dict):
        errors.append(f"{prefix}: last_validation must be an object")
    elif validation.get("result") not in ALLOWED_STATUSES:
        errors.append(f"{prefix}: last_validation has an unknown result")
    elif not isinstance(validation.get("notes"), str) or not validation["notes"].strip():
        errors.append(f"{prefix}: last_validation must record notes")


def validate_header_entry(header, index, state, roots, copyright_text):
    errors = state["errors"]
    prefix = f"headers[{index}]"
    if not isinstance(header, dict):
        errors.append(f"{prefix}: header entries must be objects")
        return
    target = validate_header_identity(header, prefix, state, errors)
    if target is None:
        return
    resolved = resolve_header_paths(target, prefix, roots, copyright_text, errors)
    if resolved is None:
        return
    state["registered_case_roots"].add(resolved["case_root"])
    validate_header_dependencies(header, prefix, resolved, state, errors)
    validate_header_provenance(header, prefix, errors)
    validate_test_applicability(header, prefix, resolved, state, roots["test"])
    validate_optional_header_fields(header, prefix, resolved["target_path"], errors)


def validate_dependencies(recorded_dependencies, registered_paths, errors):
    for prefix, target, dependencies in recorded_dependencies:
        for dependency in dependencies:
            if dependency == target:
                errors.append(f"{prefix}: a header cannot depend on itself: {dependency}")
            elif dependency not in registered_paths:
                errors.append(f"{prefix}: dependency is not a registered header: {dependency}")


def validate_exclusion_entry(exclusion, index, include_root, allowed, state):
    registered = state["registered_paths"]
    excluded = state["excluded_paths"]
    errors = state["errors"]
    prefix = f"exclusions[{index}]"
    if not isinstance(exclusion, dict):
        errors.append(f"{prefix}: exclusion entries must be objects")
        return
    target = exclusion.get("target")
    if not isinstance(target, str) or not re.match(r"(?:asc/std|asc|hw)/", target):
        errors.append(f"{prefix}: target must start with asc/std/, asc/, or hw/")
        return
    add_unique(target, excluded, "excluded target", errors)
    target_path = include_root / target
    if not target_path.resolve().is_relative_to(include_root.resolve()):
        errors.append(f"{prefix}: target escapes the include root: {target}")
        return
    if exclusion.get("category") not in allowed:
        errors.append(f"{prefix}: invalid exclusion category: {exclusion.get('category')}")
    reason = exclusion.get("reason")
    if not isinstance(reason, str) or not reason.strip():
        errors.append(f"{prefix}: exclusions require a reviewable reason")
    if target in registered:
        errors.append(f"{prefix}: a header cannot be both registered and excluded: {target}")
    if not target_path.is_file():
        errors.append(f"{prefix}: excluded target does not exist: {target}")


def validate_header_coverage(include_root, registered, excluded, errors):
    actual_headers = {path.relative_to(include_root).as_posix() for path in include_root.rglob("*") if path.is_file()}
    unaccounted = sorted(actual_headers - registered - excluded)
    stale = sorted((registered | excluded) - actual_headers)
    if unaccounted:
        errors.append("headers missing from metadata or exclusions: " + ", ".join(unaccounted))
    if stale:
        errors.append("metadata paths missing from the include tree: " + ", ".join(stale))


def make_validation_state(errors):
    return {
        "ids": set(),
        "registered_paths": set(),
        "test_names": set(),
        "recorded_dependencies": [],
        "registered_case_roots": set(),
        "expected_case_files": {},
        "expected_cannsim_cases": set(),
        "excluded_paths": set(),
        "errors": errors,
    }


def validate(manifest_path: Path, exclusions_path: Path, include_root: Path, test_root: Path):
    errors = []
    copyright_text = read_canonical_copyright(include_root, errors)
    if copyright_text is None:
        return errors
    manifest = load_json(manifest_path)
    exclusions = load_json(exclusions_path)
    allowed_categories = validate_top_level_metadata(manifest, exclusions, errors)

    headers = manifest.get("headers")
    exclusion_entries = exclusions.get("exclusions")
    if not isinstance(headers, list):
        return errors + ["headers.json: headers must be an array"]
    if not isinstance(exclusion_entries, list):
        return errors + ["header_exclusions.json: exclusions must be an array"]

    state = make_validation_state(errors)
    roots = {"include": include_root, "test": test_root}
    for index, header in enumerate(headers):
        validate_header_entry(header, index, state, roots, copyright_text)
    validate_dependencies(state["recorded_dependencies"], state["registered_paths"], errors)

    for index, exclusion in enumerate(exclusion_entries):
        validate_exclusion_entry(
            exclusion,
            index,
            include_root,
            allowed_categories,
            state,
        )
    validate_header_coverage(include_root, state["registered_paths"], state["excluded_paths"], errors)
    validate_case_layout(
        test_root,
        state["registered_case_roots"],
        state["expected_case_files"],
        state["expected_cannsim_cases"],
        errors,
    )
    return errors


def main():
    logging.basicConfig(level=logging.INFO, format="%(levelname)s: %(message)s")
    logger = logging.getLogger(__name__)
    parser = argparse.ArgumentParser(description="Validate ASC-STL header gate metadata and static rules.")
    parser.add_argument("--manifest", required=True, type=Path)
    parser.add_argument("--exclusions", required=True, type=Path)
    parser.add_argument("--include-root", required=True, type=Path)
    parser.add_argument("--test-root", required=True, type=Path)
    args = parser.parse_args()

    try:
        errors = validate(
            args.manifest.resolve(),
            args.exclusions.resolve(),
            args.include_root.resolve(),
            args.test_root.resolve(),
        )
    except ValueError as error:
        errors = [str(error)]

    if errors:
        for error in errors:
            logger.error("%s", error)
        return 1
    logger.info("ASC-STL metadata and static rules passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
