//
// Created by Admin on 30.03.2022.
//

#ifndef TFALL_MWTYPE_HPP
#define TFALL_MWTYPE_HPP

#include <cstdint>

namespace MW {
    template<typename T>
    struct Vec2 {
        T x;
        T y;

        inline Vec2(T X, T Y): x(X), y(Y) {};


    };

    typedef Vec2<int32_t> Vec2i;
    typedef Vec2<float> Vec2f;

    template<typename T>
    Vec2f operator/(const Vec2<T>& vectorL, const Vec2<T>& vectorR) {
        return {static_cast<float>(vectorL.x) / static_cast<float>(vectorR.x), static_cast<float>(vectorL.y) / static_cast<float>(vectorR.y)};
    }

    template<typename T>
    struct Rect {
        T width;
        T height;
        T left;
        T top;

        inline Rect() = default;
        inline Rect(T Width, T Height, T Left = 0, T Top = 0): width(Width), height(Height), left(Left), top(Top) {};
    };

    typedef Rect<int32_t> RectI;
    typedef Rect<float> RectF;
}


#endif //TFALL_MWTYPE_HPP
