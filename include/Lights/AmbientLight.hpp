#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

#include "ILight.hpp"

class AmbientLight : public ILight
{
    virtual void updateLightInCurrentShader() = 0;
};

#endif