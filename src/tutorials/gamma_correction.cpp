#include "local.hpp"

namespace gl_examples
{
    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    bool gammaEnabled = false;
    bool gammaKeyPressed = false;

    void processInputWithSpace(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !gammaKeyPressed)
        {
            gammaEnabled = !gammaEnabled;
            gammaKeyPressed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
        {
            gammaKeyPressed = false;
        }
    }

    int GammaCorrection()
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
        GLFWwindow *window = glfwCreateWindow(mWidth, mHeight, "Gamma Correction", NULL, NULL);
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Shader shader("5.2.1.gamma_correction.vert", "5.2.1.gamma_correction.frag");

        float planeVertices[] = {
            // positions            // normals         // texcoords
            10.0f,
            -0.5f,
            10.0f,
            0.0f,
            1.0f,
            0.0f,
            10.0f,
            0.0f,
            -10.0f,
            -0.5f,
            10.0f,
            0.0f,
            1.0f,
            0.0f,
            0.0f,
            0.0f,
            -10.0f,
            -0.5f,
            -10.0f,
            0.0f,
            1.0f,
            0.0f,
            0.0f,
            10.0f,

            10.0f,
            -0.5f,
            10.0f,
            0.0f,
            1.0f,
            0.0f,
            10.0f,
            0.0f,
            -10.0f,
            -0.5f,
            -10.0f,
            0.0f,
            1.0f,
            0.0f,
            0.0f,
            10.0f,
            10.0f,
            -0.5f,
            -10.0f,
            0.0f,
            1.0f,
            0.0f,
            10.0f,
            10.0f};

        unsigned int planeVAO, planeVBO;
        glGenVertexArrays(1, &planeVAO);
        glGenBuffers(1, &planeVBO);
        glBindVertexArray(planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glBindVertexArray(0);

        unsigned int floorTexture = loadTexture("resources/textures/wood.png", false);
        unsigned int floorTextureGammaCorrected = loadTexture("resources/textures/wood.png", true);

        shader.use();
        shader.setInt("floorTexture", 0);

        // lighting info
        // -------------
        glm::vec3 lightPositions[] = {glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(3.0f, 0.0f, 0.0f)};
        glm::vec3 lightColors[] = {
            glm::vec3(0.25),
            glm::vec3(0.50),
            glm::vec3(0.75),
            glm::vec3(1.00)};

        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInputWithSpace(window);

            // render
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // draw objects
            shader.use();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            shader.setMat4("projection", projection);
            shader.setMat4("view", view);

            // set light uniforms
            glUniform3fv(glGetUniformLocation(shader.ID, "lightPositions"), 4, &lightPositions[0][0]);
            glUniform3fv(glGetUniformLocation(shader.ID, "lightColors"), 4, &lightColors[0][0]);
            shader.setVec3("viewPos", camera.Position);
            shader.setInt("gamma", gammaEnabled);
            // floor
            glBindVertexArray(planeVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, gammaEnabled ? floorTextureGammaCorrected : floorTexture);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            std::cout << (gammaEnabled ? "Gamma enabled" : "Gamma disabled") << std::endl;

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &planeVAO);
        glDeleteBuffers(1, &planeVBO);

        glfwTerminate();
        return 0;
    }

}