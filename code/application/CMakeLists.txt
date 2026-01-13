# Sandbox - Application

add_library(SbApp STATIC
    Application.h
    Application.cpp
)

target_compile_definitions(SbApp PRIVATE GLEW_STATIC)
target_include_directories(SbApp SYSTEM PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)

target_include_directories(SbApp PRIVATE
    ${CM_SANDBOX_SOURCE_DIR}/src
    ${CM_SANDBOX_SOURCE_DIR}/game

    ${assimp_SOURCE_DIR}/include
    ${FETCHCONTENT_BASE_DIR}/assimp-build/include
    ${yaml-cpp_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
)

target_link_libraries(SbApp PRIVATE
    SbCore
    Sandbox_Game
)

message("Finished Sandbox App library")