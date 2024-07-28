#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <glad/glad.h>

class ElementBuffer {
public:
    ElementBuffer(GLsizeiptr size);
    ~ElementBuffer();

    void bind() const;
    static void unbind();
    void setData(const void* data) const;

private:
    GLuint ID;
    GLsizeiptr size;
};

#endif
