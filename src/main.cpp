#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <fmt/core.h>
#include <iostream>
#include "header/Shader.hpp"//for compiling shaders.
#include <vector>
//==================
//  THINGS LEFT TO FINISH (for spinning cube)
//  1. FINISH UP SHADER CLASS (done)
//  2. MAKE BUFFERS FOR OBJECTS -> VBO and index buffer.(DONE)
//  3. CAMERA CLASS.
//==================

//make global shaders paths. this is for testing. 
std::string VS_path = "../src/Assets/Shaders/main.vert";
std::string FS_path = "../src/Assets/Shaders/main.frag";

int main() {
    // 1. Test GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW init failed!" << std::endl;
        return -1;
    }

    // 2. Test OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple_Engine", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Window creation failed!" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3. Test GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD init failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 4. Enable sticky keys (ADD THIS RIGHT AFTER GLAD INIT)
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Debug prints
    std::cout << "=== OpenGL Debug ===" << std::endl;
    std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "====================" << std::endl << std::flush;
    //============
    //SHADER SETUP
    //============
    Shader basic_Shader;
    basic_Shader.setUpShader(VS_path,FS_path);//setup shader.
    //============
    //CREATE MESH
    //============
    std::vector<glm::vec3> positions = { { -1.0, -1.0, -1.0 },
                                        { -1.0, -1.0, 1.0 },
                                        { -1.0, 1.0, -1.0 },
                                        { -1.0, 1.0, 1.0 },
                                        { 1.0, -1.0, -1.0 },
                                        { 1.0, -1.0, 1.0 },
                                        { 1.0, 1.0, -1.0 },
                                        { 1.0, 1.0, 1.0 } };
    for (auto& pos : positions) {
        pos *= 0.5f;
    }

    std::vector<uint32_t> indices = {
        1, 7, 5, 1, 3, 7, 1, 4, 3, 1, 2, 4, 3, 8, 7, 3, 4, 8, 5, 7, 8, 5, 8, 6, 1, 5, 6, 1, 6, 2, 2, 6, 8, 2, 8, 4
    };
    for (auto& index : indices) {
        index -= 1;
    }

     // 4. Test GLM
    glm::vec3 testVec(1.0f);
    std::cout << "GLM test: " << testVec.x << std::endl;
    // 5. Test ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    std::cout << "ImGui initialized" << std::endl;
    ImGui::DestroyContext();
    // 6. Test fmt
    fmt::print("fmt test: {}\n", "Success!");


    // After GLAD initialization
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);  // Pure cyan (full green + blue

    // 5. Main rendering loop (REPLACE YOUR EXISTING LOOP WITH THIS)
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render commands would go here (e.g., draw a triangle)

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        // ESC key to close window
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }
    }
    // 4. Optional: Post-render debug
    std::cout << "Cleanup phase..." << std::endl;

    // Cleanup
    glfwTerminate();
    return 0;
}