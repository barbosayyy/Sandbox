# Sandbox - Code Root

add_subdirectory(src)

if(BUILD_GAME)
    add_subdirectory(game)
    add_subdirectory(application)
endif()

if(BUILD_EDITOR)
    add_subdirectory(editor)
endif()