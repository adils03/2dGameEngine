#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
    bind();
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::bind() const {
    glBindVertexArray(ID);
}

void VertexArray::linkAttribute(GLuint location, GLint size, GLenum type, GLboolean normalize, GLsizei stride, const void* offset) const
{
    glVertexAttribPointer(location, size, type, normalize, stride, offset);
    glEnableVertexAttribArray(location);
}

void VertexArray::LinkAttributes()
{
    linkAttribute(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    linkAttribute(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    linkAttribute(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}
