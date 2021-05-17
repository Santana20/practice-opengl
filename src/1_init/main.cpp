#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    int widthwindow = 1600, heightwindow = 900;

    glfwInit();
    
    // se indica la verison de opengl, ya que al compilar, no sabe que version utilizar.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // indica las funciones que se utilizaran(hay dos core (posee los modernos), 
    // y compatibility(posee los modernos y los que ya no se utilizan))
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // se instancia la ventana
    GLFWwindow* window = glfwCreateWindow(widthwindow, heightwindow, "I made this!", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    // le dices a opengl que la ventana creada se agrega al contexto actual.
    glfwMakeContextCurrent(window);

    // Iniciamos glad.
    gladLoadGL();

    glViewport(0, 0, widthwindow, heightwindow);
    
    // bucle para mantener la ventana ejecutandose
    while(!glfwWindowShouldClose(window))
    {

        glClearColor(0.07f, 0.13f, 0.17f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        // importante, esta funcion, hace q opengl procese todos los eventos del window como: recargarse, etc.
        //  SI no se agrega, la ventana estara SIN RESPONDER.
        
        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    // elimina el window creado.
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}