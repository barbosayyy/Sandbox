# Sandbox - Editor

add_library(SbEditor STATIC
    EditorApplication.h
    EditorApplication.cpp
    Editor.h
    Editor.cpp
    EditorWindow.h
    EditorWindow.cpp
    EditorGameService.h
    EditorGameService.cpp
    EditorMessageBus.h
    EditorMessageBus.cpp
    EditorMessage.h
    SceneTree/EditorSceneTreeWindow.h
    SceneTree/EditorSceneTreeWindow.cpp
    Inspector/EditorInspectorWindow.h
    Inspector/EditorInspectorWindow.cpp
    AssetBrowser/EditorAssetBrowserWindow.h
    AssetBrowser/EditorAssetBrowserWindow.cpp
)

target_compile_definitions(SbEditor PUBLIC SB_EDITOR)
target_compile_definitions(SbEditor PRIVATE GLEW_STATIC)

# SYSTEM flag clears warnings from vendor headers
target_include_directories(SbEditor SYSTEM PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)

target_include_directories(SbEditor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CM_SANDBOX_SOURCE_DIR}/src
    
    ${assimp_SOURCE_DIR}/include
    ${FETCHCONTENT_BASE_DIR}/assimp-build/include
    ${yaml-cpp_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
)

message("Finished Sandbox Editor library")