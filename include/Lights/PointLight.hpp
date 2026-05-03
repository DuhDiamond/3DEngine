#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "ILight.hpp"

class PointLight : public ILight
{
    virtual void updateLightInCurrentShader() = 0;
};

// pointlight {
//     vec3 pos;
//     vec3 colour;
// };

#endif