#pragma once 

#include "Base.h"
#include "Core/Base.h"
#include <string>

// Sandbox Engine configuration 

namespace Sb {
    constexpr u16 DEFAULT_WINDOW_WIDTH = 640;
    constexpr u16 DEFAULT_WINDOW_HEIGHT = 360;
    constexpr u16 DEFAULT_VIEWPORT_WIDTH = DEFAULT_WINDOW_WIDTH;
    constexpr u16 DEFAULT_VIEWPORT_HEIGHT = DEFAULT_WINDOW_HEIGHT;
    constexpr i16 DEFAULT_VIEWPORT_X = 0;
    constexpr i16 DEFAULT_VIEWPORT_Y = 0;
    
    constexpr bool SB_RENDERER_VSYNC = FALSE;
    constexpr bool SB_RENDERER_TRIPLE_BUFFERING = TRUE;
    
    constexpr u8 SB_RENDERER_MAX_NUM_LIGHTS = 255;
    
    const std::string SB_RESOURCE_FOLDER_PATH = "/resources";
    const std::string SB_RESOURCE_MANIFEST_PATH = "/resources/resource_manifest.yaml";
    const std::string SB_RESOURCE_COMMON_FOLDER_PATH = "/resources/common";

    constexpr u32 SB_RESOURCE_MANIFEST_MESH_CUBE_ID = _MAX_U32-1;
    constexpr u32 SB_RESOURCE_MANIFEST_MESH_PLANE_ID = _MAX_U32-2;
    constexpr u32 SB_RESOURCE_MANIFEST_MESH_SPHERE_ID = _MAX_U32-3;
    constexpr u32 SB_RESOURCE_MANIFEST_MESH_QUAD_ID = _MAX_U32-4;
    constexpr u32 SB_RESOURCE_MANIFEST_MAX_ASSET_ID = _MAX_U32-15;

    constexpr u32 SB_RESOURCE_MANAGER_ASSET_ENTRY_LOAD_SIZE = 500;
    constexpr u32 SB_RESOURCE_MANAGER_ASSET_ENTRY_MAX_LOADED = 1000;

    struct Config{
        Config();
        i16 windowWidth;
        i16 windowHeight;
    };
};
