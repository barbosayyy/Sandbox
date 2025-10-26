#pragma once

#include "Core/Types.h"
namespace Sb {

	struct Texture{
		u32 id;
		i32 width;
		i32 height;
		i32 numChannels;
		TextureType type;
		u32 assetID;
		String name;
	};
}