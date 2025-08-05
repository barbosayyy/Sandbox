A <b>work-in-progress</b> 3D Game Engine

## Features
- 3D forward rendering through OpenGL 3.3
- Input system for assigning input behavior to multiple objects
- Asset manifest registry tool
- (WIP) Custom pool memory allocator
- (WIP) Custom ECS
- Image loading (STB)
- Model and mesh loading (Assimp)
- Development UI (DearImGui)

## Screenshot
![Showroom](https://github.com/user-attachments/assets/74be3bdb-2dd8-40c2-929c-9e9b80fd89d0)
*This most recent experimental version features a deferred geometry buffer with position, normal and albedo+specular attachments*  

## Building
There is no automatic setup tool for the current toolchain so everything needs to be done manually.
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