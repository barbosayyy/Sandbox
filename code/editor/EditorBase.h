#include "Core/Base.h"
#include "Core/Types.h"
#include "Math/Vectors.h"

namespace SbEditor {
    using u8 = Sb::u8;
    using i8 = Sb::i8;
    using u16 = Sb::u16;
    using i16 = Sb::i16;
    using u32 = Sb::u32;
    using i32 = Sb::i32;
    using u64 = Sb::u64;
    using i64 = Sb::i64;
    using u64ptr = Sb::u64ptr;

    using String = Sb::String;
    using vec2 = Sb::vec2;
    using vec3 = Sb::vec3;
    using vec4 = Sb::vec4;

    constexpr Sb::u8 SB_EDITORUI_MENU = 1 << 0;
    constexpr Sb::u8 SB_EDITORUI_SCENETREE = 1 << 1;
    constexpr Sb::u8 SB_EDITORUI_ASSETTREE = 1 << 2;
    constexpr Sb::u8 SB_EDITORUI_ASSETEXPLORER = 1 << 3;
    constexpr Sb::u8 SB_EDITORUI_INSPECTOR = 1 << 4;
}

