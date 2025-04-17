# Sandbox - Application

add_library(Sandbox_App STATIC
    Application.h
    Application.cpp
)

target_include_directories(Sandbox_App PRIVATE ${SANDBOX_VENDOR_DIR}/includes)
target_include_directories(
    Sandbox_App
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SANDBOX_CODE_DIR}/src
    ${SANDBOX_CODE_DIR}/game
)
target_link_libraries(Sandbox_App PRIVATE
    Sandbox_Eng
    Sandbox_Game
)