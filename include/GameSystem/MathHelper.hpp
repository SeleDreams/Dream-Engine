#ifndef MATHHELPER_HPP
#define MATHHELPER_HPP

namespace DreamEngine::GameSystem
{
class Position;
class Scale;
class Rotation;
};
////////////////////////////////////////////////////////////////////////////////////////////////////POSITION
void operator+=(DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
void operator-=(DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
void operator/=(DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
void operator*=(DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
DreamEngine::GameSystem::Position operator+(const DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
DreamEngine::GameSystem::Position operator-(const DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
DreamEngine::GameSystem::Position operator/(const DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
DreamEngine::GameSystem::Position operator/(const DreamEngine::GameSystem::Position &a, const float b);
DreamEngine::GameSystem::Position operator*(const DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
DreamEngine::GameSystem::Position operator*(const DreamEngine::GameSystem::Position &a, const float b);
bool operator==(const DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);
bool operator!=(const DreamEngine::GameSystem::Position &a, const DreamEngine::GameSystem::Position &b);

///////////////////////////////////////////////////////////////////////////////////////////////////////ROTATION
bool operator==(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
bool operator!=(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
void operator+=(DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
void operator-=(DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
void operator/=(DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
void operator*=(DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
DreamEngine::GameSystem::Rotation operator+(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
DreamEngine::GameSystem::Rotation operator-(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
DreamEngine::GameSystem::Rotation operator/(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
DreamEngine::GameSystem::Rotation operator*(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
bool operator==(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);
bool operator!=(const DreamEngine::GameSystem::Rotation &a, const DreamEngine::GameSystem::Rotation &b);

/////////////////////////////////////////////////////////////////////////////////////////////////////////SCALE
bool operator==(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
bool operator!=(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
void operator+=(DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
void operator-=(DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
void operator/=(DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
void operator*=(DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
DreamEngine::GameSystem::Scale operator+(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
DreamEngine::GameSystem::Scale operator-(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
DreamEngine::GameSystem::Scale operator/(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
DreamEngine::GameSystem::Scale operator*(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
bool operator==(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
bool operator!=(const DreamEngine::GameSystem::Scale &a, const DreamEngine::GameSystem::Scale &b);
#endif