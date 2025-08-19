#pragma once

#include "Core/Collections.h"

namespace Sb {

    // Component IDs
        constexpr size_t DUMMY_COMPONENT = 0;
        constexpr size_t TRANSFORM_COMPONENT = 1;
        constexpr size_t RENDERER_COMPONENT = 2;
}

namespace Sb {

    struct DummyComponent{
    };

    struct TransformComponent{
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

    struct RendererComponent{
    };

    // static Component GetComponentFromID(size_t componentID){
    //     if(componentID == 1){
    //         return TransformComponent();
    //     if(componentID == 10){
    //         return RendererComponent();
    //     }
    //     }
    //     return Component();
    // };
}
