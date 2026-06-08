/* PACMAN ALLEGRO 5 - macOS */

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

#define MAXFILAS 20
#define MAXCOLS 29
#define TAM 30

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_TIMER *timer = NULL;

ALLEGRO_BITMAP *roca = NULL;
ALLEGRO_BITMAP *pacbmp = NULL;
ALLEGRO_BITMAP *comida = NULL;

int dir = 4;

int px = 30 * 14;
int py = 30 * 17;

char mapa[MAXFILAS][MAXCOLS + 1] = {

    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X  o   o o  XXXXX  o o   o X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X  o      o o o o o      o X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X  o  XX  o  XXX  o XX   o X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X XXX XX o    o    o XX XXX X",
    "   o  XX XXXXXXXXXXX XX  o  ",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X XXX XX o    o    o XX XXX X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X  o  XX  o  XXX  o  XX  o X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X XXX   o   o o o    o XXX X",
    "X XXX XXXX XXXXXXXX XXX XXX X",
    "X XXX XXXX  o o o   XXX XXX X",
    "X  o o o   XXXXXXXX  o o o X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

};

bool game_over() {

    for (int row = 0; row < MAXFILAS; row++) {

        for (int col = 0; col < MAXCOLS; col++) {

            if (mapa[row][col] == 'o') {
                return true;
            }
        }
    }

    return false;
}

void dibujar_mapa() {

    for (int row = 0; row < MAXFILAS; row++) {

        for (int col = 0; col < MAXCOLS; col++) {

            if (mapa[row][col] == 'X') {

                al_draw_bitmap(
                    roca,
                    col * TAM,
                    row * TAM,
                    0
                );
            }

            if (mapa[row][col] == 'o') {

                al_draw_bitmap(
                    comida,
                    col * TAM,
                    row * TAM,
                    0
                );

                // comer bolita
                if ((py / TAM) == row &&
                    (px / TAM) == col) {

                    mapa[row][col] = ' ';
                }
            }
        }
    }
}

void dibujar_personaje() {

    int frame = dir * 33;

    al_draw_bitmap_region(
        pacbmp,
        frame,
        0,
        33,
        33,
        px,
        py,
        0
    );
}

int main() {

    // iniciar allegro
    if (!al_init()) {

        cout << "Error iniciando Allegro\n";
        return -1;
    }

    // addon imagenes
    if (!al_init_image_addon()) {

        cout << "Error iniciando addon imagen\n";
        return -1;
    }

    // teclado
    al_install_keyboard();

    // ventana
    display = al_create_display(880, 600);

    if (!display) {

        cout << "No se pudo crear la ventana\n";
        return -1;
    }

    // cola eventos
    queue = al_create_event_queue();

    // timer
    timer = al_create_timer(0.15);

    // registrar eventos
    al_register_event_source(
        queue,
        al_get_keyboard_event_source()
    );

    al_register_event_source(
        queue,
        al_get_timer_event_source(timer)
    );

    // cargar imagenes
    roca = al_load_bitmap("roca.bmp");
    pacbmp = al_load_bitmap("pacman.bmp");
    comida = al_load_bitmap("comida.bmp");

    if (!roca || !pacbmp || !comida) {

        cout << "Error cargando imagenes\n";
        return -1;
    }

    bool running = true;

    al_start_timer(timer);

    while (running && game_over()) {

        ALLEGRO_EVENT ev;

        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {

            ALLEGRO_KEYBOARD_STATE estado;

            al_get_keyboard_state(&estado);

            // direcciones
            if (al_key_down(&estado, ALLEGRO_KEY_RIGHT)) {

                dir = 1;
            }

            else if (al_key_down(&estado, ALLEGRO_KEY_LEFT)) {

                dir = 0;
            }

            else if (al_key_down(&estado, ALLEGRO_KEY_UP)) {

                dir = 2;
            }

            else if (al_key_down(&estado, ALLEGRO_KEY_DOWN)) {

                dir = 3;
            }

            // mover izquierda
            if (dir == 0) {

                if ((px - TAM) >= 0 &&
                    mapa[py / TAM][(px - TAM) / TAM] != 'X') {

                    px -= TAM;
                }
            }

            // mover derecha
            if (dir == 1) {

                if ((px + TAM) < (MAXCOLS * TAM) &&
                    mapa[py / TAM][(px + TAM) / TAM] != 'X') {

                    px += TAM;
                }
            }

            // mover arriba
            if (dir == 2) {

                if ((py - TAM) >= 0 &&
                    mapa[(py - TAM) / TAM][px / TAM] != 'X') {

                    py -= TAM;
                }
            }

            // mover abajo
            if (dir == 3) {

                if ((py + TAM) < (MAXFILAS * TAM) &&
                    mapa[(py + TAM) / TAM][px / TAM] != 'X') {

                    py += TAM;
                }
            }

            // tunel lateral
            if (px < 0) {

                px = 840;
            }

            if (px > 840) {

                px = 0;
            }

            // limpiar pantalla
            al_clear_to_color(
                al_map_rgb(0, 0, 0)
            );

            // dibujar
            dibujar_mapa();
            dibujar_personaje();

            // mostrar
            al_flip_display();
        }

        // salir con ESC
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {

                running = false;
            }
        }
    }

    // liberar memoria
    al_destroy_bitmap(roca);
    al_destroy_bitmap(pacbmp);
    al_destroy_bitmap(comida);

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}