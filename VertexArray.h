#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>
#include "VertexBuffer.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void linkAttribute(GLuint location, GLint size, GLenum type, GLboolean normalize, GLsizei stride, const void* offset) const;
    void LinkAttributes();
    static void unbind();

private:
    GLuint ID;
};

#endif
