#pragma once
//include libaries.
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <fmt/core.h>
#include <iostream>
#include <vector>
class mesh
{
public:

    mesh(const std::vector<glm::vec3>& verts, const std::vector<uint32_t>& inds);
    ~mesh();

    GLuint vbo = 0;
    GLuint ibo = 0;
    GLuint vao = 0;

    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;

    void bind() const;
    void draw() const;
};