#include <stb/stb_image.h>
#include <iostream>

#include "Object/textureData.hpp"

using namespace std;

void textureData::loadTexture(string texturePath, int i)
{
    string newPath = "../textures/" + texturePath;
    const char *absolutePath = newPath.c_str();

    index = 0;

    glGenTextures(1, &Texture_ID);
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, Texture_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(absolutePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
}

unsigned int textureData::getTexture_ID() { return Texture_ID; }
void textureData::bindTexture() { 
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, Texture_ID);
}
void textureData::clearTexture() {
    // glActiveTexture(GL_TEXTURE0 + index);
    // glBindTexture(GL_TEXTURE_2D, NULL);
}

// unsigned int textureData::EmptyTexture_ID = -1;
// void textureData::bindEmptyTexture() {
//     if (EmptyTexture_ID == -1) {
//         string newPath = "../textures/EmptyTexture";
//         const char *absolutePath = newPath.c_str();

//         glGenTextures(1, &EmptyTexture_ID);
//         glBindTexture(GL_TEXTURE_2D, EmptyTexture_ID);

//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//         unsigned char *data = stbi_load(absolutePath, &width, &height, &nrChannels, 0);
//         if (data)
//         {
//             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//             glGenerateMipmap(GL_TEXTURE_2D);
//         }
//         else
//         {
//             cout << "Failed to load texture" << endl;
//         }
//         stbi_image_free(data);
//     }
//     glBindTexture(GL_TEXTURE_2D, EmptyTexture_ID);
// }