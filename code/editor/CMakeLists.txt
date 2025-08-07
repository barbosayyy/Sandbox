# Sandbox - Editor

add_library(Sandbox_Editor STATIC
    Editor.h
    Editor.cpp
)

target_compile_definitions(Sandbox_Editor PUBLIC SB_EDITOR)

target_include_directories(Sandbox_Editor PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)
target_include_directories(
    Sandbox_Editor
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CM_SANDBOX_CODE_DIR}/src
)

target_link_libraries(Sandbox_Editor PRIVATE
    Sandbox_Engine
)

message("Finished Sandbox Editor library")