#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/window.hpp"
#include "engine/geometry/sphere.hpp"
#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void handleInput(float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        camera.handleKeyboard(Camera::Movement::Forward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        camera.handleKeyboard(Camera::Movement::Backward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        camera.handleKeyboard(Camera::Movement::Left, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        camera.handleKeyboard(Camera::Movement::Right, dt);
    }
}

void onKeyPress(int key, int action) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(true);
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(false);
    }
}

void onMouseMoved(float x, float y) {
    if (firstMouse) {
        firstMouse = false;
        lastX = x;
        lastY = y;
    }

    const float xoffset = x - lastX;
    const float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    camera.handleMouseMovement(xoffset, yoffset);
}

void onScrollMoved(float x, float y) {
    camera.handleMouseScroll(y);
}



void render(const Geometry& geom1, const Geometry& geom2, const Geometry& geom3, const Geometry& geom4, const Shader& shader, Texture& tex) {

    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 model4 = glm::mat4(1.0f);
    model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view4 = glm::mat4(1.0f);
    view4 = glm::translate(view4, glm::vec3(0.0f, -2.5f, -3.0f));

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model4);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    geom4.render();


    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::rotate(model1, glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    glm::mat4 view1 = glm::mat4(1.0f);
    view1 = glm::translate(view1, glm::vec3(-2.0f, 0.0f, -15.0f));

    shader.set("model", model1);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    geom1.render();

    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::rotate(model2, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view2 = glm::mat4(1.0f);
    view2 = glm::translate(view2, glm::vec3(0.5f, -0.5f, -3.0f));

    shader.set("model", model2);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    geom2.render();

    glm::mat4 model3 = glm::mat4(1.0f);
    model3 = glm::rotate(model3, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view3 = glm::mat4(1.0f);
    view3 = glm::translate(view3, glm::vec3(-0.1f, -0.5f, -2.0f));

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model3);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    geom3.render();
    
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/EJ05_04/vertex.vs", "../projects/EJ05_04/fragment.fs");
    const Cube cube1(4.0f);
    const Cube cube2(0.5f);
    const Cube cube3(0.6f);
    const Cube cube4(4.0f);

    Texture tex("../assets/textures/cubo.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        render(cube1, cube2, cube3, cube4, shader, tex);
        window->frame();
    }

    return 0;
}