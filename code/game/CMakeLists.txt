# Sandbox - Game

add_library(Sandbox_Game STATIC
    SbGameBase.h
    SbGame.cpp
    SbGameUI.h
    SbGameUI.cpp
)

target_compile_definitions(Sandbox_Game PUBLIC SB_PROJECT_NAME="${CM_SANDBOX_GAME_PROJECT}")
target_compile_definitions(Sandbox_Game PRIVATE GLEW_STATIC)

target_include_directories(Sandbox_Game SYSTEM PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)
target_include_directories(Sandbox_Game PRIVATE
    ${assimp_SOURCE_DIR}/include
    ${FETCHCONTENT_BASE_DIR}/assimp-build/include
    ${yaml-cpp_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
    ${CM_SANDBOX_CODE_DIR}/src
)
target_link_libraries(Sandbox_Game PRIVATE Sandbox_Engine)

message("Finished Sandbox Game library")