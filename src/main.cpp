#include "App.hpp"

#include <stdexcept>
#include <iostream>

int main()
{


    App game(800, 580, 60.f);
    try
    {
        game.Run();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}
