#ifndef TEXTUREDATA_HPP
#define TEXTUREDATA_HPP

#include <glad/glad.h>
#include <vector>

using namespace std;

class textureData
{
private:
    int width;
    int height;
    int nrChannels;
    unsigned int IMAGE_ID;
public:
    void loadTexture(string texturePath);
    unsigned int getTexture_ID();
    void bindTexture();
};

#endif