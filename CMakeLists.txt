function(configure_compiler)

    if(CLANG_COMPILER)
        set(CMAKE_C_COMPILER "${CLANG_COMPILER}" CACHE STRING "C compiler" FORCE PARENT_SCOPE)
    endif()
    if(CLANGXX_COMPILER)
        set(CMAKE_CXX_COMPILER "${CLANGXX_COMPILER}" CACHE STRING "C++ compiler" FORCE PARENT_SCOPE)
    endif()

    set(CMAKE_CXX_STANDARD 20 PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED On PARENT_SCOPE)
    set(CMAKE_CXX_EXTENSIONS Off PARENT_SCOPE)
    
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

###############################################

function(configure_project_defines)
    
    # Platform & build type

    if(WIN32)
        add_compile_definitions(SB_PLATFORM_WIN)
    elseif(APPLE)
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

###############################################

function(configure_project_variables)
    set(CM_SANDBOX_OUTPUT_GAME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SampleProject PARENT_SCOPE)
    set(CM_SANDBOX_OUTPUT_EDITOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SandboxEditor PARENT_SCOPE)
    set(CM_SANDBOX_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts PARENT_SCOPE)
    set(CM_SANDBOX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/code PARENT_SCOPE)
    set(CM_SANDBOX_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor PARENT_SCOPE)
    if(WIN32)
    set(CM_SANDBOX_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows64 PARENT_SCOPE)
    elseif(APPLE)
    set(CM_SANDBOX_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/macOS PARENT_SCOPE)
    endif()
    set(CM_SANDBOX_OUTPUT_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build PARENT_SCOPE)
endfunction()

###############################################

# CMake Sandbox Engine build configuration file

cmake_minimum_required(VERSION 3.16)

project(Sandbox VERSION 0.1.0)

message("\nConfiguring CMake Project: ${PROJECT_NAME} ${PROJECT_VERSION}")
message("CMake Version: ${CMAKE_MINIMUM_REQUIRED_VERSION}")

if(NOT WIN32 AND NOT APPLE)
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} platform not supported")
endif()

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(CTest)
include(FetchContent)

configure_compiler()

configure_project_defines()

# Flags for which projects to build
option(BUILD_EDITOR "Build editor project" ON)
option(BUILD_GAME "Build game project" OFF) # Deprecated

message("BUILD_EDITOR flag: " ${BUILD_EDITOR})
message("BUILD_GAME flag: " ${BUILD_GAME})

configure_project_variables()

message("")

# ---

# Dependencies
    add_subdirectory(${CM_SANDBOX_VENDOR_DIR}/includes/smhasher)
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
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
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

    if(WIN32)
        find_library(GLEWS
            NAMES glew32s
            PATHS "${CM_SANDBOX_VENDOR_DIR}/lib/glew/Windows64"
            REQUIRED
        )

    elseif(APPLE)
        find_library(GLEWS
            NAMES libGLEW.a
            PATHS "${CM_SANDBOX_VENDOR_DIR}/lib/glew/macOS"
            REQUIRED
        )
        
    endif()

    find_package(OpenGL REQUIRED)

    add_subdirectory(${CM_SANDBOX_VENDOR_DIR}/includes/imgui)

add_subdirectory(code/src)

# Export lib and API headers to external projects' look-up directory (currently only using Development dir)
    install(TARGETS SbEngineCore SbAPI
        EXPORT SbEngineCoreTargets
        ARCHIVE DESTINATION ${CM_SANDBOX_OUTPUT_BUILD_DIR}/lib
        INCLUDES DESTINATION ${CM_SANDBOX_OUTPUT_BUILD_DIR}/include
    )
    install(DIRECTORY ${CM_SANDBOX_SOURCE_DIR}/api
        DESTINATION ${CM_SANDBOX_OUTPUT_BUILD_DIR}/include
        FILES_MATCHING
        PATTERN "*.h"
    )

# add_library(Sandbox_API INTERFACE)
# target_include_directories(Sandbox_API INTERFACE
#     ${CMAKE_CURRENT_SOURCE_DIR}/code/api
# )
# target_link_libraries(Sandbox_Engine PUBLIC Sandbox_API)

# Game build configuration

    # NOTE Game building will be deprecated in favor of having a detached project from the engine, compilation of a game project will be done externally
    
    # if(BUILD_GAME)

    #     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CM_SANDBOX_OUTPUT_GAME_DIR})
    #     set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_OUTPUT_GAME_DIR}/release)
    #     set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_OUTPUT_GAME_DIR}/debug)
    #     set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_OUTPUT_GAME_DIR}/release)
    #     set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_OUTPUT_GAME_DIR}/debug)

    #     # Temp - Set on project creation
    #     set(CM_SANDBOX_GAME_PROJECT "SandboxGame")
    #     add_executable(${CM_SANDBOX_GAME_PROJECT} code/application/main.cpp)
    #     message("\nExecutable: Game\n")

    #     add_subdirectory(code/game)
    #     add_subdirectory(code/application)

    #     target_compile_definitions(${CM_SANDBOX_GAME_PROJECT} PRIVATE GLEW_STATIC)
    #     target_link_libraries(${CM_SANDBOX_GAME_PROJECT}
    #         # Engine & game source
    #         PRIVATE Sandbox_App

    #         # Third Parties
    #         PUBLIC  smhasher
    #         PUBLIC  imgui
    #         PRIVATE assimp
    #         PRIVATE yaml-cpp
    #         PUBLIC glfw
    #         PUBLIC ${GLEWS}
    #         PRIVATE OpenGL::GL
    #     )

    #     # Post-config scripts

    #     set(CM_SANDBOX_RUN_SCRIPTS     0)

    #     if(${CM_SANDBOX_RUN_SCRIPTS} EQUAL 1)
    #         message("Running Configure Scripts:")
    #         if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    #                 # - Deprecated
    #                     message("generate_resource_manifest.py")
    #                     execute_process(COMMAND python -O ${CM_SANDBOX_SCRIPTS_DIR}/generate_resource_manifest.py --cmake=1 --res_path=${CMAKE_BINARY_DIR})    
    #                     file(COPY ${CM_SANDBOX_RESOURCES_DIR}/resource_manifest.yaml DESTINATION ${CMAKE_BINARY_DIR}/resources)
    #             endif()
    #     else()
    #         message("Configure Scripts are disabled")
    #     endif()
    # endif()

# Engine build configuration

if(BUILD_EDITOR)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CM_SANDBOX_OUTPUT_EDITOR_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_OUTPUT_EDITOR_DIR}/release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_OUTPUT_EDITOR_DIR}/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CM_SANDBOX_OUTPUT_EDITOR_DIR}/release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CM_SANDBOX_OUTPUT_EDITOR_DIR}/debug)

    add_subdirectory(code/editor)
    add_executable(SandboxEditor code/editor/main.cpp)
    message("\nExecutable: Editor\n")

    target_compile_definitions(SandboxEditor PRIVATE GLEW_STATIC)
    target_link_libraries(SandboxEditor
        PRIVATE SbEngineCore
        PRIVATE SbEditor

        # Third Parties
        PUBLIC smhasher
        PUBLIC imgui
        PRIVATE assimp
        PRIVATE yaml-cpp
        PUBLIC glfw
        PUBLIC ${GLEWS}
        PRIVATE OpenGL::GL
    )
    
endif()

# ---

message("")