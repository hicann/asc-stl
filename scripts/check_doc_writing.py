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

"""Deterministic checks for the public documentation writing rules."""
from pathlib import Path
import re

HEADING = re.compile(r"^(#{1,6}) (.+)$")
FENCE = re.compile(r"^\s*```")
RELATED = ("## 关联 API", "## 关联API", "## 相关比较接口")
REQUIRED_ORDER = ["产品支持情况", "功能说明", "函数原型", "声明", "参数说明", "数据类型",
                  "返回值说明", "约束说明", "关键特性说明", "调用示例", "关联 API", "关联API", "相关比较接口"]


def heading_errors(path: Path, index: int, lines: list[str], previous: int) -> tuple[int, list[str]]:
    heading = HEADING.match(lines[index])
    if not heading:
        return previous, []
    errors = []
    current = len(heading[1])
    if current > previous + 1:
        errors.append(f"{path}:{index + 1}: heading skips a level")
    if re.match(r"(?:[0-9]+[.、．]|[一二三四五六七八九十]+、)", heading[2]):
        errors.append(f"{path}:{index + 1}: manually numbered heading")
    if index + 1 < len(lines) and lines[index + 1].strip():
        errors.append(f"{path}:{index + 1}: blank line required after heading")
    return current, errors


def fence_errors(path: Path, index: int, lines: list[str], closing: bool) -> list[str]:
    errors = []
    if closing:
        if index + 1 < len(lines) and lines[index + 1].strip():
            errors.append(f"{path}:{index + 1}: blank line required after code fence")
        return errors
    if lines[index].strip() == "```":
        errors.append(f"{path}:{index + 1}: code fence needs a language")
    if index and lines[index - 1].strip():
        errors.append(f"{path}:{index + 1}: blank line required before code fence")
    return errors


def format_errors(path: Path) -> list[str]:
    raw = path.read_bytes()
    errors = [f"{path}: UTF-8 BOM"] if raw.startswith(b"\xef\xbb\xbf") else []
    lines = raw.decode("utf-8").splitlines()
    fenced = False
    level = 0
    for index, line in enumerate(lines):
        if FENCE.match(line):
            errors.extend(fence_errors(path, index, lines, fenced))
            fenced = not fenced
        elif not fenced:
            level, found = heading_errors(path, index, lines, level)
            errors.extend(found)
    return errors


def example_errors(path: Path, source: str) -> list[str]:
    errors = []
    if re.search(r"\busing\s+namespace\b", source):
        errors.append(f"{path}: using namespace in example")
    if re.search(r"\(void\)\s*[^;\n]+\([^;\n]*\)\s*;", source):
        errors.append(f"{path}: discarded call result in example")
    if re.search(r"void use_type\([^{}]*\)\s*\{\s*\(void\)\w+;\s*\}", source):
        errors.append(f"{path}: type-only placeholder example")
    # Narrow, proven case: these operations return a reference to their operand.
    # Do not infer lifetime merely from a variable name or reject external operands.
    functions = re.findall(r"decltype\(auto\)\s+\w+\(\)\s*\{([^{}]*)\}", source)
    for body in functions:
        locals_ = re.findall(r"\b(?:int|float|double|long|short|char)\s+(\w+)\s*(?:=|\{|;)", body)
        for name in locals_:
            operation = r"(?:forward(?:_like)?(?:<[^;]+>)?|as_const|move(?:_if_noexcept)?)"
            if re.search(r"return\s+[\w:]*" + operation + r"\(" + re.escape(name) + r"\)\s*;", body):
                errors.append(f"{path}: returning a local object through a reference-preserving operation")
    return errors


def api_section_errors(path: Path) -> list[str]:
    text = path.read_text(encoding="utf-8")
    if "## 调用示例" not in text:
        return []
    errors = []
    headings = re.findall(r"^## (.+)$", text, re.MULTILINE)
    required = ["产品支持情况", "功能说明", "约束说明", "调用示例"]
    if "函数原型" in headings:
        required += ["参数说明", "返回值说明"]
    for heading in required:
        if heading not in headings:
            errors.append(f"{path}: missing section: {heading}")
    if not any(heading in text for heading in RELATED):
        errors.append(f"{path}: missing related API section")
    order = [REQUIRED_ORDER.index(heading) for heading in headings if heading in REQUIRED_ORDER]
    if order != sorted(order):
        errors.append(f"{path}: API sections out of order")
    if "完整合同" in text:
        errors.append(f"{path}: internal contract wording")
    section = text.split("## 调用示例", 1)[1].split("\n## ", 1)[0]
    for source in re.findall(r"```cpp\n(.*?)\n```", section, re.DOTALL):
        errors.extend(example_errors(path, source))
    return errors


def normalized_title(value: str) -> str:
    return value.replace("`", "").replace("\\", "")


def navigation_errors(root: Path) -> list[str]:
    page = root / "docs/zh/api/README.md"
    if not page.exists():
        return []
    errors = []
    seen = set()
    for index, line in enumerate(page.read_text(encoding="utf-8").splitlines()):
        match = re.match(r"( *)- \[(.*)\]\(([^)]+)\)", line)
        if not match:
            continue
        target = (page.parent / match[3]).resolve()
        if target in seen:
            errors.append(f"{page}:{index + 1}: duplicate navigation target")
        seen.add(target)
        if len(match[1]) // 2 + 1 > 5:
            errors.append(f"{page}:{index + 1}: navigation exceeds five levels")
        if target.is_file():
            title = next((s[2:] for s in target.read_text(encoding="utf-8").splitlines() if s.startswith("# ")), "")
            if normalized_title(title) != normalized_title(match[2]):
                errors.append(f"{page}:{index + 1}: title differs from {match[3]}")
    return errors


def check_writing(root: Path) -> list[str]:
    errors = []
    paths = list((root / "docs").rglob("*.md"))
    paths += [p for p in (root / "README.md", root / "README_en.md", root / "CONTRIBUTING.md") if p.exists()]
    for path in sorted(paths):
        errors.extend(format_errors(path))
        if path.name not in ("README.md", "README_en.md") and "docs" in path.relative_to(root).parts:
            if not re.fullmatch(r"[a-z0-9_]+\.md", path.name):
                errors.append(f"{path}: filename must use lowercase words and underscores")
        if "api" in path.relative_to(root).parts:
            errors.extend(api_section_errors(path))
    errors.extend(navigation_errors(root))
    return errors
