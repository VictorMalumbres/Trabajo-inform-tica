#include "Tablero.h"
#include <freeglut.h>
#include <iostream>
#include <string>
#include "Mundo.h"
#pragma warning(disable : 4996) //deshabilita el error por unsafe 

Mundo mundo;

bool juegoEnPausa = false;

Tablero::Tablero() {
    // Constructor de Tablero, inicializa el vector de piezas
}

void Tablero::mostrarMenuEnVentana() {
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

void Tablero::renderizarTexto(const std::string& texto, float x, float y, void* fuente) {
    glColor3f(1.0f, 1.0f, 1.0f); // Color del texto (blanco)
    glRasterPos2f(x, y);         // Posición del texto
    for (char c : texto) {
        glutBitmapCharacter(fuente, c); // Dibujar cada carácter
    }
}
void Tablero::mostrarPausa() {
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

void Tablero::iniciarJuego() {
    mundo.inicializaModo1();
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

void Tablero::iniciar2dojuego() {
    mundo.inicializaModo2();
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

void Tablero::cerrarAplicacion() {
    std::cout << "Saliendo del juego..." << std::endl;
    //glutLeaveMainLoop(); // Cierra la ventana y termina el bucle principal de GLUT
	exit(0); // Termina el programa
}

void Tablero::manejarEntradaMenu(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        mostrarInstruccionesEnVentana();
        break;
    case '2':
        mundo.setModoJuego(1);
        iniciarJuego();
        break;
    case '3':
        mundo.setModoJuego(2);
        iniciar2dojuego();
        break;
    case '4':
        cerrarAplicacion(); // Salir del programa
        break;
    default:
        break;
    }
}

void Tablero::mostrarInstruccionesEnVentana() {
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

void Tablero::iniciarPartida(int modoJuego) {
    if (modoJuego == 1) {
        inicializaSilverman();
    }
    else if (modoJuego == 2) {
        inicializaDemi();
    }
    glutDisplayFunc([]() { mundo.dibuja(); });
    glutPostRedisplay();
}

void Tablero::dibuja() {
    float casillaSizeX = 1.0f;
    float casillaSizeY = 1.0f;

    for (int i = 0; i < 5; ++i) {  // 5 filas
        for (int j = 0; j < 4; ++j) {  // 4 columnas
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f);  // Blanco
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);  // Negro
            }

            glBegin(GL_QUADS);
            glVertex3f(j * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glVertex3f(j * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glEnd();
        }
    }

    // Dibujar las piezas
    for (Pieza* pieza : piezas) {
        pieza->dibuja();
    }
}

void Tablero::dibuja2() {
    float casillaSizeX = 1.0f;
    float casillaSizeY = 1.0f;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((i + j) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(0.0f, 0.0f, 0.0f);

            glBegin(GL_QUADS);
            glVertex3f(j * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glVertex3f(j * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glEnd();
        }
    }

    for (Pieza* pieza : piezas) {
        pieza->dibuja();
    }
}

void Tablero::inicializaSilverman() {
    piezas.clear();

    // Primer jugador (verde)
    piezas.push_back(new Torre(0.5f, 0.5f, 0, 255, 0));
    piezas.push_back(new Reina(1.5f, 0.5f, 0, 255, 0));
    piezas.push_back(new Rey(2.5f, 0.5f, 0, 255, 0));
    piezas.push_back(new Torre(3.5f, 0.5f, 0, 255, 0));

    piezas.push_back(new Peon(0.5f, 1.5f, 0, 255, 0));
    piezas.push_back(new Peon(1.5f, 1.5f, 0, 255, 0));
    piezas.push_back(new Peon(2.5f, 1.5f, 0, 255, 0));
    piezas.push_back(new Peon(3.5f, 1.5f, 0, 255, 0));

    // Segundo jugador (rojo)
    piezas.push_back(new Torre(0.5f, 4.5f, 255, 0, 0));
    piezas.push_back(new Reina(1.5f, 4.5f, 255, 0, 0));
    piezas.push_back(new Rey(2.5f, 4.5f, 255, 0, 0));
    piezas.push_back(new Torre(3.5f, 4.5f, 255, 0, 0));

    piezas.push_back(new Peon(0.5f, 3.5f, 255, 0, 0));
    piezas.push_back(new Peon(1.5f, 3.5f, 255, 0, 0));
    piezas.push_back(new Peon(2.5f, 3.5f, 255, 0, 0));
    piezas.push_back(new Peon(3.5f, 3.5f, 255, 0, 0));
}

void Tablero::inicializaDemi() {
    piezas.clear();

    // Primer jugador (verde)
    piezas.push_back(new Torre(0.5f, 0.5f, 0, 255, 0));
    piezas.push_back(new Rey(1.5f, 0.5f, 0, 255, 0));
    piezas.push_back(new Torre(3.5f, 0.5f, 0, 255, 0));

    piezas.push_back(new Alfil(2.5f, 0.5f, 0, 200, 0));      // Alfil verde
    piezas.push_back(new Caballo(0.5f, 1.5f, 0, 150, 0));    // Caballo verde
    piezas.push_back(new Caballo(1.5f, 1.5f, 0, 150, 0));    // Caballo verde
    piezas.push_back(new Peon(2.5f, 1.5f, 0, 255, 0));
    piezas.push_back(new Peon(3.5f, 1.5f, 0, 255, 0));

    // Segundo jugador (rojo)
    piezas.push_back(new Torre(0.5f, 7.5f, 255, 0, 0));
    piezas.push_back(new Rey(1.5f, 7.5f, 255, 0, 0));
    piezas.push_back(new Torre(3.5f, 7.5f, 255, 0, 0));

    piezas.push_back(new Alfil(2.5f, 7.5f, 200, 0, 0));      // Alfil rojo
    piezas.push_back(new Caballo(0.5f, 6.5f, 150, 0, 0));    // Caballo rojo
    piezas.push_back(new Caballo(1.5f, 6.5f, 150, 0, 0));    // Caballo rojo
    piezas.push_back(new Peon(2.5f, 6.5f, 255, 0, 0));
    piezas.push_back(new Peon(3.5f, 6.5f, 255, 0, 0));
}

