#!/bin/bash

BUILD_DIR="out"

mkdir -p "$BUILD_DIR"

if [ ! -f "$BUILD_DIR/CMakeCache.txt" ]; then
  echo "Configuring project for the first time..."
  cmake -B "$BUILD_DIR" -S . -G Ninja  # Ninja is much faster for iterations
else
  echo "Build files exist. Skipping configuration step."
fi

echo "Building project..."
cmake --build "$BUILD_DIR" --parallel $(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

if [ $? -eq 0 ]; then
    echo "Done! [$(date +%T)]"
else
    echo "Build Failed."
    exit 1
fi
