#pragma once

#include "Core/Base.h"

namespace SbEngine{

    // Component IDs
    constexpr size_t DUMMY_COMPONENT = 0;
    constexpr size_t TRANSFORM_COMPONENT = 1;
    constexpr size_t RENDERER_COMPONENT = 10;
}

namespace SbEngine{

    struct Component{
    };

    struct TransformComponent : Component{
        float posX;
        float posY;
        float posZ;

        float rotX;
        float rotY;
        float rotZ;
        
        float scaleX;
        float scaleY;
        float scaleZ;
    };

    struct RendererComponent : Component{
    };

    static Component GetComponentFromID(size_t componentID){
        if(componentID == 1){
            return TransformComponent();
        if(componentID == 10){
            return RendererComponent();
        }
        }
        return Component();
    };
}
