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

"""Compare the real product with independent arbitrary-precision PCG arithmetic.

The fixed algorithm is the author's pcg64_oneseq, not setseq pcg64 or DXSM:
https://github.com/imneme/pcg-cpp/blob/428802d1a5634f96bcd0705fab379ff0113bcf13/include/pcg_random.hpp
Jump uses an exactly divisible geometric sum, rather than the product's
affine-pair composition. The product and its tests need no native int128 type.
"""

import argparse
import logging
from pathlib import Path
import random
import subprocess


LOGGER = logging.getLogger(__name__)
MODULUS = 1 << 128
MASK = (1 << 64) - 1
MULTIPLIER = (2549297995355413924 << 64) | 4865540595714422341
INCREMENT = (6364136223846793005 << 64) | 1442695040888963407
SEEDS = (0, 1, 42, 54, 0xCAFEF00DD15EA5E5, MASK)
SKIPS = (0, 1, 2, 63, 64, 1000, 1 << 32, 1 << 63, MASK)


def rotate(value, count):
    count %= 64
    return ((value >> count) | (value << ((64 - count) % 64))) & MASK


def output(state):
    return rotate(((state >> 64) ^ state) & MASK, state >> 122)


def initial(seed):
    return ((seed + INCREMENT) * MULTIPLIER + INCREMENT) % MODULUS


def advance(state, count):
    geometric = (pow(MULTIPLIER, count, (MULTIPLIER - 1) * MODULUS) - 1) // (MULTIPLIER - 1)
    return (pow(MULTIPLIER, count, MODULUS) * state + INCREMENT * geometric) % MODULUS


def sequence(seed, count):
    first = advance(initial(seed), count + 1)
    second = (first * MULTIPLIER + INCREMENT) % MODULUS
    return output(first), output(second)


def sequence_cases(generator):
    pairs = [(seed, count) for seed in SEEDS for count in SKIPS]
    pairs += [(generator.getrandbits(64), generator.getrandbits(64)) for _ in range(128)]
    return [("sequence", (seed, count, 0, 0), sequence(seed, count)) for seed, count in pairs]


def arithmetic_case(operation, words):
    upper_a, lower_a, upper_b, lower_b = words
    left = (upper_a << 64) | lower_a
    right = (upper_b << 64) | lower_b
    result = (left + right if operation == "add" else left * right) % MODULUS
    return operation, words, (result >> 64, result & MASK)


def cases():
    generator = random.Random(20261123)
    records = sequence_cases(generator)
    edges = (0, 1, (1 << 32) - 1, 1 << 32, 1 << 63, MASK - 1, MASK)
    words = [(a, b, b, a) for a in edges for b in edges]
    words += [tuple(generator.getrandbits(64) for _ in range(4)) for _ in range(10000)]
    for values in words:
        records.extend(arithmetic_case(operation, values) for operation in ("add", "multiply"))
    for count in range(128):
        value = generator.getrandbits(64)
        records.append(("rotate", (value, count, 0, 0), (0, rotate(value, count))))
    return records


def verify(executable):
    records = cases()
    data = "".join(f"{operation} {' '.join(map(str, words))}\n" for operation, words, _ in records)
    result = subprocess.run([str(executable)], input=data, capture_output=True, text=True, timeout=60, check=False)
    if result.returncode != 0:
        raise ValueError(f"product bridge failed ({result.returncode}): {result.stderr}")
    actual = result.stdout.splitlines()
    if len(actual) != len(records):
        raise ValueError(f"expected {len(records)} observations, got {len(actual)}")
    for index, (line, record) in enumerate(zip(actual, records)):
        operation, words, expected = record
        if tuple(map(int, line.split())) != expected:
            raise ValueError(f"case {index} {operation} {words}: expected {expected}, got {line}")
    LOGGER.info("PCG64 independent reference: %d observations passed", len(records))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--executable", type=Path, required=True)
    args = parser.parse_args()
    try:
        verify(args.executable.resolve())
    except (OSError, ValueError, subprocess.TimeoutExpired) as error:
        LOGGER.error("%s", error)
        return 1
    return 0


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    raise SystemExit(main())
