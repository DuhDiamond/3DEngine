#ifndef TEXTUREDATA_HPP
#define TEXTUREDATA_HPP

#include <glad/glad.h>
#include <vector>

using namespace std;

class textureData
{
private:
    int *width;
    int *height;
    int *nrChannels;
    int *IMAGE_ID;
public:
    textureData();
    void loadTexture(const char *texturePath);
    ~textureData();
};

#endif