#include "Material.h"
#include "Texture.h"
#include "../Core/Debug.h"

using namespace Sandbox;

Material::Material() : textures(std::vector<Texture>{}), shaders(std::vector<Shader*>{}), roughnessStrength(32.0f), emissiveStrength(1.0f), colorOverlay(vec4(0.0f,0.0f,0.0f,1.0f)), flags(0x0) {

}

void Material::AddTexture(const Texture& tex){
    textures.push_back(tex);
    if(!(flags & SB_MAT_TEX) && textures.size() > 0){
        flags |= SB_MAT_TEX;
    }

    if(!(flags & SB_MAT_LIT) && tex.GetType() == TextureType::DIFFUSE){
        flags |= SB_MAT_LIT;
    }

    if(!(flags & SB_MAT_EMISS) && tex.GetType() == TextureType::EMISSIVE){
        flags |= SB_MAT_EMISS;
    }
};

void Material::SetColorOverlay(const vec4& color){
    colorOverlay = color;
    if(!(flags & SB_MAT_COLOVERLAY)){
        flags |= SB_MAT_COLOVERLAY;
    }
}

void Material::AddFlag(u16 flag){
    if(!(flags & flag))
        flags |= flag;
}

void Material::RemoveFlag(u16 flag){
    if(flags & flag)
        flags ^= flag;
}