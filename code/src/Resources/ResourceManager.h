#pragma once

#include "Core/Types.h"
#include "Core/Singleton.h"

namespace SbEngine{
    enum class ResourceID{
		// Shaders -> 0-15
        SHADER_FRAGMENT = 0,
		SHADER_VERTEX = 1,

		// Textures -> 16-31
		TEXTURE_JPG = 16,
		TEXTURE_PNG = 17
    };

    // TODO: This could be improved in the future
    class ResourceManager : public Singleton<ResourceManager, int>{
    public:
        ResourceManager();
        virtual void Init() {_init = true;};
        String GetYamlResourceNameFromResourceID(ResourceID rId);
        Resource GetDataFromID(ResourceID rId, int id);

    private:
        bool _init;
    };
}