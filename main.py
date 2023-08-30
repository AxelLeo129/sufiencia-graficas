import pyglet
from pyglet.gl import *
import pywavefront
from pywavefront import visualization
from pyglet.window import key
from ctypes import *

class Window(pyglet.window.Window):

    #Constructor de la clase y sus atributos
    def __init__(self):
        super().__init__(800, 600, resizable=True)
        self.rotation = 0
        self.model = pywavefront.Wavefront('cube.obj')
        self.camera_x = 0
        self.camera_y = 0
        self.camera_z = 5
        self.keys = key.KeyStateHandler()
        self.push_handlers(self.keys)
        #No me funcionó el load shader porque no me dejaba combertir los tipos de datos del .glsl con ctypes
        #self.shader_program = self.load_shaders('basic_vertex_shader.glsl', 'basic_fragment_shader.glsl')

    #Cargados de los shaders
    def load_shaders(self, vertex_shader_file, fragment_shader_file):
        # Cargar los archivos de shaders
        with open(vertex_shader_file, 'r') as f:
            vertex_shader_source = f.read()
        with open(fragment_shader_file, 'r') as f:
            fragment_shader_source = f.read()
        
        # Compilar el vertex shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER)
        source_array = (c_char_p * 1)()
        source_array[0] = c_char_p(vertex_shader_source.encode('utf-8'))
        
        glShaderSource(vertex_shader, 1, source_array, None)
        glCompileShader(vertex_shader)
        result = glGetShaderiv(vertex_shader, GL_COMPILE_STATUS)
        if not result:
            print('Error compilando el shader de vértices:')
            print(glGetShaderInfoLog(vertex_shader))
            return None
        
        # Compilar el fragment shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER)

        source_array1 = (c_char_p * 1)()
        source_array1[0] = c_char_p(fragment_shader_source.encode('utf-8'))

        glShaderSource(fragment_shader, 1, source_array1, None)
        glCompileShader(fragment_shader)
        result = glGetShaderiv(fragment_shader, GL_COMPILE_STATUS)
        if not result:
            print('Error compilando el shader de fragmentos:')
            print(glGetShaderInfoLog(fragment_shader))
            return None
        
        # Crear el programa de shaders y adjuntar los shaders
        shader_program = glCreateProgram()
        glAttachShader(shader_program, vertex_shader)
        glAttachShader(shader_program, fragment_shader)
        glLinkProgram(shader_program)
        result = glGetProgramiv(shader_program, GL_LINK_STATUS)
        if not result:
            print('Error enlazando el programa:')
            print(glGetProgramInfoLog(shader_program))
            return None
        
        # Limpiar
        glDeleteShader(vertex_shader)
        glDeleteShader(fragment_shader)
        
        return shader_program

    #Función que dibujo el .obj y aplica el shader
    def on_draw(self):
        self.clear()
        self.set_3d_view()
        #glUseProgram(self.shader_program)
        visualization.draw(self.model)
        #glUseProgram(0)

    #Setea los valores para la vista en 3D
    def set_3d_view(self):
        width, height = self.get_size()
        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(40, width/height, 0.1, 100)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        glTranslatef(0, self.camera_y, -self.camera_z)
        glRotatef(self.rotation, 0, 1, 0)

    #Listener para los botones para que se puede interactual con el objeto
    def update(self, dt):
        if self.keys[key.W]:
            if(self.camera_z > 4):
                self.camera_z -= 0.1
        if self.keys[key.S]:
            if(self.camera_z < 8):
                self.camera_z += 0.1
        if self.keys[key.A]:
            self.rotation += 1
        if self.keys[key.D]:    
            self.rotation -= 1
        if self.keys[key.UP]:
            if(self.camera_y < 1):
                self.camera_y += 0.1
        if self.keys[key.DOWN]:
            if(self.camera_y > -1):
                self.camera_y -= 0.1

    #Listener el ajuste del tamaño
    def on_resize(self, width, height):
        self.set_3d_view()
        return pyglet.event.EVENT_HANDLED

    #Listener para rotar el objeto con el mouse
    def on_mouse_drag(self, x, y, dx, dy, buttons, modifiers):
        self.rotation += dx * 0.5

#Llamada al programa
if __name__ == '__main__':
    window = Window()
    pyglet.clock.schedule_interval(window.update, 1/60.0)
    pyglet.app.run()
