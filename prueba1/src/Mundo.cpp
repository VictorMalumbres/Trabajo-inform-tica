#include "Mundo.h"
#include <freeglut.h>
#include <iostream>
#include "ETSIDI.h"

extern Mundo mundo;

bool juegoEnPausa = false;

Mundo::Mundo() : estadoActual(MENU),modoJuego(1), seleccionX(-1), seleccionY(-1) {} // forzamos el estado inicial

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

void Mundo::renderizarTexto(const std::string& texto, float x, float y, void* fuente) {
    glColor3f(1.0f, 1.0f, 1.0f); // Color del texto (blanco)
    glRasterPos2f(x, y);         // Posición del texto
    for (char c : texto) {
        glutBitmapCharacter(fuente, c); // Dibujar cada carácter
    }
}

void Mundo::renderizarTextoGrande(const char* texto, float x, float y, float escala) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);      // Mover el texto a la posición (x, y)
    glScalef(escala, escala, 1.0f); // Escalar el texto
    glLineWidth(2.0f);             // Grosor de las líneas del texto

    for (const char* c = texto; *c != '\0'; ++c) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }

    glPopMatrix();
}

void Mundo::manejarEntradaMenu(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        mostrarInstruccionesEnVentana();
        break;
        ETSIDI::stopMusica();
    case '2':
        setModoJuego(1);
        iniciarJuego();
        break;
        ETSIDI::stopMusica();
    case '3':
        setModoJuego(2);
        iniciar2dojuego();
        break;
        ETSIDI::stopMusica();
    case '4':
        cerrarAplicacion(); // Salir del programa
        ETSIDI::stopMusica();
        break;
    default:
        break;
    }
}

void Mundo::mostrarMenuEnVentana() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar la ventana

    // Fondo con textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_menu.png").id);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 0); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    ETSIDI::playMusica("sonidos/elevador.mp3", true);

    // Colores para los botones
    glColor3f(0.2f, 0.2f, 0.6f); // RGB

    // Dibujar rectángulos de fondo para cada opción
    glBegin(GL_QUADS);
    glVertex2f(-0.45f, 0.65f); glVertex2f(0.45f, 0.65f);
    glVertex2f(0.45f, 0.55f); glVertex2f(-0.45f, 0.55f);

    glVertex2f(-0.45f, 0.45f); glVertex2f(0.45f, 0.45f);
    glVertex2f(0.45f, 0.35f); glVertex2f(-0.45f, 0.35f);

    glVertex2f(-0.45f, 0.25f); glVertex2f(0.45f, 0.25f);
    glVertex2f(0.45f, 0.15f); glVertex2f(-0.45f, 0.15f);

    glVertex2f(-0.45f, 0.05f); glVertex2f(0.45f, 0.05f);
    glVertex2f(0.45f, -0.05f); glVertex2f(-0.45f, -0.05f);
    glEnd();

    // Cambiar color del texto a blanco
    glColor3f(10.0f, 10.0f, 10.0f);

    // Dibujar el título del menú
    renderizarTextoGrande("MENU DEL JUEGO", -0.45f, 0.8f, 0.0008f);
    renderizarTexto("1. Ver instrucciones del juego", -0.4f, 0.58f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Jugar partida SILVERMAN 4X5", -0.4f, 0.38f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. Jugar partida DEMI", -0.4f, 0.18f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("4. Salir", -0.4f, -0.02f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Seleccione una opcion con el teclado...", -0.4f, -0.2f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers(); // Mostrar el contenido
}

void Mundo::mostrarInstruccionesEnVentana() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar la ventana

    // Dibujar fondo general (opcional)
    glColor3f(0.1f, 0.1f, 0.1f); // Gris oscuro
    glBegin(GL_QUADS);
    glVertex2f(-0.95f, 0.75f);
    glVertex2f(0.95f, 0.75f);
    glVertex2f(0.95f, -0.4f);
    glVertex2f(-0.95f, -0.4f);
    glEnd();

    // Dibujar rectángulos de fondo más grandes para cada instrucción
    glColor3f(0.2f, 0.2f, 0.6f); // Azul oscuro
    glBegin(GL_QUADS);
    // Instrucción 1
    glVertex2f(-0.85f, 0.46f); glVertex2f(0.85f, 0.46f);
    glVertex2f(0.85f, 0.34f); glVertex2f(-0.85f, 0.34f);
    // Instrucción 2
    glVertex2f(-0.85f, 0.26f); glVertex2f(0.85f, 0.26f);
    glVertex2f(0.85f, 0.14f); glVertex2f(-0.85f, 0.14f);
    // Instrucción 3
    glVertex2f(-0.85f, 0.06f); glVertex2f(0.85f, 0.06f);
    glVertex2f(0.85f, -0.06f); glVertex2f(-0.85f, -0.06f);
    glEnd();

    // Dibujar texto encima de los rectángulos
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
    renderizarTexto("INSTRUCCIONES DEL JUEGO", -0.3f, 0.6f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("1. El objetivo del juego es capturar las piezas del oponente.", -0.8f, 0.4f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Cada pieza tiene movimientos especificos.", -0.8f, 0.2f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. El juego termina cuando el Rey de un jugador es capturado.", -0.8f, 0.0f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Presione doble click para volver al menu...", -0.8f, -0.3f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers(); // Mostrar contenido en pantalla
}

void manejarTeclado(unsigned char key, int x, int y) {
    if (key == ' ') {
        juegoEnPausa = !juegoEnPausa;
        if (juegoEnPausa)
            std::cout << "Juego pausado" << std::endl;
        else
            std::cout << "Juego reanudado" << std::endl;

        glutPostRedisplay();
    }

    else if (key == 'q' || key == 'Q') {
        mundo.cerrarAplicacion();
    }

    else if (key == 'm' || key == 'M') {
        mundo.mostrarMenuEnVentana();
        ExitProcess;
    }
}

void Mundo::iniciarJuego() {
    ETSIDI::playMusica("sonidos/musica_juego1.mp3", true);
    estadoActual = JUEGO;
    inicializaModo1();
    glutKeyboardFunc(manejarTeclado);
    glutDisplayFunc([]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!juegoEnPausa) {
            mundo.dibuja();
        }
        else {
            ETSIDI::stopMusica();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glColor3f(1.0f, 1.0f, 0.0f);
            std::string texto1 = "JUEGO EN PAUSA";
            std::string texto2 = "Presiona ESPACIO para continuar";
            std::string texto3 = "Presiona M para volver al menu";
            std::string texto4 = "Pulsa Q para salir";

            glRasterPos2f(-0.8, 0.3f);
            for (char c : texto1) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

            glRasterPos2f(-0.6f, 0.2f);
            for (char c : texto2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

            glRasterPos2f(-0.4f, 0.1f);
            for (char c : texto3) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

            glRasterPos2f(-0.2f, -0.1f);
            for (char c : texto4) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

            glutSwapBuffers();
        }
        });

    glutIdleFunc([]() {
        glutPostRedisplay();
        });
}

void Mundo::iniciar2dojuego() {
    estadoActual = JUEGO;
    inicializaModo2();
    glutKeyboardFunc(manejarTeclado);
    glutDisplayFunc([]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!juegoEnPausa) {
            mundo.dibuja();
        }
        else {
            ETSIDI::stopMusica();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glColor3f(1.0f, 1.0f, 0.0f);
            std::string texto1 = "JUEGO EN PAUSA";
            std::string texto2 = "Presiona ESPACIO para continuar";
            std::string texto3 = "Presiona M para volver al menu";
            std::string texto4 = "Pulsa Q para salir";

            glRasterPos2f(-0.8f, 0.3f);
            for (char c : texto1) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

            glRasterPos2f(-0.6f, 0.2f);
            for (char c : texto2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

            glRasterPos2f(-0.4f, 0.1f);
            for (char c : texto3) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

            glRasterPos2f(-0.2f, -0.1f);
            for (char c : texto4) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

            glutSwapBuffers();
        }
        });
    glutIdleFunc([]() {
        glutPostRedisplay();
    });
}

void Mundo::cerrarAplicacion() {
    std::cout << "Saliendo del juego..." << std::endl;
    //glutLeaveMainLoop(); // Cierra la ventana y termina el bucle principal de GLUT
    exit(0); // Termina el programa
}

void Mundo::procesarClick(int x, int y) {
    if (modoJuego == 1) {
        int columna = x / (800 / 4);
        int fila = 4 - (y / (600 / 5));

        // Desactiva el resaltado de todas las piezas
        for (Pieza* pieza : tablero.getPiezas()) {
            pieza->setResaltado(false);
        }

        // Usa la selección del tablero
        if (tablero.getSeleccionX() == -1 && tablero.getSeleccionY() == -1) {
            Pieza* p = tablero.obtenerPieza(columna, fila);
            if (p != nullptr) {
                tablero.setSeleccion(columna, fila);
            }
        }
        else {
            int origenX = tablero.getSeleccionX();
            int origenY = tablero.getSeleccionY();
            // Solo mover si el destino es diferente al origen
            if (columna != origenX || fila != origenY) {
                Pieza* p = tablero.obtenerPieza(origenX, origenY);
                if (p != nullptr) {
                    tablero.colocarPieza(p, columna, fila);
                }
            }
            // Limpia la selección siempre
            tablero.limpiarSeleccion();
        }

	}
	else if (modoJuego == 2)
	{
		int columna = x / (800 / 4);            // Tablero 8x4
		int fila = 7 - (y / (600 / 8));         // Convertimos coordenada Y
		// Desactiva el resaltado de todas las piezas
		for (Pieza* pieza : tablero2.getPiezas()) {
			pieza->setResaltado(false);
		}
		// Usa la selección del tablero
		if (tablero2.getSeleccionX() == -1 && tablero2.getSeleccionY() == -1) {
			Pieza* p = tablero2.obtenerPieza(columna, fila);
			if (p != nullptr) {
				tablero2.setSeleccion(columna, fila);
			}
		}
        else {
            int origenX = tablero2.getSeleccionX();
            int origenY = tablero2.getSeleccionY();
            // Solo mover si el destino es diferente al origen
            if (columna != origenX || fila != origenY) {
                Pieza* p = tablero2.obtenerPieza(origenX, origenY);
                if (p != nullptr) {
                    tablero2.colocarPieza(p, columna, fila);
                }
            }
            // Limpia la selección siempre
            tablero2.limpiarSeleccion();
        }

    }
    if (estadoActual == MENU) {
        // Convertir coordenadas de ventana a OpenGL [-1, 1]
        float x_gl = (float)x / 400.0f - 1.0f;
        float y_gl = 1.0f - (float)y / 200.0f;

        // Verifica si se hizo clic dentro del botón "Salir"
        if (x_gl >= -0.55f && x_gl <= 0.2f &&
            y_gl >= -0.35f && y_gl <= -0.25f) {
            std::cout << "Saliendo del juego por clic..." << std::endl;
            exit(0);
        }
    }
}