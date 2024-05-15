add_library(Sandbox_Src STATIC
    Core/Base.h
    Core/Types.h
    Core/Types.cpp
    Core/Singleton.h
    Math/Vectors.h
    Memory/Allocator.h
    Memory/Allocator.cpp
    Renderer/Renderer.h
    Renderer/Renderer.cpp
    Renderer/Camera.h
    Renderer/Camera.cpp
    Renderer/IndexBuffer.h
    Renderer/IndexBuffer.cpp
    Input/Input.h
    Input/Input.cpp
    Core/Debug.h
    Core/Debug.cpp
    Renderer/Mesh.cpp
    Renderer/Mesh.h
    Renderer/Renderable.h
    Renderer/Renderable.cpp
    Renderer/Primitives.cpp
    Renderer/Primitives.h
    Renderer/Shader.cpp
    Renderer/Shader.h
    Renderer/Texture.cpp
    Renderer/Texture.h
    Core/Utils.cpp
    Core/Utils.h
    Renderer/VertexBuffer.cpp
    Renderer/VertexBuffer.h
    Renderer/Window.h
    Renderer/Window.cpp
    ImGui/ImGuiManager.h
    ImGui/ImGuiManager.cpp
    Resources/ResourceManager.h
    Resources/ResourceManager.cpp
    Resources/ShaderManager.h
    Resources/ShaderManager.cpp
    Resources/TextureManager.h
    Resources/TextureManager.cpp

)

target_include_directories(Sandbox_Src PRIVATE ../vendor/includes)