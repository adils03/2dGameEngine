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

void VertexArray::unbind() {
    glBindVertexArray(0);
}
