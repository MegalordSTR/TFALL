#pragma once

namespace MW {
    enum class CategoryType : unsigned int {
        TypeNone = 0,
        TypeSoundEffect = 1 << 0,
        TypeFigure = 1 << 1
    };
}
