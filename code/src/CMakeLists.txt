# Sandbox - Source

add_library(Sandbox_Engine STATIC
    
    # Core
    Core/Base.h
    Core/Types.h
    Core/Types.cpp
    Core/Collections.h
    Core/Collections.cpp
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
    Core/Profiler.h
    Core/Profiler.cpp
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
    Rendering/Material.h
    Rendering/Mesh.h
    Rendering/Mesh.cpp
    Rendering/Model.h
    Rendering/Model.cpp
    Rendering/Cubemap.h
    Rendering/Cubemap.cpp
    Rendering/Shader.h
    Rendering/Shader.cpp
    Rendering/Texture.cpp
    Rendering/Texture.h
    Rendering/Light.h
    Rendering/Window.h
    Rendering/Window.cpp
    Rendering/OpenGL/GLBuffer.h
    Rendering/OpenGL/GLBuffer.cpp
    Rendering/Primitive.h
    Rendering/Primitive.cpp
    Rendering/RenderPasses/RenderPass.h
    Rendering/RenderPasses/GeometryPass.h
    Rendering/RenderPasses/GeometryPass.cpp
    Rendering/RenderPasses/LightingPass.h
    Rendering/RenderPasses/LightingPass.cpp
    Rendering/RenderPasses/SkyboxPass.h
    Rendering/RenderPasses/SkyboxPass.cpp
    
    # Resource Management
    Resources/ResourceManifest.h
    Resources/ResourceManifest.cpp
    Resources/ResourceManagement.h
    Resources/ResourceManagement.cpp
    Resources/ResourceManager.h
    Resources/ResourceManager.cpp

    Scene/SceneManagement.h
    Scene/SceneManagement.cpp
    
    # ImGui
    ImGui/ImGuiSbContext.h
    ImGui/ImGuiSbContext.cpp
    
    # ECS
    ECS/Components.h
    ECS/Systems/InputSystem.h
    ECS/Systems/PhysicsSystem.h
    ECS/Systems/RenderSystem.h
    ECS/Systems/RenderSystem.cpp
    ECS/Systems/LightSystem.h
    ECS/Systems/LightSystem.cpp
    ECS/Systems/SkyboxSystem.h
    ECS/Systems/SkyboxSystem.cpp

    ECS/Registry.h
    ECS/Registry.cpp
    ECS/EntityManagement.h
    ECS/EntityManagement.cpp
    
    # Game
    Game/Game.h
    Game/IGame.h
)

target_include_directories(Sandbox_Engine PRIVATE ${CM_SANDBOX_VENDOR_DIR}/includes)
target_include_directories(Sandbox_Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

message("Finished Sandbox Engine library")
