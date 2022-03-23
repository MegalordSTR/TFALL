//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_CATEGORYIDENTIFIERS_H
#define TEST_CATEGORYIDENTIFIERS_H

namespace MW {
    enum class CategoryType : unsigned int {
        TypeNone = 0,
        TypeSoundEffect = 1 << 0,
        TypeFigure = 1 << 1
    };
}


#endif //TEST_CATEGORYIDENTIFIERS_H
