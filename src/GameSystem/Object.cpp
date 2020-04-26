#include "GameSystem/Object.hpp"
using namespace DreamEngine::GameSystem;

Object::Object(const std::string &Name):m_Active(false),m_Name(Name)
{
}

bool Object::isActive() const
{
    return m_Active;
}
void Object::SetActive(bool active)
{
    m_Active = active;
}
const std::string &Object::GetName() const{
    return m_Name;
}
void Object::SetName(const std::string &name)
{
    m_Name = name;
}

