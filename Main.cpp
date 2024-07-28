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
#include "GameObject.h"
#include "Transform.h"

int swidth = 1280;
int sheight = 768;
Shader* shader;
Camera* camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera->setPosition(camera->getPosition() + glm::vec2(0.0f, 10.0f));
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera->setPosition(camera->getPosition() + glm::vec2(0.0f, -10.0f));
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera->setPosition(camera->getPosition() + glm::vec2(-10.0f, 0.0f));
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera->setPosition(camera->getPosition() + glm::vec2(10.0f, 0.0f));
    }
}

void setTransform(const glm::vec3& translate, float rotation,glm::vec2 scale) {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, translate);
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(scale, 1.0f));

    shader->setMat4("transform", transform);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(swidth, sheight, "OpenGL", NULL, NULL);
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

    glViewport(0, 0, swidth, sheight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    shader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1, 0, 0, 1, 0.0f, 0.0f,  // Köþe 0 (Küçük sol alt)
        -0.5f,  0.5f, 0.0f, 0, 1, 0, 1, 0.0f, 1.0f,  // Köþe 1 (Küçük sol üst)
         0.5f,  0.5f, 0.0f, 0, 0, 1, 1, 1.0f, 1.0f,  // Köþe 2 (Küçük sað üst)
         0.5f, -0.5f, 0.0f, 1, 1, 0, 1, 1.0f, 0.0f   // Köþe 3 (Küçük sað alt)
    };

    unsigned int indices[6] = {
        0, 2, 1,  // Üçgen 1: (Köþe 0, Köþe 2, Köþe 1)
        0, 3, 2   // Üçgen 2: (Köþe 0, Köþe 3, Köþe 2)
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

    

    // Þeffaflýk
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float lastFrame = 0.0f;
    float value = 0.0f;

    Transform transform(*shader, glm::vec2(300, 300), 0, glm::vec2(100, 100));
    Light light(*shader,glm::vec2(200,300), glm::vec3(1, 1, 1), 150);

    camera = new Camera(*shader, static_cast<float>(swidth),static_cast<float>(sheight));
    GameObject gameobject(*shader,transform);

    shader->setPriority(0);
    transform.setPriority(1);
    camera->setPriority(2);
    light.setPriority(3);
    texture.setPriority(5);


    gameobject.addComponent(camera);
    gameobject.addComponent(shader);
    gameobject.addComponent(&light);
    gameobject.addComponent(&texture);



    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        value += deltaTime;

        transform.Translate(glm::vec2(50,0)*deltaTime);

        gameobject.update();
        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);


        //
        //shader->use();
        //shader->setMat4("viewProjection", camera->getViewProjection());
        //light.use(*shader);
        //texture.Bind();
        //setTransform(glm::vec3(value, 300, 0.0f), 0.0f, glm::vec2(100,100));  // Dünya koordinatlarý ve ölçek
        //vao.bind();
        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        //

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shader->deleteShader();
    texture.Delete();
    glfwTerminate();
    return 0;
}
