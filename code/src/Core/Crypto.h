#pragma once

#include "Base.h"
#include "Types.h"

namespace Sb {
    enum class GUIDDomain : u8 {
        Default = 1,
        Engine = 2
    };

    // Sandbox Engine Cryptographic ops class
    class Crypto {
    public:
        static const SbGUID NewGUID();
		static const SbGUID GetGUIDFromHashedInput(const String& input, GUIDDomain domain);
        static String GetStringFromGUID(const SbGUID& guid);
        static SbGUID GetGUIDFromString(const String& string);
        static u32 GetU32HashFromPath(const std::string& path);

        template<typename T>
        static size_t HashCombine(size_t& h, const T& v) {
            h ^= std::hash<T>{}(v) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };
}

// Sandbox Engine std::hash specialization for custom GUID type
namespace std {
	template <>
	struct hash<Sb::SbGUID> {
		size_t operator()(const Sb::SbGUID& guid) const {
            size_t h = 0;
            Sb::Crypto::HashCombine(h, guid.h1);
            Sb::Crypto::HashCombine(h, guid.h2);
            return h;
		}
	};
}