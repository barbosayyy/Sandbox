A <b>work-in-progress</b> 3D Game Engine  
Planned for Windows, macOS (Apple Silicon) and Linux

## Features
- 3D deferred rendering (OpenGL 3.3)
- Basic Input System
- Multiple supported asset formats
- On-demand asset management
- Custom ECS 
- Project Manager
- (WIP) Scene Editor
- (WIP) Custom memory management
- (WIP) C++ Scripting

## Planned Features

- 2D
- Audio support
- Physics
- Animation System
- Support for more asset formats

## Screenshot
![Showroom](https://github.com/user-attachments/assets/74be3bdb-2dd8-40c2-929c-9e9b80fd89d0)

## Getting Started - Windows

### Clone

```shell
git clone https://github.com/barbosayyy/Sandbox.git
```

1. Install and Add to the PATH environment variable (winget or scoop recommended):

[CMake](https://cmake.org/download/)

[LLVM (clang++)](https://github.com/llvm/llvm-project/releases)

[Ninja](https://github.com/ninja-build/ninja/releases)

### CMake

Generate build files (Release/Debug)
```
cd <repository path>
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_EDITOR=ON -S<repository path> -B<repository path>/build -G Ninja
```
Generate executable (Release/Debug)
```
cmake --build <repository path>/build --config Release --target all
```

### VS Code

Install the clangd and CMake extensions. Set the Clang x86-64-pc-windows-msvc as the CMake build kit and cmake.generator extension setting to "Ninja".
The BUILD_EDITOR and BUILD_GAME flags may be toggled using the `Set Build` task.

## macOS

1. Install Xcode Command Line Tools
```shell
xcode-select --install
```
2. Install Homebrew

```shell
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

3. Install Ninja

```shell
brew install ninja
```

4. Install the clangd and CMake extensions. Set CMake build kit to Clang++ and it should also use Ninja by default, otherwise add it to the CMake generator extension setting.
