# Sandbox - Application

add_library(Sandbox_App STATIC
    Application.h
    Application.cpp
)

target_compile_definitions(Sandbox_App PRIVATE GLEW_STATIC)
target_include_directories(Sandbox_App SYSTEM PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)
target_include_directories(Sandbox_App PRIVATE
    ${assimp_SOURCE_DIR}/include
    ${FETCHCONTENT_BASE_DIR}/assimp-build/include
    ${yaml-cpp_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
    ${CM_SANDBOX_CODE_DIR}/src
    ${CM_SANDBOX_CODE_DIR}/game
)

target_link_libraries(Sandbox_App PRIVATE
    Sandbox_Engine
    Sandbox_Game
)

message("Finished Sandbox App library")