#ifndef HPP_COLOR
#define HPP_COLOR
namespace DreamEngine
{
namespace GameSystem
{
enum Colors
{
    RED,
    BLUE,
    GREEN,
    BLACK,
    WHITE
};
class Color
{
  public:
    void SetColor(Colors color);
    void SetColor(int r, int g, int b);
    void GetColorRGB(int *r, int *g, int *b) const;
  private:
    int R, G, B;
};
};
};
#endif