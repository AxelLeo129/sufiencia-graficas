# Universidad del Valle de Guatemala
# Graficas por computador - Exámen de suficiencia
## Author: Axel López - 20768

[![N|Solid](https://res.cloudinary.com/webuvg/image/upload/f_auto/v1551291412/WEB/institucional/logouvg.png)](https://www.uvg.edu.gt/)

Tecnologias:

- Python 3.10
- C++

## Instalacion

Clonar repositorio

- Python:

Instalar dependencias

Ejecutar `python main.py`

- C++

Instalar dependencias

Ejecutar (2 archivos distintos) :
    `g++ -o gouraud_shader gouraud-shader.cpp -lGL -lGLU -lglut`
    `./gouraud_shader`
    `g++ -o toon_shader toon-shader.cpp -lGL -lGLU -lglut`
    `./toon_shader`


## Instrucciones
Para el programa en python las teclas a utilizar son 'W' y 'S' para hacer Zoom, 'A' y 'D' para rotar el objeto y las flechas de arriba y abajo para movernos en el eje Y.

## PD

Al no poder aplicar los shader en Python cree dos archivos uno para Gouraund Shader y otro para Toon Shader con C++ y GLSL.

## License

MIT

**Free Software, software to learn!**