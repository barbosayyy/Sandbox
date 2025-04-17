
cmake_minimum_required(VERSION 3.10)

project(Sandbox VERSION 0.1.0)
message("\nProject: ${PROJECT_NAME} ${PROJECT_VERSION}")

include(CTest)

#
# Compiler Info
#
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
if(CMAKE_CXX_COMPILER)
    message("C++ Compiler: ${CMAKE_CXX_COMPILER}")
    message("Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
    message("Standard: ${CMAKE_CXX_STANDARD}")
    if(CMAKE_CXX_COMPILER STREQUAL clang++)
        add_compile_definitions(SB_COMPILER_CLANGPP)
    endif()
else()  
    message(FATAL_ERROR "C++ compiler not found.")
endif()

#
# Definitions
#
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SANDBOX_TARGET_PLATFORM "Windows")  
    add_compile_definitions(SB_PLATFORM_WIN)
elseif()
    message(FATAL_ERROR "Other platforms not supported yet.")
endif() 

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SANDBOX_TARGET_MODE "Debug")
    add_compile_definitions(SB_BUILD_DEBUG)
    endif()
    
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(SANDBOX_TARGET_MODE "Release")
    add_compile_definitions(SB_BUILD_RELEASE)
endif()

if(SANDBOX_TARGET_PLATFORM)
    message("Building for platform: ${SANDBOX_TARGET_PLATFORM} ${CMAKE_SYSTEM_PROCESSOR} in ${SANDBOX_TARGET_MODE} mode")
else()
    message(FATAL_ERROR "Platform: ${SANDBOX_TARGET_PLATFORM} ${CMAKE_SYSTEM_PROCESSOR} not supported.")
endif()

#
# Dir
#
set(SANDBOX_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SANDBOX_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(SANDBOX_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(SANDBOX_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts)
set(SANDBOX_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/code)

#
# Exec and Linking
#
add_subdirectory(code)
add_subdirectory(${SANDBOX_VENDOR_DIR}/includes/imgui)

add_executable(Sandbox code/main.cpp)
target_include_directories(Sandbox PRIVATE vendor/includes)
target_include_directories(Sandbox PUBLIC
    code/src
    code/game
    code/application
)

target_link_libraries(Sandbox 
    # Sandbox App links application with engine source and game source
    PRIVATE Sandbox_App

    # Third Parties
    PUBLIC imgui
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/glew32.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/assimp-vc143-mtd.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/glfw3.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/OpenGL32.lib
    PRIVATE  ${SANDBOX_VENDOR_DIR}/libs/yaml-cppd.lib
)

#
# TEMP: Dependencies and resources copying to build folder
#
file(COPY ${SANDBOX_VENDOR_DIR}/dlls/ DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${SANDBOX_VENDOR_DIR}/libs/ DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${SANDBOX_RESOURCES_DIR} DESTINATION ${CMAKE_BINARY_DIR})

#
# Run final scripts
#
set(SANDBOX_SCRIPTS_RUN_SCRIPTS     1)

if(${SANDBOX_SCRIPTS_RUN_SCRIPTS} EQUAL 1)
    message("\nRunning Scripts:")
    if(${SANDBOX_TARGET_MODE} STREQUAL "Debug")
        if(${SANDBOX_TARGET_PLATFORM} STREQUAL "Windows")
            message("generate_resource_manifest.py")
            execute_process(COMMAND python -O ${SANDBOX_SCRIPTS_DIR}/generate_resource_manifest.py --target=0 --cmake=1)
            file(COPY ${SANDBOX_RESOURCES_DIR}/resource_manifest.yaml DESTINATION ${CMAKE_BINARY_DIR}/resources)
        endif()
    elseif(${SANDBOX_TARGET_MODE} STREQUAL "Release")
        if(${SANDBOX_TARGET_PLATFORM} STREQUAL "Windows")
            execute_process(COMMAND python ${SANDBOX_SCRIPTS_DIR}/generate_resource_manifest.py --target=1 --cmake=1)
        endif()
    endif()
else()
    message("Scripts are disabled")
endif()

# ---

message("")
