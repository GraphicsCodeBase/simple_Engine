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

    mesh();
    mesh(const std::vector<glm::vec3>& verts, const std::vector<uint32_t>& inds);
    //move constructor.
    mesh(mesh&& other)
        : vao(other.vao), vbo(other.vbo), ibo(other.ibo),
        vertices(std::move(other.vertices)), indices(std::move(other.indices))
    {
        other.vao = 0;
        other.vbo = 0;
        other.ibo = 0;
    }
    // Disallow copy
    mesh(const mesh&) = delete;
    mesh& operator=(const mesh&) = delete;

    ~mesh();

    GLuint vbo = 0;
    GLuint ibo = 0;
    GLuint vao = 0;

    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;

    //mesh move assignment.
    mesh& operator=(mesh&& other) noexcept
    {
        if (this != &other)
        {
            // Delete old resources
            if (vao) glDeleteVertexArrays(1, &vao);
            if (vbo) glDeleteBuffers(1, &vbo);
            if (ibo) glDeleteBuffers(1, &ibo);

            // Steal other's resources
            vao = other.vao;
            vbo = other.vbo;
            ibo = other.ibo;
            vertices = std::move(other.vertices);
            indices = std::move(other.indices);

            // Null out the other
            other.vao = 0;
            other.vbo = 0;
            other.ibo = 0;
        }

        return *this;
    }


    void bind() const;
    void draw() const;
};