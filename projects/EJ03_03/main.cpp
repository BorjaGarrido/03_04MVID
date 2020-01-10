#include <glad/glad.h>

#include "engine/input.hpp"
#include "engine/window.hpp"
#include "engine/shader.hpp"

#include <iostream>
#include <GLFW\glfw3.h>

void handleInput() {
    std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();
    for (auto& key : keys) {
        std::cout << key.first << " - " << key.second << std::endl;
    }
}

uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
    float vertices[] = {
        -1.0f,  0.0f, 0.0f,      1.0f, 0.0f, 0.0f,
        -0.95f,  0.1f, 0.0f,     0.0f, 1.0f, 0.0f,
        -0.9f,  0.0f, 0.0f,       0.0f, 0.0f, 1.0f
    };

    uint32_t indices[] = {
        0, 2, 1
    };

    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}


void render(uint32_t VAO, const Shader& shader, float changeColor[3], float pos) {
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.set("addColor", changeColor[0], changeColor[1], changeColor[2]);

    shader.use();
    shader.set("changePos", pos, 0.0f, 0.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

int main(int, char* []) {
    Window* window = Window::instance();

    double lastTime = glfwGetTime(), timer = lastTime;

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    float changeColor[3] = { 0.0f, 0.0f, 0.2f };

    float pos = 0.0;

    uint32_t VBO, EBO;
    const uint32_t VAO = createVertexData(&VBO, &EBO);
    const Shader shader("../projects/EJ03_03/vertex.vs", "../projects/EJ03_03/fragment.fs");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {

        // - Timer de un segundo
        if (glfwGetTime() - timer > 1.0) {

            handleInput();
            render(VAO, shader, changeColor, pos);
            window->frame();

            std::cout << "Timer: " << timer << std::endl;

            for (int i = 0; i < 3; i++) {
                if (i == 2 && changeColor[2] < 1.0) {
                    changeColor[i] = changeColor[i] + 0.2;

                    pos = pos + 0.1;
                }
                else if (i == 1 && changeColor[1] < 1.0 && changeColor[2] == 1.0) {
                    changeColor[i] = changeColor[i] + 0.2;

                    pos = pos + 0.1;
                }
                else if (i == 0 && changeColor[0] < 1.0 && changeColor[2] == 1.0 && changeColor[1] == 1.0) {
                    changeColor[i] = changeColor[i] + 0.2;

                    pos = pos + 0.1;
                }
                else if (changeColor[0] == 1.0 && changeColor[2] == 1.0 && changeColor[1] == 1.0) {
                    changeColor[0] = 0.0;
                    changeColor[1] = 0.0;
                    changeColor[2] = 0.0;

                    pos = pos + 0.1;
                }
            }

            timer++;
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}