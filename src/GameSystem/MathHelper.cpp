#include "GameSystem/MathHelper.hpp"
#include "GameSystem/Position.hpp"
#include "GameSystem/Rotation.hpp"
#include "GameSystem/Scale.hpp"
using namespace DreamEngine::GameSystem;

//////////////////////////////////////////////////////POSITION
void operator+=(Position &a, const Position &b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
}
void operator-=(Position &a, const Position &b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
}
void operator/=(Position &a, const Position &b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
}
void operator*=(Position &a, const Position &b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
}
Position operator+(const Position &a, const Position &b)
{
    Position pos(a);
    pos += b;
    return pos;
}
Position operator-(const Position &a, const Position &b)
{
    Position pos(a);
    pos -= b;
    return pos;
}
Position operator/(const Position &a, const Position &b)
{
    Position pos(a);
    pos /= b;
    return pos;
}
Position operator*(const Position &a, const Position &b)
{
    Position pos(a);
    pos *= b;
    return pos;
}
Position operator*(const Position &a, const float b)
{
    Position pos(a);
    pos.x *= b;
    pos.y *= b;
    pos.z *= b;
    return pos;
}
Position operator/(const Position &a, const float b)
{
    Position pos(a);
    pos.x /= b;
    pos.y /= b;
    pos.z /= b;
    return pos;
}
bool operator==(const Position &a, const Position &b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}
bool operator!=(const Position &a, const Position &b)
{
    return (a.x != b.x || a.y != b.y || a.z != b.z);
}

///////////////////////////////////////////////////////////////////ROTATION
void operator+=(Rotation &a, const Rotation &b)
{
    a.Angle += b.Angle;
}
void operator-=(Rotation &a, const Rotation &b)
{
    a.Angle -= b.Angle;
}
void operator/=(Rotation &a, const Rotation &b)
{
    a.Angle /= b.Angle;
}
void operator*=(Rotation &a, const Rotation &b)
{
    a.Angle *= b.Angle;
}
Rotation operator+(const Rotation &a, const Rotation &b)
{
    Rotation rot(a);
    rot += b;
    return rot;
}
Rotation operator-(const Rotation &a, const Rotation &b)
{
    Rotation rot(a);
    rot -= b;
    return rot;
}
Rotation operator/(const Rotation &a, const Rotation &b)
{
    Rotation rot(a);
    rot /= b;
    return rot;
}
Rotation operator*(const Rotation &a, const Rotation &b)
{
    Rotation rot(a);
    rot *= b;
    return rot;
}
bool operator==(const Rotation &a, const Rotation &b)
{
    return (a.Angle == b.Angle);
}
bool operator!=(const Rotation &a, const Rotation &b)
{
    return (a.Angle != b.Angle);
}

////////////////////////////////////////////////////////////SCALE

void operator+=(Scale &a, const Scale &b)
{
    a.w += b.w;
    a.h += b.h;
}
void operator-=(Scale &a, const Scale &b)
{
    a.w -= b.w;
    a.h -= b.h;
}
void operator/=(Scale &a, const Scale &b)
{
    a.w /= b.w;
    a.h /= b.h;
}
void operator*=(Scale &a, const Scale &b)
{
    a.w *= b.w;
    a.h *= b.h;
}
Scale operator+(const Scale &a, const Scale &b)
{
    Scale scale(a);
    scale += b;
    return scale;
}
Scale operator-(const Scale &a, const Scale &b)
{
    Scale scale(a);
    scale -= b;
    return scale;
}
Scale operator/(const Scale &a, const Scale &b)
{
    Scale scale(a);
    scale /= b;
    return scale;
}
Scale operator*(const Scale &a, const Scale &b)
{
    Scale scale(a);
    scale *= b;
    return scale;
}
bool operator==(const Scale &a, const Scale &b)
{
    return (a.w == b.w && a.h == b.h);
}
bool operator!=(const Scale &a, const Scale &b)
{
    return !(a == b);
}
