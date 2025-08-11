#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <fmt/core.h>
#include <iostream>
#include <vector>
#include "header/Shader.hpp"//for compiling shaders.
#include "header/camera.hpp"
#include "header/MeshLoader.hpp"
//==================
//  THINGS LEFT TO FINISH 
//  1. add a model loader from assimp
//  2. bind it into the opengl renderer.
//==================

//make global shaders paths. this is for testing. 
//apparently the path starts from the exe file path.
std::string VS_path = "../src/Assets/Shaders/main.vert";
std::string FS_path = "../src/Assets/Shaders/main.frag";
std::string model_path = "Assets/klee_mdl.glb";
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
    //get window width and height.
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    //============
    //SHADER SETUP
    //============
    Shader basic_Shader;
    basic_Shader.setUpShader(VS_path,FS_path);//setup shader.
    //============
    //CREATE MESH
    //============
    //vertex positions.
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

    //================
    //  MODEL LOADER
    //================
    MeshLoader loader;
    
    //================
    //  OBJECT SETUP
    //================
    object testObject;
    testObject.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));//start at the origin.
    testObject.setScale(glm::vec3(2.0f, 2.0f, 2.0f));
    testObject.setRotation(0.0f);
    testObject.uploadMesh(positions, indices);

    //model object 
    std::shared_ptr<object> secondObject = loader.loadMesh(model_path);
    secondObject->setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
    secondObject->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
    secondObject->setRotation(0.0f);
    //================
    //  CAMERA SETUP 
    //================
    camera main_camera;

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

    double lastTime = glfwGetTime();//record the last time.
    // 5. Main rendering loop (REPLACE YOUR EXISTING LOOP WITH THIS)
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);
        // Render commands would go here (e.g., draw a triangle)
        basic_Shader.use(); //bind shader.
        //get the delta time
        double currentTime = glfwGetTime();
        double dt = currentTime - lastTime;
        lastTime = currentTime;//update last time. 
        //update camera
        main_camera.update(static_cast<float>(dt),window,display_w,display_h);
        testObject.update(static_cast<float>(dt));
        //set uniforms.
        basic_Shader.setMat4("uniform_m2w",testObject.getmodelMat());//model to world matrix
        basic_Shader.setMat4("uniform_vp",main_camera.getViewProj());//camera matrix.
        basic_Shader.setVec4("uniform_color", glm::vec4(1.0f, 0.0f, 0.0f,0.0f));//set to red for now.
        //testObject.render();
        secondObject->renderObject();
        //unbind shader
        basic_Shader.unUse();
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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