# Sandbox - Game

add_library(Sandbox_Game STATIC
    SbGame.h
    SbGame.cpp
)

target_include_directories(Sandbox_Game PRIVATE ${SANDBOX_VENDOR_DIR}/includes)
target_include_directories(
    Sandbox_Game 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SANDBOX_CODE_DIR}/src
)
target_link_libraries(Sandbox_Game PRIVATE Sandbox_Eng)