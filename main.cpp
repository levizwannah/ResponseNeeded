#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"

#include "cube.h"
#include "cubeFactory.h"
#include "cubeMover.h"
#include "constants.h"

#include <iostream>
#include <vector>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);



// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//Sphere Const
const GLfloat PI = 3.14159265358979323846f;

//Sphere, divide the ball horizontally and vertically into a 500*500 grid
const int Y_SEGMENTS = 500;
const int X_SEGMENTS = 500;

int main()
{
    // glfw: initialize and configure

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FoShoot", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);

    //capture mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    std::vector<float> sphereVertices;
	std::vector<int> sphereIndices;

    /*2-Calculate the vertices of the sphere*/
	//Generate the vertices of the ball
	for (int y = 0; y <= Y_SEGMENTS; y++)
	{
		for (int x = 0; x <= X_SEGMENTS; x++)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			sphereVertices.push_back(xPos);
			sphereVertices.push_back(yPos);
			sphereVertices.push_back(zPos);
		}
	}

	//Indices that generate the ball
	for (int i = 0; i < Y_SEGMENTS; i++)
	{
		for (int j = 0; j < X_SEGMENTS; j++)
		{
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
		}
	}

	/*3-Data processing*/
	unsigned int sphereVBO, sphereVAO;
	glGenVertexArrays(1, &sphereVAO);
	glGenBuffers(1, &sphereVBO);
	//Generate and bind the VAO and VBO of the sphere
	glBindVertexArray(sphereVAO);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
	// Bind the vertex data to the current default buffer
	glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);

	GLuint sphere_element_buffer_object;//EBO
	glGenBuffers(1, &sphere_element_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

	//Set the vertex attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*4-shader*/
	Shader sphereShader("sphereVertexShader.glsl", "sphereFragmentShader.glsl");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    Shader ourShader("shaders/cubevertexshader.GLSL", "shaders/cubefragmentshader.GLSL");

    //game initial set up
    //------------------------------
    std::vector<float> cubeVertices = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f 
    };
    float* cVerticesArr = &cubeVertices[0];
  
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(cVerticesArr), cVerticesArr, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //number of cubes per target
    const int NUM_CUBES_PER_TARGET = 1;
    const glm::vec4 BACKGROUND_COLOR(0.98f, 0.988f, 0.87f, 1.0f);
    glm::mat4 dModelMat(1.0f);
    std::vector<Cube> cubeInventory;
    Cube::cubeVAO = cubeVAO;

    CubeFactory cubeFactory(dModelMat, cubeVertices);
    cubeFactory.setTargetNum(NUM_CUBES_PER_TARGET);
    cubeFactory.startProduction();

    CubeMover cubeMover(0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    cubeMover.setRevEndCoord(cubeMover.getVertices()[0], cubeMover.getVertices()[1], cubeMover.getVertices()[2]);

    Player::consecutiveMiss = 0;
    Player::maxConsecutiveMiss = 10;

    Player currentPlayer;
    cubeMover.start();

    int i = 0;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //input processing
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        //Activate sphereShader
        sphereShader.use();
		//Draw the ball
		//Turn on face culling (only one face needs to be displayed, otherwise there will be overlap)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glBindVertexArray(sphereVAO);
		//Draw using wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, X_SEGMENTS * Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);

  
        // activate shader

        glClearColor(BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, BACKGROUND_COLOR.w);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  
        //check we are producing cubes then 
        if (cubeFactory.isProducing()) {
            cubeFactory.produce(cubeInventory);
        }

        //if there is cube in the inventory, add it to the mover
        if (cubeInventory.size() > 0) {
            Cube newCube = cubeInventory[cubeInventory.size() - 1];
            cubeMover.addCube(newCube);
            cubeInventory.pop_back();
        }

        
        //move the cubes based on time
        cubeMover.moveAndCheck(glfwGetTime(), currentPlayer);

        //draw
        ourShader.use();

        ourShader.setVec3("colorOut", glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setVec3("viewPos", camera.Position);

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        
        for (Cube c : cubeMover.getMovingCubes()) {
            c.render(glfwGetTime(), ourShader);
        }
        



        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.2f, -0.5f));
        float angle = 20.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);
       
        // render the cube
        //glBindVertexArray(cubeVAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
        //if (i == 10) break;
        i++;

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    	/*6-End*/
	//Delete sVAO and sVBO, EBO
	glDeleteVertexArrays(1, &sphereVAO);
	glDeleteBuffers(1, &sphereVBO);
	glDeleteBuffers(1, &sphere_element_buffer_object);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}