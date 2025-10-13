#pragma once

#include "Math/Vectors.h"

namespace Sb {
    enum class LightType {
        Point = 0,
        Spot = 1,
        Directional = 2,
        Ambient = 3,
        Rect = 4
    };
    class Light {
    public:
        void SetColor(vec3 color) {_color = color;}
        void SetIntensity(float intensity) {_intensity = intensity;}
        void SetType(LightType type) {_type = type;}
    private:
        vec3 _color;
        float _intensity;
        LightType _type;
        float range;
    };
}