#include <stb/stb_image.h>
#include <iostream>

#include "Object/textureData.hpp"

using namespace std;

void textureData::loadTexture(string texturePath)
{
    string newPath = "../textures/" + texturePath;
    const char *absolutePath = newPath.c_str();

    glGenTextures(1, &IMAGE_ID);
    glBindTexture(GL_TEXTURE_2D, IMAGE_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(absolutePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
}

unsigned int textureData::getTexture_ID() { return IMAGE_ID; }

void textureData::bindTexture() { glBindTexture(GL_TEXTURE_2D, getTexture_ID()); }