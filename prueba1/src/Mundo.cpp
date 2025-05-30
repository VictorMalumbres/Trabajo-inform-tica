#include "Mundo.h"
#include <freeglut.h>
#include <iostream>
#include "ETSIDI.h"

extern Mundo mundo;

bool juegoEnPausa = false;

bool musica = false;  //Para cargar la musica en mostrarMenuEnVentana una sola vez (luego se encarga setEstadoActual)

bool leyendaParaInicio = false;

Mundo::Mundo() : estadoActual(MENU), modoJuego(1), seleccionX(-1), seleccionY(-1) {} // forzamos el estado inicial

void Mundo::inicializaModo1() {
    tablero.reiniciarTablero();
    tablero.inicializaSilverman();
}

void Mundo::inicializaModo2() {
    tablero.reiniciarTablero();
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
    case CONFIRMAR_MENU:
        mostrarConfirmacionMenu();
        break;
    case CONFIRMAR_SALIR:
        mostrarConfirmacionSalir();
        break;
    case VICTORIA:
        mostrarMenuVictoria();
        break;
    case EMPATE:
        mostrarMenuEmpate();
        break;
    case CORONACION:
        mostrarMenuCoronacion();
        break;
    case OPONENTE:
        mostrarMenuOponente();
        break;
    case INSTRUCCIONES_DEMI:
        mostrarInstruccionesDemi();
        break;
    case INSTRUCCIONES_SILVERMAN:
        mostrarInstruccionesSilverman();
        break;
    case INSTRUCCIONES_PIEZAS:
        mostrarInstruccionesPiezas();
        break;

    case LEYENDA:
        mostrarLeyenda();
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
    glColor3f(1.0f, 0.4f, 0.7f); // Color rosita

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(escala, escala, 1.0f);

    glLineWidth(4.0f); // Grosor de línea para negrita

    float offset = 0.005f;  // desplazamiento para simular negrita
    for (float dx = -offset; dx <= offset; dx += offset) {
        for (float dy = -offset; dy <= offset; dy += offset) {
            glPushMatrix();
            glTranslatef(dx, dy, 0.0f);
            for (const char* c = texto; *c != '\0'; ++c) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
            }
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void Mundo::mostrarMenuEnVentana() {
    // Restablecer matrices de proyección y modelado
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    tablero.reiniciarTablero();
    tablero2.reiniciarTablero();
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar la ventana

    // Fondo con textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/MENU.png").id);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 0); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    if (musica == false) {
        musicaActual = "sonidos/elevador.mp3";
        ETSIDI::playMusica(musicaActual.c_str(), true);
        musica = true;
    }

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

    glColor3f(0.0f, 0.5f, 0.0f); // verde
    glVertex2f(-0.45f, -0.25f); glVertex2f(0.45f, -0.25f);
    glVertex2f(0.45f, -0.15f); glVertex2f(-0.45f, -0.15f);
    glEnd();

    // Dibujar el título del menú
    renderizarTextoGrande("MENU DEL JUEGO", -0.45f, 0.8f, 0.0008f);
    renderizarTexto("1. Ver instrucciones del juego", -0.4f, 0.58f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Jugar partida SILVERMAN 4X5", -0.4f, 0.38f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. Jugar partida DEMI", -0.4f, 0.18f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("4. Salir", -0.4f, -0.02f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Seleccione una opcion con el raton...", -0.3f, -0.22f, GLUT_BITMAP_HELVETICA_12);

    //Instrucciones de la música en el juego
    renderizarTexto("Usa + o - para cambiar el volumen en el juego", 0.45f, -0.38f, GLUT_BITMAP_HELVETICA_10);
    renderizarTexto("Pulsa espacio para pausar el juego", 0.45f, -0.43f, GLUT_BITMAP_HELVETICA_10);

    glutSwapBuffers(); // Mostrar el contenido
}

void Mundo::mostrarInstruccionesEnVentana() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar la ventana

    // Dibujar fondo general
    glColor3f(0.1f, 0.1f, 0.1f); // Gris oscuro
    glBegin(GL_QUADS);
    glVertex2f(-0.95f, 0.75f); glVertex2f(0.95f, 0.75f);
    glVertex2f(0.95f, -0.4f); glVertex2f(-0.95f, -0.4f);
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
    renderizarTexto("INSTRUCCIONES DEL JUEGO", -0.3f, 0.6f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("1. Instrucciones modo DEMI.", -0.8f, 0.4f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Instrucciones modo SILVERMAN.", -0.8f, 0.2f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. Movimiento estandar piezas.", -0.8f, 0.0f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Presione la tecla esc para volver al menu...", -0.8f, -0.3f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers(); // Mostrar contenido en pantalla
    glutKeyboardFunc(manejarTeclado);
}

void manejarTeclado(unsigned char key, int x, int y) {
    if (mundo.getEstadoActual() == JUEGO) {
        if (key == ' ') {
            juegoEnPausa = !juegoEnPausa;
            if (juegoEnPausa) {
                ETSIDI::stopMusica();
                std::cout << "Juego pausado" << std::endl;
            }
            else {
                ETSIDI::playMusica(mundo.musicaActual.c_str(), true);
                std::cout << "Juego reanudado" << std::endl;
            }
            glutPostRedisplay();
        }
    }


    else if ((mundo.getEstadoActual() == INSTRUCCIONES ||
        mundo.getEstadoActual() == INSTRUCCIONES_DEMI ||
        mundo.getEstadoActual() == INSTRUCCIONES_SILVERMAN ||
        mundo.getEstadoActual() == INSTRUCCIONES_PIEZAS) && key == 27) { // ESC
        if (mundo.getEstadoActual() == INSTRUCCIONES) {
            mundo.setEstadoActual(MENU);  // Volver al menú principal
        }
        else {
            mundo.setEstadoActual(INSTRUCCIONES);  // Volver al menú de instrucciones
        }
        glutPostRedisplay();
        return;
    }

    if (juegoEnPausa) {  //Sin esto se podia pulsar en cualquier momento
        if (key == 'q' || key == 'Q') {
            juegoEnPausa = false;
            mundo.setEstadoActual(CONFIRMAR_SALIR);
            glutPostRedisplay();
        }

        else if (key == 'm' || key == 'M') {
            juegoEnPausa = false;
            mundo.setEstadoActual(CONFIRMAR_MENU);
            mundo.musicaActual = "sonidos/elevador.mp3";
            ETSIDI::playMusica(mundo.musicaActual.c_str(), true);
            glutPostRedisplay();
        }
    }


    else if (key == '-') {  //Bajar la musica en el juego
        if (mundo.getVolumen() > 0) {
            mundo.decrementoVolumen();
            mundo.volumenMusica();
        }
    }

    else if (key == '+') {  //Subir la musica en el juego
        if (mundo.getVolumen() < 3) {
            mundo.incrementoVolumen();
            mundo.volumenMusica();
        }
    }
}

void Mundo::volumenMusica() {
    if (mundo.volumen == 3) {
        mundo.musicaActual = "sonidos/musica_clasica.mp3";
        ETSIDI::playMusica(mundo.musicaActual.c_str(), true);
    }
    if (mundo.volumen == 2) {
        mundo.musicaActual = "sonidos/musica_clasica (-50%).mp3";
        ETSIDI::playMusica(mundo.musicaActual.c_str(), true);
    }
    else if (mundo.volumen == 1) {
        mundo.musicaActual = "sonidos/musica_clasica (-85%).mp3";
        ETSIDI::playMusica(mundo.musicaActual.c_str(), true);
    }
    else if (mundo.volumen == 0) {
        ETSIDI::stopMusica();
    }
}

void Mundo::manejarTeclado(unsigned char key, int x, int y) {
    ::manejarTeclado(key, x, y);
}

void Mundo::mostrarPausa() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 0.0f);
    std::string texto1 = "JUEGO EN PAUSA";
    glRasterPos2f(-0.8f, 0.7f);
    for (char c : texto1) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    float anchoBoton = 1.0f; // ancho total 1.0 (de -0.5 a 0.5)
    float alturaBoton = 0.15f; // altura de cada botón
    float separacion = 0.05f; // separación entre botones

    // Posiciones verticales de los botones (de arriba a abajo)
    float yBotonVerLeyenda = 0.5f;
    float yBotonReiniciar = yBotonVerLeyenda - alturaBoton - separacion;
    float yBotonVolverMenu = yBotonReiniciar - alturaBoton - separacion;
    float yBotonSalirJuego = yBotonVolverMenu - alturaBoton - separacion;

    // Botón Ver Leyenda
    glColor3f(0.7f, 0.7f, 0.2f); // Amarillo claro
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, yBotonVerLeyenda);
    glVertex2f(0.5f, yBotonVerLeyenda);
    glVertex2f(0.5f, yBotonVerLeyenda - alturaBoton);
    glVertex2f(-0.5f, yBotonVerLeyenda - alturaBoton);
    glEnd();

    // Botón Reiniciar partida
    glColor3f(0.2f, 0.6f, 0.6f); // Azul verdoso
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, yBotonReiniciar);
    glVertex2f(0.5f, yBotonReiniciar);
    glVertex2f(0.5f, yBotonReiniciar - alturaBoton);
    glVertex2f(-0.5f, yBotonReiniciar - alturaBoton);
    glEnd();

    // Botón Volver al menú
    glColor3f(0.2f, 0.6f, 0.2f); // Verde
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, yBotonVolverMenu);
    glVertex2f(0.5f, yBotonVolverMenu);
    glVertex2f(0.5f, yBotonVolverMenu - alturaBoton);
    glVertex2f(-0.5f, yBotonVolverMenu - alturaBoton);
    glEnd();

    // Botón Salir del juego
    glColor3f(0.6f, 0.2f, 0.2f); // Rojo
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, yBotonSalirJuego);
    glVertex2f(0.5f, yBotonSalirJuego);
    glVertex2f(0.5f, yBotonSalirJuego - alturaBoton);
    glVertex2f(-0.5f, yBotonSalirJuego - alturaBoton);
    glEnd();


    renderizarTexto("Ver Leyenda", -0.17f, 0.4f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("Reiniciar partida", -0.17f, 0.2f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("Volver al menu", -0.17f, 0.0f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("Salir del juego", -0.17f, -0.2f, GLUT_BITMAP_HELVETICA_18);




    glutSwapBuffers();
}

void Mundo::iniciarJuego() {
    mundo.volumenMusica();
    musica = false;

    mundo.enJuego = true;
    estadoActual = JUEGO;
    inicializaModo1();
    //glutKeyboardFunc(manejarTeclado);
    glutDisplayFunc([]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!juegoEnPausa) {
            mundo.dibuja();
        }
        else {
            ETSIDI::stopMusica();
            mundo.mostrarPausa();
        }
        });
    glutIdleFunc([]() {glutPostRedisplay(); });
}

void Mundo::iniciar2dojuego() {
    mundo.volumenMusica();
    musica = false;

    mundo.enJuego = true;
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
            mundo.mostrarPausa();
        }

        });
    glutIdleFunc([]() {glutPostRedisplay(); });
}

void Mundo::cerrarAplicacion() {
    std::cout << "Saliendo del juego..." << std::endl;
    //glutLeaveMainLoop(); // Cierra la ventana y termina el bucle principal de GLUT, no funciona
    exit(0); // Termina el programa
}

bool Mundo::estaEnMenu() const {
    return estadoActual == MENU;
}

void Mundo::procesarClick(int x, int y) {
    // Convertir coordenadas de ventana a OpenGL [-1, 1]
    float x_gl = (float)x / 400.0f - 1.0f; // 800px de ancho
    float y_gl = 1.0f - (float)y / 300.0f; // 600px de alto

    if (estadoActual == CONFIRMAR_SALIR) {
        // Botón SI: x entre -0.4 y -0.1, y entre -0.3 y -0.1
        if (x_gl >= -0.4f && x_gl <= -0.1f && y_gl >= -0.3f && y_gl <= -0.1f) {
            cerrarAplicacion(); // Salir del juego
            return;
        }
        // Botón NO: x entre 0.1 y 0.4, y entre -0.3 y -0.1
        if (x_gl >= 0.1f && x_gl <= 0.4f && y_gl >= -0.3f && y_gl <= -0.1f) {
            if (mundo.enJuego == true) {
                setEstadoActual(JUEGO); // Vuelve al juego si estabamos jugando
            }
            else if (mundo.enJuego == false) {
                setEstadoActual(MENU); // Vuelve al menu si no estabamos jugando
            }
            glutPostRedisplay();
            return;
        }
    }

    if (estadoActual == CONFIRMAR_MENU) {
        // Botón SI: x entre -0.4 y -0.1, y entre -0.3 y -0.1
        if (x_gl >= -0.4f && x_gl <= -0.1f && y_gl >= -0.3f && y_gl <= -0.1f) {
            // Aquí debes ponerlo:
            setEstadoActual(MENU);
            glutPostRedisplay();
            return;
        }
        // Botón NO: x entre 0.1 y 0.4, y entre -0.3 y -0.1
        if (x_gl >= 0.1f && x_gl <= 0.4f && y_gl >= -0.3f && y_gl <= -0.1f) {
            // Cancelar y volver al juego
            setEstadoActual(JUEGO);
            glutPostRedisplay();
            return;
        }
    }
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
                    if (p->mueve(tablero, columna, fila)) {
                        tablero.colocarPieza(p, columna, fila);
                    }
                    else {
                        std::cout << "Movimiento invalido" << std::endl;
                    }
                }
            }
            // Limpia la selección siempre
            tablero.limpiarSeleccion();

            if (activarIA) {

                if (tablero.getTurno() == 1) {
                    iaNegras.jugar(tablero);
                    tablero.limpiarSeleccion();
                }
                glutPostRedisplay();
            }
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

            if (activarIA) {

                if (tablero2.getTurno() == 1) {
                    iaNegras.jugar(tablero2);
                    tablero2.limpiarSeleccion();
                }
                glutPostRedisplay();
            }
        }
    }
    if (estadoActual == MENU) {
        // Convertir coordenadas de ventana a OpenGL [-1, 1]
        float x_gl = (float)x / 400.0f - 1.0f;      // Correcto para 800px de ancho
        float y_gl = 1.0f - (float)y / 300.0f;



        // Comprobamos las opciones en el área de botones
        if (x_gl >= -0.45f && x_gl <= 0.45f) {
            if (y_gl >= 0.55f && y_gl <= 0.65f) {
                // Opción 1: Ver instrucciones
                estadoActual = INSTRUCCIONES;
                std::cout << "Opción 1: Ver instrucciones" << std::endl;
                glutPostRedisplay();
                return;
            }
            else if (y_gl >= 0.35f && y_gl <= 0.45f) {
                // Opción 2: Jugar partida SILVERMAN 4X5
                setModoJuego(1);
                estadoActual = OPONENTE;
                std::cout << "Opción 2: Jugar SILVERMAN 4X5" << std::endl;
                return;
            }
            else if (y_gl >= 0.15f && y_gl <= 0.25f) {
                // Opción 3: Jugar partida DEMI
                setModoJuego(2);
                estadoActual = OPONENTE;
                std::cout << "Opción 3: Jugar DEMI" << std::endl;
                return;
            }
            else if (y_gl >= -0.05f && y_gl <= 0.05f) {
                // Opción 4: Salir
                setEstadoActual(CONFIRMAR_SALIR); // Cambia esto
                glutPostRedisplay();
                return;
            }

        }
    }

    if (estadoActual == INSTRUCCIONES) {
        if (x_gl >= -0.6f && x_gl <= 0.6f) {
            if (y_gl >= 0.4f && y_gl <= 0.5f) {
                // Instrucciones modo DEMI
                estadoActual = INSTRUCCIONES_DEMI;
                glutPostRedisplay();
                return;
            }
            else if (y_gl >= 0.2f && y_gl <= 0.3f) {
                // Instrucciones modo SILVERMAN
                estadoActual = INSTRUCCIONES_SILVERMAN;
                glutPostRedisplay();
                return;
            }
            else if (y_gl >= 0.0f && y_gl <= 0.1f) {
                // Movimiento piezas estándar
                estadoActual = INSTRUCCIONES_PIEZAS;
                glutPostRedisplay();
                return;
            }
        }
    }
    if (estadoActual == OPONENTE) {
        float x_gl = (float)x / 400.0f - 1.0f;
        float y_gl = 1.0f - (float)y / 300.0f;

        if (x_gl >= -0.45f && x_gl <= 0.45f) {
            if (y_gl >= 0.55f && y_gl <= 0.65f) {
                activarIA = false;
                proximoVsIA = false;
                leyendaParaInicio = true; // <--- Añade esto
                estadoActual = LEYENDA;
                glutPostRedisplay();
                std::cout << "Opción 1: Jugador VS Jugador" << std::endl;
                return;
            }
            else if (y_gl >= 0.35f && y_gl <= 0.45f) {
                activarIA = true;
                proximoVsIA = true;
                leyendaParaInicio = true;
                estadoActual = LEYENDA;
                glutPostRedisplay();
                std::cout << "Opción 2: Jugador VS IA" << std::endl;
                return;
            }
            else if (y_gl >= -0.05f && y_gl <= 0.05f) {
                // Volver al menú
                setEstadoActual(MENU);
                glutPostRedisplay();
                return;
            }
        }
    }

    if (juegoEnPausa) {
        // Convertir coordenadas de ventana a OpenGL [-1, 1]
        float x_gl = (float)x / 400.0f - 1.0f; // 800px de ancho
        float y_gl = 1.0f - (float)y / 300.0f; // 600px de alto

        // Botón "Ver Leyenda"
        if (x_gl >= -0.5f && x_gl <= 0.5f && y_gl >= 0.40f && y_gl <= 0.55f) {
            juegoEnPausa = false;
            leyendaParaInicio = false;
            setEstadoActual(LEYENDA);
            glutPostRedisplay();
            return;
        }

        // Botón "Volver al menú"
        if (x_gl >= -0.5f && x_gl <= 0.5f && y_gl >= -0.05f && y_gl <= 0.1f) {
            juegoEnPausa = false;
            setEstadoActual(CONFIRMAR_MENU);
            glutPostRedisplay();
            return;
        }
        // Botón "Salir del juego"
        if (x_gl >= -0.5f && x_gl <= 0.5f && y_gl >= -0.3f && y_gl <= -0.15f) {
            juegoEnPausa = false;
            setEstadoActual(CONFIRMAR_SALIR);
            glutPostRedisplay();
            return;
        }

        if (x_gl >= -0.5f && x_gl <= 0.5f && y_gl >= 0.20f && y_gl <= 0.35f) {
            juegoEnPausa = false;

            //reiniciar
            if (modoJuego == 1) iniciarJuego();
            else iniciar2dojuego();
            return;
        }

        // Si se hace clic fuera de los botones, no hacer nada
        return;
    }
    if (estadoActual == VICTORIA) {
        float x_gl = (float)x / 400.0f - 1.0f;
        float y_gl = 1.0f - (float)y / 300.0f;

        // Volver a jugar
        if (x_gl >= -0.4f && x_gl <= 0.4f && y_gl >= -0.05f && y_gl <= 0.1f) {
            if (modoJuego == 1)
                iniciarJuego();
            else
                iniciar2dojuego();
            return;
        }
        // Volver al menú
        if (x_gl >= -0.4f && x_gl <= 0.4f && y_gl >= -0.3f && y_gl <= -0.15f) {
            setEstadoActual(MENU);
            glutPostRedisplay();
            return;
        }
    }
    if (estadoActual == EMPATE) {  //Deteccion de botones para menu empate
        float x_gl = (float)x / 400.0f - 1.0f;
        float y_gl = 1.0f - (float)y / 300.0f;

        // Volver a jugar
        if (x_gl >= -0.4f && x_gl <= 0.4f && y_gl >= -0.05f && y_gl <= 0.1f) {
            if (modoJuego == 1)
                iniciarJuego();
            else
                iniciar2dojuego();
            return;
        }
        // Volver al menú
        if (x_gl >= -0.4f && x_gl <= 0.4f && y_gl >= -0.3f && y_gl <= -0.15f) {
            setEstadoActual(MENU);
            glutPostRedisplay();
            return;
        }
    }
    if (estadoActual == CORONACION) {
        // Convierte las coordenadas del ratón a las del menú
        float x_gl = (float)x / 400.0f - 1.0f;
        float y_gl = 1.0f - (float)y / 300.0f;

        if (modoJuego == 1) { // Silverman
            // Torre
            if (x_gl >= -0.3f && x_gl <= 0.3f && y_gl >= 0.05f && y_gl <= 0.15f) {
                tablero.anadirPieza(new Torre(coronacionX, coronacionY, colorCoronacion));
                tablero.cambiarTurno(); // Cambia el turno de forma segura
                setEstadoActual(JUEGO);
                glutPostRedisplay();
                return;
            }
            // Reina
            if (x_gl >= -0.3f && x_gl <= 0.3f && y_gl >= -0.15f && y_gl <= -0.05f) {
                tablero.anadirPieza(new Reina(coronacionX, coronacionY, colorCoronacion));
                tablero.cambiarTurno();
                setEstadoActual(JUEGO);
                glutPostRedisplay();
                return;
            }
        }
        else { // Demi
            // Alfil
            if (x_gl >= -0.3f && x_gl <= 0.3f && y_gl >= 0.10f && y_gl <= 0.20f) {
                tablero2.anadirPieza(new Alfil(coronacionX, coronacionY, colorCoronacion));
                tablero2.cambiarTurno();
                setEstadoActual(JUEGO);
                glutPostRedisplay();
                return;
            }
            // Caballo
            if (x_gl >= -0.3f && x_gl <= 0.3f && y_gl >= -0.05f && y_gl <= 0.05f) {
                tablero2.anadirPieza(new Caballo(coronacionX, coronacionY, colorCoronacion));
                tablero2.cambiarTurno();
                setEstadoActual(JUEGO);
                glutPostRedisplay();
                return;
            }
            // Torre
            if (x_gl >= -0.3f && x_gl <= 0.3f && y_gl >= -0.20f && y_gl <= -0.10f) {
                tablero2.anadirPieza(new Torre(coronacionX, coronacionY, colorCoronacion));
                tablero2.cambiarTurno();
                setEstadoActual(JUEGO);
                glutPostRedisplay();
                return;
            }
        }


        return;
    }
    if (estadoActual == LEYENDA) {
        if (leyendaParaInicio) {
            activarIA = proximoVsIA;
            if (modoJuego == 1) iniciarJuego();
            else iniciar2dojuego();
        }
        else {
            setEstadoActual(JUEGO);
            glutPostRedisplay();
        }
        return;
    }

}

void Mundo::mostrarConfirmacionMenu() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f); glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Mensaje
    renderizarTexto("¿Estas seguro de que quieres volver al menu?", -0.7f, 0.2f, GLUT_BITMAP_HELVETICA_18);

    // Botón Sí
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.1f); glVertex2f(-0.1f, -0.1f);
    glVertex2f(-0.1f, -0.3f); glVertex2f(-0.4f, -0.3f);
    glEnd();
    renderizarTexto("SI", -0.32f, -0.22f, GLUT_BITMAP_HELVETICA_18);

    // Botón No
    glColor3f(0.6f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.1f, -0.1f); glVertex2f(0.4f, -0.1f);
    glVertex2f(0.4f, -0.3f); glVertex2f(0.1f, -0.3f);
    glEnd();
    renderizarTexto("NO", 0.18f, -0.22f, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

void Mundo::mostrarConfirmacionSalir() {
    // Fondo con imagen de la librería
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/miniontriste.png").id);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    // Invertir X y Y de las coordenadas de textura para girar 180 grados
    glTexCoord2f(1, 0); glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(0, 0); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(-1.0f, -1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    // Mensaje
    renderizarTexto("¿Estas seguro de que quieres salir del juego?", -0.7f, 0.2f, GLUT_BITMAP_HELVETICA_18);

    // Botón Sí
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.1f); glVertex2f(-0.1f, -0.1f);
    glVertex2f(-0.1f, -0.3f); glVertex2f(-0.4f, -0.3f);
    glEnd();
    renderizarTexto("SI", -0.32f, -0.22f, GLUT_BITMAP_HELVETICA_18);

    // Botón No
    glColor3f(0.6f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.1f, -0.1f); glVertex2f(0.4f, -0.1f);
    glVertex2f(0.4f, -0.3f); glVertex2f(0.1f, -0.3f);
    glEnd();
    renderizarTexto("NO", 0.18f, -0.22f, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

void Mundo::setEstadoActual(EstadoMundo estado) {
    estadoActual = estado;
    if (estado == MENU) {
        mundo.enJuego = false;
    }
    else if (estado == JUEGO) {
        mundo.volumenMusica();
    }
    // No pongas música para CONFIRMAR_MENU ni CONFIRMAR_SALIR
}

void Mundo::volverAlMenu() {
    estadoActual = MENU;
    tablero.reiniciarTablero();
    tablero2.reiniciarTablero();
    glutDisplayFunc([]() {
        mundo.mostrarMenuEnVentana();
        });
    glutPostRedisplay();
}

void Mundo::inicializarTableros() {
    tablero.setMundo(this);
    tablero2.setMundo(this);
}

void Mundo::mostrarMenuVictoria() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f); glVertex2f(-1.0f, -1.0f);
    glEnd();


    // Mensaje "JAQUE MATE" grande y centrado arriba
    renderizarTextoGrande("JAQUE MATE", -0.47f, 0.7f, 0.0012f);

    // Mensaje de victoria (más pequeño y centrado)
    glColor3f(1.0f, 1.0f, 0.0f);
    std::string mensaje = (jugadorGanador == 0) ? "¡Ganan las BLANCAS!" : "¡Ganan las NEGRAS!";
    renderizarTextoGrande(mensaje.c_str(), -0.42f, 0.5f, 0.0007f);


    // Botón: Volver a jugar
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, 0.1f); glVertex2f(0.4f, 0.1f);
    glVertex2f(0.4f, -0.05f); glVertex2f(-0.4f, -0.05f);
    glEnd();
    renderizarTexto("Volver a jugar", -0.15f, 0.02f, GLUT_BITMAP_HELVETICA_18);

    // Botón: Volver al menú
    glColor3f(0.2f, 0.2f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.15f); glVertex2f(0.4f, -0.15f);
    glVertex2f(0.4f, -0.3f); glVertex2f(-0.4f, -0.3f);
    glEnd();
    renderizarTexto("Volver al menu", -0.17f, -0.23f, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

void Mundo::mostrarMenuEmpate() {  //Menu de empate, practicamente igual que el de victoria
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f); glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Mensaje de empate (más pequeño y centrado)
    glColor3f(1.0f, 1.0f, 0.0f);
    std::string mensaje = "EMPATE";
    renderizarTextoGrande(mensaje.c_str(), -0.18f, 0.5f, 0.0007f);

    // Botón: Volver a jugar
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, 0.1f); glVertex2f(0.4f, 0.1f);
    glVertex2f(0.4f, -0.05f); glVertex2f(-0.4f, -0.05f);
    glEnd();
    renderizarTexto("Volver a jugar", -0.15f, 0.02f, GLUT_BITMAP_HELVETICA_18);

    // Botón: Volver al menú
    glColor3f(0.2f, 0.2f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.15f); glVertex2f(0.4f, -0.15f);
    glVertex2f(0.4f, -0.3f); glVertex2f(-0.4f, -0.3f);
    glEnd();
    renderizarTexto("Volver al menu", -0.16f, -0.23f, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

void Mundo::mostrarMenuCoronacion() {
    // Configura la proyección y el modelo de vista
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo general del menú
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, 0.5f); glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f); glVertex2f(-0.5f, -0.5f);
    glEnd();

    if (modoJuego == 1) { // Silverman
        renderizarTexto("Elige pieza:", -0.1f, 0.3f, GLUT_BITMAP_HELVETICA_18);

        // Rectángulo para "1. Torre"
        glColor3f(0.2f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.18f); glVertex2f(0.25f, 0.18f);
        glVertex2f(0.25f, 0.06f); glVertex2f(-0.15f, 0.06f);
        glEnd();
        renderizarTexto("1. Torre", -0.1f, 0.1f, GLUT_BITMAP_HELVETICA_18);

        // Rectángulo para "2. Reina"
        glColor3f(0.2f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.02f); glVertex2f(0.25f, -0.02f);
        glVertex2f(0.25f, -0.14f); glVertex2f(-0.15f, -0.14f);
        glEnd();
        renderizarTexto("2. Reina", -0.1f, -0.1f, GLUT_BITMAP_HELVETICA_18);
    }
    else { // Demi
        renderizarTexto("Elige pieza:", -0.1f, 0.3f, GLUT_BITMAP_HELVETICA_18);

        // Rectángulo para "1. Alfil"
        glColor3f(0.2f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.23f); glVertex2f(0.25f, 0.23f);
        glVertex2f(0.25f, 0.11f); glVertex2f(-0.15f, 0.11f);
        glEnd();
        renderizarTexto("1. Alfil", -0.1f, 0.15f, GLUT_BITMAP_HELVETICA_18);

        // Rectángulo para "2. Caballo"
        glColor3f(0.2f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.08f); glVertex2f(0.25f, 0.08f);
        glVertex2f(0.25f, -0.04f); glVertex2f(-0.15f, -0.04f);
        glEnd();
        renderizarTexto("2. Caballo", -0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18);

        // Rectángulo para "3. Torre"
        glColor3f(0.2f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.07f); glVertex2f(0.25f, -0.07f);
        glVertex2f(0.25f, -0.19f); glVertex2f(-0.15f, -0.19f);
        glEnd();
        renderizarTexto("3. Torre", -0.1f, -0.15f, GLUT_BITMAP_HELVETICA_18);
    }

    glutSwapBuffers();
}

void Mundo::mostrarMenuOponente() {
    // Restablecer matrices de proyección y modelado
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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

    // Colores para los botones
    glColor3f(0.2f, 0.2f, 0.6f); // RGB

    // Dibujar rectángulos de fondo para cada opción
    glBegin(GL_QUADS);
    glVertex2f(-0.45f, 0.65f); glVertex2f(0.45f, 0.65f);
    glVertex2f(0.45f, 0.55f); glVertex2f(-0.45f, 0.55f);

    glVertex2f(-0.45f, 0.45f); glVertex2f(0.45f, 0.45f);
    glVertex2f(0.45f, 0.35f); glVertex2f(-0.45f, 0.35f);

    glVertex2f(-0.45f, 0.05f); glVertex2f(0.45f, 0.05f);
    glVertex2f(0.45f, -0.05f); glVertex2f(-0.45f, -0.05f);
    glEnd();

    // Dibujar el título del menú
    renderizarTextoGrande("MODO DE JUEGO", -0.45f, 0.8f, 0.0008f);
    renderizarTexto("1. Jugador VS Jugador", -0.4f, 0.58f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("2. Jugador VS Maquina", -0.4f, 0.38f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("3. Volver", -0.4f, -0.02f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers(); // Mostrar el contenido
}

void Mundo::mostrarInstruccionesDemi() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo para instrucciones Demi
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/instrucciones.png").id);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 0); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);

    // Título fijo
    renderizarTextoGrande("DEMI", -0.45f, 0.8f, 0.0008f);

    // Texto centrado horizontalmente justo debajo del título
    float x_text = -0.5f;  // Ajusta según convenga
    float y_start = 0.55f;
    float line_height = 0.05f;

    renderizarTexto("Juego de miniajedrez Demi con el cual puedes jugar", x_text, y_start, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("contra el ordenador o entre dos con un amigo.", x_text, y_start - line_height, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Esta singular variante del mini ajedrez tiene un tablero", x_text, y_start - 2 * line_height, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("estrecho de 4x8 casillas que lleva la mitad de las piezas", x_text, y_start - 3 * line_height, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("del ajedrez estándar y excluye las reinas.", x_text, y_start - 4 * line_height, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Sigue las reglas estándar del Ajedrez, en la promoción", x_text, y_start - 5 * line_height, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("puedes elegir entre alfil, caballo y torre,", x_text, y_start - 6 * line_height, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("es posible la captura al paso y no hay enroque.", x_text, y_start - 7 * line_height, GLUT_BITMAP_HELVETICA_12);

    renderizarTexto("Presione ESC para volver al menu...", x_text, -0.3f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}

void Mundo::mostrarInstruccionesSilverman() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo para instrucciones Silverman
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/instrucciones.png").id);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 0); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);

    renderizarTextoGrande("SILVERMAN", -0.45f, 0.8f, 0.0008f);

    renderizarTexto("Juego de Ajedrez 4x5 con torres y reina.", -0.5f, 0.55f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Te da la posibilidad de jugar con un amigo en el mismo ordenador.", -0.5f, 0.50f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Esta singular variante del miniajedrez tiene un tablero de 4x5 casillas", -0.5f, 0.45f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("y no tiene los alfiles ni los caballos.", -0.5f, 0.40f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Sigue las reglas estándar del Ajedrez, el peón de su posición inicial", -0.5f, 0.35f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("puede ir adelante de solo una casilla.", -0.5f, 0.30f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("En la promoción puedes elegir entre dama y torre, no hay enroque.", -0.5f, 0.25f, GLUT_BITMAP_HELVETICA_12);

    renderizarTexto("Presione ESC para volver al menu...", -0.5f, -0.3f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}

void Mundo::mostrarInstruccionesPiezas() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo para instrucciones piezas estándar
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/instrucciones.png").id);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 0); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);

    renderizarTextoGrande("MOVIMIENTO DE PIEZAS ESTÁNDAR", -0.9f, 0.8f, 0.0008f);

    renderizarTexto("Cada pieza se mueve según las reglas clásicas del ajedrez.", -0.5f, 0.55f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("- Peones avanzan hacia adelante una casilla, con captura diagonal.", -0.5f, 0.50f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("- Torres se mueven en líneas rectas horizontales y verticales.", -0.5f, 0.45f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("- Alfiles se mueven en diagonal.", -0.5f, 0.40f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("- Caballos se mueven en L.", -0.5f, 0.35f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("- Rey se mueve una casilla en cualquier dirección.", -0.5f, 0.30f, GLUT_BITMAP_HELVETICA_12);
    renderizarTexto("Presione ESC para volver al menu...", -0.5f, -0.3f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}

void Mundo::dibujarPieza(float x, float y, const char* nombre, int color) {
    char archivo[100] = "imagenes/";
    strcat_s(archivo, sizeof(archivo), nombre);
    strcat_s(archivo, sizeof(archivo), "_");
    if (color == 0)
        strcat_s(archivo, sizeof(archivo), "blanco.png");
    else
        strcat_s(archivo, sizeof(archivo), "negro.png");

    unsigned texID = ETSIDI::getTexture(archivo).id;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    // Mejorar calidad con filtrado lineal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(1, 0); glVertex2f(x + 0.2f, y);
    glTexCoord2f(1, 1); glVertex2f(x + 0.2f, y - 0.2f);
    glTexCoord2f(0, 1); glVertex2f(x, y - 0.2f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    renderizarTexto(nombre, x + 0.22f, y - 0.1f, GLUT_BITMAP_HELVETICA_18);
}

void Mundo::mostrarLeyenda() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();

    renderizarTexto("Equipo Blanco", -0.85f, 0.7f, GLUT_BITMAP_HELVETICA_18);
    renderizarTexto("Equipo Negro", 0.15f, 0.7f, GLUT_BITMAP_HELVETICA_18);

    const char* piezasModo1[] = { "rey", "reina", "torre", "peon" };              // Silverman
    const char* piezasModo2[] = { "rey", "torre", "caballo", "alfil", "peon" };   // Demi

    const char** piezas;
    int numPiezas;

    if (modoJuego == 1) {
        piezas = piezasModo1;
        numPiezas = 4;
    }
    else {
        piezas = piezasModo2;
        numPiezas = 5;
    }

    float y = (modoJuego == 1) ? 0.4f : 0.5f;
    float separacion = -0.3f;

    for (int i = 0; i < numPiezas; i++) {
        dibujarPieza(-0.85f, y + i * separacion, piezas[i], 0);  // Blanco
        dibujarPieza(0.15f, y + i * separacion, piezas[i], 1);  // Negro
    }

    renderizarTexto("Haz clic para continuar", -0.3f, -0.85f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}