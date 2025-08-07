# Sandbox - Application

add_library(Sandbox_App STATIC
    Application.h
    Application.cpp
)

target_include_directories(Sandbox_App PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)
target_include_directories(
    Sandbox_App
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CM_SANDBOX_CODE_DIR}/src
    ${CM_SANDBOX_CODE_DIR}/game
)
target_link_libraries(Sandbox_App PRIVATE
    Sandbox_Engine
    Sandbox_Game
)

message("Finished Sandbox App library")