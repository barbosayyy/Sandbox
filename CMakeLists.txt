function(configure_compiler)

    if(CLANG_COMPILER)
        set(CMAKE_C_COMPILER "${CLANG_COMPILER}" CACHE STRING "C compiler" FORCE)
    endif()
    if(CLANGXX_COMPILER)
        set(CMAKE_CXX_COMPILER "${CLANGXX_COMPILER}" CACHE STRING "C++ compiler" FORCE)
    endif()

    # set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED On)
    set(CMAKE_CXX_EXTENSIONS Off)

    if(APPLE)
        add_compile_options(-stdlib=libc++)
        add_link_options(-stdlib=libc++)
    endif()

    if(CMAKE_CXX_COMPILER)
        message("C++ Compiler: ${CMAKE_CXX_COMPILER}")
        message("Compiler ID: " ${CMAKE_CXX_COMPILER_ID} " " ${CMAKE_CXX_COMPILER_VERSION})
        message("Standard: ${CMAKE_CXX_STANDARD}")
    else()
        message(FATAL_ERROR "C++ compiler not found.")
    endif()
endfunction()

function(configure_project_defines)
    
    # Platform & build type

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        add_compile_definitions(SB_PLATFORM_WIN)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        add_compile_definitions(SB_PLATFORM_MAC)
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_definitions(SB_BUILD_RELEASE)
    else()
        add_compile_definitions(SB_BUILD_DEBUG)
    endif()

    # C++ Compiler

    if(CMAKE_CXX_COMPILER STREQUAL clang++)
        add_compile_definitions(SB_COMPILER_CLANGCPP)
    endif()

    message("For platform: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR} - ${CMAKE_BUILD_TYPE}")
endfunction()

function(configure_project_variables)
    set(CM_SANDBOX_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
    set(CM_SANDBOX_GAME_DIR ${CM_SANDBOX_DIR}/SampleProject PARENT_SCOPE)
    set(CM_SANDBOX_EDITOR_DIR ${CM_SANDBOX_DIR}/SandboxEditor PARENT_SCOPE)
    set(CM_SANDBOX_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources PARENT_SCOPE)
    set(CM_SANDBOX_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts PARENT_SCOPE)
    set(CM_SANDBOX_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/code PARENT_SCOPE)
    set(CM_SANDBOX_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor PARENT_SCOPE)
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(CM_SANDBOX_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows64 PARENT_SCOPE)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CM_SANDBOX_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/macOS PARENT_SCOPE)
    endif()
endfunction()

###############################################

# CMake Sandbox Engine build configuration file

cmake_minimum_required(VERSION 3.16)

project(Sandbox VERSION 0.1.0)

message("\nConfiguring CMake Project: ${PROJECT_NAME} ${PROJECT_VERSION}")
message("CMake Version: ${CMAKE_MINIMUM_REQUIRED_VERSION}")

if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} platform not supported")
endif()

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(CTest)
include(FetchContent)

configure_compiler()

configure_project_defines()

# Flags for which projects to build
option(BUILD_EDITOR "Build editor project" OFF)
option(BUILD_GAME "Build game project" ON)

message("BUILD_EDITOR flag: " ${BUILD_EDITOR})
message("BUILD_GAME flag: " ${BUILD_GAME})

configure_project_variables()

message("")

# ---

# Main Source
    add_subdirectory(code/src)
    add_subdirectory(${CM_SANDBOX_VENDOR_DIR}/includes/smhasher)
    add_subdirectory(${CM_SANDBOX_VENDOR_DIR}/includes/imgui)

# Dependencies
    set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_deps)

    FetchContent_Declare(yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
    )
    FetchContent_MakeAvailable(yaml-cpp)

    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw)

    FetchContent_Declare(assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.4.3
    )
    set(ASSIMP_BUILD_TESTS OFF)
    set(ASSIMP_INSTALL OFF)
    set(ASSIMP_BUILD_DOCS OFF)
    set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(assimp)

    find_package(OpenGL REQUIRED)

# Game build configuration

if(BUILD_GAME)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CM_SANDBOX_GAME_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_GAME_DIR}/release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_GAME_DIR}/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_GAME_DIR}/release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_GAME_DIR}/debug)

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
        PUBLIC smhasher
        PUBLIC imgui
        PRIVATE  assimp
        PRIVATE  yaml-cpp
        PRIVATE  glfw
        PRIVATE  OpenGL::GL
    )
    
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(${CM_SANDBOX_GAME_PROJECT}
            PRIVATE ${CM_SANDBOX_LIB_DIR}/glew32s.lib
        )
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        target_link_libraries(${CM_SANDBOX_GAME_PROJECT}
            PRIVATE  ${CM_SANDBOX_LIB_DIR}/libGLEW.a
        )
    endif()
    # if(CMAKE_BUILD_TYPE STREQUAL "Release")
    #     file(COPY ${CM_SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE})
    # else()
        # file(COPY ${CM_SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
    # endif()
    # file(COPY ${CM_SANDBOX_VENDOR_DIR}/dlls/ DESTINATION ${CM_SANDBOX_GAME_DIR})

    # Post-config scripts

    set(CM_SANDBOX_RUN_SCRIPTS     0)

    if(${CM_SANDBOX_RUN_SCRIPTS} EQUAL 1)
        message("Running Configure Scripts:")
        if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
                # - Deprecated
                    message("generate_resource_manifest.py")
                    execute_process(COMMAND python -O ${CM_SANDBOX_SCRIPTS_DIR}/generate_resource_manifest.py --cmake=1 --res_path=${CMAKE_BINARY_DIR})    
                    file(COPY ${CM_SANDBOX_RESOURCES_DIR}/resource_manifest.yaml DESTINATION ${CMAKE_BINARY_DIR}/resources)
            endif()
    else()
        message("Configure Scripts are disabled")
    endif()
endif()

# Engine build configuration

if(BUILD_EDITOR)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CM_SANDBOX_EDITOR_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_EDITOR_DIR}/release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_EDITOR_DIR}/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_EDITOR_DIR}/release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_EDITOR_DIR}/debug)

    add_subdirectory(code/editor)
    add_executable(SandboxEditor code/editor/main.cpp)
    target_include_directories(SandboxEditor PRIVATE vendor/includes)
    message("\nExecutable: Editor\n")

    target_link_libraries(SandboxEditor
        PRIVATE Sandbox_Editor

        # Third Parties
        PUBLIC smhasher
        PUBLIC imgui
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/glew32.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/assimp-vc143-mtd.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/glfw3.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/OpenGL32.lib
        PRIVATE  ${CM_SANDBOX_VENDOR_DIR}/libs/yaml-cppd.lib
    )

    # if(CMAKE_BUILD_TYPE STREQUAL "Release")
    #     file(COPY ${CM_SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE})
    # else()
    #     file(COPY ${CM_SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
    # endif()
    # file(COPY ${CM_SANDBOX_VENDOR_DIR}/dlls/ DESTINATION ${CM_SANDBOX_EDITOR_DIR})
endif()

# ---

message("")