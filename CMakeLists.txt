
# CMake Sandbox Engine build configuration root

cmake_minimum_required(VERSION 3.19)

project(Sandbox VERSION 0.1.0)

message("\nConfiguring CMake Project: ${PROJECT_NAME} ${PROJECT_VERSION}")
message("CMake Version: ${CMAKE_MINIMUM_REQUIRED_VERSION}")

include(CTest)

# Compiler configuration

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

if(CMAKE_CXX_COMPILER)
    message("C++ Compiler: ${CMAKE_CXX_COMPILER}")
    message("Compiler ID: " ${CMAKE_CXX_COMPILER_ID} " " ${CMAKE_CXX_COMPILER_VERSION})
    message("Standard: ${CMAKE_CXX_STANDARD}")
else()
    message(FATAL_ERROR "C++ compiler not found.")
endif()

# Project defines

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(SB_PLATFORM_WIN)
elseif()
    message(FATAL_ERROR "Other platforms not supported yet.")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(SB_BUILD_DEBUG)
endif()
    
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(SB_BUILD_RELEASE)
endif()
if(CMAKE_CXX_COMPILER STREQUAL clang++)
    add_compile_definitions(SB_COMPILER_CLANGPP)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message("For platform: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR} - ${CMAKE_BUILD_TYPE}")
# Temp
else()
    message(FATAL_ERROR "Platform: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR} not supported.")
endif()

option(BUILD_EDITOR "Build editor project" ON)
option(BUILD_GAME "Build game project" ON)
message("BUILD_EDITOR flag: " ${BUILD_EDITOR})
message("BUILD_GAME flag: " ${BUILD_GAME})

# Project directory variables

set(CM_SANDBOX_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CM_SANDBOX_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(CM_SANDBOX_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(CM_SANDBOX_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts)
set(CM_SANDBOX_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/code)

message("")

# ---

# Engine build configuration

add_subdirectory(code/src)

add_subdirectory(${CM_SANDBOX_VENDOR_DIR}/includes/imgui)

# Game build configuration

if(BUILD_GAME)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/game-debug)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/game-debug)
    endif()

    # Temp - Set on project creation
    set(CM_SANDBOX_GAME_PROJECT "SandboxGame")
    add_executable(${CM_SANDBOX_GAME_PROJECT} code/application/main.cpp)
    message("\nExecutable: Game\n")

    add_subdirectory(code/game)
    add_subdirectory(code/application)

    target_link_libraries(${CM_SANDBOX_GAME_PROJECT}
        # Engine & game source
        PRIVATE Sandbox_App

        # Third Parties
        PUBLIC imgui
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/glew32.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/assimp-vc143-mtd.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/glfw3.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/OpenGL32.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/yaml-cppd.lib
    )

    file(COPY ${CM_SANDBOX_VENDOR_DIR}/dlls/ DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CM_SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CM_SANDBOX_RESOURCES_DIR} DESTINATION ${CMAKE_BINARY_DIR})

    # Post-config scripts

    set(CM_SANDBOX_RUN_SCRIPTS     1)

    if(${CM_SANDBOX_RUN_SCRIPTS} EQUAL 1)
        message("Running Scripts:")
        if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
                message("generate_resource_manifest.py")
                execute_process(COMMAND python -O ${CM_SANDBOX_SCRIPTS_DIR}/generate_resource_manifest.py --cmake=1 --res_path=${CMAKE_BINARY_DIR})    
                file(COPY ${CM_SANDBOX_RESOURCES_DIR}/resource_manifest.yaml DESTINATION ${CMAKE_BINARY_DIR}/resources)
            endif()
    else()
        message("Scripts are disabled")
    endif()
endif()

# Engine build configuration

if(BUILD_EDITOR)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/editor-debug)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/editor-debug)
    endif()

    add_subdirectory(code/editor)
    add_executable(SandboxEditor code/editor/main.cpp)
    target_include_directories(SandboxEditor PRIVATE vendor/includes)
    message("\nExecutable: Editor\n")

    target_link_libraries(SandboxEditor
        PRIVATE Sandbox_Editor

        # Third Parties
        PUBLIC imgui
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/glew32.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/assimp-vc143-mtd.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/glfw3.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/OpenGL32.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/yaml-cppd.lib
    )

    file(COPY ${CM_SANDBOX_VENDOR_DIR}/dlls/ DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CM_SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_BINARY_DIR})
endif()

# ---

message("")