// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"

namespace gl_examples
{
    // Define Some Constants
    const int mWidth = 1280;
    const int mHeight = 800;

    extern Camera camera;
    extern float lastX;
    extern float lastY;
    extern bool firstMouse;

    // timing
    extern float deltaTime; // time between current frame and last frame
    extern float lastFrame;

    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void processInput(GLFWwindow *window);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    int HelloWindow();
    int HelloTriangle();
    int Shaders();
    int TexturesCombined();
    int Transformations();
    int CoordinateSystemMultiple();
    int CameraClass();
    int ColorsProgram();
    int BasicLightingProgram();
    int MaterialProgram();
    int MultipleLights();
    int ModelProgram();
    int StencilTestingProgram();
    int BlendingSorted();
} // namespace gl_examples

#endif //~ Glitter Header
