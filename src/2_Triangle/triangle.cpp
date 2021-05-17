#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* vertexShaderSource = "#version  330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main(){\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

const char* fragmentShaderSource = "#version  330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n";

int main()
{
    int widthwindow = 900, heightwindow = 900;

    glfwInit();
    
    // se indica la verison de opengl, ya que al compilar, no sabe que version utilizar.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // indica las funciones que se utilizaran(hay dos core (posee los modernos), 
    // y compatibility(posee los modernos y los que ya no se utilizan))
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = 
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
    };

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

    /*
    CONFIGURACION DE LOS SHADERS
    */

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //eliminamos los shaders innecesarios
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);




    /*
    CONFIGURACION PARA EL TRIANGULO
    */
    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  


    // bucle para mantener la ventana ejecutandose
    while(!glfwWindowShouldClose(window))
    {

        glClearColor(0.07f, 0.13f, 0.17f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        // Para que los cambios se muestren, basicamente todos los cambios se hacen en un buffer, y esta funcion hace que el
        // buffer(back buffer) con la ventana mostrada (front buffer) se intercambien.
        glfwSwapBuffers(window);
        // importante, esta funcion, hace q opengl procese todos los eventos del window como: recargarse, etc.
        //  SI no se agrega, la ventana estara SIN RESPONDER.
        glfwPollEvents();

    }

    // eliminamos los objetos creados hoy.
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);


    // elimina el window creado.
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
