#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void drawBoard()
{
    bool color = true;
    float square_length = 0.175, square_width = 0.175;
    float offset = 0.1;
    for(int x = -4; x < 4; x++)
    {
        for(int y = -4; y < 4; y++)
        {
            if(color)
                glColor3f(0.95, 0.75, 0.55);
            else
                glColor3f(0.42, 0.30, 0.20);

            glRectf(float((x + offset)*square_width), float((y + offset)*square_width), float(((x + offset) +1)*square_width), float(((y + offset) + 1)*square_length));
            color = !color;
        }
        color = !color;
    }
}


 int main(void)
 {
    GLFWwindow* window;

    /* Initialize the library */
    glfwInit();
    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, "Chess", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        drawBoard();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
