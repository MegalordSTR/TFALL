//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_CATEGORYIDENTIFIERS_H
#define TEST_CATEGORYIDENTIFIERS_H

namespace Game {
    enum class CategoryType : unsigned int {
        None = 0,
        SoundEffect = 1 << 0
    };
}


#endif //TEST_CATEGORYIDENTIFIERS_H
