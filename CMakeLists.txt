cmake_minimum_required(VERSION 3.10)

project(Sandbox 
        VERSION 0.1.0
)
message("\nProject: ${PROJECT_NAME}")

include(CTest)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

if(CMAKE_CXX_COMPILER)
message("C++ Compiler: ${CMAKE_CXX_COMPILER}")
message("Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message("Standard: ${CMAKE_CXX_STANDARD}")
else()  
message(FATAL_ERROR "C++ compiler not found.")
endif()

# Def

add_compile_definitions(SANDBOX_ENGINE)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SANDBOX_TARGET_PLATFORM "Windows")  
    add_compile_definitions(WINDOWS)
endif() 

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SANDBOX_TARGET_MODE "Debug")
    add_compile_definitions(DEBUG_MODE)
    endif()
    
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(SANDBOX_TARGET_MODE "Release")
    add_compile_definitions(RELEASE_MODE)
endif()

if(SANDBOX_TARGET_PLATFORM)
message("Building for platform: ${SANDBOX_TARGET_PLATFORM} ${CMAKE_SYSTEM_PROCESSOR} in ${SANDBOX_TARGET_MODE} mode")
else()
message(FATAL_ERROR "Platform: ${SANDBOX_TARGET_PLATFORM} ${CMAKE_SYSTEM_PROCESSOR} not supported.")
endif()

# Dir

set(SANDBOX_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SANDBOX_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(SANDBOX_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(SANDBOX_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts)

add_subdirectory(src)
add_subdirectory(${SANDBOX_VENDOR_DIR}/includes/imgui)

add_executable(Sandbox src/main.cpp)
target_include_directories(Sandbox PRIVATE vendor/includes)

target_link_libraries(Sandbox 
    PRIVATE Sandbox_Src
    PUBLIC imgui
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/glew32.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/assimp-vc143-mtd.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/glfw3.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/OpenGL32.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/yaml-cppd.lib
)

# File

file(COPY ${SANDBOX_VENDOR_DIR}/dlls/ DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${SANDBOX_RESOURCES_DIR} DESTINATION ${CMAKE_BINARY_DIR})

# Configure Resource Data 

set(SANDBOX_SCRIPTS_RUN_SCRIPTS     1)
set(SANDBOX_SCRIPTS_DEBUG           0)

if(${SANDBOX_SCRIPTS_RUN_SCRIPTS} EQUAL 1)
    message("\nRunning Script: resource-serializer.py")
    if(${SANDBOX_SCRIPTS_DEBUG} EQUAL 1)
            execute_process(COMMAND python ${SANDBOX_SCRIPTS_DIR}/resource-serializer.py)
    else()
            execute_process(COMMAND python -O ${SANDBOX_SCRIPTS_DIR}/resource-serializer.py)
    endif()
else()
    message("Scripts are disabled")
endif()

# ---

message("")
