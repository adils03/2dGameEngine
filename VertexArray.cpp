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

void VertexArray::unbind() {
    glBindVertexArray(0);
}
