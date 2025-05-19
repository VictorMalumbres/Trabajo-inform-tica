#include <iostream>
#include "Mundo.h"
#include <freeglut.h>

Mundo::Mundo() : modoJuego(1) {
    // Constructor
}

<<<<<<< Updated upstream
void Mundo::inicializaModo1() {
    tablero.inicializaSilverman();
=======
void Mundo::inicializa() {
    //mostrarMenuEnVentana();
>>>>>>> Stashed changes
}

void Mundo::inicializaModo2() {
    tablero2.inicializaDemi();
}


void Mundo::dibuja() {
<<<<<<< Updated upstream
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (modoJuego == 1) {
        glOrtho(0.0, 4.0, 0.0, 5.0, -1.0, 1.0);
        tablero.dibuja();    // Tablero 4x5
    }
    else if (modoJuego == 2) {
        glOrtho(0.0, 4.0, 0.0, 8.0, -1.0, 1.0);
        tablero2.dibuja2();  // Tablero 4x8
    }
=======
    switch (estadoActual) {
    case MENU:
        mostrarMenuEnVentana();
        break;
    case JUEGO:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 4.0, 0.0, 5.0, -1.0, 1.0);
>>>>>>> Stashed changes

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        tablero.dibuja();

        glutSwapBuffers();
        break;
    case INSTRUCCIONES:
        mostrarInstruccionesEnVentana();
        break;
    }
}

void Mundo::mostrarMenuEnVentana() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar la ventana

    // Dibujar el título del menú
    renderizarTexto("MENU DEL JUEGO", -0.2f, 0.6f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("1. Ver instrucciones del juego", -0.4f, 0.4f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Jugar partida", -0.4f, 0.2f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. Salir", -0.4f, 0.0f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Seleccione una opcion con el teclado...", -0.4f, -0.2f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers(); // Intercambiar buffers para mostrar el contenido
}

void Mundo::renderizarTexto(const std::string& texto, float x, float y, void* fuente) {
    glColor3f(1.0f, 1.0f, 1.0f); // Color del texto (blanco)
    glRasterPos2f(x, y);         // Posición del texto
    for (char c : texto) {
        glutBitmapCharacter(fuente, c); // Dibujar cada carácter
    }
}

void Mundo::iniciarJuego() {
    tablero.inicializa();  // Inicializar el mundo (tablero y piezas)
    dibuja();  // Cambiar la función de renderizado para dibujar el juego
    glutPostRedisplay();  // Forzar el redibujado de la ventana
}

void Mundo::cerrarAplicacion() {
    std::cout << "Saliendo del juego..." << std::endl;
    //glutLeaveMainLoop(); // Cierra la ventana y termina el bucle principal de GLUT
    exit(0); // Termina el programa
}

void Mundo::manejarEntradaMenu(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        estadoActual = INSTRUCCIONES;
        break;
    case '2':
        estadoActual = JUEGO;
        iniciarJuego();
        break;
    case '3':
        cerrarAplicacion();
        break;
    default:
        break;
    }
}

void Mundo::mostrarInstruccionesEnVentana() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar la ventana

    // Dibujar las instrucciones
    renderizarTexto("INSTRUCCIONES DEL JUEGO", -0.3f, 0.6f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("1. El objetivo del juego es capturar las piezas del oponente.", -0.8f, 0.4f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Cada pieza tiene movimientos especificos.", -0.8f, 0.2f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. El juego termina cuando el Rey de un jugador es capturado.", -0.8f, 0.0f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Presione cualquier tecla para volver al menu...", -0.8f, -0.2f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers(); // Intercambiar buffers para mostrar el contenido
    glutKeyboardFunc([](unsigned char, int, int) { glutPostRedisplay(); }); // Volver al menú
}

void Mundo::procesarClick(int x, int y) {
    int columna = x / (800 / 4);            // Tablero 5x4
    int fila = 4 - (y / (600 / 5));         // Convertimos coordenada Y

    if (seleccionX == -1 && seleccionY == -1) {
        Pieza* p = tablero.obtenerPieza(columna, fila);
        if (p != nullptr) {
            //std::cout << "Pieza seleccionada!" << std::endl;
            seleccionX = columna;
            seleccionY = fila;
        }
    }
    else {
        Pieza* p = tablero.obtenerPieza(seleccionX, seleccionY);
        if (p != nullptr) {
            tablero.colocarPieza(p, columna, fila);
        }
        seleccionX = -1;
        seleccionY = -1;
    }
}





<<<<<<< Updated upstream




=======
>>>>>>> Stashed changes
