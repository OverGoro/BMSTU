#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

./test_san.sh
./clean.sh

./build_debug.sh
./func_tests/scripts/func_tests.sh -v
./clean.sh

./build_release.sh
./func_tests/scripts/func_tests.sh -v
./clean.sh

./collect_coverage.sh
./clean.sh