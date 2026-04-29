#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <thread>

#include <Shaders/shader.h>

#include <camera.cpp>
#include "CollisionManager.h"
#include "ObjectManager.h"


#include <ft2build.h>
#include FT_FREETYPE_H
#include "Character.h"

#include "coin.cpp"
#include "BouncingCube.cpp"
#include "Background.cpp"
#include "DebugCube.cpp"

#include <string>
#include <map>

bool start = true;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* configGL();

Shader* ourShader;
Shader* modelShader;
Shader* textShader;

int scale = 50;

// settings
const unsigned int SCR_WIDTH = 9 * scale;
const unsigned int SCR_HEIGHT = 16 * scale;

GLFWwindow* window;
auto& UDMan = UDManager::getInstance();

CollisionManager& cm = CollisionManager::getInstance();


const double TARGET_FPS = 60.0;
const std::chrono::duration<double> FRAME_DURATION(1.0 / TARGET_FPS); // ~16.67ms


unsigned int VAO, VBO;
std::map<char, Character> Characters;

void renderLoop();

int main()
{
    
    //window setup
    window = configGL();
    modelShader = new Shader("C:/Users/joefr/source/repos/SconchMath/modelShader.vs", "C:/Users/joefr/source/repos/SconchMath/modelShader.fs");
    textShader = new Shader("C:/Users/joefr/source/repos/SconchMath/textShader.vs", "C:/Users/joefr/source/repos/SconchMath/textShader.fs");
    InputManager* input = new InputManager(window);


    //object setup
    char path1[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj";
    char path2[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj";

    BouncingCube* debugCube = new BouncingCube(modelShader, path1);
    debugCube->setId(3);
    debugCube->setVelocity(glm::vec3(0.45f, -0.15f, .0f));

    BouncingCube* dC2 = new BouncingCube(modelShader, path2);
    dC2->setId(4);
    dC2->translate(glm::vec3(.0f, -5.0f,0.0f));
    dC2->setVelocity(glm::vec3(0.35f, 0.24f, .0f));


    UDMan.addUD(debugCube);
    UDMan.addUD(dC2);


    Background* bg = new Background(modelShader);
    bg->setId(1);
    UDMan.addUD(bg);

    int idNum = 10;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            Coin* coiny = new Coin(modelShader);
            coiny->setId(idNum++);
            coiny->translate(glm::vec3((float)i * 3.0f - 6, (float)j * 4.3f - 10.7f, 0.0f));
           UDMan.addUD(coiny);
        }
    }

    //text setup
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std
        ::endl;
    FT_Face face;
    if (FT_New_Face(ft, "C:/Windows/Fonts/arial.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
    

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // no byte-alignment restriction
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT);
    textShader->use();
    textShader->setMat4("projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6*4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    //camera setup
    camera* cam = new camera(modelShader, SCR_WIDTH, SCR_HEIGHT);

    cam->setup();
 

    renderLoop();

    


    glfwTerminate();
    return 0;
}

void RenderText(Shader& s, std::string text, float x, float y, float scale,
    glm::vec3 color)
{

    // activate corresponding render state
    s.use();
    s.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];
        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
        { xpos, ypos + h, 0.0f, 0.0f },
        { xpos, ypos, 0.0f, 1.0f },
        { xpos + w, ypos, 1.0f, 1.0f },
        { xpos, ypos + h, 0.0f, 0.0f },
        { xpos + w, ypos, 1.0f, 1.0f },
        { xpos + w, ypos + h, 1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // advance cursors for next glyph (advance is 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void renderLoop() {

    while (!glfwWindowShouldClose(window))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //bg.render();

        modelShader->use();


        if (start) {

            cm.checkCollision2D();
            UDMan.updateUDs();
            UDMan.drawUDs();

        }


        textShader->use();
        RenderText(*textShader, "This is sample text", 0.0f, 0.0f, 1.0f,
            glm::vec3(0.5, 0.8f, 0.2f));
        RenderText(*textShader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f,
            glm::vec3(0.3, 0.7f, 0.9f));

        glfwSwapBuffers(window);
        glfwPollEvents();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = frameEnd - frameStart;

        if (elapsed < FRAME_DURATION) {
            std::this_thread::sleep_for(FRAME_DURATION - elapsed);
        }
    }
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        start = true;
        
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

GLFWwindow* configGL() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;   
    }
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return window;
}

