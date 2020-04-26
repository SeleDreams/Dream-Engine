#include "Misc/Color.hpp"

using namespace DreamEngine::GameSystem;
void Color::SetColor(int r, int g, int b)
{
    R = r;
    G = g;
    B = b;
}

void Color::SetColor(Colors color)
{
    switch (color)
    {
    case Colors::BLACK:
        SetColor(0, 0, 0);
        break;
    case Colors::WHITE:
        SetColor(255, 255, 255);
        break;
    case Colors::BLUE:
        SetColor(0, 0, 255);
        break;
    case Colors::GREEN:
        SetColor(0, 255, 0);
        break;
    case Colors::RED:
        SetColor(255, 0, 0);
        break;
    default:
        SetColor(0, 0, 0);
        break;
    }
}
