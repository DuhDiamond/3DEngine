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
    unsigned int Texture_ID;
    // once an object without a texture is found, loads the empty texture into OpenGL and sets to the id
    // static unsigned int EmptyTexture_ID;
public:
    unsigned int index = -1;

    void loadTexture(string texturePath, int i);
    unsigned int getTexture_ID();
    void bindTexture();
    void clearTexture();
    // void bindEmptyTexture();
};

#endif