#pragma once

#include "Core/Types.h"
namespace Sb {

	struct Texture{
		u32 id;
		s32 width;
		s32 height;
		s32 numChannels;
		TextureType type;
		u32 assetID;
		String name;
	};
}