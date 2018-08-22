// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// my headers
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

// utils
std::string LoadFileAsString(const std::string location)
{
    auto basePath = "./../Glitter/";

    std::ifstream file;
    file.open(basePath + location);
    
    if (!file.good())
    {
        std::cout << "ERROR::FILESYSTEM::COULD_NOT_LOAD_FILE : " << location << std::endl;
        return "ERROR: SEE ABOVE";
    }

    std::stringstream fileContents;
    fileContents << file.rdbuf();

    auto result = fileContents.str();

    return result;
}

// Define Some Constants
//const int mWidth = 1280;
//const int mHeight = 800;
const int mWidth = 640;
const int mHeight = 360;

#endif //~ Glitter Header
