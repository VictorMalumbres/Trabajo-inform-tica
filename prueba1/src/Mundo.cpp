#include "Mundo.h"
#include <freeglut.h>
#include <iostream>

extern Mundo mundo;

bool juegoEnPausa = false;


Mundo::Mundo() : estadoActual(MENU),  // forzamos el estado inicial
modoJuego(1),
seleccionX(-1),
seleccionY(-1) 
{

}

void Mundo::inicializaModo1() {
    tablero.inicializaSilverman();
}

void Mundo::inicializaModo2() {
    tablero2.inicializaDemi();
}


void Mundo::dibuja() {
    switch (estadoActual) {
    case MENU:
        mostrarMenuEnVentana();
        break;
    case JUEGO:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

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
    renderizarTexto("MENU DEL JUEGO", -0.2f, 0.8f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("1. Ver instrucciones del juego", -0.4f, 0.6f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Jugar partida SILVERMAN 4X5", -0.4f, 0.4f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. Jugar partida DEMI", -0.4f, 0.2f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("4. Salir", -0.4f, 0.0f, GLUT_BITMAP_HELVETICA_12);
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
void Mundo::mostrarPausa() {
    glClear(GL_COLOR_BUFFER_BIT);
    renderizarTexto("JUEGO EN PAUSA", -0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("Presiona 'P' para continuar...", -0.3f, -0.2f, GLUT_BITMAP_HELVETICA_12);
    glutSwapBuffers();
}

void manejarTeclado(unsigned char key, int x, int y) {
    if (key == 27) { // Código ASCII de la tecla ESC
        juegoEnPausa = !juegoEnPausa;  // Cambiar el estado de pausa
        if (juegoEnPausa) {
            std::cout << "Juego pausado" << std::endl;
        }
        else {
            std::cout << "Juego reanudado" << std::endl;
        }
        glutPostRedisplay(); // Forzar redibujado
    }
}

void Mundo::iniciarJuego() {
    estadoActual = JUEGO;
    inicializaModo1();
    glutDisplayFunc([]() {
        if (!juegoEnPausa) {
            mundo.dibuja();
        }
        else {
            glClear(GL_COLOR_BUFFER_BIT);
            // Mostrar texto de "PAUSA"
            glColor3f(1.0f, 1.0f, 0.0f); // Color amarillo
            glRasterPos2f(-0.2f, 0.0f);
            std::string texto = "Juego en pausa (ESC para continuar)";
            for (char c : texto) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
            glutSwapBuffers();
        }
        });
    glutKeyboardFunc(manejarTeclado);
    glutIdleFunc([]() {
        glutPostRedisplay();
        });
}

void Mundo::iniciar2dojuego() {
    estadoActual = JUEGO;
    inicializaModo2();
    glutDisplayFunc([]() {
        if (!juegoEnPausa) {
            mundo.dibuja();
        }
        else {
            glClear(GL_COLOR_BUFFER_BIT);
            // Mostrar texto de "PAUSA"
            glColor3f(1.0f, 1.0f, 0.0f); // Color amarillo
            glRasterPos2f(-0.2f, 0.0f);
            std::string texto = "Juego en pausa (ESC para continuar)";
            for (char c : texto) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
            glutSwapBuffers();
        }
        });
    glutKeyboardFunc(manejarTeclado);
    glutIdleFunc([]() {
        glutPostRedisplay();
        });
}

void Mundo::cerrarAplicacion() {
    std::cout << "Saliendo del juego..." << std::endl;
    //glutLeaveMainLoop(); // Cierra la ventana y termina el bucle principal de GLUT
    exit(0); // Termina el programa
}

void Mundo::manejarEntradaMenu(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        mostrarInstruccionesEnVentana();
        break;
    case '2':
        setModoJuego(1);
        iniciarJuego();
        break;
    case '3':
        setModoJuego(2);
        iniciar2dojuego();
        break;
    case '4':
        cerrarAplicacion(); // Salir del programa
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
    renderizarTexto("Presione doble click para volver al menu...", -0.8f, -0.2f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers(); // Intercambiar buffers para mostrar el contenido
    //glutKeyboardFunc([](unsigned char, int, int) { glutPostRedisplay(); }); // Volver al menú
}

void Mundo::procesarClick(int x, int y) {
    if (modoJuego == 1)
    {
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
    else if (modoJuego == 2)
    {
        int columna = x / (800 / 4);            // Tablero 8x4
        int fila = 7 - (y / (600 / 8));         // Convertimos coordenada Y

        if (seleccionX == -1 && seleccionY == -1) {
            Pieza* p = tablero2.obtenerPieza(columna, fila);
            if (p != nullptr) {
                //std::cout << "Pieza seleccionada!" << std::endl;
                seleccionX = columna;
                seleccionY = fila;
            }
        }
        else {
            Pieza* p = tablero2.obtenerPieza(seleccionX, seleccionY);
            if (p != nullptr) {
                tablero2.colocarPieza(p, columna, fila);
            }
            seleccionX = -1;
            seleccionY = -1;
        }
    }
}

