#!/bin/bash

BUILD_DIR="out"

if [ ! -d "$BUILD_DIR" ]; then
  echo "Creating build directory..."
  mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR" || exit

echo "Configuring project..."
cmake ..

echo "Building project..."
cmake --build . --parallel $(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

if [ $? -eq 0 ]; then
    echo "---------------------------"
    echo "Build Successful!"
    echo "Executable is located in: $BUILD_DIR/"
else
    echo "Build Failed."
    exit 1
fi
