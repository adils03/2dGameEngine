#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/glad.h>

class VertexBuffer {
public:
    VertexBuffer(GLsizeiptr size);
    ~VertexBuffer();

    void bind() const;
    static void unbind();
    void setData(const void* data) const;

private:
    GLuint ID;
    GLsizeiptr size;
};

#endif
