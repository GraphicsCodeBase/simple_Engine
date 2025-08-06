#Minimum cmake version.
cmake_minimum_required(VERSION 3.8)
#Project name.
project(basic_OPEN_GL_PROJECT)

# Demo
add_executable(${PROJECT_NAME}
        main.cpp
        header/object.hpp "object.cpp"
        header/Shader.hpp "shader.cpp"
        header/mesh.hpp "mesh.cpp" "camera.cpp"
        header/camera.hpp "camera.cpp" 
        header/MeshLoader.hpp  "MeshLoader.cpp")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20) 

## ImGui
find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)

## ImGuizmo
#find_package(imguizmo CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE imguizmo::imguizmo)

# GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

# GLAD
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)

# GLFW3
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# fmt
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)

#assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp)