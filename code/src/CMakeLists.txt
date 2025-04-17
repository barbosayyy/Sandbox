# Sandbox - Source

add_library(Sandbox_Eng STATIC
    
    # Core
    Core/Base.h
    Core/Types.h
    Core/Types.cpp
    Core/Singleton.h
    Math/Vectors.h
    Memory/Allocator.h
    Memory/Allocator.cpp
    Core/Debug.h
    Core/Debug.cpp
    Core/Utils.cpp
    Core/Utils.h
    Core/Config.h
    Core/Config.cpp
    Engine/IEngine.h
    Engine/Engine.h
    Engine/Engine.cpp
    Input/Input.h
    Input/Input.cpp
    
    # Rendering
    Rendering/Renderer.h
    Rendering/Renderer.cpp
    Rendering/Camera.h
    Rendering/Camera.cpp
    Rendering/VertexBuffer.h
    Rendering/VertexBuffer.cpp
    Rendering/IndexBuffer.h
    Rendering/IndexBuffer.cpp
    # Rendering/Assimp.h
    # Rendering/Assimp.cpp
    Rendering/Material.h
    Rendering/Material.cpp
    Rendering/Mesh.h
    Rendering/Mesh.cpp
    Rendering/Model.h
    Rendering/Model.cpp
    Rendering/Renderable.h
    Rendering/Renderable.cpp
    Rendering/Primitives.h
    Rendering/Primitives.cpp
    Rendering/Shader.h
    Rendering/Shader.cpp
    Rendering/Texture.cpp
    Rendering/Texture.h
    Rendering/Window.h
    Rendering/Window.cpp
    
    # Resource Management
    Resources/ShaderManager.h
    Resources/ShaderManager.cpp
    Resources/ResourceManager.h
    Resources/ResourceManager.cpp

    Scene/SceneManager.h
    Scene/Scene.h
    Scene/Scene.cpp

    # ImGui
    ImGui/ImGuiSbContext.h
    ImGui/ImGuiSbContext.cpp
    # ECS
    ECS/Components.h
    ECS/ComponentManager.h
    ECS/ComponentManager.cpp
    ECS/System.h

    # Game
    Game/IGame.h
)

target_include_directories(Sandbox_Eng PRIVATE ${SANDBOX_VENDOR_DIR}/includes)
target_include_directories(Sandbox_Eng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})