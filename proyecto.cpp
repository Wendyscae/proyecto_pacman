
<<<<<<< HEAD
/* parte dos de pac man */
#include <allegro.h> 

#define MAXFILAS 21
#define MAXCOLS 30

BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;

int dir=0;
int px=30*10, py=30*10;

char mapa[MAXFILAS][MAXCOLS] = {
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X           XXXXX           X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X                           X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X     XX     XXX     XX     X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X XXX XX             XX XXX X",
    "      XX XXXXXXXXXXX XX      ",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X     XX     XXX     XX     X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X                           X",
    "X XXX XXXX XXXXXXXX XXXX XXXX",
    "X XXX XXXX           XXXX XXX X",
    "X                             X",
    "X XXX XXXX XXXXXXX XXXX XXX X",
    "X XXX XXXX           XXXX XXX X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
};

void dibujar_mapa() {
    int row, col;

    for (row = 0; row < MAXFILAS; row++) {
        // Recorremos hasta 29 para procesar solo los caracteres visibles del laberinto
        for (col = 0; col < 29; col++) { 
            if (mapa[row][col] == 'X') { 
                draw_sprite(buffer, roca, col * 30, row * 30);
            }
        } // <- Aquí cierra el for de las columnas (col)
    } // <- Aquí cierra el for de las filas (row)
} // <- Aquí cierra la función dibujar_mapa

void pantalla(){
	blit(buffwe, screen, 0,0,0,0,880,600);
	
}
void bibujar_personaje(){
	
}
int main(){
	allegro_init();
	install_keyboard();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,880,600,0,0);
	
	buffer= create_bitmap(880, 600);
	roca = load_bitmap("roca.bmp",NULL);
	pacbmp = load_bitmap("pacman.bmp",NULL);
	pacman = create_bitmap(33,33);
	
	
	while(!key[KEY_ESC]){
		if(key[KEY_RIGHT]) dir = 1;  
		else if(key[KEY_LEFT]) dir = 0;
		else if(key[KEY_UP]) dir = 2;
		else if(key[KEY_UP]) dir = 3;
		
		                                   //cuando se precione una tecla
		dibujar_mapa();
		pantalla();
	}
	
	
	
}
END OF MAIN();
=======
int main() {
    printf("proyecto pacman sofia\n");
    return 0;
}
>>>>>>> c6b042e8e63013021f115aa4e58bb26f89682bbc
