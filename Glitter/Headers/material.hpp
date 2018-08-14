#pragma once

#include "glitter.hpp"
#include <vector>

#include "texture.hpp"
#include "shader.hpp"

// TODO: note to self: being wasteful with texture ids
class Material
{
public:
    Material(const Shader* shader, Texture* firstTexture)
        : mShader(shader)
    {
        textures.push_back(firstTexture);
    }

    void Apply() const
    {
        mShader->Use();
        mShader->SetInt("texture2", 1); // this needs to be made more generic - maybe these are like the properties in an engine like unity?

        for (std::vector<Texture*>::size_type i = 0; i < textures.size(); i++)
        {
            auto texture = textures[i];
            texture->Activate(i);
        }
    }

    void AddTexture(Texture* texture)
    {
        textures.push_back(texture);
    }
private:
    const Shader* mShader;
    std::vector<Texture*> textures;
};
