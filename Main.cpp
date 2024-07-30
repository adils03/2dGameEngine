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
#include "Collision.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

const int FIXED_WIDTH = 1280;
const int FIXED_HEIGHT = 768;
Transform* transform;
Shader* shader;
Shader* shader2;
Camera* camera;
float deltaTime;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

float speed = 100;

void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	///
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		transform->Translate(glm::vec2(0, speed) * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		transform->Translate(glm::vec2(0, -speed) * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		transform->Translate(glm::vec2(-speed, 0) * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		transform->Translate(glm::vec2(speed, 0) * deltaTime);
	}
	/////
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->move(glm::vec2(0, 1000) * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->move(glm::vec2(0, -1000) * deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->move(glm::vec2(-1000, 0) * deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->move(glm::vec2(1000, 0) * deltaTime);

	}
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	if (!primaryMonitor) {
		std::cerr << "Failed to get primary monitor" << std::endl;
		glfwTerminate();
		return -1;
	}

	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
	if (!mode) {
		std::cerr << "Failed to get video mode" << std::endl;
		glfwTerminate();
		return -1;
	}

	int xpos = (mode->width - FIXED_WIDTH) / 2;
	int ypos = (mode->height - FIXED_HEIGHT) / 2;

	GLFWwindow* window = glfwCreateWindow(FIXED_WIDTH, FIXED_HEIGHT, "OpenGL", NULL, NULL);
	glfwSetWindowPos(window, xpos, ypos);
	glfwSetWindowSizeLimits(window, FIXED_WIDTH, FIXED_HEIGHT, FIXED_WIDTH, FIXED_HEIGHT);

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
	glViewport(0, 0, FIXED_WIDTH, FIXED_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	shader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	shader2 = new Shader("resources/shaders/vertex_shader2.glsl", "resources/shaders/fragment_shader2.glsl");

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

	vao.LinkAttributes();

	VertexBuffer::unbind();
	VertexArray::unbind();

	Texture texture("resources/textures/pngwing.com.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture texture2("resources/textures/pngwing.com.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(*shader, "tex0", 0);
	texture2.texUnit(*shader2, "tex0", 0);

	

	// Þeffaflýk
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float lastFrame = 0.0f;
	float value = 0.0f;

	transform = new Transform(*shader, glm::vec2(0, 0), 0, glm::vec2(100, 100));
	Transform transform2(*shader2, glm::vec2(50, 75), 0, glm::vec2(100, 100));

	Light light(*shader, glm::vec2(0, 0), glm::vec3(1, 1, 1), 1000);
	Light light2(*shader2, glm::vec2(0, 0), glm::vec3(1, 1, 1), 1000);

	camera = new Camera(*shader, static_cast<float>(FIXED_WIDTH), static_cast<float>(FIXED_HEIGHT));
	GameObject gameobject(*shader, *transform);
	GameObject gameobject2(*shader2, transform2);

	BoxCollider collider1(*transform, transform->position, 1, transform->scale,100,100);
	BoxCollider collider2(transform2, transform2.position, 1, transform2.scale, 100,100);

	camera->setPriority(2);
	light.setPriority(3);
	texture.setPriority(5);
	collider1.setPriority(4);

	light2.setPriority(3);
	texture2.setPriority(5);
	collider2.setPriority(4);

	gameobject.addComponent(camera);
	gameobject.addComponent(shader);
	gameobject.addComponent(&collider1);
	gameobject.addComponent(&light);
	gameobject.addComponent(&texture);

	gameobject2.addComponent(camera);
	gameobject2.addComponent(shader2);
	gameobject2.addComponent(&collider2);
	gameobject2.addComponent(&light);
	gameobject2.addComponent(&texture);

	int indiceCount = sizeof(indices) / sizeof(unsigned int);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window, deltaTime);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

		value += deltaTime;

		glm::vec2 normal = glm::vec2();
		float depth = 0;

		if (Collisions::IntersectPolygons(collider1.position, collider2.position,collider1.getVertices(),collider2.getVertices(),normal,depth)) {
			collider1.Translate(-normal * depth);
			collider2.Translate(normal * depth);
		}
		gameobject.update();
		vao.bind();
		glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);

		gameobject2.update();
		vao.bind();
		glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//cleanup
	shader->deleteShader();
	texture.Delete();
	glfwTerminate();
	return 0;
}
