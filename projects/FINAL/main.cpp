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
#include "engine/geometry/quad.hpp"
#include <engine\model.hpp>
#include <iostream>

#pragma region Declaraciones Globales
    Camera camera(glm::vec3(0.0f, 0.0f, 15.0f));

    glm::vec3 modelPosition(0.0f, -3.0f, -0.25f);  
    glm::vec3 lightPos(0.0f, -2.5f, 0.0f);
    glm::vec3 velPos(0.075f, 0.075f, 0.0f);
    bool startGame = false;
    int contadorCubos = 0;

    int vidas = 3;

    bool dibujarModels = true;

    float lastFrame = 0.0f;
    float lastX, lastY;
    bool firstMouse = true;

    glm::vec3 cubePositions[] = {
        glm::vec3(-3.0f, 3.0f, 0.0f),
        glm::vec3(-2.0f, 3.0f, 0.0f),
        glm::vec3(-1.0f, 3.0f, 0.0f),
        glm::vec3( 0.0f, 3.0f, 0.0f),
        glm::vec3( 1.0f, 3.0f, 0.0f),
        glm::vec3( 2.0f, 3.0f, 0.0f),
        glm::vec3( 3.0f, 3.0f, 0.0f),
        glm::vec3(-3.0f, 2.0f, 0.0f),
        glm::vec3(-2.0f, 2.0f, 0.0f),
        glm::vec3(-1.0f, 2.0f, 0.0f),
        glm::vec3(0.0f, 2.0f, 0.0f),
        glm::vec3(1.0f, 2.0f, 0.0f),
        glm::vec3(2.0f, 2.0f, 0.0f),
        glm::vec3(3.0f, 2.0f, 0.0f),
        glm::vec3(-3.0f, 1.0f, 0.0f),
        glm::vec3(-2.0f, 1.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(2.0f, 1.0f, 0.0f),
        glm::vec3(3.0f, 1.0f, 0.0f),
    };

    bool dibujarCubos[] = {
        true,true,true,true,true,true,true,
        true,true,true,true,true,true,true,
        true,true,true,true,true,true,true,
    };

    glm::vec3 marcoPared[] = {
         glm::vec3(-4.0f, 0.0f, 0.0f),
         glm::vec3(4.0f, 0.0f, 0.0f),
    };

    glm::vec3 marcoTecho[] = {
        glm::vec3(0.0f, 4.5f, 0.0f),
        glm::vec3(0.0f,-4.5f, 0.0f),
    };

#pragma endregion

#pragma region Funciones Teclado-Mouse
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

        if (input->isKeyPressed(GLFW_KEY_RIGHT)) {
            if (modelPosition[0] < 2.5f) {
                modelPosition[0] = modelPosition[0] + 0.2f;
            }
        }
        if (input->isKeyPressed(GLFW_KEY_LEFT)) {
            if (modelPosition[0] > -2.5f) {
                modelPosition[0] = modelPosition[0] - 0.2f;
            }
        }

        if (startGame == false) {
            if (input->isKeyPressed(GLFW_KEY_RIGHT)) {
                if (lightPos.x < 2.6f) {
                    lightPos.x = lightPos.x + 0.2f;
                }
            }
            if (input->isKeyPressed(GLFW_KEY_LEFT)) {
                if (lightPos.x > -2.6f) {
                    lightPos.x = lightPos.x - 0.2f;
                }
            }
        }

        if (input->isKeyPressed(GLFW_KEY_SPACE)) {
            startGame = true;
        }

        if (input->isKeyPressed(GLFW_KEY_R)) {
            if (contadorCubos == 21) {
                dibujarModels = true;

                contadorCubos = 0;

                vidas = 3;

                for (int i = 0; i < 21; i++) {
                    dibujarCubos[i] = true;
                }
            }
            
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
#pragma endregion

#pragma region MovimientoBola

    void positionBall(float dt) {
        
        if (startGame == true) {

            lightPos += velPos;

            #pragma region reboteConParedes
                if (lightPos.y >= 3.75f) {
                    velPos.y = -velPos.y;
                }

                if (lightPos.x <= -3.25f) {
                    velPos.x = -velPos.x;
                }

                if (lightPos.x >= 3.25f) {
                    velPos.x = -velPos.x;
                }
            #pragma endregion

            //Choque con los cubos         
            for (int i = 0; i < 21; i++) {
                if ((lightPos.x >= cubePositions[i].x - 0.4f &&
                    lightPos.x <= cubePositions[i].x + 0.4f) &&
                   (lightPos.y >= cubePositions[i].y - 0.4f &&
                    lightPos.y <= cubePositions[i].y + 0.4f)
                    && dibujarCubos[i] == true) {

                    velPos.y = -velPos.y;
                    dibujarCubos[i] = false;
                    contadorCubos++;
                }
            }
           
            //Choque con la caja rebotadora
            if ((lightPos.y <= -2.5f && lightPos.y >= -3.6f) && (lightPos.x >= modelPosition.x - 0.65f &&
                lightPos.x <= modelPosition.x + 0.65f) ) {
                velPos.y = -velPos.y;
            }

            //La bola ha llegado al borde inferior, se resta una vida y se reinicia el juego
            if (lightPos.y <= -3.75f) {

                vidas -= 1;

                startGame = false;
                modelPosition = glm::vec3(0.0f, -3.0f, -0.25f);
                lightPos = glm::vec3(0.0f, -2.5f, 0.0f);
                velPos = glm::vec3(-0.075f, 0.075f, 0.0f);
            }
        }
    }

    void endGame() {

        if (vidas < 1) {
            vidas = 3;
            contadorCubos = 0;
            for (int i = 0; i < 21; i++) {
                dibujarCubos[i] = true;
            }
        }

        if (contadorCubos == 21) {

            dibujarModels = false;

        }

    }
#pragma endregion

#pragma region Render

    void render(const Shader& s_phongModel, const Model& objectModel, const Model& objectModelNumber1, 
        const Model& objectModelNumber2, const Model& objectModelNumber3, const Model& objectModelGanador,
        const Geometry& floor, const Geometry& object, const Geometry& light, 
        const Shader& s_phong, const Shader& s_phongBis, const Shader& s_light, const Texture& t_albedo, const Texture& t_specular) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

        #pragma region Render BolaLuz

        s_light.use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.25f));
        s_light.set("model", model);
        s_light.set("view", view);
        s_light.set("proj", proj);
        s_light.set("lightColor", 1.0f, 1.0f, 1.0f);

        if (dibujarModels == true) {
            light.render();
        }
        #pragma endregion  

        #pragma region Render Model

            #pragma region Rebotador
                if(dibujarModels == true){
                    s_phongModel.use();
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, modelPosition);
                    model = glm::scale(model, glm::vec3(0.007f, 0.007f, 0.007f));
                    s_phongModel.set("model", model);
                    s_phongModel.set("view", view);
                    s_phongModel.set("proj", proj);

                    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
                    s_phongModel.set("normalMat", normalMat);

                    objectModel.render(s_phongModel);
                }
                    
            #pragma endregion
            
            #pragma region Vidas
                if (dibujarModels == true) {
                    s_phongModel.use();
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(6.0f, 2.0f, 0.0f));
                    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
                    s_phongModel.set("model", model);
                    s_phongModel.set("view", view);
                    s_phongModel.set("proj", proj);

                    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
                    s_phongModel.set("normalMat", normalMat);

                    if (vidas == 3) {
                        objectModelNumber3.render(s_phongModel);
                    }
                    else if (vidas == 2) {
                        objectModelNumber2.render(s_phongModel);
                    }
                    else if (vidas == 1) {
                        objectModelNumber1.render(s_phongModel);
                    }
                }
            #pragma endregion

            #pragma region Ganador
                if (contadorCubos == 21) {
                        s_phongModel.use();
                        model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
                        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
                        s_phongModel.set("model", model);
                        s_phongModel.set("view", view);
                        s_phongModel.set("proj", proj);

                        glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
                        s_phongModel.set("normalMat", normalMat);

                        objectModelGanador.render(s_phongModel);

                }
                    
            #pragma endregion

        #pragma endregion 

        #pragma region LuzShader

        s_phong.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
        s_phong.set("model", model);
        s_phong.set("view", view);
        s_phong.set("proj", proj);

        glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
        s_phong.set("normalMat", normalMat);

        s_phong.set("viewPos", camera.getPosition());

        s_phong.set("light.position", lightPos);
        s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
        s_phong.set("light.diffuse", 0.5f, 0.5f, 0.5f);
        s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);
        s_phong.set("light.constant", 1.0f);
        s_phong.set("light.linear", 0.2f);
        s_phong.set("light.quadratic", 0.06f);

        t_albedo.use(s_phong, "material.diffuse", 0);
        t_specular.use(s_phong, "material.specular", 1);
        s_phong.set("material.shininess", 32);

        #pragma endregion

        #pragma region Cubos
        for (int i = 0; i < 21; i++) {
            if (dibujarCubos[i] == true) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
                s_phong.set("model", model);

                glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
                s_phong.set("normalMat", normalMat);

                object.render();
            }
        }
        #pragma endregion

        #pragma region Paredes
        for (const auto& cubePos : marcoPared) {

            s_phongBis.use();

            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);
            model = glm::scale(model, glm::vec3(1.0f, 10.0f, 1.0f));
            s_phongBis.set("model", model);
            s_phongBis.set("view", view);
            s_phongBis.set("proj", proj);

            glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
            s_phongBis.set("normalMat", normalMat);

            s_phongBis.set("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
            s_phongBis.set("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

            s_phongBis.set("ambientStrength", 0.2f);
            s_phongBis.set("lightPos", lightPos);

            s_phongBis.set("viewPos", camera.getPosition());
            s_phongBis.set("shininess", 64);
            s_phongBis.set("specularStrength", 0.6f);

            object.render();
        }

        for (const auto& cubePos : marcoTecho) {

            s_phongBis.use();

            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);
            model = glm::scale(model, glm::vec3(7.0f, 1.0f, 1.0f));
            s_phongBis.set("model", model);
            s_phongBis.set("view", view);
            s_phongBis.set("proj", proj);

            glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
            s_phongBis.set("normalMat", normalMat);

            s_phongBis.set("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
            s_phongBis.set("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

            s_phongBis.set("ambientStrength", 0.2f);
            s_phongBis.set("lightPos", lightPos);

            s_phongBis.set("viewPos", camera.getPosition());
            s_phongBis.set("shininess", 64);
            s_phongBis.set("specularStrength", 0.6f);

            object.render();
        }
        #pragma endregion

    }

#pragma endregion

int main(int, char* []) {

    #pragma region Declaraciones
        Window* window = Window::instance();

        glClearColor(0.1f, 0.1f, 0.1f, 0.5f);

        const Shader s_phongModel("../projects/FINAL/simple.vs", "../projects/FINAL/simple.fs");
        const Model object("../assets/models/container/12280_Container_v1_L1.obj");

        const Model objectNumber1("../assets/models/number1/20811_Number_1_v1.obj");
        const Model objectNumber2("../assets/models/number2/20812_Number_2_v1.obj");
        const Model objectNumber3("../assets/models/number3/20813_Number_3_v1.obj");

        const Model objectGanador("../assets/models/Winner Cup/WinnerCup.obj");

        const Shader s_phong("../projects/FINAL/phong.vs", "../projects/FINAL/blinn.fs");
        const Shader s_phongBis("../projects/FINAL/phongBis.vs", "../projects/FINAL/blinnBis.fs");
        const Shader s_light("../projects/FINAL/light.vs", "../projects/FINAL/light.fs");
        const Texture t_albedo("../assets/textures/bloqueAlbedo.png", Texture::Format::RGB);
        const Texture t_specular("../assets/textures/bloqueSpecular.png", Texture::Format::RGB);
        const Sphere sphere(1.0f, 50, 50);
        const Cube cube(1.0f);
        const Quad quad(1.0f);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Input::instance()->setKeyPressedCallback(onKeyPress);
        Input::instance()->setMouseMoveCallback(onMouseMoved);
        Input::instance()->setScrollMoveCallback(onScrollMoved);
    #pragma endregion

    #pragma region refrescoPantalla
        while (window->alive()) {
            const float currentFrame = glfwGetTime();
            const float deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            handleInput(deltaTime);
            positionBall(deltaTime);
            endGame();


            render(s_phongModel, object, objectNumber1, objectNumber2, objectNumber3, objectGanador, quad, cube, sphere, s_phong, s_phongBis, s_light, t_albedo, t_specular);
            window->frame();
        }

    #pragma endregion

    return 0;
}