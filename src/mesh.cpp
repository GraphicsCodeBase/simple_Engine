#include "header/mesh.hpp"

mesh::mesh()
{
    // Safe default: no buffers generated yet.
    vbo = 0;
    ibo = 0;
    vao = 0;
}

mesh::mesh(const std::vector<glm::vec3>& verts, const std::vector<uint32_t>& inds)
	: vertices(verts), indices(inds)
{
    // Generate VAO, VBO, IBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // Setup vertex attribute pointer for position (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,              // attribute index
        3,              // size (vec3)
        GL_FLOAT,       // type
        GL_FALSE,       // normalized?
        sizeof(glm::vec3), // stride
        (void*)0        // offset
    );

    glBindVertexArray(0);
}

mesh::~mesh()
{
    // Delete buffers and VAO to free GPU resources
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteVertexArrays(1, &vao);
}

void mesh::bind() const
{
    glBindVertexArray(vao);
}

void mesh::draw() const
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}