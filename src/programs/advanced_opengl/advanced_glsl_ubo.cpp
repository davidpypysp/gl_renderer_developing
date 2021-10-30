#include "programs/global.h"

namespace glrd
{
    int AdvancedGLSLUbo()
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(mWidth, mHeight, "Advanced ubo", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glEnable(GL_DEPTH_TEST);

        Shader shaderRed("4.8.1.advanced_glsl.vert", "4.8.1.red.frag");
        Shader shaderGreen("4.8.1.advanced_glsl.vert", "4.8.1.green.frag");
        Shader shaderBlue("4.8.1.advanced_glsl.vert", "4.8.1.blue.frag");
        Shader shaderYellow("4.8.1.advanced_glsl.vert", "4.8.1.yellow.frag");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float cubeVertices[] = {
            // positions
            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,

            -0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,

            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,

            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,

            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,

            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
        };

        unsigned int cubeVAO, cubeVBO;
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.ID, "Matrices");
        unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.ID, "Matrices");
        unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.ID, "Matrices");
        unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.ID, "Matrices");
        // then we link each shader's uniform block to this uniform binding point
        glUniformBlockBinding(shaderRed.ID, uniformBlockIndexRed, 0);
        glUniformBlockBinding(shaderGreen.ID, uniformBlockIndexGreen, 0);
        glUniformBlockBinding(shaderBlue.ID, uniformBlockIndexBlue, 0);
        glUniformBlockBinding(shaderYellow.ID, uniformBlockIndexYellow, 0);

        unsigned int uboMatrices;
        glGenBuffers(1, &uboMatrices);
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

        glm::mat4 projection = glm::perspective(45.0f, (float)mWidth / (float)mHeight, 0.1f, 100.0f);
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        while (!glfwWindowShouldClose(window))
        {
            /* code */
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 view = camera.GetViewMatrix();
            glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
            glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            glBindVertexArray(cubeVAO);
            shaderRed.use();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));
            shaderRed.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // green
            shaderGreen.use();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));
            shaderGreen.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // yellow
            shaderYellow.use();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));
            shaderYellow.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // blue
            shaderBlue.use();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));
            shaderBlue.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteBuffers(1, &cubeVBO);

        glfwTerminate();
        return 0;
    }
}

int main() {
    return glrd::AdvancedGLSLUbo();
}