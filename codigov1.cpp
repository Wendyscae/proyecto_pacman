
<<<<<<< HEAD
/* parte dos de pac man */
#include <allegro.h>

#define MAXFILAS 21
#define MAXCOLS 30

BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;

int dir=4;
int px=30*14,py=30*17;

char mapa[MAXFILAS][MAXCOLS] = {
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X  o   o o  XXXXX  o o   o  X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X  o      o o o o o      o  X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X  o  XX  o  XXX  o XX   o  X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X XXX XX o    o    o XX XXX X",
    "   o  XX XXXXXXXXXXX XX  o   ",
    "X XXX XX XXXXXXXXXXX XX XXX X",//
    "X XXX XX o    o    o XX XXX X", //
    "X XXX XXXXXX XXX XXXXXX XXX X",//
    "X  o  XX  o  XXX  o  XX  o  X",//
    "X XXX XX XXXXXXXXXXX XX XXX X",//
    "X XXX   o   o o o    o  XXX X",//
    "X XXX XXXX XXXXXXXX XXX XXX X",// 
    "X XXX XXXX  o o o   XXX XXX X",//4
    "X  o o o   XXXXXXXX  o o o  X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

void dibujar_mapa() {
    int row, col;

    for (row = 0; row < MAXFILAS; row++) {
        // Recorremos hasta 29 para procesar solo los caracteres visibles del laberinto
        for (col = 0; col < MAXCOLS; col++) { 
            if (mapa[row][col] == 'X') { 
                draw_sprite(buffer, roca, col * 30, row * 30);
            }
        } else if(mapa[row][col]=='o'){
		    draw_sprite(buffer,comida,col*30,row*30);
	        if(py/30==row && px/30==col){
	    	    mapa[row][col]=' ';
		}
	}// <- Aquí cierra el for de las columnas (col)
    } // <- Aquí cierra el for de las filas (row)
} // <- Aquí cierra la función dibujar_mapa

void pantalla(){
	blit(buffer, screen, 0,0,0,0,880,600);
	
}
void bibujar_personaje() {
    blit(pacbmp,pacman,dir*33,0,0,0,33,33);
    draw_sprite(buffer,pacman,px,py);
}
//funcion para que cuando se coma todas las bolitas sea game over
bool game_over(){
	int row,col;
	
	for(row=0;row<MAXFILAS;row++){
		for(col=0;col<MALXCOL;col++){
			if(mapa[row][col]=='o'){
				return true;
			}
			
		}
	}
	return false;
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
	
	
	while(!key[KEY_ESCAPE]&&game_over()){
		if(key[KEY_RIGHT]) dir = 1;  
		else if(key[KEY_LEFT]) dir = 0;
		else if(key[KEY_UP]) dir = 2;
		else if(key[KEY_DOWN]) dir = 3;

    if(dir==0){
		if(mapa[py/30][(px-30)/30]!='X')
		px-=30;
		else dir=4;
	}
	if(dir==1){
		if(mapa[py/30][(px+30)/30]!='X')
		px+=30;
		else dir=4;
	}
	if(dir==2){
		if(mapa[(py-30)/30][(px/30]!='X')
		py-=30;
		else dir=4;
	}
	if(dir==3){
		if(mapa[(py+30)/30][(px/30]!='X')
		py+=30;
		else dir=4;
	} 
    //conectamos rutina para que salga por el otro lado del atajo
	if(px<=-30){
		px=870;
	}else if(px>=870){
		px=-30;
	}
	
        clear(buffer);
        dibujar_mapa();
        dibujar_personaje();
		pantalla();
        rest(70);
        clear(pacman);
        blit(pacbmp,pacman,4*33,0,0,0,33,33);
        draw_sprite(buffer,pacman,px,py);
        pantalla();
        rest(90);
	}
	
	
	
}
END OF MAIN();