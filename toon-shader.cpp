#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//Vertex Shader en GLSL
const char* vertexShaderCode = R"(
    #version 330 core
    layout(location = 0) in vec3 inPosition;

    uniform mat4 modelViewProjection;

    void main() {
        gl_Position = modelViewProjection * vec4(inPosition, 1.0);
    }
)";

//Fragment Shader en GLSL
const char* fragmentShaderCode = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        vec3 lightDirection = normalize(vec3(0.0, 0.0, -1.0));
        float intensity = dot(lightDirection, normalize(-normalize(gl_FragCoord.xyz)));
        if (intensity > 0.85)
            FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        else if (intensity > 0.6)
            FragColor = vec4(0.8, 0.8, 0.0, 1.0);
        else if (intensity > 0.4)
            FragColor = vec4(0.6, 0.6, 0.0, 1.0);
        else
            FragColor = vec4(0.4, 0.4, 0.0, 1.0);
    }
)";

// Declaración del ID del programa GLSL
GLuint programID;

void display() {
    // Limpieza del búfer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activa el programa GLSL
    glUseProgram(programID);

    // Obtención de la ubicación de la variable uniform en el shader
    GLuint modelViewProjectionLocation = glGetUniformLocation(programID, "modelViewProjection");
    
    // Creación de las matrices de proyección, vista y modelo
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 modelViewProjection = projection * view * model;

    // Envía la matriz modelViewProjection al shader
    glUniformMatrix4fv(modelViewProjectionLocation, 1, GL_FALSE, glm::value_ptr(modelViewProjection));

    // Renderiza un triángulo en el espacio 3D
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Intercambia los búferes y muestra el resultado
    glutSwapBuffers();
}

void initializeGL() {
    // Inicialización de GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Creación del shader de vértices
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShaderID);

    // Creación del shader de fragmentos
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShaderID);

    // Creación y enlace del programa GLSL
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Limpieza de los shaders después del enlace
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

int main(int argc, char** argv) {
    // Inicialización de GLUT y creación de la ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Toon Shader Example");

    // Asignación de la función de renderización
    glutDisplayFunc(display);

    // Inicialización de OpenGL y GLUT
    initializeGL();

    // Inicio del bucle principal de GLUT
    glutMainLoop();

    return 0;
}