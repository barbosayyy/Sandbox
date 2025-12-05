# Sandbox - Editor

add_library(Sandbox_Editor STATIC
    EditorApplication.h
    EditorApplication.cpp
    Editor.h
    Editor.cpp
)

target_compile_definitions(Sandbox_Editor PUBLIC SB_EDITOR)
target_compile_definitions(Sandbox_Editor PRIVATE GLEW_STATIC)

# SYSTEM flag clears warnings from vendor headers
target_include_directories(Sandbox_Editor SYSTEM PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)
target_include_directories(Sandbox_Editor PRIVATE
    ${assimp_SOURCE_DIR}/include
    ${FETCHCONTENT_BASE_DIR}/assimp-build/include
    ${yaml-cpp_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
    ${CM_SANDBOX_CODE_DIR}/src
)

target_link_libraries(Sandbox_Editor PRIVATE Sandbox_Engine )

message("Finished Sandbox Editor library")