#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

echo "Address sanitizer: "
./clean.sh
./build_debug_asan.sh
./func_tests/scripts/func_tests.sh -v

echo "Memory sanitizer: "
./clean.sh
./build_debug_msan.sh
./func_tests/scripts/func_tests.sh -v

echo "Undefined behaviour sanitizer: "
./clean.sh
./build_debug_ubsan.sh
./func_tests/scripts/func_tests.sh -v
