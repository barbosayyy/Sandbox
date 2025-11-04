#pragma once

#include "Base.h"
#include "Types.h"

namespace Sb {
    enum class GUIDDomain : u8 {
        Default = 1,
        Engine = 2
    };

    class Crypto {
    public:
        static const SbGUID NewGUID();
		static const SbGUID GetGUIDFromHashedInput(const String& input, GUIDDomain domain);
        static String GetStringFromGUID(const SbGUID& guid);
        static SbGUID GetGUIDFromString(const String& string);
    };
}