cmake_minimum_required(VERSION 3.10)
project(Sandbox VERSION 0.1.0)

include(CTest)

# C++ Standard 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_CXX_EXTENSIONS Off)

# Dirs

set(Build_Dir ${CMAKE_CURRENT_SOURCE_DIR})

set(Vendor_Dir ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(Resources_Dir ${CMAKE_CURRENT_SOURCE_DIR}/resources)

add_subdirectory(vendor/includes/imgui)

# Def

add_compile_definitions(SANDBOX_ENGINE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(RELEASE_MODE)
endif()

# Linking

file(GLOB_RECURSE Lib_Sandbox CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)
list(FILTER Lib_Sandbox EXCLUDE REGEX "src/application.cpp")
add_library(Sandbox_Src STATIC ${Lib_Sandbox})

add_executable(Sandbox src/application.cpp)
target_link_libraries(Sandbox PRIVATE Sandbox_Src)

target_include_directories(Sandbox_Src PUBLIC vendor/includes)
target_include_directories(Sandbox PUBLIC vendor/includes)

file(COPY ${Vendor_Dir}/dlls/ DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${Resources_Dir} DESTINATION ${CMAKE_BINARY_DIR})

#include_directories(vendor/includes)


target_link_libraries(Sandbox 
    PRIVATE "D:/Programming/Cpp/Sandboxvscode/vendor/libs/glew32.lib"
    PRIVATE "D:/Programming/Cpp/Sandboxvscode/vendor/libs/glfw3.lib"
    PRIVATE "D:/Programming/Cpp/Sandboxvscode/vendor/libs/assimp-vc143-mtd.lib"
    PRIVATE "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64/OpenGL32.Lib"
    PRIVATE Sandbox_Src
    PUBLIC imgui
    )
