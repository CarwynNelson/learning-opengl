#pragma once

#include "glitter.hpp"
#include <iostream>

class Texture
{
public:
    Texture(const std::string& location, bool hasAlpha = false)
    {
        stbi_set_flip_vertically_on_load(true);
        // Generate a "texture buffer"
        glGenTextures(1, &mId);
        glBindTexture(GL_TEXTURE_2D, mId);

        // load the image data into cpu memory
        auto imageData = stbi_load(
            (mBasePath + location).c_str(),
            &mWidth, &mHeight, &mChannelCount, 0
        );
        
        // TODO: Handle if there is no image data

        // load the image into the gpu and generate mipmaps
        GLenum format = hasAlpha ? GL_RGBA : GL_RGB;
        glTexImage2D(
                GL_TEXTURE_2D, 0,
                format, mWidth, mHeight,
                0, format, GL_UNSIGNED_BYTE,
                imageData
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        // release the image data from the cpu
        stbi_image_free(imageData);
    }

    void Activate(const int unitId = 0)
    {
        glActiveTexture(GL_TEXTURE0 + unitId);
        glBindTexture(GL_TEXTURE_2D, mId);
    }

    int Id() const
    {
        return mId;
    }
private:
    static int sUnitId;
    unsigned int mId;
    int mWidth, mHeight, mChannelCount;
    const std::string mBasePath = "./../Glitter/Resources/";
};

// Texture container("container.jpg");
// t.nothing...

