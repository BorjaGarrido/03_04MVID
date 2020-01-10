#include <glad/glad.h>

#include "engine/window.hpp"
#include "engine/shader.hpp"

#include "engine/texture.hpp"
#include "engine/geometry/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

void handleInput() {/*Intentionally Left BLank*/ }

void render(const Geometry& geom1, const Geometry& geom2, const Geometry& geom3, const Geometry& geom4, const Shader& shader, Texture& tex) {

    glClear(GL_COLOR_BUFFER_BIT);  


    glm::mat4 model4 = glm::mat4(1.0f);
    model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view4 = glm::mat4(1.0f);
    view4 = glm::translate(view4, glm::vec3(0.0f, -2.5f, -3.0f));

    glm::mat4 proj4 = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model4);
    shader.set("view", view4);
    shader.set("proj", proj4);  //TODO const mat4

    geom4.render();

    
    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::rotate(model1,  glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    glm::mat4 view1 = glm::mat4(1.0f);
    view1 = glm::translate(view1, glm::vec3(-2.0f, 0.0f, -15.0f));

    glm::mat4 proj1 = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model1);
    shader.set("view", view1);
    shader.set("proj", proj1);  //TODO const mat4

    geom1.render();
    
    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::rotate(model2, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view2 = glm::mat4(1.0f);
    view2 = glm::translate(view2, glm::vec3(0.5f, -0.5f, -3.0f));

    glm::mat4 proj2 = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model2);
    shader.set("view", view2);
    shader.set("proj", proj2);  //TODO const mat4

    geom2.render();

    glm::mat4 model3 = glm::mat4(1.0f);
    model3 = glm::rotate(model3, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view3 = glm::mat4(1.0f);
    view3 = glm::translate(view3, glm::vec3(-0.1f, -0.5f, -2.0f));

    glm::mat4 proj3 = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model3);
    shader.set("view", view3);
    shader.set("proj", proj3);  //TODO const mat4

    geom3.render();


    // const Geometry& geom1, const Geometry& geom2, const Geometry& geom3,   :vec3(1.5f, 3.0f, 1.0f)
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
        handleInput();
        render(cube1, cube2, cube3, cube4, shader, tex);
        window->frame();
    }

    return 0;
}