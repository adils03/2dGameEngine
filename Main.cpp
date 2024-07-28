#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "Light.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <STB/stb_image.h>

Shader* shader;
Camera camera(800.0f,800.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    shader->setVec2("viewPortSize", glm::vec2(width, height));
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.setPosition(camera.getPosition() + glm::vec2(0.0f, 10.0f));
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.setPosition(camera.getPosition() + glm::vec2(0.0f, -10.0f));
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.setPosition(camera.getPosition() + glm::vec2(-10.0f, 0.0f));
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.setPosition(camera.getPosition() + glm::vec2(10.0f, 0.0f));
    }
}

void setTransform(const glm::vec3& translate, float rotation, float scale) {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, translate);
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(scale, scale, 1.0f));

    shader->setMat4("transform", transform);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(400, 400, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 400, 400);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    shader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1, 0, 0, 1, 0.0f, 0.0f,  // K��e 0 (K���k sol alt)
        -0.5f,  0.5f, 0.0f, 0, 1, 0, 1, 0.0f, 1.0f,  // K��e 1 (K���k sol �st)
         0.5f,  0.5f, 0.0f, 0, 0, 1, 1, 1.0f, 1.0f,  // K��e 2 (K���k sa� �st)
         0.5f, -0.5f, 0.0f, 1, 1, 0, 1, 1.0f, 0.0f   // K��e 3 (K���k sa� alt)
    };

    unsigned int indices[6] = {
        0, 2, 1,  // ��gen 1: (K��e 0, K��e 2, K��e 1)
        0, 3, 2   // ��gen 2: (K��e 0, K��e 3, K��e 2)
    };

    VertexArray vao;

    VertexBuffer vbo(sizeof(vertices));
    vbo.setData(vertices);

    ElementBuffer ebo(sizeof(indices));
    ebo.setData(indices);

    VertexBuffer::unbind();
    VertexArray::unbind();

    Texture texture("resources/textures/pngwing.com.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture.texUnit(*shader, "tex0", 0);

    // �effafl�k
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader->setVec2("viewPortSize", glm::vec2(400, 400));

    float lastFrame = 0.0f;
    float value = 0.0f;

    // light
    Light light(glm::vec2(200,300), glm::vec3(1, 1, 1), 150);
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        value += deltaTime;

        shader->use();
        shader->setMat4("viewProjection", camera.getViewProjection());
        light.use(*shader);
        texture.Bind();
        setTransform(glm::vec3(400, 300, 0.0f), 0.0f, 100.0f);  // D�nya koordinatlar� ve �l�ek
        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        shader->use();
        shader->setMat4("viewProjection", camera.getViewProjection());
        light.use(*shader);
        texture.Bind();
        setTransform(glm::vec3(value*55, 300, 0.0f), 0.0f, 100.0f);  // D�nya koordinatlar� ve �l�ek
        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shader->deleteShader();
    texture.Delete();
    glfwTerminate();
    return 0;
}
