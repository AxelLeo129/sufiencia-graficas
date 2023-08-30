#include <GL/glut.h>
#include <GL/gl.h>

// Vertex shader en GLSL
const char* vertexShaderCode = R"(
    attribute vec3 inPosition;
    attribute vec3 inColor;
    varying vec3 fragColor;

    void main() {
        // Transforma la posición del vértice
        gl_Position = ftransform();
        fragColor = inColor;
    }
)";

// Fragment shader en GLSL
const char* fragmentShaderCode = R"(
    varying vec3 fragColor;

    void main() {
        // Asigna el color final del fragmento
        gl_FragColor = vec4(fragColor, 1.0);
    }
)";

// ID del programa GLSL
GLuint programID;

// Función para renderizar la escena
void display() {
    // Limpia los búferes de color y profundidad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Usa el programa GLSL
    glUseProgram(programID);

    // Obtiene las ubicaciones de los atributos del shader
    GLuint inPositionLocation = glGetAttribLocation(programID, "inPosition");
    GLuint inColorLocation = glGetAttribLocation(programID, "inColor");

    // Habilita los atributos de posición y color
    glEnableVertexAttribArray(inPositionLocation);
    glEnableVertexAttribArray(inColorLocation);

    // Especifica el formato y la ubicación de los atributos de posición y color
    glVertexAttribPointer(inPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertices[0].x);
    glVertexAttribPointer(inColorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertices[0].r);

    // Dibuja los triángulos
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Deshabilita los atributos después de dibujar
    glDisableVertexAttribArray(inPositionLocation);
    glDisableVertexAttribArray(inColorLocation);

    // Intercambia los búferes y muestra el resultado
    glutSwapBuffers();
}

// Función para inicializar OpenGL y cargar shaders
void initializeGL() {
    // Inicialización de GLEW para manejar las extensiones de OpenGL
    glewExperimental = GL_TRUE;
    glewInit();
    
    // Crea shaders de vértices y fragmentos
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShaderID);

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShaderID);

    // Crea y enlaza el programa GLSL
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Limpia los shaders después del enlace
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

// Función principal
int main(int argc, char** argv) {
    // Inicializa GLUT y crea la ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Gouraud Shader Example (GLSL)");

    // Asigna la función de renderización
    glutDisplayFunc(display);

    // Inicializa OpenGL y los shaders
    initializeGL();

    // Inicia el bucle principal de GLUT
    glutMainLoop();

    return 0;
}
