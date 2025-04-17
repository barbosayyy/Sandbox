# Sandbox Renderer

## Overview
A <b>work-in-progress</b> 3D Game Engine. Currently supports OpenGL.

## Building

### Required

Only builds to Windows at the moment

1. Install and Add to the PATH environment variable:

[Python](https://www.python.org/downloads/)

[CMake](https://cmake.org/download/)

[LLVM Clang](https://github.com/llvm/llvm-project/releases)

[Ninja](https://github.com/ninja-build/ninja/releases) build system

2. Install yaml python module ```pip install pyyaml``` 

### Clone

```shell
git clone https://github.com/barbosayyy/Sandbox.git
```

### Build with CMake

Go to repository path
```
cd <repository path>
```
Generate build files (Release/Debug)
```
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -S<repository path> -B<repository path>/build -G Ninja
```
Generate executable (Release/Debug)
```
cmake --build <repository path>/build --config Release --target all
```

### Developing in VS Code (Windows)

1. Set cmake.generator extension setting to "Ninja"