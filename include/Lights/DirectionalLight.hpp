#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "ILight.hpp"

class DirectionalLight : public ILight
{
    virtual void updateLightInCurrentShader() = 0;
};

#endif